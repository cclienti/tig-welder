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

#include "tig-welder/lcd_menu.h"
#include "tig-welder/lcd_display.h"
#include "tig-welder/rotary_encoder.h"
#include "tig-welder/switch.h"
#include "tig-welder/buzzer.h"

#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>


class MenuEntryBase
{
public:
	enum class Type {Void, Bool, Int, Float};

	const std::string &get_title(void) const {return m_title;}
	Type get_type(void) const {return m_type;}

	virtual int get_encoder() const = 0;

protected:
	MenuEntryBase(const std::string &title, Type type):
		m_title(title),
		m_type(type)
	{
	}

private:
	std::string m_title;
	Type m_type;
};


class MenuEntryBool: public MenuEntryBase
{
public:
	MenuEntryBool(const std::string title, bool &variable):
		MenuEntryBase(title, Type::Bool),
		m_variable(variable)
	{
	}

	int get_encoder(void) const override {return get_value();}

	void set_value(bool value) {m_variable = value;}
	bool get_value(void) const {return m_variable;}

private:
	bool &m_variable;
};


class MenuEntryInt: public MenuEntryBase
{
public:
	MenuEntryInt(const std::string title, int &variable, int min, int max,
	             const std::string &unit):
		MenuEntryBase (title, Type::Int),
		m_variable    (variable),
		m_min         (min),
		m_max         (max)
	{
	}

	int get_encoder(void) const override {return get_value();}

	int get_min(void) const {return m_min;}
	int get_max(void) const {return m_max;}
	const std::string &get_unit(void) const {return m_unit;}

	void set_value(int value) {m_variable = std::min(std::max(value, m_min), m_max);}
	int get_value(void) const {return m_variable;}

private:
	int &m_variable;
	int m_min;
	int m_max;
	const std::string m_unit;
};


class MenuEntryFloat: public MenuEntryBase
{
public:
	MenuEntryFloat(const std::string title, float &variable,
	               float min, float max, float precision,
	               const std::string &unit):
		MenuEntryBase (title, Type::Float),
		m_variable    (variable),
		m_min         (min),
		m_max         (max),
		m_precision   (precision),
		m_inv_prec    (1/precision),
		m_num_decimal (static_cast<int>(std::ceil(std::log10(m_inv_prec)))),
		m_unit        (unit)
	{
	}

	int get_encoder(void) const override {return int(get_value() * m_inv_prec);}

	float get_min(void) const {return m_min;}
	float get_max(void) const {return m_max;}
	float get_precision(void) const {return m_precision;}
	float get_num_decimal(void) const {return m_num_decimal;}
	const std::string &get_unit(void) const {return m_unit;}

	void set_value(float value) {m_variable = std::min(std::max(value, m_min), m_max);}
	float get_value(void) const {return m_variable;}

private:
	float &m_variable;
	const float m_min;
	const float m_max;
	const float m_precision;
	const float m_inv_prec;
	const int m_num_decimal;
	const std::string m_unit;
};


LCDMenu::LCDMenu(LCDDisplayUPtr lcd_display, RotaryEncoderUPtr rotary_encoder,
                 SwitchUPtr button, BuzzerSPtr buzzer, std::uint8_t title_line,
	        std::uint8_t value_line):
	m_lcd_display    (std::move(lcd_display)),
	m_rotary_encoder (std::move(rotary_encoder)),
	m_button         (std::move(button)),
	m_buzzer         (buzzer),
	m_menu_entry_id  (0),
	m_change_value   (false),
	m_title_line     (title_line),
	m_value_line     (value_line)
{
	m_rotary_encoder->set_rotation(0);
	m_lcd_display->clear();
	m_lcd_display->home();

	refresh(true);
}


void LCDMenu::register_entry(const std::string &title, bool &variable)
{
	auto menu_title = format_title(title);
	m_menu_entries.insert(m_menu_entries.begin(),
	                      std::make_shared<MenuEntryBool>(menu_title, variable));
}


void LCDMenu::register_entry(const std::string &title, int &variable, int min, int max,
                             const std::string &unit)
{
	auto menu_title = format_title(title);
	auto menu_entry = std::make_shared<MenuEntryInt>(menu_title, variable,
	                                                 min, max, unit);
	menu_entry->set_value(menu_entry->get_value());
	m_menu_entries.insert(m_menu_entries.begin(), std::move(menu_entry));
}


void LCDMenu::register_entry(const std::string &title, float &variable,
                             float min, float max, float precision,
                             const std::string &unit)
{
	auto menu_title = format_title(title);
	auto menu_entry = std::make_shared<MenuEntryFloat>(menu_title, variable,
	                                                   min, max, precision, unit);
	menu_entry->set_value(menu_entry->get_value());
	m_menu_entries.insert(m_menu_entries.begin(), menu_entry);
}


void LCDMenu::refresh(bool force)
{
	const auto &entry = m_menu_entries[m_menu_entry_id];

	bool button_released = m_button->is_released();
	m_change_value = m_change_value ^ button_released;

	if (m_change_value) {
		if (button_released) {
			m_rotary_encoder->set_rotation(entry->get_encoder());
		}
	}
	else {
		if (button_released) {
			m_rotary_encoder->set_rotation(m_menu_entry_id);
		}
		m_menu_entry_id = m_rotary_encoder->get_rotation() % m_menu_entries.size();
	}

	m_lcd_display->set_pos(m_title_line, 0);
	m_lcd_display->print(entry->get_title());

	switch (entry->get_type()) {
	case MenuEntryBool::Type::Bool:
		{
			const auto &bool_entry = std::static_pointer_cast<MenuEntryBool>(entry);
			bool value;

			if (m_change_value) {
				value = m_rotary_encoder->get_rotation() % 2;
				bool_entry->set_value(value);
			}

			value = bool_entry->get_value();
			m_lcd_display->set_pos(m_value_line, 0);

			if (value) {
				m_lcd_display->print(format_value("yes"));
			}
			else {
				m_lcd_display->print(format_value("no"));
			}
		}
		break;

	case MenuEntryBool::Type::Int:
		{
			const auto &float_entry = std::static_pointer_cast<MenuEntryFloat>(entry);
			float value;

			if (m_change_value) {
				value = m_rotary_encoder->get_rotation();
				float_entry->set_value(value);
				if (value != float_entry->get_value()) {
					// The set_value clipped the value, we update the rotary
					// encoder back.
					m_rotary_encoder->set_rotation(float_entry->get_encoder());
				}
			}

			value = float_entry->get_value();
			m_lcd_display->set_pos(m_value_line, 0);
			m_lcd_display->print(format_value(std::to_string(value) + float_entry->get_unit()));
		}
		break;

	case MenuEntryBool::Type::Float:
		{
			const auto &float_entry = std::static_pointer_cast<MenuEntryFloat>(entry);
			float value;

			if (m_change_value) {
				value = m_rotary_encoder->get_rotation() * float_entry->get_precision();
				float_entry->set_value(value);
				if (value != float_entry->get_value()) {
					// The set_value clipped the value, we update the rotary
					// encoder back.
					m_rotary_encoder->set_rotation(float_entry->get_encoder());
				}
			}

			std::stringstream ss;
			value = float_entry->get_value();
			ss << std::setprecision(float_entry->get_num_decimal()) << std::fixed << value;
			m_lcd_display->set_pos(m_value_line, 0);
			m_lcd_display->print(format_value(ss.str() + float_entry->get_unit()));
		}
		break;

	default:
		break;
	}


}


std::string LCDMenu::format_title(std::string title)
{
	int num_cols = m_lcd_display->get_num_cols();
	int title_len = title.size();

	std::string title_ = title;
	if (title_len > num_cols - 4) {
		title_.resize(num_cols-4);
	}
	title_.insert(0, "-<");
	title_ += ">-";

	int padding = (num_cols - title_.size()) / 2;

	std::string menu_title(num_cols, '-');
	menu_title.replace(padding, title_.size(), title_);

	return menu_title;
}


std::string LCDMenu::format_value(std::string value)
{
	int num_cols = m_lcd_display->get_num_cols();
	int value_len = value.size();

	std::string value_ = value;
	if (value_len > num_cols) {
		value_.resize(num_cols);
	}

	int padding = (num_cols - value_.size()) / 2;

	std::string menu_value(num_cols, ' ');
	menu_value.replace(padding, value_.size(), value_);

	return menu_value;
}
