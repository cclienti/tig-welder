#include "tig-welder/lcd_display.h"
#include "tig-welder/relay.h"
#include "tig-welder/switch.h"
#include "tig-welder/rotary_encoder.h"
#include "tig-welder/spi_adc.h"

#include <cstdio>
#include <cstring>



int main(void)
{
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

	while(1)
	{
		static int redcnt{0};
		static int blackcnt{0};
		static int codercnt{0};
		blackcnt += black_switch.is_released();
		redcnt += red_switch.is_released();
		codercnt += coder_switch.is_released();
		lcd.set_pos(0, 0);
		lcd.printf("Black switch = %05d", blackcnt);
		lcd.set_pos(1, 0);
		lcd.printf("Red switch   = %05d", redcnt);
		lcd.set_pos(2, 0);
		//lcd.printf("Coder switch = %05d", codercnt);
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
