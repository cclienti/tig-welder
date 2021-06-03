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

#include "tig-welder/spi_adc.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"


SPIADC::SPIADC(std::uint8_t spi_inst_num, std::uint32_t spi_speed,
               std::uint32_t cs_pin, std::uint32_t clk_pin,
               std::uint32_t tx_pin, std::uint32_t rx_pin) :
	m_spi (spi_inst_num == 0 ? spi0 : spi1),
	m_cs_pin (cs_pin),
	m_clk_pin (clk_pin),
	m_tx_pin (tx_pin),
	m_rx_pin (rx_pin)

{
	// Init the CS pin
	gpio_init(m_cs_pin);
	gpio_put(m_cs_pin, true);
	gpio_set_dir(m_cs_pin, GPIO_OUT);

	spi_init(m_spi, spi_speed);
	gpio_set_function(m_rx_pin, GPIO_FUNC_SPI);
	gpio_set_function(m_clk_pin, GPIO_FUNC_SPI);
	gpio_set_function(m_tx_pin, GPIO_FUNC_SPI);
}

std::uint16_t SPIADC::read8_single(std::uint8_t channel) const
{
	return readn<8>(channel, true);
}

std::uint16_t SPIADC::read8_diff(std::uint8_t channel_diff) const
{
	return readn<8>(channel_diff, false);
}

std::uint16_t SPIADC::read_single(std::uint8_t channel) const
{
	return read(channel, true);
}

std::uint16_t SPIADC::read_diff(std::uint8_t channel_diff) const
{
	return read(channel_diff, false);
}

template<std::uint8_t N>
std::uint16_t SPIADC::readn(std::uint8_t channel, bool single) const
{
	std::uint32_t sum = 0;
	for (int i=0; i<N; i++) {
		sum += read(channel, single);
	}
	return sum / N;
}


std::uint16_t SPIADC::read(std::uint8_t channel, bool single) const
{
	std::uint8_t src[] = {
		static_cast<std::uint8_t>(4 + (single ? 2 : 0) + ((channel & 4) >> 2)),
		static_cast<std::uint8_t>((channel & 3) << 6),
		static_cast<std::uint8_t>(0)
	};

	std::uint8_t dest[] = {0, 0, 0};

	cs_select();
	spi_write_read_blocking(m_spi, src, dest, 3);
	cs_deselect();

	std::uint16_t result;
	result = dest[1] & 0xf;
	result = (result << 8) + dest[2];

	return result;
}

void SPIADC::cs_select(void) const
{
	gpio_put(m_cs_pin, false);
}

void SPIADC::cs_deselect(void) const
{
	gpio_put(m_cs_pin, true);
}
