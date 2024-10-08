//I2C drivers
#ifndef I2C_Drivers_h
#define I2C_Drivers_h
void I2C_Init(void);
void I2C_Start(unsigned char address,unsigned char numberofbytes,unsigned char firstbyte);
void I2C_Stop(void);
unsigned char I2C_Write(unsigned char);
unsigned char I2C_Read(void);
void updateI2CCNT(unsigned char update);
#endif
