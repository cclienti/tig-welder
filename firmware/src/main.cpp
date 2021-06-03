// This file is part of the tig-welder project
// (https://github.com/cclienti/tig-welder)
// Copyright (c) 2021 Christophe Clienti
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.


#include "tig-welder/lcd_menu.h"
#include "tig-welder/relay.h"
#include "tig-welder/switch.h"
#include "tig-welder/rotary_encoder.h"
#include "tig-welder/spi_adc.h"
#include "tig-welder/buzzer.h"
#include "tig-welder/ctn.h"
#include "tig-welder/hbridge.h"

#include "hardware/gpio.h"
#include "pico/time.h"

#include <cstdio>
#include <cstring>
#include <memory>

struct WeldingParams
{
	float pre_flow{0.5};
	float post_flow{8.0};
	float start_ramp{0.0};
	float end_ramp{0.0};
	int current{40};
};


enum class WeldingStates
{
	Idle,
	PreFlow,
	Welding,
	PostFlow,
	Protection
};


enum TempInfo
{
	Warning1      = 105,
	Warning2      = 115,
	Protection    = 125,
	EndProtection = 70
};


int main(void)
{
	stdio_init_all();
	printf("Hello World!");

	Relay solenoid(9, true);
	Relay hf_spark(8, true);
	Switch red_switch(10, true);
	Switch black_switch(11, true);
	SPIADC adc;
	HBridge hbridge(10e-9, 22, 21, 20, 19, 18);
	hbridge.set_wrap(20000); //10ns Counter, wrap at 20000 => 5000hz period
	std::uint16_t hb_duty = 10000;

	auto lcd_display = std::make_unique<LCDDisplay>();
	auto lcd_encoder = std::make_unique<RotaryEncoder>(12, 13, 0);
	auto lcd_button = std::make_unique<Switch>(14, true);
	auto buzzer = std::make_shared<Buzzer>();

	LCDMenu lcd_menu(std::move(lcd_display), std::move(lcd_encoder),
	                 std::move(lcd_button), buzzer);

	bool start = false;
	bool warn1 = false;
	bool warn2 = false;
	bool protection = true;
	int temp = 0;
	int pedal = 0;
	bool mute = true;
	WeldingStates welding_state {WeldingStates::Idle};
	WeldingParams welding_params;

	lcd_menu.register_menu("Mute", mute);
	lcd_menu.register_menu("Post Flow", welding_params.post_flow, 1, 10.0, 0.1, "s");
	lcd_menu.register_menu("End Ramp", welding_params.end_ramp, 0, 10.0, 0.1, "s");
	lcd_menu.register_menu("Current", welding_params.current, 5, 200, "A");
	lcd_menu.register_menu("Start Ramp", welding_params.start_ramp, 0, 10.0, 0.1, "s");
	lcd_menu.register_menu("Pre Flow", welding_params.pre_flow, 1, 10.0, 0.1, "s");
	lcd_menu.register_footer(LCDMenu::FooterPosition::Left,
	                         "Temp", temp, "C");
	lcd_menu.register_footer(LCDMenu::FooterPosition::Right,
	                         "P", pedal, "V");


	while(1)
	{
		temp = get_temp_int(adc.read8_single(1));
		pedal = adc.read8_single(0);

		switch(welding_state) {
		case WeldingStates::Idle:
			{
				warn1 = false;
				warn2 = false;
				hbridge.freewheel();

				lcd_menu.refresh();
				if (mute && !buzzer->is_muted()) {
					buzzer->mute();
				}else if (!mute && buzzer->is_muted()) {
					buzzer->unmute();
				}

				if (pedal >= 2048) {
					welding_state = WeldingStates::PreFlow;
					buzzer->valid();
				}
			}
			break;

		case WeldingStates::PreFlow:
			{
				hbridge.freewheel();
				lcd_menu.splash("Pre-flow");
				solenoid.enable();
				sleep_ms(welding_params.pre_flow * 1000);
				welding_state = WeldingStates::Welding;
			}
			break;

		case WeldingStates::Welding:
			{
				lcd_menu.splash("Welding");
				hbridge.forward(hb_duty);

				if (!warn1 && temp >= TempInfo::Warning1) {
					warn1 = true;
					buzzer->warning();
				}
				else if (!warn2 && temp >= TempInfo::Warning2) {
					warn2 = true;
					buzzer->warning();
				}
				else if (temp >= TempInfo::Protection) {
					welding_state = WeldingStates::PostFlow;
					buzzer->error();
				}
				else if (pedal < 2048) {
					welding_state = WeldingStates::PostFlow;
				}
			}
			break;

		case WeldingStates::PostFlow:
			{
				hbridge.freewheel();
				lcd_menu.splash("Post-flow");

				if (temp >= TempInfo::Protection) {
					welding_state = WeldingStates::Protection;
				}
				else {
					welding_state = WeldingStates::Idle;
				}

				sleep_ms(welding_params.post_flow * 1000);
				solenoid.disable();
			}
			break;

		case WeldingStates::Protection:
			{
				hbridge.freewheel();
				solenoid.disable();
				lcd_menu.splash("Protection");
				if (temp <= TempInfo::EndProtection) {
					welding_state = WeldingStates::Idle;
				}
			}
			break;
		}
	}

	return 0;
}
