//globals to keep track of current and prev temperature
float prevTempRead = 0; 
float newTempRead = 0;
void setup() {
 
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0, INPUT);
  // Configure Timer1  for 250ms blinking
  TCCR1A = 0; // Timer1 Control Register A
  TCCR1B = (1 << CS12) | (1 << WGM12); // Set Timer1 prescaler to 256 and enable CTC mode
  OCR1A = 31250; // Set the default compare value to achieve 0.5s (approx)
  TIMSK1 = (1 << OCIE1A); // Enable Timer1 compare match interrupt
  Serial.begin(9600);

}

void loop() {
  //read temperature
  newTempRead = (analogRead(A0)*(5000/1024))/10   ;   //convert ADC reading to mV and then divide by 10 to get Celcuis
  Serial.println(newTempRead);
  //check if we dropped below 30 
  if(prevTempRead >= 30 && newTempRead < 30){
    OCR1A = 15625; // Set the compare value to achieve 0.25s;
  }
  //check if we crossed above 30 
  else if (prevTempRead <= 30 && newTempRead > 30){
    OCR1A = 31250; // Set the compare value to achieve 0.5s;
  }
  
  prevTempRead = newTempRead; //store this reading as prev reading

}

// Timer1 compare match interrupt service routine
ISR(TIMER1_COMPA_vect) {
  // Toggle the onboard LED
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
