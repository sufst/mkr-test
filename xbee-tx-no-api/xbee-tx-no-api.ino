
/* Cart-side XBee Address
    HIGH: 0x0013A200
    LOW:  0x41E758C2
*/

/* XBee serial baud-rate */
const int xbee_baud = 115200; 

/* On MKR Zero, LED_BUILTIN = 32 */
const int ledPin = LED_BUILTIN;

/* example data to be sent to cart-side XBee */
uint8_t payload[] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

void setup() {
  
  Serial.begin(xbee_baud);

  pinMode(LED_BUILTIN, OUTPUT);  

}

uint delay_ms = 1000;

void loop() {   
  digitalWrite(LED_BUILTIN, HIGH); // flash led when transmitting

  for (int i=0; i<6; ++i) 
    Serial.print(payload[i]);

  digitalWrite(LED_BUILTIN, LOW);
  delay(delay_ms);                  
}