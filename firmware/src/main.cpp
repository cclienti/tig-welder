#include "tig-welder/lcd_display.h"

#include <cstdio>
#include <cstring>


int main(void)
{
	LCDDisplay lcd;
	lcd.set_pos(2, 3);
	lcd.home();
	lcd.printf("Value = %08.3f", 3.141592);
	while(1);
}
