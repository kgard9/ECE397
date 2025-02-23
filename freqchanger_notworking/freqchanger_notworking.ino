#include <ELECHOUSE_CC1101_SRC_DRV.h>

#define BUTTON_PIN 2   // Momentary button input
#define LED_PIN 9      // Status LED

// Frequency options
float frequencies[] = {433.0, 868.0, 915.0};  // Frequencies in MHz
int freqIndex = 0;  // Start with the first frequency

unsigned long lastDebounceTime = 0;  // Last time the button state was changed
unsigned long debounceDelay = 200;   // Debounce delay (in milliseconds)

void setup() {
  Serial.begin(115200);
  Serial.println("Starting CC1101 test...");

  // Initialize CC1101
  if (ELECHOUSE_cc1101.getCC1101()) {
    Serial.println("CC1101 initialized successfully.");
    setFrequency(freqIndex);  // Set initial frequency
  } else {
    Serial.println("CC1101 initialization failed.");
  }

  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Enable pull-up resistor for the button
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Ensure LED is OFF initially
}

void loop() {
  static bool lastButtonState = HIGH;  // Default button state (unpressed)
  bool buttonState = digitalRead(BUTTON_PIN);  // Read button state

  // Check if the button was pressed (LOW state)
  if (buttonState == LOW && lastButtonState == HIGH) {
    unsigned long currentMillis = millis();
    
    // Only change frequency if the debounce delay has passed
    if (currentMillis - lastDebounceTime > debounceDelay) {
      lastDebounceTime = currentMillis;  // Update the debounce time
      freqIndex = (freqIndex + 1) % (sizeof(frequencies) / sizeof(frequencies[0]));  // Cycle frequencies
      setFrequency(freqIndex);
      Serial.println("Button Pressed! Changing frequency...");
    }
  }

  lastButtonState = buttonState;  // Update last button state
}

// Function to update CC1101 frequency
void setFrequency(int index) {
  float selectedFreq = frequencies[index];
  Serial.print("Setting frequency to: ");
  Serial.print(selectedFreq);
  Serial.println(" MHz");
  
  ELECHOUSE_cc1101.Init();  // Reinitialize CC1101
  ELECHOUSE_cc1101.setMHZ(selectedFreq);  // Set the frequency

  Serial.print("New Frequency: ");
  Serial.print(selectedFreq);
  Serial.println(" MHz");

  // Indicate frequency change with LED
  digitalWrite(LED_PIN, HIGH);
  delay(200);  // LED on for 200ms
  digitalWrite(LED_PIN, LOW);
}
