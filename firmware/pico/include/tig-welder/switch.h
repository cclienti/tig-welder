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

#ifndef TIG_WELDER_SWITCH_H
#define TIG_WELDER_SWITCH_H

#include "hardware/gpio.h"


class Switch final
{
public:
	Switch(std::uint32_t gpio, bool inverted=true) :
		m_gpio (gpio),
		m_inverted (inverted)
	{
		gpio_init(m_gpio);
		gpio_set_dir(m_gpio, GPIO_IN);
	}

	bool is_pressed(void) const
	{
		return (get() ^ m_inverted);
	}

	bool is_released(void)
	{
		bool last{m_pressed};
		m_pressed = is_pressed();
		return last & (!m_pressed);
	}

private:
	inline std::uint32_t get(void) const
	{
		return gpio_get(m_gpio);
	}

	const std::uint32_t m_gpio;
	const std::uint32_t m_inverted;

	bool m_pressed{false};
};

#endif
