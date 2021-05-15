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

#ifndef TIG_WELDER_LCD_MENU_FOOTER_H
#define TIG_WELDER_LCD_MENU_FOOTER_H

#include <string>
#include <cstdint>
#include <sstream>
#include <cmath>
#include <iomanip>


class FooterNoteBase
{
public:
	enum class Type {Void, Bool, Int, Float};

	virtual std::string get_display(void)
	{
		std::string fmttext = m_text + ": " + get_value();
		fmttext.resize(m_width, ' ');
		return fmttext;
	}

protected:
	FooterNoteBase(Type type, std::uint8_t width, const std::string &text):
		m_type  (type),
		m_width (width),
		m_text  (text)
	{
	}

	virtual std::string get_value(void) = 0;

private:
	const Type m_type;
	const std::uint8_t m_width;
	const std::string m_text;
};

class FooterNoteBool: public FooterNoteBase
{
public:
	FooterNoteBool(std::uint8_t width, const std::string &text, const bool &variable):
		FooterNoteBase (FooterNoteBase::Type::Bool, width, text),
		m_variable     (variable)
	{
	}

private:
	std::string get_value(void) final
	{
		if (m_variable) {
			return "yes";
		}
		else {
			return "no";
		}
	}

private:
	const bool &m_variable;
};

class FooterNoteInt: public FooterNoteBase
{
public:
	FooterNoteInt(std::uint8_t width, const std::string &text, const int &variable,
	              const std::string &unit):
		FooterNoteBase (FooterNoteBase::Type::Int, width, text),
		m_variable     (variable),
		m_unit         (unit)
	{
	}

private:
	std::string get_value(void) final
	{
		return std::to_string(m_variable) + m_unit;
	}

private:
	const int &m_variable;
	const std::string m_unit;
};

class FooterNoteFloat: public FooterNoteBase
{
public:
	FooterNoteFloat(std::uint8_t width, const std::string &text,
	                const float &variable, float precision,
	                const std::string &unit):
		FooterNoteBase (FooterNoteBase::Type::Float, width, text),
		m_variable     (variable),
		m_precision   (precision),
		m_inv_prec    (1/precision),
		m_num_decimal (std::max(static_cast<int>(std::ceil(std::log10(m_inv_prec))), 0)),
		m_unit        (unit)
	{
	}

private:
	std::string get_value(void) final
	{
		std::stringstream ss;
		ss << std::setprecision(m_num_decimal)
		   << std::fixed << m_variable << m_unit;
		return ss.str();
	}

private:
	const float &m_variable;
	const float m_precision;
	const float m_inv_prec;
	const int m_num_decimal;
	const std::string m_unit;
};


#endif
