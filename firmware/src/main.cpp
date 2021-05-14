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


#include <cstdio>
#include <cstring>
#include <memory>

struct WeldingParams
{
	float pre_flow{0.0};
	float post_flow{5.0};
	float start_ramp{0.0};
	float end_ramp{0.0};
	int current{40};
};


int main(void)
{
	stdio_init_all();

	Relay solenoid(9, true);
	Relay hf_spark(8, true);
	Switch red_switch(10, true);
	Switch black_switch(11, true);
	SPIADC adc;

	auto lcd_display = std::make_unique<LCDDisplay>();
	auto lcd_encoder = std::make_unique<RotaryEncoder>(12, 13, 0);
	auto lcd_button = std::make_unique<Switch>(14, true);
	auto buzzer = std::make_shared<Buzzer>();

	LCDMenu lcd_menu(std::move(lcd_display), std::move(lcd_encoder),
	                 std::move(lcd_button), buzzer);
	WeldingParams welding_params;
	bool mute = false;
	lcd_menu.register_entry("Mute", mute);
	lcd_menu.register_entry("Post Flow", welding_params.post_flow, 1, 10.0, 0.1, "s");
	lcd_menu.register_entry("End Ramp", welding_params.end_ramp, 0, 10.0, 0.1, "s");
	lcd_menu.register_entry("Current", welding_params.current, 5, 200, "A");
	lcd_menu.register_entry("Start Ramp", welding_params.start_ramp, 0, 10.0, 0.1, "s");
	lcd_menu.register_entry("Pre Flow", welding_params.pre_flow, 1, 10.0, 0.1, "s");

	// buzzer.melody(
	// 	 {
	// 		 {Buzzer::Note::Sol, 500},  {Buzzer::Note::Silence, 100},
	// 		 {Buzzer::Note::Sol, 500},  {Buzzer::Note::Silence, 100},
	// 		 {Buzzer::Note::Sol, 500},  {Buzzer::Note::Silence, 100},
	// 		 {Buzzer::Note::La,  500},  {Buzzer::Note::Silence, 100},
	// 		 {Buzzer::Note::Si,  500},  {Buzzer::Note::Silence, 100},
	// 		 {Buzzer::Note::La,  500},  {Buzzer::Note::Silence, 100},
	// 		 {Buzzer::Note::Sol, 500},  {Buzzer::Note::Silence, 100},
	// 		 {Buzzer::Note::Si,  500},  {Buzzer::Note::Silence, 100},
	// 		 {Buzzer::Note::La,  500},  {Buzzer::Note::Silence, 100},
	// 		 {Buzzer::Note::La,  500},  {Buzzer::Note::Silence, 100},
	// 		 {Buzzer::Note::Sol, 500},  {Buzzer::Note::Silence, 100}
	// 	 }
	// );

	while(1)
	{
		static int redcnt{0};
		static int blackcnt{0};

		lcd_menu.refresh();
		if (mute) {
			buzzer->mute();
		} else if (buzzer->is_muted()) {
			buzzer->unmute();
		}

		if (black_switch.is_released()) {
			buzzer->error();
			blackcnt +=1;
		}

		if (red_switch.is_released()) {
			buzzer->valid();
			redcnt += 1;
		}

		if (blackcnt % 2 == 1) solenoid.enable();
		else solenoid.disable();

		if (redcnt % 2 == 1) hf_spark.enable();
		else hf_spark.disable();
	}
	return 0;
}
