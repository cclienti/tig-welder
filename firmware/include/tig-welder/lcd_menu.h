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


#include <memory>
#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>


class LCDDisplay;
class RotaryEncoder;
class Switch;
class Buzzer;
class MenuEntryBase;


class LCDMenu final
{
public:
	// enum class CbParam {Inc, Dec, Refresh};
	// using Callback = std::function<std::string(CbParam)>;

	using LCDDisplayUPtr = std::unique_ptr<LCDDisplay>;
	using RotaryEncoderUPtr = std::unique_ptr<RotaryEncoder>;
	using SwitchUPtr = std::unique_ptr<Switch>;
	using BuzzerSPtr = std::shared_ptr<Buzzer>;

	LCDMenu(LCDDisplayUPtr lcd_display, RotaryEncoderUPtr rotary_encoder,
	        SwitchUPtr button, BuzzerSPtr buzzer);

	void register_entry(const std::string &title, bool &variable);
	void register_entry(const std::string &title, int &variable,
	                    int min, int max, const std::string &unit);
	void register_entry(const std::string &title, float &variable,
	                    float min, float max, float precision,
	                    const std::string &unit);

	void refresh(bool force=false);

private:
	std::string format_title(std::string title);
	std::string format_value(std::string value);

private:
	LCDDisplayUPtr m_lcd_display;
	RotaryEncoderUPtr m_rotary_encoder;
	SwitchUPtr m_button;
	BuzzerSPtr m_buzzer;

	std::vector<std::shared_ptr<MenuEntryBase>> m_menu_entries;
	std::size_t m_menu_entry_id;
	bool m_change_value;
	bool m_sound_enable;
};


#endif
