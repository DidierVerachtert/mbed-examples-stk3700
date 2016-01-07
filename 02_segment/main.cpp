/* 
    OCTA-Connect Examples
    Copyright (c) 2016 Octa-Connect Limited.
    
    File:           02_segment
    Revision:       1.0
    Description:    Display Text and Numbers on LCD 
*/

#include "EFM32_SegmentLCD.h"

/************************* Define I/O ********************************/
silabs::EFM32_SegmentLCD segment_display;

/************************* Define Timers *****************************/
LowPowerTicker refresh;

/************************* Define global variables *******************/
#define INIT_SECONDS		0
volatile uint32_t count = 0, seconds = INIT_SECONDS;

/************************* Define callback handlers ******************/
void counter(void);


/**
 * Callback for 1 second period counter
 */
void counter(void) {												
	uint32_t timerValue = ((seconds / 60) % 60) * 100 + (seconds % 60);		// Calculate timer value
	segment_display.Number(timerValue);										// Display timer value
	segment_display.Symbol(LCD_SYMBOL_COL10, seconds & 0x1);				// Toggle colon
	segment_display.ARing(count & 0x7, (count & 0x8) == 0);					// Display animated ring value
    seconds++;																// Increment uint32_t seconds
    count++;																// Increment uint32_t count
}


/**
 * main
 */
int main() {

	refresh.attach(&counter, 1.0f);											// Start generating the 1Hz timebase
	wait(0.01f); 															// Delay for serial transmission to flush buffer
	segment_display.Write("OCTA");											// Write text to LCD

	while(1)
	{
		sleep();															// Go into sleeping mode while nothing to do
	}
}

