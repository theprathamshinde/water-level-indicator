#include <avr/io.h>

#include "lcd/lcd.h"

#define BUZZER_PIN PC7
#define LOW_LED_PIN PC0
#define MEDIUM_LED_PIN PC1
#define HIGH_LED_PIN PC2


void initGPIO() {
	// Set toggle switch pins as input
	DDRB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
	PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2); // Enable internal pull-up resistors

	// Set LED pins as output
	DDRC |= (1 << LOW_LED_PIN) | (1 << MEDIUM_LED_PIN) | (1 << HIGH_LED_PIN);

	// Set buzzer pin as output
	DDRC |= (1 << BUZZER_PIN);
}

void buzzerOn() {
	PORTC |= (1 << BUZZER_PIN);     // Set buzzer pin high
}

void buzzerOff() {
	PORTC &= ~(1 << BUZZER_PIN);    // Set buzzer pin low
}

void turnOnLED(uint8_t pin) {
	PORTC |= (1 << pin);            // Set LED pin high
}

void turnOffLED(uint8_t pin) {
	PORTC &= ~(1 << pin);           // Set LED pin low
}

void delay(unsigned long int j)
{
	for(int i=0;i<=j;i++);
}
	
	
int main()
{

	initGPIO();                
	lcd_init(LCD_DISP_ON_CURSOR);

		// Read toggle switch states
while (1){
			uint8_t lowSwitch = (PINB & (1 << PB0)) ? 0 : 1;
		uint8_t mediumSwitch = (PINB & (1 << PB1)) ? 0 : 1;
		uint8_t highSwitch = (PINB & (1 << PB2)) ? 0 : 1;

		// Control LEDs based on toggle switch states
		if (lowSwitch==1 && mediumSwitch==0 && highSwitch==0) 
		{
			turnOnLED(LOW_LED_PIN );
			
			lcd_home();
			lcd_puts("LEVEL : LOW");
		}
			else {
			turnOffLED(LOW_LED_PIN);
			delay(650000);
			lcd_clrscr();
			
		}

		if (lowSwitch==1 && mediumSwitch==1 && highSwitch==0)
			{
			turnOnLED(MEDIUM_LED_PIN);
		
			lcd_home();
			lcd_puts("LEVEL : MEDIUM");
			} 
			else 
			{
			turnOffLED(MEDIUM_LED_PIN);
			delay(650000);
			lcd_clrscr();
			
			}
			

		if (lowSwitch==1 && mediumSwitch== 1 && highSwitch==1) 
		{
			turnOnLED(HIGH_LED_PIN);
			buzzerOn();
		
			lcd_home();
			lcd_puts("LEVEL : HIGH");
			} 
			else
			 {
			turnOffLED(HIGH_LED_PIN);
			buzzerOff();
			delay(650000);
			lcd_clrscr();
	
			 }
		
		}
  
    
	
}