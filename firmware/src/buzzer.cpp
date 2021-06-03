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

#include "tig-welder/buzzer.h"

#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "pico/time.h"


Buzzer::Buzzer(std::uint32_t pin) :
	m_pin (pin),
	m_pwm_slice (pwm_gpio_to_slice_num(pin))
{
	gpio_set_function(m_pin, GPIO_FUNC_PWM);

	pwm_set_gpio_level(m_pin, 0);
	pwm_set_enabled(m_pwm_slice, true);

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
	std::int32_t top;

	auto freq = static_cast<std::uint32_t>(note);

	if (freq == 0) {
		pwm_set_gpio_level(m_pin, 0);
		return;
	}

	top =  m_tref / freq - 1;
	top = (top < 0) ? 0 : top;
	top = (top > 65535) ? 65535 : top;

	pwm_set_wrap(m_pwm_slice, top);
	if (m_muted) {
		pwm_set_gpio_level(m_pin, 0);
	}
	else {
		pwm_set_gpio_level(m_pin, top / 2);
	}
}


std::int64_t Buzzer::timer_callback(alarm_id_t id, void *context)
{
	Buzzer &instance = *reinterpret_cast<Buzzer*>(context);

	if (instance.m_melody_counter == 0) {
		pwm_set_gpio_level(instance.m_pin, 0);
		instance.m_lock = false;
		return 0;
	}

	const Melody &note = instance.pop_note();

	instance.buzz(note.freq);
	return note.duration_ms * 1000; // convert to us
}
