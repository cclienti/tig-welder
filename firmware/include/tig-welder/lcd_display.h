#ifndef TIG_WELDER_LCD_DISPLAY_H
#define TIG_WELDER_LCD_DISPLAY_H

#include "hardware/i2c.h"
#include <iostream>
#include <string>
#include <cstdint>


class LCDDisplay final
{
public:
	/**
	 * LCDDisplay constructor.
	 *
	 * @param i2c_inst_num, RPI Pico i2c instance
	 * @param i2c_speed, i2c speed in bit/s
	 * @param i2c_addr, i2c address of the screen io expander
	 * @param sda_pin, RPI Pico SDA pin number
	 * @param scl_pin, RPI Pico SCL pin number
	 * @param pullup, enable internal i2c pullup resistors
	 * @param num_cols, number of lines in the screen
	 * @param num_lines, number of columns in the screen
	 * @param backlight, enable the backlight
	 */
	LCDDisplay(std::uint8_t i2c_inst_num = 0u, std::uint32_t i2c_speed = 100 * 1000u,
	           std::uint8_t i2c_addr = 0x27, std::uint8_t sda_pin = 0u,
	           std::uint8_t scl_pin = 1u, bool pullup = false,
	           std::uint8_t num_lines = 4, std::uint8_t num_cols = 20,
	           bool backlight = true);

	/**
	 * Enable or disable the backlight
	 */
	void backlight(bool enable=true);

	/**
	 * Clear the screen
	 */
	void clear(void);

	/**
	 * Move cursor to home
	 */
	void home(void);

	/**
	 * Set the position to given row and col.
	 *
	 * The row argument will be clipped to [0, m_num_lines-1] and col
	* to [0, num_cols-1].
	*/
  void set_pos(std::uint8_t row, std::uint8_t col);

  /**
	* Write a single char to the screen at the current position, the
	* position is incremented to the next column.
	*/
  int putchar(std::uint8_t value);

  /**
	* Write the given string to the screen at the current position.
	*/
  void write(const char *str);

  /**
	* Implementation of a printf method to write string format to the
	* screen at the current position.
	*/
	void printf(const char *format, ...);

private:
	/**
	 * Return the backlight mask for the screen controller depending on
	 * its state (enable or disabled).
	 */
	std::uint8_t get_backlight_state(void);

	/**
	 * Write a byte to the screen through i2c connection.
	 */
	void i2c_write(std::uint8_t value);

	/**
	 * Write a nibble (4 bits) to the screen.
	 *
	 * The screen is managed by a 8-bit i2c io expander (PCF8574). The
	 * screen is in 4-bit data mode in order to keep 4 bits the screen
	 * controls (enable, backlight, RS, R/W).
	 */
	void send_nibble(std::uint8_t nibble);

	/**
	 * Write a byte to the screen.
	 *
	 * The function calls send_nibble two times.
	 *
	 * The mode is used to send the byte as a command or as a
	  * character.
	  */
	 void send_byte(std::uint8_t value, std::uint8_t mode);

	/**
	 * Write a byte command to the screen.
	 *
	 * This is a simple wrapper for send_byte in command mode.
	 */
	void send_command(std::uint8_t value);

private:
	i2c_inst_t &m_i2c_inst;
	const std::uint8_t m_i2c_addr;
	const std::uint8_t m_num_lines;
	const std::uint8_t m_num_cols;
	bool m_backlight;
};

#endif
