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

#include "tig-welder/lcd_menu_entry.h"
#include "tig-welder/lcd_menu_footer.h"
#include "tig-welder/lcd_menu.h"
#include "tig-welder/lcd_display.h"
#include "tig-welder/rotary_encoder.h"
#include "tig-welder/switch.h"
#include "tig-welder/buzzer.h"


LCDMenu::LCDMenu(LCDDisplayUPtr lcd_display, RotaryEncoderUPtr rotary_encoder,
                 SwitchUPtr button, BuzzerSPtr buzzer):
	m_lcd_display      (std::move(lcd_display)),
	m_rotary_encoder   (std::move(rotary_encoder)),
	m_button           (std::move(button)),
	m_buzzer           (buzzer),
	m_menu_entry_id    (0),
	m_change_value     (false),
	m_footer_separator (static_cast<std::size_t>(m_lcd_display->get_num_cols()), '-')
{
	m_rotary_encoder->set_rotation(0);
	m_lcd_display->clear();
	m_lcd_display->home();

	refresh();
}


void LCDMenu::splash(const std::string &text)
{
	m_lcd_display->clear();
	m_lcd_display->home();
	m_lcd_display->set_pos(m_lcd_display->get_num_cols()/2, 0);
	m_lcd_display->print(MenuEntryBase::format_info("[" + text + "]",
	                                                m_lcd_display->get_num_cols(), '='));
}


void LCDMenu::register_menu(const std::string &title, bool &variable)
{
	const auto &menu = std::make_shared<MenuEntryBool>(title, m_lcd_display->get_num_cols(), variable);
	m_menu_entries.insert(m_menu_entries.begin(), menu);
}


void LCDMenu::register_menu(const std::string &title, int &variable,
                             int min, int max, const std::string &unit)
{
	const auto &menu = std::make_shared<MenuEntryInt>(title, m_lcd_display->get_num_cols(), variable,
	                                                  min, max, unit);
	m_menu_entries.insert(m_menu_entries.begin(), menu);
}


void LCDMenu::register_menu(const std::string &title, float &variable,
                             float min, float max, float precision,
                             const std::string &unit)
{
	const auto &menu = std::make_shared<MenuEntryFloat>(title, m_lcd_display->get_num_cols(), variable,
	                                                   min, max, precision, unit);
	m_menu_entries.insert(m_menu_entries.begin(), menu);
}


void LCDMenu::register_footer(FooterPosition position,
                              const std::string &text, const bool &variable)
{
	const auto &note = std::make_shared<FooterNoteBool>(m_lcd_display->get_num_cols()/2-1,
	                                                    text, variable);
	if (position == FooterPosition::Left) {
		m_footer_left = note;
	}
	else {
		m_footer_right = note;
	}
}


void LCDMenu::register_footer(FooterPosition position,
                              const std::string &text, const int &variable,
                              const std::string &unit)
{
	const auto &note = std::make_shared<FooterNoteInt>(m_lcd_display->get_num_cols()/2-1,
	                                                    text, variable, unit);
	if (position == FooterPosition::Left) {
		m_footer_left = note;
	}
	else {
		m_footer_right = note;
	}
}


void LCDMenu::register_footer(FooterPosition position,
                              const std::string &text,
                              const float &variable, float precision,
                              const std::string &unit)
{
	const auto &note = std::make_shared<FooterNoteFloat>(m_lcd_display->get_num_cols()/2-1,
	                                                     text, variable, precision, unit);
	if (position == FooterPosition::Left) {
		m_footer_left = note;
	}
	else {
		m_footer_right = note;
	}
}


void LCDMenu::refresh()
{
	refresh_menu();
	refresh_footer();
}


void LCDMenu::refresh_menu()
{
	if (m_menu_entries.empty()) {
		return;
	}

	const auto &entry = m_menu_entries[m_menu_entry_id];

	bool button_released = m_button->is_released();
	m_change_value = m_change_value ^ button_released;

	if (m_change_value) {
		if (button_released) {
			m_rotary_encoder->set_rotation(entry->get_encoder_from_value());
		}
	}
	else {
		if (button_released) {
			m_rotary_encoder->set_rotation(m_menu_entry_id);
		}
		m_menu_entry_id = m_rotary_encoder->get_rotation() % m_menu_entries.size();
	}

	m_lcd_display->set_pos(m_title_line, 0);
	m_lcd_display->print(entry->get_formatted_title());

	if (m_change_value) {
		auto rotation = m_rotary_encoder->get_rotation();
		entry->set_value_from_encoder(rotation);
		auto rotation_update = entry->get_encoder_from_value();
		if (rotation != rotation_update) {
			// The value can be clipped by the entry class, we update the
			// rotary encoder back.
			m_rotary_encoder->set_rotation(rotation_update);
		}
	}

	m_lcd_display->set_pos(m_value_line, 0);
	m_lcd_display->print(entry->get_formatted_value());
}


void LCDMenu::refresh_footer()
{
	m_lcd_display->set_pos(m_separator_line, 0);
	m_lcd_display->print(m_footer_separator);

	if (m_footer_left) {
		m_lcd_display->set_pos(m_footer_line, 0);
		m_lcd_display->print(m_footer_left->get_display());
	}

	m_lcd_display->set_pos(m_footer_line, m_lcd_display->get_num_cols()/2);
	m_lcd_display->putchar(' ');

	if (m_footer_right) {
		m_lcd_display->set_pos(m_footer_line, m_lcd_display->get_num_cols()/2+1);
		m_lcd_display->print(m_footer_right->get_display());
	}
}
