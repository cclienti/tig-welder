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
