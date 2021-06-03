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

#ifndef TIG_WELDER_RELAY_H
#define TIG_WELDER_RELAY_H

#include "hardware/gpio.h"
#include <cstdint>


class Relay final
{
public:
	Relay(std::uint32_t gpio, bool inverted=true) :
		m_gpio (gpio),
		m_inverted (inverted)
	{
		gpio_init(m_gpio);
		gpio_put(m_gpio, m_inverted);
		gpio_set_dir(m_gpio, GPIO_OUT);
	}

	void enable(void) const
	{
		gpio_put(m_gpio, !m_inverted);
	}

	void disable(void) const
	{
		gpio_put(m_gpio, m_inverted);
	}

private:
	const std::uint32_t m_gpio;
	const bool m_inverted;
};

#endif
