//I2C drivers
#ifndef I2C_Drivers_h
#define I2C_Drivers_h
void I2C_Start(void);
void I2C_Restart(void);
void I2C_Stop(void);
unsigned char I2C_Write(unsigned char);
void I2C_ACK(void);
void I2C_Nack(void);
unsigned char I2C_Read(void);
#endif
