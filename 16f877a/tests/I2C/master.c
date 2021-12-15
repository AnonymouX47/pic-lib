#pragma config FOSC = HS, WDTE = OFF, PWRTE = OFF, BOREN = ON, LVP = OFF, CPD = OFF, WRT = OFF, DEBUG = OFF, CP = OFF

#include <xc.h>

#define _XTAL_FREQ 50000000

#include "../i2c.h"

void main(void)
{
    TRISA = TRISC = TRISD = TRISE = 0;
    TRISB = 0xff;
    PORTA = PORTB = PORTC = PORTD = PORTE = 0;

    I2C_Master_Init(400000);

    while (1) {
        // PORTB = PORTB ? (unsigned char)PORTB >> 1 : 0x80;

        I2C_Master_Start();
        I2C_Master_Write(0x55 << 1);  // Slave address + Write
        I2C_Master_Write(PORTB);

        I2C_Master_RepeatedStart();
        I2C_Master_Write((0x55 << 1) | 1);  // Slave address + Read
        PORTD = I2C_Master_Read(0);

        I2C_Master_Stop();
        __delay_ms(10);
    }
}

