#include <xc.h>
/*I2C_Read
 *This method does the read operation for I2C
 * It takes in no parameters
 * It returns an unsigned char (the data from the slave device).
 */
unsigned char I2C_Read(void){
    //wait for buffer to be full
    while (!I2C1STAT1bits.RXBF);  
    //LATA3=1;
    unsigned char data=I2C1RXB;
    return data;
}
