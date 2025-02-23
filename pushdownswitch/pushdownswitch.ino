// Define pins
int switchPin = 2;  // Reads switch state (C1)
int ledPin = 9;     // Controls the internal LED ("-" pin)
int micPin = A6;    // Analog input for the MAX4466 microphone

void setup() {
  pinMode(switchPin, INPUT_PULLUP);  // Enable pull-up resistor for switch
  pinMode(ledPin, OUTPUT);
  //digitalWrite(ledPin, LOW);  // Ensure LED is OFF initially
  Serial.begin(115200);
}

void loop() {
  int switchState = digitalRead(switchPin);  // Read switch state
  int micValue = analogRead(micPin);         // Read microphone output

  // Switch handling
  if (switchState == LOW) {  
    digitalWrite(ledPin, LOW);  // Turn ON internal LED
    //Serial.println("Switch Pressed - LED ON");
  } else {  
    digitalWrite(ledPin, HIGH);   // Turn OFF internal LED
    //Serial.println("Switch Released - LED OFF");
  }

  // Print microphone value
  Serial.print("Microphone Output: ");
  Serial.println(micValue);

  delay(200);  // Small delay for stability
}
