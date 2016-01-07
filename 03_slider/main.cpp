/* 
    OCTA-Connect Examples
    Copyright (c) 2016 Octa-Connect Limited.
    
    File:           03_slider
    Revision:       1.0
    Description:    Dislay the value of the capacitive slider on LCD
*/

#include "EFM32_SegmentLCD.h"
#include "EFM32_CapSenseSlider.h"

/************************* Define I/O ********************************/
silabs::EFM32_SegmentLCD segment_display;
silabs::EFM32_CapSenseSlider slider;

/************************* Define callback handlers ******************/
void touchCallback(void);
void slideCallback(void);
void instructions(void);

/**
 * Callback for touching/untouching the capacitive slider
 */
void touchCallback(void) {
    if(!slider.isTouched()) {
        segment_display.Write("OCTA");
    }
}

/**
 * Callback for sliding the capacitive slider
 */
void slideCallback(void) {
    segment_display.LowerNumber(slider.get_position());
}

/**
 * Callback for sliding the instructions
 */
void instructions(void) {
	// Display instructions
	segment_display.Write("TOUCH");
	wait(1.0f);
	segment_display.Write("THE");
	wait(1.0f);	
	segment_display.Write("SLIdER");
	wait(1.5f);		
}


/**
 * main
 */
int main() {
	
	instructions();
	
	// Enable capacitive slider
	slider.start();
	slider.attach_touch(touchCallback);
	slider.attach_untouch(touchCallback);
	slider.attach_slide(-1, slideCallback);
	wait(0.01f); 															// Delay for serial transmission to flush buffer
	
	segment_display.Write("OCTA");											// Write text to LCD

	while(1)
	{
		sleep();															// Go into sleeping mode while nothing to do
	}
}

