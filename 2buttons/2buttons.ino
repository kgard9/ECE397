// Define LED pins
int ledPin1 = 13;
int ledPin2 = 12;

// Define button pins
int buttonPin1 = 2;
int buttonPin2 = 3;

// Variables to store button states
int buttonState1 = 0;
int prevButtonState1 = 0;
int buttonState2 = 0;
int prevButtonState2 = 0;

// LED states
int ledState1 = LOW;
int ledState2 = LOW;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  Serial.begin(115200);
}

// Function to toggle LEDs with XOR logic (only one LED ON at a time)
void toggleLED(int buttonState, int &prevButtonState, int &ledStateSelf, int &ledStateOther, int ledPinSelf, int ledPinOther) {
  if (buttonState == HIGH && prevButtonState == LOW) {
    // If the other LED is ON, turn it OFF
    if (ledStateOther == HIGH) {
      ledStateOther = LOW;
      digitalWrite(ledPinOther, LOW);
    }
    
    // Always turn ON the current LED
    ledStateSelf = HIGH;
    digitalWrite(ledPinSelf, HIGH);

    // Print state to Serial Monitor
    Serial.print("Button Pressed! LED ");
    Serial.print(ledPinSelf == 13 ? "1" : "2");
    Serial.print(" ON, LED ");
    Serial.print(ledPinOther == 13 ? "1" : "2");
    Serial.println(" OFF.");

    delay(200); // Debounce delay
  }
}

void loop() {
  // Read button states
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

  // Button 1 turns ON LED 1 and turns OFF LED 2 if needed
  toggleLED(buttonState1, prevButtonState1, ledState1, ledState2, ledPin1, ledPin2);
  
  // Button 2 turns ON LED 2 and turns OFF LED 1 if needed
  toggleLED(buttonState2, prevButtonState2, ledState2, ledState1, ledPin2, ledPin1);

  // Update previous button states
  prevButtonState1 = buttonState1;
  prevButtonState2 = buttonState2;
}
