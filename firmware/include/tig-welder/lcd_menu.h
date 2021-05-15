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

	LCDMenu(LCDDisplayUPtr lcd_display, RotaryEncoderUPtr rotary_encoder,
	        SwitchUPtr button, BuzzerSPtr buzzer);

	void splash(std::string text);

	void register_menu(const std::string &title, bool &variable);
	void register_menu(const std::string &title, int &variable,
	                   int min, int max, const std::string &unit);
	void register_menu(const std::string &title, float &variable,
	                   float min, float max, float precision,
	                   const std::string &unit);

	void register_footer(FooterPosition position,
	                     const std::string &text, const bool &variable);
	void register_footer(FooterPosition position,
	                     const std::string &text, const int &variable,
	                     const std::string &unit);
	void register_footer(FooterPosition position,
	                     const std::string &text, const float &variable,
	                     float precision, const std::string &unit);

	void refresh();

private:
	void refresh_menu();
	void refresh_footer();

	std::string format_splash(std::string value);

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
};


#endif
