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

#ifndef TIG_WELDER_LCD_MENU_ENTRY_H
#define TIG_WELDER_LCD_MENU_ENTRY_H

#include <string>
#include <cstdint>
#include <sstream>
#include <cmath>
#include <iomanip>


class MenuEntryBase
{
public:
	enum class Type {Bool, Int, Float};

	const std::string &get_formatted_title(void) const {
		return m_title;
	}

	Type get_type(void) const {
		return m_type;
	}

	std::string get_formatted_value(void)
	{
		return format_info(get_value_str(), m_width, ' ');
	}

	virtual int get_encoder_from_value() const = 0;

	virtual void set_value_from_encoder(int encoder) = 0;

	static std::string format_info(const std::string &info, std::uint8_t width, char pad)
	{
		int info_len = info.size();

		std::string info_ = info;
		if (info_len > width) {
			info_.resize(width);
		}

		int padding = (width - info_.size()) / 2;

		std::string menu_info(width, pad);
		menu_info.replace(padding, info_.size(), info_);

		return menu_info;
	}

protected:
	MenuEntryBase(Type type, std::uint8_t width, const std::string &title):
		m_title (format_info("<" + title + ">", width, '-')),
		m_width (width),
		m_type  (type)
	{
	}

	virtual std::string get_value_str(void) = 0;

private:
	Type m_type;
	std::uint8_t m_width;
	std::string m_title;
};


class MenuEntryBool: public MenuEntryBase
{
public:
	MenuEntryBool(const std::string title, std::uint8_t width, bool &variable):
		MenuEntryBase(Type::Bool, width, title),
		m_variable(variable)
	{
	}

	int get_encoder_from_value(void) const final {
		return get_value();
	}

	void set_value_from_encoder(int encoder) final
	{
		m_variable = encoder % 2;
	}

	void set_value(bool value) {
		m_variable = value;
	}

	bool get_value(void) const {
		return m_variable;
	}

private:
	std::string get_value_str(void) final
	{
		if (m_variable) {
			return "yes";
		}
		else {
			return "no";
		}
	}

private:
	bool &m_variable;
};


class MenuEntryInt: public MenuEntryBase
{
public:
	MenuEntryInt(const std::string title, std::uint8_t width, int &variable,
	             int min, int max, const std::string &unit):
		MenuEntryBase (Type::Int, width, title),
		m_variable    (variable),
		m_min         (min),
		m_max         (max),
		m_unit        (unit)
	{
		// The variable can be not initialized correctly regaring
		// min/max.
		set_value(get_value());
	}

	int get_encoder_from_value(void) const final {
		return get_value();
	}

	void set_value_from_encoder(int encoder) final
	{
		set_value(encoder);
	}

	void set_value(int value) {
		m_variable = std::min(std::max(value, m_min), m_max);
	}

	int get_value(void) const {
		return m_variable;
	}

private:
	std::string get_value_str(void) final
	{
		return std::to_string(m_variable) + m_unit;
	}

private:
	int &m_variable;
	int m_min;
	int m_max;
	const std::string m_unit;
};


class MenuEntryFloat: public MenuEntryBase
{
public:
	MenuEntryFloat(const std::string title, std::uint8_t width, float &variable,
	               float min, float max, float precision, const std::string &unit):
		MenuEntryBase (Type::Float, width, title),
		m_variable    (variable),
		m_min         (min),
		m_max         (max),
		m_precision   (precision),
		m_inv_prec    (1/precision),
		m_num_decimal (std::max(static_cast<int>(std::ceil(std::log10(m_inv_prec))), 0)),
		m_unit        (unit)
	{
		// The variable can be not initialized correctly regaring
		// min/max.
		set_value(get_value());
	}

	int get_encoder_from_value(void) const final {
		return static_cast<int>(get_value() * m_inv_prec);
	}

	void set_value_from_encoder(int encoder) final
	{
		set_value(encoder * m_precision);
	}

	void set_value(float value) {
		m_variable = std::min(std::max(value, m_min), m_max);
	}

	float get_value(void) const {
		return m_variable;
	}

private:
	std::string get_value_str(void) final
	{
		std::stringstream ss;
		ss << std::setprecision(m_num_decimal)
		   << std::fixed << m_variable << m_unit;
		return ss.str();
	}

private:
	float &m_variable;
	const float m_min;
	const float m_max;
	const float m_precision;
	const float m_inv_prec;
	const int m_num_decimal;
	const std::string m_unit;
};


#endif
