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
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "pico/time.h"


#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cstdarg>


namespace {
enum LCDConstants : std::uint8_t {
	LCDControlCommandMode = 0x00,
	LCDControlCharacterMode = 0x01,
	LCDControlReadMode = 0x02,
	LCDControlEnable = 0x04,
	LCDControlBacklightOn = 0x08,
	LCDControlBacklightOff = 0x00,

	LCDCommandClearDisplay = 0x01,

	LCDCommandReturnHome = 0x02,

	LCDCommandEntryMode = 0x04,
	LCDEntryModeDisplayShift = 0x01,
	LCDEntryModeIncrement = 0x02,
	LCDEntryModeDecrement = 0x00,

	LCDCommandDisplayControl = 0x08,
	LCDDisplayControlBlinkingOff = 0x00,
	LCDDisplayControlBlinkingOn = 0x01,
	LCDDisplayControlCursorOff = 0x00,
	LCDDisplayControlCursorOn = 0x02,
	LCDDisplayControlEntireDisplay = 0x04,

	LCDCommandCursorShift = 0x10,
	LCDCursorShiftLeft = 0x00,
	LCDCursorShiftright = 0x04,
	LCDCursorShiftCursorMove = 0x00,
	LCDCursorShiftDisplayShift = 0x08,

	LCDCommandFunctionSet = 0x20,
	LCDFunctionSet5x10Dots = 0x04,
	LCDFunctionSet5x8Dots = 0x00,
	LCDFunctionSet2Lines = 0x08,
	LCDFunctionSet1Line = 0x00,

	LCDCommandSetCGRAM = 0x40,

	LCDCommandSetDDRAM = 0x80,
};
}


LCDDisplay::LCDDisplay(std::uint8_t i2c_inst_num, std::uint32_t i2c_speed,
                       std::uint8_t i2c_addr, std::uint8_t sda_pin,
                       std::uint8_t scl_pin, bool pullup,
                       std::uint8_t num_lines, std::uint8_t num_cols,
                       bool backlight):
	m_i2c_inst (i2c_inst_num == 0 ? *i2c0 : *i2c1),
	m_i2c_addr (i2c_addr),
	m_num_lines (num_lines),
	m_num_cols (num_cols),
	m_backlight (backlight)
{
	// Init the i2c interface
	i2c_init(&m_i2c_inst, i2c_speed);

	gpio_set_function(sda_pin, GPIO_FUNC_I2C);
	gpio_set_function(scl_pin, GPIO_FUNC_I2C);

	if (pullup) {
		gpio_pull_up(sda_pin);
		gpio_pull_up(scl_pin);
	}

	// We use the LCD in 4-bit mode in order to keep 4 bits for the LCD
	// control bits (the i2c expander PCF8574 provides only 8-bit).

	// Specific init sequence for the lcd to put it in 4 bits mode.
	send_nibble(0x30);
	sleep_ms(5);
	send_nibble(0x30);
	sleep_ms(5);
	send_nibble(0x30);
	sleep_us(120);
	send_nibble(0x20);

	if (num_lines > 1) {
		send_command(LCDCommandFunctionSet | LCDFunctionSet5x8Dots | LCDFunctionSet2Lines);
	}
	else {
		send_command(LCDCommandFunctionSet | LCDFunctionSet5x8Dots | LCDFunctionSet1Line);
	}
	send_command(LCDCommandEntryMode | LCDEntryModeIncrement);
	send_command(LCDCommandDisplayControl | LCDDisplayControlBlinkingOff |
	             LCDDisplayControlCursorOff | LCDDisplayControlEntireDisplay);

	clear();
	home();
}

void LCDDisplay::backlight(bool enable)
{
	m_backlight = enable;
	i2c_write(get_backlight_state());
}

void LCDDisplay::clear(void)
{
	send_command(LCDCommandClearDisplay);
	sleep_ms(2);
}

void LCDDisplay::home(void)
{
	send_command(LCDCommandReturnHome);
	// Execution time of "Return home" command is 1.52 ms
	sleep_ms(2);
}

void LCDDisplay::set_pos(std::uint8_t row, std::uint8_t col)
{
	// For four lines LCD, There is only two lines in the controller
	// brocken into four physical lines.
	//
	//                  Position   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
	// Line 0 DDRAM Address(hex)  00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 10 11 12 13
	// Line 1 DDRAM Address(hex)  40 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f 50 51 52 53
	// Line 2 DDRAM Address(hex)  14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 20 21 22 23 24 25 26 27
	// Line 3 DDRAM Address(hex)  54 55 56 57 58 59 5a 5b 5c 5d 5e 5f 60 61 62 63 64 65 66 67
	std::uint8_t const row_offsets[] = {0x00, 0x40, 0x14, 0x54};
	row = std::min<std::uint8_t>(row, m_num_lines - 1);
	col = std::min<std::uint8_t>(col, m_num_cols - 1);
	std::uint8_t ddram = row_offsets[row] + col;
	send_command(LCDCommandSetDDRAM | ddram);
}

void LCDDisplay::set_char(std::uint8_t address, std::uint8_t char_map[8])
{
	address &= 0x07;
	send_command(LCDCommandSetCGRAM | address << 3);
	for (int i=0; i<8; i++) {
		send_byte(char_map[i], LCDControlCharacterMode);
	}
}

int LCDDisplay::putchar(std::uint8_t value)
{
	send_byte(value, LCDControlCharacterMode);
	return value;
}

void LCDDisplay::write(const char *str)
{
	while(*str) {
		putchar(*str++);
	}
}

void LCDDisplay::printf(const char *format, ...)
{
	char buffer[32];
	va_list ap;
	va_start(ap, format);
	vsnprintf(buffer, sizeof(buffer), format, ap);
	write(buffer);
}

void LCDDisplay::print(const std::string str)
{
	write(str.c_str());
}

std::uint8_t LCDDisplay::get_backlight_state(void)
{
	return m_backlight ? LCDControlBacklightOn : LCDControlBacklightOff;
}

void LCDDisplay::i2c_write(std::uint8_t value)
{
	i2c_write_blocking(&m_i2c_inst, m_i2c_addr, &value, 1, false);
}

void LCDDisplay::send_nibble(std::uint8_t nibble)
{
	i2c_write(nibble);
	sleep_us(1);
	i2c_write(nibble | LCDControlEnable);
	sleep_us(1);
	i2c_write(nibble & ~LCDControlEnable);
	sleep_us(50);
}

void LCDDisplay::send_byte(std::uint8_t value, std::uint8_t mode)
{
	std::uint8_t backlight = get_backlight_state();
	std::uint8_t high = (value & 0xF0) | mode | backlight;
	std::uint8_t low = ((value << 4) & 0xF0) | mode | backlight;

	send_nibble(high);
	send_nibble(low);
}

void LCDDisplay::send_command(std::uint8_t value)
{
	send_byte(value, LCDControlCommandMode);
}
