#pragma config FOSC = HS, WDTE = OFF, PWRTE = OFF, BOREN = ON, LVP = OFF, CPD = OFF, WRT = OFF, DEBUG = OFF, CP = OFF

#include <xc.h>

#define _XTAL_FREQ 50000000

#include "../i2c.h"

void __interrupt() I2C_Slave_Read_Write()
{
    if(SSPIE & SSPIF)
    {
        SSPCONbits.CKP = 0;

        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL))  // If overflow or collision
        {
            SSPSTATbits.BF = 0;
            SSPCONbits.SSPOV = 0;  // Clear the overflow flag
            SSPCONbits.WCOL = 0;  // Clear the collision bit
            SSPCONbits.CKP = 1;
        }

        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW)  // If last byte was Address + Write
        {
            SSPSTATbits.BF = 0;
            while(!SSPSTATbits.BF);
            PORTB = SSPBUF;
            SSPCONbits.CKP = 1;
        }
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW)  // If last byte was Address + Read
        {
            SSPSTATbits.BF = 0;
            SSPBUF = PORTD;
            SSPCONbits.CKP = 1;
            while(SSPSTATbits.BF);
        }

        SSPIF = 0;
    }
}


void main(void)
{
    char x = 0;

    TRISA = TRISB = TRISC = TRISD = TRISE = 0;
    // TRISD = 0xff;
    PORTA = PORTB = PORTC = PORTD = PORTE = 0;

    I2C_Slave_Init(0x55);

    while (1) {
        PORTD = PORTD ? PORTD << 1 : 1;
        __delay_ms(50);
    }
}

