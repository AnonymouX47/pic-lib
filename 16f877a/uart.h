#include <stdio.h>

char UART_init(unsigned int baudrate)
{
    // Converted 'baudrate' to `long` cos `baudrate * 64` can be larger than `int`,
    // in which case, the result is wrongly truncated.
    // Did not declare 'baudrate' as `long` for the sake of space.
    unsigned int x = (_XTAL_FREQ - (long)baudrate*64) / ((long)baudrate*64);

    if (x > 255) {
        x = (_XTAL_FREQ - baudrate*16)/(baudrate*16);
        BRGH = 1;
    }

    if (x < 256) {
      SPBRG = x;
      SYNC = 0;
      SPEN = TRISC7 = TRISC6 = CREN = TXEN = 1;
      return 1;
    }

    return 0;
}

char UART_tx_empty()
{
    return TRMT;
}

char UART_data_ready()
{
    return RCIF;
}

char UART_read()
{
    if (OERR) {
        CREN = 0;
        CREN = 1;
    }
    while (!RCIF);
    return RCREG;
}

void UART_read_text(char *output, unsigned int length)
{
    while (length--) *output++ = UART_read();
}

void UART_write(char data)
{
    while (!TRMT);
    TXREG = data;
}

void UART_write_text(char *text)
{
    while (*text) UART_write(*text++);
}

void UART_write_int(long n)
{
    char s[11] = {0}, *p = s + sizeof(s) - 1;

    if (n < 0) {
        UART_write('-');
        n = -n;
    }

    do *--p = '0' + (unsigned long)n % 10;
    while (p > s && (n = (unsigned long)n / 10));
    UART_write_text(p);
}
