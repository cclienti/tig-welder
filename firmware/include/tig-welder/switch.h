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
	std::uint32_t get(void) const
	{
		return gpio_get(m_gpio);
	}

	const std::uint32_t m_gpio;
	const std::uint32_t m_inverted;

	bool m_pressed{false};
};

#endif
