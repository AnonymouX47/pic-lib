// To use this library, you must include the I2C library before it, within the same translation unit.
// You must also initialize the microcontroller as an I2C master device before calling any of the functions or macros provided in here.

#ifdef I2C_H

#ifndef MCP4725_H
#define MCP4725_H

// General call commands
#define GENERAL_RESET 0x06
#define GENERAL_WAKE_UP 0x09

// Write commands
#define FAST_MODE 0b00
#define REG_ONLY 0b010
#define REG_EEPROM 0b011

// Power-down bits
#define NORMAL_MODE 0b00
#define GROUND_1k 0b01
#define GROUND_100k 0b10
#define GROUND_500k 0b11


#define mcp4725_write_data(a0, data) mcp4725_write(a0, NORMAL_MODE, data, 0)

#define mcp4725_power_down(a0) mcp4725_write(a0, GROUND_1k, mcp4725_read(a0).data, 0)

#define mcp4725_power_up(a0) mcp4725_write(a0, NORMAL_MODE, mcp4725_read(a0).data, 0)

#define mcp4725_busy(a0) !mcp4725_read(a0).RDY_nBSY


struct mcp4725_data {
    unsigned RDY_nBSY : 1;
    unsigned POR : 1;
    unsigned PD1 : 1;
    unsigned PD0 : 1;
    unsigned data;
};

struct mcp4725_data mcp4725_read(char a0);


/* Write to DAC register and/or EEPROM
 * power: If 0, device is powered-down. Otherwise, the device is powered-up
 * value: 12-bit DAC input data
 * save: If not 0, also write to EEPROM
 */
void mcp4725_write(char a0, char power, unsigned short value, char save)
{
    while (mcp4725_busy(a0));
    I2C_Master_Start();
    // 7-bit Address (0b11000000 | a0) + Write Bit
    I2C_Master_Write(0xc0 | (!!a0 << 1));
    // Write Command + Power Down Bits
    I2C_Master_Write(((save ? REG_EEPROM : REG_ONLY) << 5) | ((power & 0x03) << 1));
    // DAC input
    I2C_Master_Write(value >> 4);
    I2C_Master_Write(value << 4);
    I2C_Master_Stop();
}


/* Read DAC register content */
struct mcp4725_data mcp4725_read(char a0)
{
    __uint24 data;

    I2C_Master_Start();
    // 7-bit Address (0b11000000 | a0) + Read Bit
    I2C_Master_Write(0xc1 | (!!a0 << 1));
    data = I2C_Master_Read(1);
    data = (data << 8) | I2C_Master_Read(1);
    data = (data << 8) | I2C_Master_Read(0);
    I2C_Master_Stop();

    return (struct mcp4725_data){
        data >> 23,
        (data >> 22) & 1,
        (data >> 18) & 1,
        (data >> 17) & 1,
        (data >> 4) & 0xfff,
    };
}


/* reset: If 0, the device is restored to it's last saved state (from it's EEPROM),
 * otherwise, the DAC input is set to 0 in Normal Mode.
 */
void mcp4725_init(char a0, char reset)
{
    //while (mcp4725_read(a0).POR);  // Power-On-Reset period
    if (reset) mcp4725_write(a0, NORMAL_MODE, 0, 0);  // Power-up with 0V output
}


/* Save current DAC register content to EEPROM */
void mcp4725_save_state(char a0)
{
    struct mcp4725_data state = mcp4725_read(a0);
    mcp4725_write(a0, (state.PD1 << 1) | state.PD0, state.data, 1);
    while (mcp4725_busy(a0));
}

#endif

#endif
