#include "tig-welder/hbridge.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include <algorithm>
#include <stdio.h>


HBridge::HBridge(float counter_period, std::uint32_t pin_shutdown,
                 std::uint32_t pin_high_0, std::uint32_t pin_low_1,
                 std::uint32_t pin_high_1, std::uint32_t pin_low_0):
	m_high_0         (pin_high_0),
	m_low_0          (pin_low_0),
	m_high_1         (pin_high_1),
	m_low_1          (pin_low_1),
	m_shutdown       (pin_shutdown),
	m_counter_period (counter_period),
	m_pwm_slice_0    (pwm_gpio_to_slice_num(m_high_0)),
	m_pwm_slice_1    (pwm_gpio_to_slice_num(m_high_1)),
	m_wrap_value     (0xffffu)
{
	gpio_init(m_shutdown);
	gpio_put(m_shutdown, 0);
	gpio_set_dir(m_shutdown, GPIO_OUT);

	gpio_init(m_low_0);
	gpio_put(m_low_0, 0);
	gpio_set_dir(m_low_0, GPIO_OUT);

	gpio_init(m_low_1);
	gpio_put(m_low_1, 0);
	gpio_set_dir(m_low_1, GPIO_OUT);

	//gpio_set_function(m_low_0, GPIO_FUNC_PWM);
	//gpio_set_function(m_low_1, GPIO_FUNC_PWM);
	gpio_set_function(m_high_0, GPIO_FUNC_PWM);
	gpio_set_function(m_high_1, GPIO_FUNC_PWM);

	pwm_set_clkdiv_mode(m_pwm_slice_0, PWM_DIV_FREE_RUNNING);
	pwm_set_clkdiv_mode(m_pwm_slice_1, PWM_DIV_FREE_RUNNING);

	float divider = clock_get_hz(clk_sys) * counter_period;
	pwm_set_clkdiv(m_pwm_slice_0, divider);
	pwm_set_clkdiv(m_pwm_slice_1, divider);

	pwm_set_phase_correct(m_pwm_slice_0, false);
	pwm_set_phase_correct(m_pwm_slice_1, false);

	pwm_set_output_polarity(m_pwm_slice_0, false, false);
	pwm_set_output_polarity(m_pwm_slice_1, false, false);

	pwm_set_wrap(m_pwm_slice_0, m_wrap_value);
	pwm_set_wrap(m_pwm_slice_1, m_wrap_value);

	// pwm_set_both_levels(m_pwm_slice_0, 0, 0);
	// pwm_set_both_levels(m_pwm_slice_1, 0, 0);
	pwm_set_chan_level(m_pwm_slice_0, PWM_CHAN_B, 0);
	pwm_set_chan_level(m_pwm_slice_1, PWM_CHAN_B, 0);

	pwm_set_enabled(m_pwm_slice_0, true);
	pwm_set_enabled(m_pwm_slice_1, true);
}

void HBridge::freewheel(void) const
{
	printf("pin_high_0: %d\n", m_high_0);
	printf("pin_low_1: %d\n", m_low_1);
	printf("pin_high_1: %d\n", m_high_1);
	printf("pin_low_0: %d\n", m_low_0);
	//pwm_set_both_levels(m_pwm_slice_0, 0, 0);
	//pwm_set_both_levels(m_pwm_slice_1, 0, 0);
	gpio_put(m_low_0, 0);
	gpio_put(m_low_1, 0);
	pwm_set_chan_level(m_pwm_slice_0, PWM_CHAN_B, 0);
	pwm_set_chan_level(m_pwm_slice_1, PWM_CHAN_B, 0);
}

void HBridge::stop(void) const
{
	//pwm_set_chan_level(m_pwm_slice_0, PWM_CHAN_A, m_wrap_value);
	//pwm_set_chan_level(m_pwm_slice_1, PWM_CHAN_A, m_wrap_value);
	gpio_put(m_low_0, 1);
	gpio_put(m_low_1, 1);
	pwm_set_chan_level(m_pwm_slice_0, PWM_CHAN_B, 0);
	pwm_set_chan_level(m_pwm_slice_1, PWM_CHAN_B, 0);

}

void HBridge::set_wrap(std::uint16_t counter_value)
{
	m_wrap_value = counter_value;
	gpio_put(m_low_0, 0);
	gpio_put(m_low_1, 0);
	//pwm_set_both_levels(m_pwm_slice_0, 0, 0);
	//pwm_set_both_levels(m_pwm_slice_1, 0, 0);
	pwm_set_chan_level(m_pwm_slice_0, PWM_CHAN_B, 0);
	pwm_set_chan_level(m_pwm_slice_1, PWM_CHAN_B, 0);
	pwm_set_wrap(m_pwm_slice_0, m_wrap_value);
	pwm_set_wrap(m_pwm_slice_1, m_wrap_value);
}

void HBridge::forward(std::uint16_t threshold) const
{
	std::uint16_t value = std::min(threshold, m_wrap_value);
	// pwm_set_both_levels(m_pwm_slice_1, 0, 0);
	// pwm_set_both_levels(m_pwm_slice_0, threshold, threshold);
	gpio_put(m_low_0, 0);
	gpio_put(m_low_1, 1);
	pwm_set_chan_level(m_pwm_slice_0, PWM_CHAN_B, value);
}

void HBridge::backward(std::uint16_t threshold) const
{
	std::uint16_t value = std::min(threshold, m_wrap_value);
	// pwm_set_both_levels(m_pwm_slice_0, 0, 0);
	// pwm_set_both_levels(m_pwm_slice_1, threshold, threshold);
	gpio_put(m_low_0, 1);
	gpio_put(m_low_1, 0);
	pwm_set_chan_level(m_pwm_slice_1, PWM_CHAN_B, value);
}
