// Define LED pins
int ledPin1 = 13;
int ledPin2 = 12;

// Define button pins
int buttonPin1 = 2;
int buttonPin2 = 3;

// Variable to store button states
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

void loop() {
  // Read button states
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

  // XOR behavior: Each button press swaps LED states
  if (buttonState1 == HIGH && prevButtonState1 == LOW) {
    ledState1 = !ledState1;  // Toggle LED1
    ledState2 = !ledState1;  // Ensure LED2 is the opposite
    digitalWrite(ledPin1, ledState1);
    digitalWrite(ledPin2, ledState2);

    Serial.print("Button 1 Pressed! LED1: ");
    Serial.print(ledState1);
    Serial.print(" | LED2: ");
    Serial.println(ledState2);
    
    delay(200); // Debounce delay
  }

  if (buttonState2 == HIGH && prevButtonState2 == LOW) {
    ledState2 = !ledState2;  // Toggle LED2
    ledState1 = !ledState2;  // Ensure LED1 is the opposite
    digitalWrite(ledPin1, ledState1);
    digitalWrite(ledPin2, ledState2);

    Serial.print("Button 2 Pressed! LED1: ");
    Serial.print(ledState1);
    Serial.print(" | LED2: ");
    Serial.println(ledState2);

    delay(200); // Debounce delay
  }

  // Update previous button states
  prevButtonState1 = buttonState1;
  prevButtonState2 = buttonState2;
}
