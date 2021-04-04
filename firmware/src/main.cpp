#include "tig-welder/lcd_display.h"
#include "tig-welder/relay.h"
#include "tig-welder/switch.h"

#include <cstdio>
#include <cstring>



int main(void)
{
	Relay solenoid(9, true);
	Relay hf_spark(8, true);
	Switch red_switch(10, true);
	Switch black_switch(11, true);

	LCDDisplay lcd;
	lcd.clear();
	lcd.home();

	while(1)
	{
		static int redcnt{0};
		static int blackcnt{0};
		blackcnt += black_switch.is_released();
		redcnt += red_switch.is_released();
		lcd.set_pos(0, 0);
		lcd.printf("Black switch = %01d", blackcnt);
		lcd.set_pos(1, 0);
		lcd.printf("Red switch   = %01d", redcnt);
	}
	return 0;
}
