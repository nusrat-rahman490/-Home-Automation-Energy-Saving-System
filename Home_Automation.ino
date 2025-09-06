
int pirPin = 2;      // PIR sensor output pin connected to digital pin 2
int ledPin = 13;     // LED connected to digital pin 13
int pirState = LOW;  // Current state of PIR sensor
int val = 0;         // Variable for reading PIR pin status

unsigned long lastMotionTime = 0;   // Tracks last motion time
unsigned long delayTime = 5000;     // Delay (ms) before turning LED off (5 seconds)

void setup() {
  pinMode(ledPin, OUTPUT);   
  pinMode(pirPin, INPUT);    
  Serial.begin(9600);        // For debugging output
}

void loop() {
  val = digitalRead(pirPin);   // Read PIR sensor state

  if (val == HIGH) {           // If motion detected
    digitalWrite(ledPin, HIGH);  // Turn LED ON
    if (pirState == LOW) {
      Serial.println("Motion detected! Lights ON");
      pirState = HIGH;          // Update state
    }
    lastMotionTime = millis();  // Update motion timer
  } 
  else {
    // If no motion for delayTime -> turn off LED
    if (millis() - lastMotionTime > delayTime) {
      digitalWrite(ledPin, LOW);
      if (pirState == HIGH) {
        Serial.println("No motion. Lights OFF");
        pirState = LOW;        // Update state
      }
    }
  }
}
