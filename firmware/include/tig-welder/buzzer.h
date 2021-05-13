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

	void melody(const std::vector<Melody> &melody);

	void error();

	void valid();

	void warning();

private:
	void buzz(Note note);

	const Melody &pop_note(void);

private:
	static std::int64_t timer_callback(alarm_id_t id, void *context);

private:
	static constexpr std::uint32_t m_tref = 1'000'000;

	std::uint32_t m_pin;
	std::uint32_t m_pwm_slice;

	bool m_lock{false};
	std::vector<Melody> m_melody;
	volatile std::uint32_t m_melody_counter{0};
};

#endif
