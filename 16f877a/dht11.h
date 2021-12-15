#include <stdint.h>

#define DATA_PIN RD0
#define DATA_PIN_STATE TRISD0

/* Read and return 32-bit raw data from DHT11
 *
 * If the data is incorrect, returns 0 (Humidity == 0 == Temp is unlikely).
 */
uint32_t _dht11_read_data(void)
{
    uint32_t data;
    uint8_t parity, sum = 0, i, j;

    // Start signal
    DATA_PIN_STATE = 0;
    DATA_PIN = 0;
    __delay_ms(20);
    DATA_PIN = 1;

    // DHT11 Response
    DATA_PIN_STATE = 1;
    while(DATA_PIN);
    while(!DATA_PIN);  // Response Signal
    while(DATA_PIN);  // Data ready

    // Read data
    for (i = 4; i--;) {
        for (j = 8; j--;) {
            while (!DATA_PIN);  // 50us LOW pulse
            __delay_us(30);  // 0-bit has 26us-28us high-time, while 1-bit has 70us high-time.
            data = (data << 1) | DATA_PIN;  // Current state of DATA line indicates bit value.
            while (DATA_PIN);  // Rest of HIGH pulse (if any)
        }
        // Add last byte of data to sum that'll be compared with the parity
        sum += data & 0xFF;
    }

    // Read parity byte
    for (i = 8; i--;) {
        while(!DATA_PIN);  // 50us LOW pulse
        __delay_us(30);  // 0-bit has 26us-28us high-time, while 1-bit has 70us high-time.
        parity = (parity << 1) | DATA_PIN;  // Current state of DATA line indicates bit value.
	while (DATA_PIN);  // Rest of HIGH pulse (if any)
    }

    __delay_ms(980);  // Rest of 1sec sampling interval
    return data;  // sum == parity ? data : 0;
}


/* NOTE: It is adviced to allow a 5sec minimum interval between successive reads
 * to get accurate data
 */


void dht11_init(void)
{
    __delay_ms(1000);
    _dht11_read_data();
}


uint8_t dht11_read_temp(void)
{
    uint32_t data;
    // while (!(data = _dht11_read_data())) UART_write_text("Again\r\n");
    data = _dht11_read_data();
    return (data >> 8) & 0xFF;
}

