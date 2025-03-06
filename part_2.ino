// Define LED and meter pin
const byte LED_PIN = 13;
const byte METER_PIN = A4;

void setup() {
    pinMode(LED_PIN, OUTPUT);  // Set LED pin as output
    pinMode(METER_PIN, INPUT); // Set meter pin as input

    Serial.begin(9600);        // Start serial communication

    startTimer(0.5);  // Start the timer with a frequency of 0.5Hz (2-second interval)
}

void loop() {
    // Nothing here, the LED blinks using the timer interrupt
}

// Function to start Timer1 with a given frequency
void startTimer(double timeFrequency) {
    noInterrupts(); // Stop interrupts while setting up the timer

    TCCR1A = 0; // Set Timer1 to normal mode
    TCCR1B = 0; // Clear Timer1 settings

    TCCR1B |= (1 << WGM12);  // Set CTC mode
    TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024

    // Calculate OCR1A value based on the given frequency
    OCR1A = (16000000 / (1024 * timeFrequency)) - 1;

    TIMSK1 |= (1 << OCIE1A); // Enable Timer1 compare match interrupt

    interrupts(); // Allow interrupts again
}

// Timer1 interrupt service routine (ISR) - runs at the given frequency
ISR(TIMER1_COMPA_vect) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle LED
}
