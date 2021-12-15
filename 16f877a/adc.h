// Conversion clock bits
#define FOSC_2  0b000  // FOSC/2
#define FOSC_4  0b011  // FOSC/4
#define FOSC_8  0b001  // FOSC/8
#define FOSC_16 0b101  // FOSC/16
#define FOSC_32 0b010  // FOSC/32
#define FOSC_64 0b110  // FOSC/64
#define FRC 0b011  // FRC (clock derived from the internal A/D RC oscillator)

/* Initializes the A/D module
 * clock: Conversion clock speed (use the macros provided above)
 * pcfg: A/D Port Configuration Control bits (ADCON1 regster, pg128 of the datasheet)
 */
void adc_init(char clock, char pcfg)
{
    ADCON0 = clock << 6 | 1;
    ADCON1 = 0x80 | clock << 4 | pcfg;
}


/* Performs A/D conversion using a given channel and returns the result.
 * channel: 0-7, the analog channel to be used for conversion.
 */
unsigned short adc_read(char channel)
{
    ADCON0bits.CHS = channel;  // Selects analog channel
    ADCON0bits.GO_DONE = 1;  // Starts A/D conversion
    while (ADCON0bits.GO_DONE);  // Wait till conversion is done

    return (ADRESH << 8) | ADRESL;
}
