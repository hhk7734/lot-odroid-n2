#include <lot/lot.h>
#include <lot/I2c.h>
#include <iostream>

#include "mpu9250_reg.h"

lot::I2c mpu( "/dev/i2c-2" );

int main( void )
{
    lot::init();

    mpu.init();

    mpu.write_reg( MPU9250_ADDRESS, MPU9250_PWR_MGMT_1, MPU9250_H_RESET );
    lot::delay_ms( 100 );

    mpu.write_reg( MPU9250_ADDRESS, MPU9250_PWR_MGMT_1, MPU9250_CLKSEL_PLL );

    mpu.write_reg( MPU9250_ADDRESS, MPU9250_USER_CTRL, MPU9250_I2C_MST_EN );

    for( ;; )
    {
        uint8_t data[6];
        int16_t xyz[3];

        mpu.read_reg( MPU9250_ADDRESS, MPU9250_ACCEL_XOUT_H, data, 6 );

        xyz[0] = ( data[0] << 8 ) | data[1];
        xyz[1] = ( data[2] << 8 ) | data[3];
        xyz[2] = ( data[4] << 8 ) | data[5];

        std::cout << xyz[0] << "\t" << xyz[1] << "\t" << xyz[2] << std::endl;

        lot::delay_ms( 300 );
    }
}