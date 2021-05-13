#include "tig-welder/buzzer.h"

#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "pico/time.h"


Buzzer::Buzzer(std::uint32_t pin) :
	m_pin (pin),
	m_pwm_slice (pwm_gpio_to_slice_num(pin))
{
	gpio_set_function(pin, GPIO_FUNC_PWM);

	float divider;
	divider = clock_get_hz(clk_sys) / m_tref;
	pwm_set_clkdiv(m_pwm_slice, divider);
}


void Buzzer::melody(const std::vector<Buzzer::Melody> &melody)
{
	if (m_lock) {
		return;
	}
	m_lock = true;

	m_melody = melody;
	m_melody_counter = melody.size();

	const Melody &note = pop_note();
	buzz(note.freq);
	add_alarm_in_ms(note.duration_ms, Buzzer::timer_callback, this, true);
}

void Buzzer::error()
{
	melody({{Note::Sol, 300}, {Note::Do, 600}});
}

void Buzzer::valid()
{
	melody({{Note::Sol, 300}, {Note::Si, 300}});
}

void Buzzer::warning()
{
	melody({{Note::Do, 300}, {Note::Silence, 300},
	        {Note::Do, 300}, {Note::Silence, 300},
	        {Note::Do, 300}, {Note::Silence, 300},
	        {Note::Do, 300}, {Note::Silence, 300},
	        {Note::Do, 300}, {Note::Silence, 300},
	        {Note::Do, 300}, {Note::Silence, 300}});
}

const Buzzer::Melody &Buzzer::pop_note(void)
{
	const Melody &note = m_melody[m_melody.size() - m_melody_counter];
	m_melody_counter--;
	return note;
}

void Buzzer::buzz(Note note)
{
	std::uint8_t duty_cycle = 128;

	std::int32_t top;

	auto freq = static_cast<std::uint32_t>(note);

	if (freq == 0) {
		pwm_set_enabled(m_pwm_slice, false);
		return;
	}

	top =  m_tref / freq - 1;
	top = (top < 0) ? 0 : top;
	top = (top > 65535) ? 65535 : top;

	// std::int32_t level;
	// level = top + 1;
	// level = level * duty_cycle;
	// level = level >> (8*sizeof(duty_cycle));
	// level = level - 1;
	// level = (level < 0) ? 0 : level;
	// level = (level >= top/2) ? (top/2 - 1) : level;

	pwm_set_wrap(m_pwm_slice, top);
	pwm_set_gpio_level(m_pin, top / 2);
	pwm_set_enabled(m_pwm_slice, true);
}


std::int64_t Buzzer::timer_callback(alarm_id_t id, void *context)
{
	Buzzer &instance = *reinterpret_cast<Buzzer*>(context);

	if (instance.m_melody_counter == 0) {
		pwm_set_enabled(instance.m_pwm_slice, false);
		instance.m_lock = false;
		return 0;
	}

	const Melody &note = instance.pop_note();

	instance.buzz(note.freq);
	return note.duration_ms * 1000; // convert to us
}
