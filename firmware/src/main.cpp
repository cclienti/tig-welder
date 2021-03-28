/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "tig-welder/lcd_display.h"

#include <cstdio>
#include <cstring>


int main(void)
{
	LCDDisplay lcd;
	//lcd.set_pos(0, 0);
	lcd << "Hello" << " " << "World! "
	    << LCDDisplay::FormatFill('*')
	    << LCDDisplay::FormatWidth(4) << 100;
	while(1);
}
