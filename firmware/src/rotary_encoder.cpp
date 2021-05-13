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

#include "tig-welder/rotary_encoder.h"

#include "hardware/pio.h"
#include "hardware/irq.h"
#include "pico/error.h"

#include "rotary_encoder.pio.h"


int RotaryEncoder::s_rotation {0};


RotaryEncoder::RotaryEncoder(std::uint32_t pin_a, std::uint32_t pin_b, std::uint32_t sm)
{
	// configure the used pins as input with pull up
	pio_gpio_init(pio0, pin_a);
	pio_gpio_init(pio0, pin_b);

	// load the pio program into the pio memory
	uint offset = pio_add_program(pio0, &pio_rotary_encoder_program);

	// make a sm config
	pio_sm_config c = pio_rotary_encoder_program_get_default_config(offset);

	// set the 'in' pins
	sm_config_set_in_pins(&c, pin_a);

	// set shift to left: bits shifted by 'in' enter at the least
	// significant bit (LSB), no autopush
	sm_config_set_in_shift(&c, false, false, 0);

	// set the IRQ handler
	irq_set_exclusive_handler(PIO0_IRQ_0, RotaryEncoder::irq_handler);

	// enable the IRQ
	irq_set_enabled(PIO0_IRQ_0, true);
	pio0->inte0 = PIO_IRQ0_INTE_SM0_BITS | PIO_IRQ0_INTE_SM1_BITS;

	// init the sm.
	pio_sm_init(pio0, sm, pio_rotary_encoder_offset_pc_start, &c);

	// enable the sm
	pio_sm_set_enabled(pio0, sm, true);
}


void RotaryEncoder::irq_handler(void)
{
	// test if irq 0 was raised
	if (pio0->irq & 1)
	{
		s_rotation--;
	}
	// test if irq 1 was raised
	if (pio0->irq & 2)
	{
		s_rotation++;
	}
	// clear both interrupts
	pio0->irq = 3;
}
