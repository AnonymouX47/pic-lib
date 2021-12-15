#pragma config FOSC = HS, WDTE = OFF, PWRTE = OFF, BOREN = ON, LVP = OFF, CPD = OFF, WRT = OFF, DEBUG = OFF, CP = OFF

#include <xc.h>

#define _XTAL_FREQ 20000000

#include "../../spi.h"

void main(void)
{
    char x = 0;

    TRISA = TRISB = TRISC = TRISD = TRISE = 0;
    // TRISD = 0xff;
    PORTA = PORTB = PORTC = PORTD = PORTE = 0;

    spi_init_slave();

    while (1) {
        PORTD = x = x ? x << 1 : 1;
        PORTB = ~spi_trans_recv_byte(x);
        __delay_ms(100);
    }
}

