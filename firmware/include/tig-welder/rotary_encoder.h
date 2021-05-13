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

#ifndef TIG_WELDER_ROTARY_ENCODER_H
#define TIG_WELDER_ROTARY_ENCODER_H

#include <cstdint>


class RotaryEncoder
{
public:
	RotaryEncoder(std::uint32_t pin_a, std::uint32_t pin_b, std::uint32_t sm=0);

	void set_rotation(int rotation) {s_rotation = rotation;}

	int get_rotation(void) const {return s_rotation>>2;}

private:
	static void irq_handler(void);

private:
	// the current location of rotation
	static int s_rotation;
};

#endif
