#ifndef TIG_WELDER_LCD_DISPLAY_H
#define TIG_WELDER_LCD_DISPLAY_H

#include "hardware/i2c.h"
#include <iostream>
#include <string>
#include <cstdint>


class LCDDisplay
{
public:
	struct FormatFill
	{
		FormatFill(char c) : m_c(c) {}
		char m_c;
	};

	struct FormatWidth
	{
		FormatWidth(int w) : m_w(w) {}
		int m_w;
	};

public:
	LCDDisplay(std::uint8_t i2c_inst_num = 0u, std::uint32_t i2c_speed = 100 * 1000u,
	           std::uint8_t i2c_addr = 0x27, std::uint8_t sda_pin = 0u,
	           std::uint8_t scl_pin = 1u, bool pullup = false,
	           std::uint8_t num_cols = 20, std::uint8_t num_lines = 4,
	           bool backlight = true);


	void backlight(bool enable=true);
	void clear(void);
	void home(void);
	void set_pos(std::uint8_t row, std::uint8_t col);
	void write(const char *str);
	void reset_format();

	static FormatFill setfill(char value) {return FormatFill(value);}
	static FormatWidth setw(int value) {return FormatWidth(value);}

	LCDDisplay &operator<<(const char *str);
	LCDDisplay &operator<<(const std::string &str);
	LCDDisplay &operator<<(const int &num);
	LCDDisplay &operator<<(const FormatFill &f);
	LCDDisplay &operator<<(const FormatWidth &w);


private:
	std::uint8_t get_backlight_state(void);
	void i2c_write(std::uint8_t value);
	void send_nibble(std::uint8_t nibble);
	void send_byte(std::uint8_t value, std::uint8_t mode);
	void send_command(std::uint8_t value);
	void send_char(std::uint8_t value);

private:
	i2c_inst_t &m_i2c_inst;
	const std::uint8_t m_i2c_addr;
	const std::uint8_t m_num_cols;
	const std::uint8_t m_num_lines;
	bool m_backlight;
	char m_format_fill{'\0'};
	std::uint8_t m_format_width{0};
};

#endif
