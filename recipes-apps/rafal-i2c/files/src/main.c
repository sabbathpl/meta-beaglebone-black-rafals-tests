#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

int main()
{
    // Settings
    const unsigned char io_expander[2] = {0x20, 0x27}; // I2C addresses IO expanders
    const unsigned char register_offset = 0x00;        // Address of temperature register
    const char filename[] = "/dev/i2c-1";              // Location of I2C device file
  
    int file;
    unsigned char buf[10] = {0};
    int16_t temp_buf;
    float temp_c;
    
    // Open the device file for read/write
    if ((file = open(filename, O_RDWR)) < 0)
    {
        printf("Failed to open the bus.\n");
        exit(1);
    }
    
    // Change to I2C address of ...
    if (ioctl(file, I2C_SLAVE, register_offset) < 0) {
        printf("Failed to acquire bus access or talk to device.\n");
        exit(1);
    }
    
    // Start read by writing location of temperature register
    buf[0] = 0x20;
    if (write(file, buf, 1) != 1)
    {
        printf("Could not write to I2C device.\n");
        exit(1);
    }
    
    // Read temperature
    if (read(file, buf, 2) != 2)
    {
        printf("Could not read from I2C device.\n");
        exit(1);
    }
    
    // Combine received bytes to single 16-bit value
    // temp_buf = (buf[0] << 4) | (buf[1] >> 4);
    
    // // If value is negative (2s complement), pad empty 4 bits with 1s
    // if (temp_buf > 0x7FF)
    // {
    //     temp_buf |= 0xF000;
    // }
    
    // // Convert sensor reading to temperature (Celsius)
    // temp_c = temp_buf * 0.0625;
    
    // // Print results
    // printf("%.2f deg C\n", temp_c);
    
    return 0;
}