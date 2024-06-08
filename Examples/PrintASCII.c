/*
 * Name: Timothy Marchant
 * Context: This project is for driving the SSD1306 OLED display.
 * This specific program prints all printable ASCII characters (from 33-126).
 */
#include "CONFIG.h"
#include "SSD1306_Drivers.h"
#include "I2C_Drivers.h"
#define _XTAL_FREQ 64000000
void main(void){
    //initialization.
    TRISC=0x00;
    GIE=0;
    ANSELC=0;
    ODCONC=0xff;
    LATC3=1;
    LATC4=1;
    I2C_Init();
    init_OLED();
    //send character data.
    for (unsigned char i=33;i<127;i++){
        sendcharacter(i);
    }
    //display buffer
    Display();
    //do nothing after the demostration.
    while (1){
        __nop();
    }
}
