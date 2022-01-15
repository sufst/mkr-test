const int baud     = 115200;
const int delay_ms = 1000;

const String msg = "Hello, World!";

int i = 0;

void setup() {

  Serial.begin(baud);
  while(!Serial); // Wait for serial monitor to connect

  Serial.println("Setup Complete.");

} 

void loop() {
  
  Serial.println(msg + " (loop " + i + ")");
  delay(delay_ms);

  i++;  
} 
