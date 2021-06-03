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

#ifndef TIG_WELDER_SPI_ADC_H
#define TIG_WELDER_SPI_ADC_H

#include "hardware/spi.h"
#include <cstdint>


class SPIADC
{
public:
	SPIADC(std::uint8_t spi_inst_num=0u, std::uint32_t spi_speed=1000 * 1000u,
	       std::uint32_t cs_pin=5u, std::uint32_t clk_pin=2u,
	       std::uint32_t tx_pin=3u, std::uint32_t rx_pin=4u);

	std::uint16_t read8_single(std::uint8_t channel) const;
	std::uint16_t read8_diff(std::uint8_t channel_diff) const;

	std::uint16_t read_single(std::uint8_t channel) const;
	std::uint16_t read_diff(std::uint8_t channel_diff) const;

private:
	template<std::uint8_t N>
	std::uint16_t readn(std::uint8_t channel, bool single) const;

	std::uint16_t read(std::uint8_t channel, bool single) const;

	void cs_select(void) const;
	void cs_deselect(void) const;

private:
	spi_inst_t * const m_spi;

	std::uint32_t m_cs_pin;
	std::uint32_t m_clk_pin;
	std::uint32_t m_tx_pin;
	std::uint32_t m_rx_pin;

};


#endif
