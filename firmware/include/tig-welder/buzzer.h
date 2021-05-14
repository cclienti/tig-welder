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

#ifndef TIG_WELDER_BUZZER_H
#define TIG_WELDER_BUZZER_H


#include "pico/stdlib.h"

#include <cstdint>
#include <vector>


class Buzzer
{
public:
	enum class Note: std::uint32_t
	{
		Silence = 0,
		Do = 261,
		Re = 293,
		Mi = 329,
		Fa = 349,
		Sol = 392,
		La = 440,
		Si = 493
	};

	struct Melody
	{
		Note freq;
		std::uint32_t duration_ms;
	};

public:
	Buzzer(std::uint32_t pin=15);

	void mute(void) {m_muted = true;}
	void unmute(void) {m_muted = false;}
	bool is_muted(void) const {return m_muted;}

	void melody(const std::vector<Melody> &melody);
	void error(void);
	void valid(void);
	void warning(void);

private:
	void buzz(Note note);

	const Melody &pop_note(void);

private:
	static std::int64_t timer_callback(alarm_id_t id, void *context);

private:
	static constexpr std::uint32_t m_tref = 1'000'000;
	bool m_muted{false};

	std::uint32_t m_pin;
	std::uint32_t m_pwm_slice;

	bool m_lock{false};
	std::vector<Melody> m_melody;
	volatile std::uint32_t m_melody_counter{0};
};

#endif
