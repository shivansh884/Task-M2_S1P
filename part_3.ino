// Define LED and potentiometer pin  
const byte LED_PIN = 13;  
const byte POT_PIN = A4;  

void setup() {
  pinMode(LED_PIN, OUTPUT);  // Set LED as output  
  pinMode(POT_PIN, INPUT);   // Set potentiometer as input  

  Serial.begin(9600);  // Start serial communication  

  double initialFrequency = getPotFrequency(); // Get frequency from potentiometer  
  startTimer(initialFrequency);  // Start timer with this frequency  
}

void loop() {
  double newFrequency = getPotFrequency();  // Read new frequency  
  startTimer(newFrequency);  // Update timer with new frequency  
  delay(500);  // Short delay to avoid fast changes  
}

// Start Timer1 with a given frequency  
void startTimer(double timerFrequency) {
  noInterrupts();  // Stop interrupts  

  TCCR1A = 0;  // Normal mode  
  TCCR1B = 0;  // Clear settings  

  TCCR1B |= (1 << WGM12);  // Set CTC mode  
  TCCR1B |= (1 << CS12) | (1 << CS10);  // Set prescaler to 1024  

  OCR1A = (16000000 / (1024 * timerFrequency)) - 1;  // Calculate timer value  

  TIMSK1 |= (1 << OCIE1A);  // Enable timer interrupt  

  interrupts();  // Start interrupts  
}

// Read potentiometer and map to frequency range  
double getPotFrequency() {
  int potValue = analogRead(POT_PIN);  // Read potentiometer value  
  double frequency = map(potValue, 0, 1023, 1, 10);  // Map to 1Hz - 10Hz  

  Serial.print("Timer Frequency: ");
  Serial.print(frequency);
  Serial.println(" Hz");

  return frequency;  
}

// Timer interrupt - toggles LED  
ISR(TIMER1_COMPA_vect) {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));  // Toggle LED  
}
