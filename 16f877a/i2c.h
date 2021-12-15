/* Originally from https://electrosome.com/i2c-pic-microcontroller-mplab-xc8/
 * Modified and Improved
 */

#ifndef I2C_H
#define I2C_H

#define GENERAL_CALL 0x00

void I2C_Master_Init(const unsigned long speed)
{
    TRISC3 = TRISC4 = 1;  //Setting as input as given in datasheet
    SSPCON = 0b00101000;  //SSP Module as Master
    SSPCON2 = 0;
    SSPADD = (_XTAL_FREQ / (4 * speed)) - 1;  //Setting Clock Speed
    SSPSTAT = 0;
}


void I2C_Master_Wait()
{
    while ((SSPSTATbits.R_nW) || (SSPCON2 & 0x1F));  // The bus is not idle
}


void I2C_Master_Start()
{
    I2C_Master_Wait();
    SEN = 1;  //Initiate start condition
}


void I2C_Master_RepeatedStart()
{
    I2C_Master_Wait();
    RSEN = 1;  //Initiate repeated start condition
}


void I2C_Master_Stop()
{
    I2C_Master_Wait();
    PEN = 1;  //Initiate stop condition
}


void I2C_Master_Write(unsigned char data)
{
    I2C_Master_Wait();
    SSPBUF = data;  //Write data to SSPBUF
    while(SSPSTATbits.BF);  // Transmit in progress
}


/* ack: If 0, NACK is signaled, otherwise ACK is signaled */
unsigned char I2C_Master_Read(char ack)
{
    unsigned char temp;
    I2C_Master_Wait();
    RCEN = 1;
    I2C_Master_Wait();
    temp = SSPBUF;  //Read data from SSPBUF
    I2C_Master_Wait();
    ACKDT = !ack;  //Acknowledge bit
    ACKEN = 1;  //Acknowledge sequence
    return temp;
}


/* Slave Functions */

void I2C_Slave_Init(short address)
{
    SSPSTAT = 0x80;
    SSPADD = address << 1;  //Setting address
    SSPCON = 0x36;  //As a slave device
    SSPCON2 = 0x01;
    TRISC3 = TRISC4 = 1;  //Setting as input as given in datasheet
    GIE = 1;  //Global interrupt enable
    PEIE = 1;  //Peripheral interrupt enable
    SSPIF = 0;  //Clear interrupt flag
    SSPIE = 1;  //Synchronous serial port interrupt enable
}


/*
char i2c_trans, i2c_recv;

void __interrupt() I2C_Slave_Read_Write()
{
    if (SSPIE && SSPIF)
    {
        SSPCONbits.CKP = 0;

        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL))  // If overflow or collision
        {
            SSPSTATbits.BF = 0;
            SSPCONbits.SSPOV = 0;  // Clear the overflow flag
            SSPCONbits.WCOL = 0;  // Clear the collision bit
            SSPCONbits.CKP = 1;
        }

        // Receive
        if (!SSPSTATbits.D_nA && !SSPSTATbits.R_nW)  // If last byte was Address + Write
        {
            SSPSTATbits.BF = 0;
            while(!SSPSTATbits.BF);
            i2c_recv = SSPBUF;
            SSPCONbits.CKP = 1;
        }
        // Transmit
        else if (!SSPSTATbits.D_nA && SSPSTATbits.R_nW)  // If last byte was Address + Read
        {
            SSPSTATbits.BF = 0;
            SSPBUF = i2c_trans;
            SSPCONbits.CKP = 1;
            while(SSPSTATbits.BF);  // Transmit in progress
        }

        SSPIF = 0;
    }
}
*/

#endif
