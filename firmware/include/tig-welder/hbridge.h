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

#ifndef TIG_WELDER_HBRIDGE_H
#define TIG_WELDER_HBRIDGE_H


#include "pico/stdlib.h"
#include <cstdint>


class HBridge
{
public:
	HBridge(float counter_period, std::uint32_t pin_shutdown,
	        std::uint32_t pin_high_0, std::uint32_t pin_low_1,
	        std::uint32_t pin_high_1, std::uint32_t pin_low_0);

	void freewheel() const;
	void stop() const;
	void forward(std::uint16_t threshold) const;
	void backward(std::uint16_t threshold) const;

	void set_wrap(std::uint16_t counter_value);

private:
	const std::uint32_t m_high_0;
	const std::uint32_t m_low_0;
	const std::uint32_t m_high_1;
	const std::uint32_t m_low_1;
	const std::uint32_t m_shutdown;
	const std::uint32_t m_pwm_slice_0;
	const std::uint32_t m_pwm_slice_1;
	const float m_counter_period;
	std::uint16_t m_wrap_value;
};

#endif
