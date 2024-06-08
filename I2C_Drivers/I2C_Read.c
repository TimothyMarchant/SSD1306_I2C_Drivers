#include <xc.h>
void I2C_ACK(void);
void I2C_Nack(void);
unsigned char I2C_Read(void);
void I2C_Wait(void);
void I2C_ACK(void) {
    I2C_Wait();
    ACKDT = 0;
    ACKEN = 1;
}

void I2C_NACK(void) {
    I2C_Wait();
    ACKDT = 1;
    ACKEN = 1;
}
//general read method.  Need to write slave address first though.

unsigned char I2C_Read(void) {
    I2C_Wait();
    //set RCEN bit high, then wait for it to clear then read SSP1BUF register.
    RCEN = 1;
    I2C_Wait();
    return SSP1BUF;
}
