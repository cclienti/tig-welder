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
