#pragma config FOSC = HS, WDTE = OFF, PWRTE = OFF, BOREN = ON, LVP = OFF, CPD = OFF, WRT = OFF, DEBUG = OFF, CP = OFF

#include <xc.h>

#define _XTAL_FREQ 20000000

#include "../../spi.h"

void main(void)
{
    char x = 0;

    TRISA = TRISC = TRISD = TRISE = 0;
    TRISB = 0xff;
    PORTA = PORTC = PORTD = PORTE = 0;

    spi_init_master(0);

    while (1) {
        x = x ? x << 1 : 1;
        __delay_ms(1);
        PORTD = ~spi_trans_recv_byte(PORTB);
        __delay_ms(100);
    }
}

