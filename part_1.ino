// Define LED and meter pin
const byte LED_PIN = 13;
const byte METER_PIN = A4;

void setup() {
    pinMode(LED_PIN, OUTPUT);  // Set LED pin as output
    pinMode(METER_PIN, INPUT); // Set meter pin as input

    Serial.begin(9600);        // Start serial communication

    startTimer();  // Start the timer to make LED blink every 2 seconds
}

void loop() {
    // Nothing here, the LED blinks using the timer interrupt
}

void startTimer() {
    noInterrupts(); // Stop interrupts while setting up the timer

    TCCR1A = 0; // Set Timer1 to normal mode
    TCCR1B = 0; // Clear Timer1 settings

    TCCR1B |= (1 << WGM12);  // Set CTC (Clear Timer on Compare Match) mode
    TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024

    OCR1A = 15624; // Set the timer count for 2 seconds

    TIMSK1 |= (1 << OCIE1A); // Enable Timer1 compare match interrupt

    interrupts(); // Allow interrupts again
}

// Timer1 interrupt service routine (ISR) - runs every 2 seconds
ISR(TIMER1_COMPA_vect) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle LED
}
