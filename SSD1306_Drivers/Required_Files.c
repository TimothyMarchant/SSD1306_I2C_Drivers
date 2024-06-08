#include "I2C_Drivers.h"
#include "OLED_Commands.h"
#include <xc.h>
void ClearTextBuffer(void);
//these two are private
//send a single command
void Send_Command(unsigned char command){
    I2C_Start(OLED_Address,2,OLED_Inst);
    I2C_Write(command);
    I2C_Stop();
}
//send a single byte of data
void Send_Data(unsigned char data){
    I2C_Start(OLED_Address,2,OLED_Data);
    I2C_Write(data);
    I2C_Stop();
}
//private
//x needs to be between 0 and 127 (including 0 and 127). while y must be between 0 and 63.
void SetPosition(unsigned char x,unsigned char y){
    //if given an invalid position return.
    if (x>127||y>63){
        return;
    }
    //set position
    I2C_Start(OLED_Address,5,OLED_Inst);
    //set column address first
    I2C_Write(SetColumnAddress);
    I2C_Write(x);
    I2C_Write(127);
    //set starting line second
    //Modify the data with this starting line.  After it's been modified move the starting line back to 0 (0x40).
    I2C_Write(y|0b01000000);
    I2C_Stop();
}
void ClearDisplay(void){
    //start at top left.
    I2C_Start(OLED_Address,11,OLED_Inst);
    I2C_Write(0x2E);
    I2C_Write(0x20);
    I2C_Write(0x00);
    I2C_Write(0x21);
    I2C_Write(0x00);
    I2C_Write(127);
    I2C_Write(0x22);
    I2C_Write(0x00);
    I2C_Write(0x07);
    I2C_Write(0x40);
    I2C_Stop();
    //runs 1024 times.
    for (unsigned int i=0;i<8;i++){
        I2C_Start(OLED_Address,0x81,OLED_Data);
        for (unsigned int j=0;j<128;j++){
            //write 0 to each bit to turn them off.
            I2C_Write(0x00);
        }
        I2C_Stop();
    }
    //there is no need to reset the memory address since the address increments back to the original address.
    ClearTextBuffer();
}
//sends DisplayOn command
void DisplayTurnOn(void){
    Send_Command(DisplayON);
}
//sends DisplayOff command
void DisplayTurnOff(void){
    Send_Command(DisplayOFF);
}
/*init_OLED
 *Intializes the SSD1306 oled screen.
 * This method returns void and takes in nothing.
 */
void init_OLED(void){
    I2C_Start(OLED_Address,OLED_Init_Inst_Length+1,OLED_Inst);
    for (unsigned char i=0;i<OLED_Init_Inst_Length;i++){
        I2C_Write(OLED_Init_Inst[i]);
    }
    I2C_Stop();
    ClearDisplay();
}