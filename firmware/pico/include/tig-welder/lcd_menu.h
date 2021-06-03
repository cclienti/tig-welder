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

#ifndef TIG_WELDER_LCD_MENU_H
#define TIG_WELDER_LCD_MENU_H


#include "lcd_display.h"
#include "rotary_encoder.h"
#include "switch.h"
#include "buzzer.h"

#include <memory>
#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>


// Forward declaration of private classes
class MenuEntryBase;
class FooterNoteBase;


class LCDMenu final
{
public:
	enum class FooterPosition {Left, Right};

	using LCDDisplayUPtr = std::unique_ptr<LCDDisplay>;
	using RotaryEncoderUPtr = std::unique_ptr<RotaryEncoder>;
	using SwitchUPtr = std::unique_ptr<Switch>;
	using BuzzerSPtr = std::shared_ptr<Buzzer>;

	/**
	 * LCDMenu constructor.
	 *
	 * The lcd_display shows the menu and the footer information. The
	 * rotary_encoder is used to navigate into the menu and button
	 * validates menu entry modification.
	 *
	 * @param lcd_display, Unique pointer to LCDDisplay instance
	 * @param rotary_encoder, Unique pointer to RotaryEncoder instance
	 * @param button, Unique pointer to Switch instance
	 * @param buzzer, Shared pointer to Buzzer instance
	 */

	LCDMenu(LCDDisplayUPtr lcd_display, RotaryEncoderUPtr rotary_encoder,
	        SwitchUPtr button, BuzzerSPtr buzzer);

	/**
	 * Add an entry in the menu to display/update a boolean variable.
	 *
	 * The entry is inserted at the beginning of the menu list.
	 *
	 * @param title, menu title
	 * @param variable, variable reference to display/update
	 */
	void register_menu(const std::string &title, bool &variable);

	/**
	 * Add an entry in the menu to display/update an int variable.
	 *
	 * The entry is inserted at the beginning of the menu list.
	 *
	 * @param title, menu title
	 * @param variable, variable reference to display/update
	 * @param min, minimum authorized value to update the variable.
	 * @param max, maximum authorized value to update the variable.
	 * @param unit, physical unit string to display after the value.
	 */
	void register_menu(const std::string &title, int &variable,
	                   int min, int max, const std::string &unit);

	/**
	 * Add an entry in the menu to display/update a float variable.
	 *
	 * The entry is inserted at the beginning of the menu list.
	 *
	 * @param title, menu title
	 * @param variable, variable reference to display/update
	 * @param min, minimum authorized value to update the variable.
	 * @param max, maximum authorized value to update the variable.
	 * @param precision, minimal floating point increment to consider (ex: 0.1).
	 * @param unit, physical unit string to display after the value.
	 */
	void register_menu(const std::string &title, float &variable,
	                   float min, float max, float precision,
	                   const std::string &unit);

	/**
	 * Add a footer note to display only a boolean variable.
	 *
	 * @param position, left or right
	 * @param text, footer note text info
	 * @param variable, variable reference to display/update
	 */
	void register_footer(FooterPosition position,
	                     const std::string &text, const bool &variable);

	/**
	 * Add a footer note to display only an int variable.
	 *
	 * @param position, left or right
	 * @param text, footer note text info
	 * @param variable, variable reference to display/update
	 * @param unit, physical unit string to display after the value.
	 */
	void register_footer(FooterPosition position,
	                     const std::string &text, const int &variable,
	                     const std::string &unit);

	/**
	 * Add a footer note to display only a float variable.
	 *
	 * @param position, left or right
	 * @param text, footer note text info
	 * @param variable, variable reference to display/update
	 * @param unit, physical unit string to display after the value.
	 */
	void register_footer(FooterPosition position,
	                     const std::string &text, const float &variable,
	                     float precision, const std::string &unit);

	/**
	 * Refresh the menu and the footer notes.
	 */
	void refresh();

	/**
	 * Clear the screen and display a text in the middle of the screen.
	 *
	 * @param text, splash screen text.
	 */
	void splash(const std::string &text);

private:
	/**
	 * Refresh the menu
	 */
	void refresh_menu();

	/**
	 * Refresh the footer notes
	 */
	void refresh_footer();

private:
	LCDDisplayUPtr m_lcd_display;
	RotaryEncoderUPtr m_rotary_encoder;
	SwitchUPtr m_button;
	BuzzerSPtr m_buzzer;

	std::vector<std::shared_ptr<MenuEntryBase>> m_menu_entries;
	std::shared_ptr<FooterNoteBase> m_footer_left;
	std::shared_ptr<FooterNoteBase> m_footer_right;

	std::size_t m_menu_entry_id;
	bool m_change_value;

	const std::string m_footer_separator;

	static constexpr std::uint8_t m_title_line{0};
	static constexpr std::uint8_t m_value_line{1};
	static constexpr std::uint8_t m_separator_line{2};
	static constexpr std::uint8_t m_footer_line{3};

	bool is_refreshed{false};
	bool is_splashed{false};
};


#endif
