#include <xc.h>
void I2C_Start(unsigned char address,unsigned char numberofbytes,unsigned char firstbyte){
    //wait for bus to be free.
    while (!I2C1STAT0bits.BFRE);
    //__delay_ms(250);
    //load the number of bytes to be transmitted.
    
    I2C1CNT=numberofbytes;
    I2C1ADB1=address;
    //if zero it's a write not a read.
    if ((address&0b00000001)==0){
    while (!I2C1STAT1bits.TXBE);
    I2C1TXB=firstbyte;
    }
    //issue stop once total number of bytes are transmitted.
    I2C1CON0bits.RSEN=0;
    //restart upon sending total number of bytes.
    I2C1CON0bits.S=1;
    //Wait for start condition to finish.
    while (!I2C1STAT0bits.MMA);
}
//wait for stop before doing anything else.
void I2C_Stop(void){
    while (I2C1STAT0bits.MMA);
}
/*I2C_Write
 *This method does a write operation for I2C.
 * It takes in an unsigned char for the data to be sent.
 * It also returns an unsigned char in particular it returns the acknoledge bit.
 */
unsigned char I2C_Write(unsigned char data){
    //I2C_Wait();
    //wait for buffer to empty.
    while (!I2C1STAT1bits.TXBE);
    I2C1TXB=data;
    
    return I2C1CON1bits.ACKSTAT;
}
/*I2C_Init
 *This method does all required initalizing for I2C.  This initalizes the I2C 1 registers.
 *This method takes in nothing and returns void.
 */
void I2C_Init(void){
    RC3I2C=0b01000001;
    RC4I2C=0b01000001;
    I2C1SCLPPS=0b00010011;
    I2C1SDAPPS=0b00010100;
    RC3PPS=0b00100001;
    RC4PPS=0b00100010;
    I2C1CON0=0b00000100;
    I2C1CON1=0x80;
    //ABD=1 means the address registers are ignored.
    I2C1CON2=0x21;
    I2C1STAT0=0;
    I2C1STAT1=0;
    I2C1ERR=0;
    I2C1CLK=0x03;
    I2C1PIE=0;
    //errata sheet says to do this before enabling.  
    I2C1CON0bits.EN=1;
    //this will take 6.5> micro seconds to finish at 64 MHz
    for (unsigned char i=0;i<100;i++){
    __nop();
    };
    I2C1PIR=0;
}
void updateI2CCNT(unsigned char update){
    //do not update if this causes an overflow.
    if (I2C1CNT+update<I2C1CNT){
        return;
    }
    I2C1CNT+=update;
}