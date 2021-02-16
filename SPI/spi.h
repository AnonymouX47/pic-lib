#ifndef SPI_H
#define SPI_H

/* The following SPI parameters are fixed in this library:
 * - Clock Polarity (CKP) = 0
 * - Clock Egde (CKE) = 0  # Inverted CPHA (Clock Phase)
 * - Input Sample Phase (SMP) = 0
 */


/* Initialize SPI to master mode.
 *
 * 'clock': Determines the clock to be used. Valid values are:
 * - 0 = SPI Master mode, clock = F OSC /4
 * - 1 = SPI Master mode, clock = F OSC /16
 * - 2 = SPI Master mode, clock = F OSC /64
 * - 3 = SPI Master mode, clock = TMR2 output/2
 * For any other value, 0 will be used.
 */
void spi_init_master(unsigned char clock)
{
    // Set I/O state of SPI pins without affecting other pins.
    TRISC = (TRISC & 0b11000111) | 0b00010000;
    SSPCON = 0 | (clock <= 3 ? clock : 0);
    SSPSTAT = 0;
    SSPBUF = 0;
    SSPCONbits.SSPEN = 1;
}


/* Initializes SPI to slave mode.
 *
 * NOTE: SS (Slave Select) is always enabled.
 */
void spi_init_slave(void)
{
    // Set I/O state of SPI pins without affecting other pins.
    TRISC = (TRISC & 0b11000111) | 0b00011000;
    TRISAbits.TRISA5 = 1;
    SSPCON = 0x04;
    SSPSTAT = 0;
    SSPBUF = 0;
    SSPCONbits.SSPEN = 1;
}


/* Transmit a byte */
void spi_trans_byte(char byte)
{
    SSPBUF = byte;
    while (!SSPSTATbits.BF);
}


/* Receive next byte */
char spi_recv_byte()
{
    SSPBUF = 0;
    while (!SSPSTATbits.BF);
    return SSPBUF;
}


/* Transmit a byte and return received byte */
char spi_trans_recv_byte(char byte)
{
    SSPBUF = byte;
    while (!SSPSTATbits.BF);

    return SSPBUF;
}


/* Read current byte */
char spi_read_byte()
{
    return SSPBUF;
}


#endif

