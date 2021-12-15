/* 
 * File:   eeprom.h
 * Author: Lekzy
 *
 * Created on 26 March 2020, 01:07
 */

//#include <xc.h>

void delay(){
    __delay_us(500);
}

void data_init(){
    PIR2bits.EEIF = 0;
    EECON1bits.EEPGD = 0;
    EECON1bits.WREN = 0;
}

unsigned char data_read(unsigned char addr){
    EEADR = addr;
    EECON1bits.RD = 1;
    while(EECON1bits.RD);
    delay();
    return EEDATA;
}

void data_write(unsigned char addr, unsigned char data){
    if(!EEIF || EECON1bits.WR){
        while(EECON1bits.WR);
    }
    delay();
    EEIF = 0;
    EEADR = addr;
    EEDATA = data;
    EECON1bits.WREN = 1;
    char prev_gie = GIE;  // Store Interrupt state
    INTCONbits.GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    GIE = prev_gie;  // Restore Interrupt state
    EECON1bits.WREN = 0;
    while(EECON1bits.WR || !EEIF);
    return;
}

// Passing in an array (declared outside) as a parameter modifies that array outside.
void cont_data_read(char read_arr[], unsigned char start, unsigned char len,  char end_char){
    unsigned char i;
    for(i = 0; i < len; i++){
        read_arr[i] = data_read(start + i);
        delay();
    }
    read_arr[i] = end_char;
}

void cont_data_write(unsigned char start, char arr[], char end_char){
    unsigned char i, len = 0;
//    len = sizeof(arr)/sizeof(*arr);
    while(arr[len] != end_char) len++;
    for(i = 0; i < len; i++){
        data_write(start + i, arr[i]);
        delay();
    }
}

void data_clear(unsigned char start, unsigned char end){
    unsigned char addr;
    if(end == 0xFF){
        end = 0xFE;
        data_write(0xFF, 0xFF);
    }
    for(addr = start; addr <= end; addr++){
        data_write(addr, 0xFF);
        delay();
    }
}