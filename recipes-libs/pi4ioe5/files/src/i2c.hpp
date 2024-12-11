// Userspace I2C
// Copyright (C) 2023 Polaris Industries Inc
// 
// Author: Daniel Beer <daniel.beer@igorinstitute.com>

#ifndef I2C_H_
#define I2C_H_

#include <cstdint>
#include "fd.hpp"

class I2cDevice {
public:
    I2cDevice(const char *buf, uint8_t addr);

    I2cDevice(const I2cDevice&) = delete;
    I2cDevice& operator=(const I2cDevice&) = delete;

    int W8D8(uint8_t reg, uint8_t data);
    int R8D8(uint8_t reg);

    int WBlock(const uint8_t *data, size_t len);
    int R8DBlock(uint8_t reg, uint8_t *data, size_t len);

    void swap(I2cDevice& other) {
	std::swap(_addr, other._addr);
	_fd.swap(other._fd);
    }

    I2cDevice(I2cDevice&& r) : _addr(r._addr), _fd(std::move(r._fd)) { }

    I2cDevice& operator=(I2cDevice&& r)
    {
	I2cDevice take(std::move(r));
	swap(take);
	return *this;
    }

    bool isCommunicationOk(void) { return !m_communication_fail; }

private:
    uint8_t _addr;
    Fd _fd;
    bool m_communication_fail;
};

#endif
