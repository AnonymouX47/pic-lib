/* 
 * File:   keypad.h
 * Author: Lekzy
 *
 * Created on 26 March 2020, 02:11
 */

unsigned char scan(unsigned char keys[4][4]){    
    unsigned char key = 10;

    __delay_ms(5);

    PORTB = 0B11110111;
    __delay_ms(5);
    if(!RB7){
        __delay_ms(5);
        while(!RB7){
            key = keys[0][0];
        }
        __delay_ms(5);
    }
    else if(!RB6){
        __delay_ms(5);
        while(!RB6){
            key = keys[1][0];
        }
        __delay_ms(5);
    }
    else if(!RB5){
        __delay_ms(5);
        while(!RB5){
            key = keys[2][0];
        }
        __delay_ms(5);
    }
    else if(!RB4){
        __delay_ms(5);
        while(!RB4){
            key = keys[3][0];
        }
        __delay_ms(5);
    }

    __delay_ms(5);

    PORTB = 0B11111011;
    __delay_ms(5);
    if(!RB7){
        __delay_ms(5);
        while(!RB7){
            key = keys[0][1];
        }
        __delay_ms(5);
    }
    else if(!RB6){
        __delay_ms(5);
        while(!RB6){
            key = keys[1][1];
        }
        __delay_ms(5);
    }
    else if(!RB5){
        __delay_ms(5);
        while(!RB5){
            key = keys[2][1];
        }
        __delay_ms(5);
    }
    else if(!RB4){
        __delay_ms(5);
        while(!RB4){
            key = keys[3][1];
        }
        __delay_ms(5);
    }

    __delay_ms(5);

    PORTB = 0B11111101;
    __delay_ms(5);
    if(!RB7){
        __delay_ms(5);
        while(!RB7){
            key = keys[0][2];
        }
        __delay_ms(5);
    }
    else if(!RB6){
        __delay_ms(5);
        while(!RB6){
            key = keys[1][2];
        }
        __delay_ms(5);
    }
    else if(!RB5){
        __delay_ms(5);
        while(!RB5){
            key = keys[2][2];
        }
        __delay_ms(5);
    }
    else if(!RB4){
        __delay_ms(5);
        while(!RB4){
            key = keys[3][2];
        }
        __delay_ms(5);
    }

    __delay_ms(5);

    PORTB = 0B11111110;
    __delay_ms(5);
    if(!RB7){
        __delay_ms(5);
        while(!RB7){
            key = keys[0][3];
        }
        __delay_ms(5);
    }
    else if(!RB6){
        __delay_ms(5);
        while(!RB6){
            key = keys[1][3];
        }
        __delay_ms(5);
    }
    else if(!RB5){
        __delay_ms(5);
        while(!RB5){
            key = keys[2][3];
        }
        __delay_ms(5);
    }
    else if(!RB4){
        __delay_ms(5);
        while(!RB4){
            key = keys[3][3];
        }
        __delay_ms(5);
    }
    
    return key;
}
