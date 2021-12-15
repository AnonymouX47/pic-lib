#include <stdint.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))


/* Set PWM period.
 *
 * 'res' -> Resolutiion, in number of bits (must be 2 <= res <= 10).
 * Directly proportional to the period; Inversely proportional to the frequency.
 */
#define pwm_set_period(res) PR2 = (1 << (min(max(res, 2), 10) - 2)) - 1

/* Start PWM operation */
#define pwm_start() T2CONbits.TMR2ON = 1

/* Stop PWM operation */
#define pwm_stop() T2CONbits.TMR2ON = 0

void pwm_duty_cycle (int8_t channel, uint8_t percent);


/* Set up PWM operation.
 *
 * Default Resolution is 10 bits.
 * Initial Duty Cycle is set to 0% i.e output is all LOW.
 *
 * 'prescaler' is for Timer2, can only be 1, 4 or 16
 * Inversely proportional to the frequency.
 *
 * 'channels' -> PWM channels to be used.
 * - 0x01 -> CCP1 only
 * - 0x10 -> CCP2 only
 * - 0x11 -> Both
 */
void pwm_init (int8_t channels, uint8_t prescaler)
{
    T2CONbits.T2CKPS = min(prescaler, 8) >> 2;
    if (channels & 1) {
        TRISCbits.TRISC2 = 0;
        CCP1CON = 0b1100;
        pwm_duty_cycle(0, 0);
    }
    if (channels & 2) {
        TRISCbits.TRISC1 = 0;
        CCP2CON = 0b1100;
        pwm_duty_cycle(1, 0);
    }

    pwm_set_period(10);
    pwm_stop();
}


/* Set Duty Cycle
 * 
 * 'channel' -> PWM channel for which duty cycle is changed.
 * - 0 -> CCP1
 * - 1 -> CCP2
 *
 * 'percent' -> The percentage of the period to set the duty cycle to.
 */
void pwm_duty_cycle (int8_t channel, uint8_t percent)
{
    percent = min(percent, 100);
    if (channel) {
        CCPR2L = PR2 * percent/100;
        CCP2X = T2CKPS1;
        CCP2Y = T2CKPS0;
    }
    else {
        CCPR1L = PR2 * percent/100;
        CCP1X = T2CKPS1;
        CCP1Y = T2CKPS0;
    }
}

