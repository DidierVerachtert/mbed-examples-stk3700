/* 
    OCTA-Connect Examples
    Copyright (c) 2016 Octa-Connect Limited.
    
    File:           01_blink
    Revision:       1.0
    Description:    Toggle LED0 and LED1 with 0,5s delay. 
*/

#include "mbed.h"

DigitalOut led_0(LED0);                                             // Initialise LED0 with function DigitalOut          
DigitalOut led_1(LED1);                                             // Initialise LED1 with function DigitalOut

LowPowerTicker low_power_ticker;                                    // Enable LowPowerTicker function, more info: bit.ly/1OBS6Hp 

void toggle_led(void) {                                             // Create toggle function
    led_0 = !led_0;
    led_1 = !led_1;
}
 
int main() {
    led_0 = 0;                                                      // LED0 off
    led_1 = 1;                                                      // LED1 on
    low_power_ticker.attach(&toggle_led, 0.5f);                     // Set LowPowerTicker to 0,5s (float) and apply on toggle_led
    while(1) {                                                      // Sleep while nothing to do
        sleep();
    }
}

