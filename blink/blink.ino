const int baud           = 115200;
const int blink_delay_ms = 1000;

/* On MKR Zero, LED_BUILTIN = 32 */
const int blinkPin = LED_BUILTIN; // change this to pin number if not using onboard LED

void setup() {
  
  Serial.begin(baud);
  
  pinMode(blinkPin, OUTPUT);
  
}

void loop() {
  
  digitalWrite(blinkPin, HIGH);
  Serial.println("LED On");
  delay(blink_delay_ms);
  
  digitalWrite(blinkPin, LOW);
  Serial.println("LED Off");
  delay(blink_delay_ms);
  
}
