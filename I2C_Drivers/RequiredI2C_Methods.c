//These methods are required for I2C to even function
//This includes Start, Stop, Restart, and a waiting function
//we also include the write function since you must write to the address.
#include <xc.h>
void I2C_Wait(void);
void I2C_Start(void);
void I2C_Restart(void);
void I2C_Stop(void);
unsigned char I2C_Write(unsigned char);
void I2C_Wait(void) {
    /*We need to wait for the start, stop, etc to finish.
    //the datasheet says to bitwise or the third bit of SSP1CON1 with the start, stop, etc bits.
    //when this is zero, we know that said conditions are finished.*/
    while (((SSP1STAT & 0b00000100) | (SSP1CON2 & 0b00011111)));
}

void I2C_Start(void) {
    I2C_Wait();
    SEN = 1;
}

void I2C_Restart(void) {
    I2C_Wait();
    RSEN = 1;
}

void I2C_Stop(void) {
    I2C_Wait();
    PEN = 1;
}
unsigned char I2C_Write(unsigned char data) {
    //Wait then write
    I2C_Wait();
    //Write
    SSP1BUF = data;
    I2C_Wait();
    return ACKSTAT;
}