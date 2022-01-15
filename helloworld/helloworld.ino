const int baud     = 115200;
const int delay_ms = 1000;

const String msg   = "Hello, World!";

void setup() {

  Serial.begin(baud);
  
} 

void loop() {
  
  Serial.println(msg);
  delay(delay_ms);
  
} 
