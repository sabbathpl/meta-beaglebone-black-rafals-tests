#ifndef PI4IOE5V64XX_H
#define PI4IOE5V64XX_H

#include <stdint.h> 
#include "i2c.hpp"

namespace PI4IOE5V64XX
{
    namespace Registers
    {
        enum : uint8_t
        {
            INPUT_PORT_0 = 0x00,
            INPUT_PORT_1,
            OUTPUT_PORT_0,
            OUTPUT_PORT_1,
            POLARITY_INVERSION_PORT_0,
            POLARITY_INVERSION_PORT_1,
            CONFIGURATION_PORT_0,
            CONFIGURATION_PORT_1,
            OUTPUT_DRIVE_STRENGTH_REGISTER_0_0 = 0x40,
            OUTPUT_DRIVE_STRENGTH_REGISTER_0_1,
            OUTPUT_DRIVE_STRENGTH_REGISTER_1_0,
            OUTPUT_DRIVE_STRENGTH_REGISTER_1_1,
            INPUT_LATCH_REGISTER_0,
            INPUT_LATCH_REGISTER_1,
            PULL_UP_DOWN_ENABLE_REGISTER_0,
            PULL_UP_DOWN_ENABLE_REGISTER_1,
            PULL_UP_DOWN_SELECTION_REGISTER_0,
            PULL_UP_DOWN_SELECTION_REGISTER_1,
            INTERRUPT_MASK_REGISTER_0,
            INTERRUPT_MASK_REGISTER_1,
            INTERRUPT_STATUS_REGISTER_0,
            INTERRUPT_STATUS_REGISTER_1,
            OUTPUT_PORT_CONFIGURATION_REGISTER
        };
    }

    namespace Port
    {
        enum Port : uint8_t
        {
            P00, P01, P02, P03, P04, P05, P06, P07,
            P10, P11, P12, P13, P14, P15, P16, P17
        };
    }

    namespace Level
    {
        enum Level : uint8_t { L, H };
        enum LevelAll : uint16_t { L_ALL = 0x0000, H_ALL = 0xFFFF };
    }

    namespace Polarity
    {
        enum Polarity : uint8_t { ORIGINAL, INVERTED };
        enum PolarityAll : uint16_t { ORIGINAL_ALL = 0x0000, INVERTED_ALL = 0xFFFF };
    }

    namespace Direction
    {
        enum Direction : uint8_t { OUT, IN };
        enum DirectionAll : uint16_t { OUT_ALL = 0x0000, IN_ALL = 0xFFFF };
    }

    namespace PullUpDownEnable
    {
        enum PullUpDownEnable : uint8_t { DISABLE, ENABLE };
        enum PullUpDownEnableAll : uint16_t { DISABLE_ALL = 0x0000, ENABLE_ALL = 0xFFFF };
    }

    namespace PullUpDownSelection
    {
        enum PullUpDownSelection : uint8_t { PULL_DOWN, PULL_UP };
        enum PullUpDownSelectionAll : uint16_t { PULL_DOWN_ALL = 0x0000, PULL_UP_ALL = 0xFFFF };
    }

    template <typename I2c = I2cDevice>
    class PI4IOE5V64XX
    {
        union Ports
        {
            uint16_t w;
            uint8_t b[2];
        };

        static constexpr uint8_t BASE_I2C_ADDR = 0x20;

        I2cDevice *i2c{nullptr};
        uint8_t addr{BASE_I2C_ADDR};
        Ports input{0x0000};
        Ports output{0xFFFF};
        Ports pol{0x0000};
        Ports dir{0xFFFF};
        Ports pe{0x0000};
        Ports pud{0x0000};
        uint8_t status{0x00};

    public:
        void attach(I2cDevice &device, uint8_t i2c_addr)
        {
            this->i2c = &device;
            this->addr = i2c_addr;
        }

        uint16_t read()
        {
            uint8_t buffer[2];
            i2c->R8DBlock(Registers::INPUT_PORT_0, buffer, 2);
            input = (static_cast<uint16_t>(buffer[1]) << 8) | buffer[0];
            return input;
        }

        Level::Level read(const Port::Port port)
        {
            uint16_t value = read();
            return (value & (1 << port)) ? Level::H : Level::L;
        }

        bool write(const uint16_t value)
        {
            output = value;
            return write_impl();
        }

        bool write(const Port::Port port, const Level::Level level)
        {
            if (level == Level::H)
            {
                output |= (1 << port);
            }
            else
            {
                output &= ~(1 << port);
            }
            return write_impl();
        }

        bool polarity(const uint16_t value)
        {
            this->pol.w = value;
            return polarity_impl();
        }

        bool polarity(const Port::Port port, const Polarity::Polarity pol)
        {
            if (pol == Polarity::INVERTED)
            {
                this->pol.w |= (1 << port);
            }
            else
            {
                this->pol.w &= ~(1 << port);
            }
            return polarity_impl();
        }

        bool direction(const uint16_t value)
        {
            this->dir.w = value;
            return direction_impl();
        }

        bool direction(const Port::Port port, const Direction::Direction dir)
        {
            if (dir == Direction::IN)
            {
                this->dir.w |= (1 << port);
            }
            else
            {
                this->dir.w &= ~(1 << port);
            }
            return direction_impl();
        }

        bool pullUpDownEnable(const uint16_t value)
        {
            this->pe.w = value;
            return pullup_down_enable_impl();
        }

        bool pullUpDownEnable(const Port::Port port, const PullUpDownEnable::PullUpDownEnable pe)
        {
            if (pe == PullUpDownEnable::ENABLE)
            {
                this->pe.w |= (1 << port);
            }
            else
            {
                this->pe.w &= ~(1 << port);
            }
            return pullup_down_enable_impl();
        }

        bool pullUpDownSelection(const uint16_t value)
        {
            this->pud.w = value;
            return pullup_down_selection_impl();
        }

        bool pullUpDownSelection(const Port::Port port, const PullUpDownSelection::PullUpDownSelection pud)
        {
            if (pud == PullUpDownSelection::PULL_UP)
            {
                this->pud.w |= (1 << port);
            }
            else
            {
                this->pud.w &= ~(1 << port);
            }
            return pullup_down_selection_impl();
        }

        uint8_t i2c_error() const
        {
            return status;
        }

    private:
        bool write_impl()
        {
            return write_to_register(this->addr, Registers::OUTPUT_PORT_0, output);
        }

        bool polarity_impl()
        {
            return write_to_register(Registers::POLARITY_INVERSION_PORT_0, pol);
        }

        bool direction_impl()
        {
            return write_to_register(Registers::CONFIGURATION_PORT_0, dir);
        }

        bool pullup_down_enable_impl()
        {
            return write_to_register(Registers::PULL_UP_DOWN_ENABLE_REGISTER_0, dir);
        }

        bool pullup_down_selection_impl()
        {
            return write_to_register(Registers::PULL_UP_DOWN_SELECTION_REGISTER_0, dir);
        }

        int8_t read_bytes(const uint8_t dev, const uint8_t reg, uint8_t *data, const uint8_t size)
        {
            uint8_t reg_buffer[1] = {reg};
            if (!i2c->WBlock(reg_buffer, 1))
            {
                return -1;
            }
            return i2c->R8DBlock(reg, data, size);
        }

        bool write_bytes(const uint8_t dev, const uint8_t reg, const uint8_t *data, const uint8_t size)
        {
            uint8_t buffer[size + 1];
            buffer[0] = reg;
            for (uint8_t i = 0; i < size; ++i)
            {
                buffer[i + 1] = data[i];
            }

            return i2c->WBlock(buffer, size + 1);
        }
    };
}

#endif // PI4IOE5V64XX_H