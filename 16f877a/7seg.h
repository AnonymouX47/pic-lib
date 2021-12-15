/* 
 * File:   7seg.h
 * Author: Lekzy
 *
 * Created on 04 May 2020, 18:26
 */


// Common Cathode
unsigned char disp_cc(char digit){
    unsigned char PORT;
    switch(digit){
        case 0: PORT = 0B00111111;
        break;
        case 1: PORT = 0B00000110;
        break;
        case 2: PORT = 0B01011011;
        break;
        case 3: PORT = 0B01001111;
        break;
        case 4: PORT = 0B01100110;
        break;
        case 5: PORT = 0B01101101;
        break;
        case 6: PORT = 0B01111101;
        break;
        case 7: PORT = 0B00000111;
        break;
        case 8: PORT = 0B01111111;
        break;
        case 9: PORT = 0B01101111;
        break;
        case '.': PORT = 0B10000000;
        break;
        case 'A': PORT = 0B01110111;
        break;
        case 'b': PORT = 0B01111100;
        break;
        case 'E': PORT = 0B01111001;
        break;
        case 'H': PORT = 0B01110110;
        break;
        case 'L': PORT = 0B00111000;
        break;
        case 'T': PORT = 0B00110001;
        break;
        default: PORT = 0B00000000;
        break;
    }
    return PORT;
}


// Common Anode
unsigned char disp_ca(char digit){
    unsigned char PORT;
    switch(digit){
        case 0: PORT = 0B11000000;
        break;
        case 1: PORT = 0B11111001;
        break;
        case 2: PORT = 0B10100100;
        break;
        case 3: PORT = 0B10110000;
        break;
        case 4: PORT = 0B10011001;
        break;
        case 5: PORT = 0B10010010;
        break;
        case 6: PORT = 0B10000010;
        break;
        case 7: PORT = 0B11111000;
        break;
        case 8: PORT = 0B10000000;
        break;
        case 9: PORT = 0B10010000;
        break;
        case '.': PORT = 0B01111111;
        break;
        case 'A': PORT = ~0B01110111;
        break;
        case 'b': PORT = ~0B01111100;
        break;
        case 'E': PORT = ~0B01111001;
        break;
        case 'H': PORT = ~0B01110110;
        break;
        case 'L': PORT = ~0B00111000;
        break;
        case 'T': PORT = ~0B00110001;
        break;
        default: PORT = 0B11111111;
        break;
    }
    return PORT;
}
