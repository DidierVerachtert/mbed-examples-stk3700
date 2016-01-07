/* 
    OCTA-Connect Examples
    Copyright (c) 2016 Octa-Connect Limited.
    
    File:           04_serial
    Revision:       1.0
    Description:    Establish a serial connection with the device. Use a serial monitor like PuTTY to see the results (http://www.putty.org/). 
    
    More info about mbed asynchronous APIs: https://developer.mbed.org/teams/SiliconLabs/wiki/Using-the-mbed-asynchronous-APIs
*/
 
#include "mbed.h"
#include "EFM32_SegmentLCD.h"

/**************** Define constants ****************************/
#define TX_PIN          USBTX
#define RX_PIN          USBRX
#define BRATE           115200
#define LED_PIN         LED0
#define TOGGLE_SPEED    (0.5f)
#define BUFFER_LENGTH    1

/**************** Define I/O *********************************/
silabs::EFM32_SegmentLCD segment_display;

/*************** Check if platform compatible ****************/
#if DEVICE_SERIAL_ASYNCH
Serial test_connection(USBTX, USBRX);
#else
#error "Device not compatible with Example: 04_serial"
#endif

/**************** Variables **********************************/
LowPowerTicker      counter;
bool                blinking = false;
event_callback_t    serial_event;
DigitalOut          LED(LED_PIN);
uint8_t             rx_buffer[BUFFER_LENGTH + 1];

/**************** Callbacks **********************************/
void blink(void) {
    LED = !LED;																																// Toggle blink
}

/**
* Callback serial
**/
void serial(int events) {
    unsigned char i;
    if(events & SERIAL_EVENT_RX_CHARACTER_MATCH) {
        for(i = 0; i < BUFFER_LENGTH; i++) {
            if(rx_buffer[i] == 't') break;																									// 't' is received, check for buffer length
        }
        
        if(blinking) {																														// Toggle blink
            counter.detach();
            blinking = false;
        } else {
            counter.attach(blink, TOGGLE_SPEED);
            blinking = true;
        }
    } else if (events & SERIAL_EVENT_RX_COMPLETE) {
        i = BUFFER_LENGTH - 1;
    }
    
    test_connection.write(rx_buffer, i+1, 0, 0);																							// Echo string without callback																			
    test_connection.read(rx_buffer, BUFFER_LENGTH, serial_event, SERIAL_EVENT_RX_ALL, 't');													// Reset serial reception
}

void instructions(void) {
	segment_display.Write("COnnECT");
	wait(1.0f);
	segment_display.Write("A");
	wait(1.0f);
	segment_display.Write("SERIAL");
	wait(1.0f);
	segment_display.Write("MONITOR");
	wait(1.5f);	
}

/**************** Main **********************************/
int main() {
    instructions();																															// Display instructions on LCD
    segment_display.Write("OCTA");																											
    wait(0.01f);																															
    serial_event.attach(serial);																											// Set up the functionpointer object to point to the 'handler' method on this object
    
    test_connection.baud(BRATE);																											// Set baud rate
    test_connection.printf("Example: 04_serial\r\nCopyright (c) 2016 Octa-Connect Limited.\r\n\r\nSend 't' to toggle blink function\r\n");	// Display initial text
    test_connection.read(rx_buffer, BUFFER_LENGTH, serial_event, SERIAL_EVENT_RX_ALL, 't');													// Is 't' pressed?
    
    while(1) sleep();																														// Sleep while nothing to do
}