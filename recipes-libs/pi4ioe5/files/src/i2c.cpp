// Userspace I2C
// Copyright (C) 2023 Polaris Industries Inc
//
// Author: Daniel Beer <daniel.beer@igorinstitute.com>

#include <linux/i2c-dev.h>
#include <linux/i2c.h>
// #include <i2c/smbus.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include "i2c.hpp"
#include <stdio.h>
#include <system_error>

I2cDevice::I2cDevice(const char *bus, uint8_t addr) : _addr(addr),
													  _fd(::open(bus, O_RDWR | O_NOCTTY))
{
	if (_fd.get() < 0)
	{
		printf("%s: Failed to open %s: %s\n", __PRETTY_FUNCTION__, bus, strerror(errno));
		throw std::system_error(errno, std::generic_category());
	}

	if (ioctl(_fd.get(), I2C_SLAVE, addr) < 0)
	{
		printf("%s: Failed to set I2C_SLAVE on %s with address 0x%02x: %s\n",
			   __PRETTY_FUNCTION__, bus, addr, strerror(errno));
		throw std::system_error(errno, std::generic_category());
	}
}

void I2cDevice::WBlock(const uint8_t *data, size_t len)
{
	if (write(_fd.get(), data, len) < 0)
	{
		printf("%s: Failed to write block to address 0x%02x: %s\n", __PRETTY_FUNCTION__, _addr, strerror(errno));
		throw std::system_error(errno, std::generic_category());
	}
}

void I2cDevice::W8D8(uint8_t reg, uint8_t data)
{
	uint8_t buf[2] = {reg, data};

	if (write(_fd.get(), buf, 2) < 0)
	{
		printf("%s: Failed to write to register 0x%02x on address 0x%02x with data 0x%02x: %s\n",
			   __PRETTY_FUNCTION__, reg, _addr, data, strerror(errno));
		throw std::system_error(errno, std::generic_category());
	}
}

uint8_t I2cDevice::R8D8(uint8_t reg)
{
	uint8_t inbuf;
	::i2c_msg msgs[] = {
		{
			.addr = _addr,
			.flags = 0,
			.len = 1,
			.buf = &reg,
		},
		{
			.addr = _addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = &inbuf,
		},
	};

	::i2c_rdwr_ioctl_data rdwr = {
		.msgs = msgs,
		.nmsgs = 2,
	};

	if (ioctl(_fd.get(), I2C_RDWR, &rdwr) < 0)
	{
		printf("%s: Failed to perform I2C_RDWR on address 0x%02x, register 0x%02x: %s\n",
			   __PRETTY_FUNCTION__, _addr, reg, strerror(errno));
		throw std::system_error(errno, std::generic_category());
	}

	return inbuf;
}

void I2cDevice::R8DBlock(uint8_t reg, uint8_t *data, size_t len)
{
	::i2c_msg msgs[] = {
		{
			.addr = _addr,
			.flags = 0,
			.len = 1,
			.buf = &reg,
		},
		{
			.addr = _addr,
			.flags = I2C_M_RD,
			.len = __u16(len),
			.buf = data,
		},
	};

	::i2c_rdwr_ioctl_data rdwr = {
		.msgs = msgs,
		.nmsgs = 2,
	};

	if (ioctl(_fd.get(), I2C_RDWR, &rdwr) < 0)
	{
		printf("%s: Failed to perform I2C_RDWR on address 0x%02x, register 0x%02x: %s\n",
			   __PRETTY_FUNCTION__, _addr, reg, strerror(errno));
		throw std::system_error(errno, std::generic_category());
	}
}
