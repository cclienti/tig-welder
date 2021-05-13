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

#include "tig-welder/lcd_display.h"
#include "tig-welder/relay.h"
#include "tig-welder/switch.h"
#include "tig-welder/rotary_encoder.h"
#include "tig-welder/spi_adc.h"
#include "tig-welder/buzzer.h"

#include <cstdio>
#include <cstring>


int main(void)
{
	stdio_init_all();

	Relay solenoid(9, true);
	Relay hf_spark(8, true);
	Switch red_switch(10, true);
	Switch black_switch(11, true);
	Switch coder_switch(14, true);

	LCDDisplay lcd;
	lcd.clear();
	lcd.home();

	RotaryEncoder encoder(12, 13, 0);
	encoder.set_rotation(0);

	SPIADC adc;
	Buzzer buzzer;

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

	buzzer.error();

	while(1)
	{
		static int redcnt{0};
		static int blackcnt{0};

		if (black_switch.is_released()) {
			buzzer.error();
			blackcnt +=1;
		}

		if (red_switch.is_released()) {
			buzzer.valid();
			redcnt += 1;
		}

		if (coder_switch.is_released()) {
			buzzer.warning();
		}

		lcd.set_pos(0, 0);
		lcd.printf("Black switch = %05d", blackcnt);
		lcd.set_pos(1, 0);
		lcd.printf("Red switch   = %05d", redcnt);
		lcd.set_pos(2, 0);
		std::uint16_t adc_value = adc.read_single(0);
		lcd.printf("ADC chan0    = %05d", adc_value);
		lcd.set_pos(3, 0);
		lcd.printf("Encoder      = %05d", encoder.get_rotation());

		if (blackcnt % 2 == 1) solenoid.enable();
		else solenoid.disable();

		if (redcnt % 2 == 1) hf_spark.enable();
		else hf_spark.disable();
	}
	return 0;
}
