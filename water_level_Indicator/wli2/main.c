#include <avr/io.h>

#define BUZZER_PIN PD0
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
	DDRD |= (1 << BUZZER_PIN);
}

void buzzerOn() {
	PORTD |= (1 << BUZZER_PIN);     // Set buzzer pin high
}

void buzzerOff() {
	PORTD &= ~(1 << BUZZER_PIN);    // Set buzzer pin low
}

void turnOnLED(uint8_t pin) {
	PORTC |= (1 << pin);            // Set LED pin high
}

void turnOffLED(uint8_t pin) {
	PORTC &= ~(1 << pin);           // Set LED pin low
}

int main() {
	initGPIO();                     // Initialize GPIO pins

	while (1) {
		// Read toggle switch states
		uint8_t lowSwitch = (PINB & (1 << PB0)) ? 0 : 1;
		uint8_t mediumSwitch = (PINB & (1 << PB1)) ? 0 : 1;
		uint8_t highSwitch = (PINB & (1 << PB2)) ? 0 : 1;

		// Control LEDs based on toggle switch states
		if (lowSwitch) {
			turnOnLED(LOW_LED_PIN);
			} else {
			turnOffLED(LOW_LED_PIN);
		}

		if (mediumSwitch) {
			turnOnLED(MEDIUM_LED_PIN);
			} else {
			turnOffLED(MEDIUM_LED_PIN);
		}

		if (highSwitch) {
			turnOnLED(HIGH_LED_PIN);
			buzzerOn();
			} else {
			turnOffLED(HIGH_LED_PIN);
			buzzerOff();
		}
	}

	return 0;
}
