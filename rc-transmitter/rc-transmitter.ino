#include "RF24.h" // https://nrf24.github.io/RF24/

#define PIN_ANALOG_X 0
#define PIN_ANALOG_Y 1

RF24 radio(9, 10); 

int SentMessage[1] = {000}; // Used to store value before being sent through the NRF24L01

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 

void setup() { 
  Serial.begin(9600);

  radio.begin(); // Start the NRF24L01
  radio.openWritingPipe(pipe); // Get NRF24L01 ready to transmit
}

void loop() {
  // Print x axis values
  Serial.print("x: ");
  Serial.println(analogRead(PIN_ANALOG_X));
  SentMessage[0] = analogRead(PIN_ANALOG_X);
  radio.write(SentMessage, 1); // Send value through NRF24L01

  // Print y axis values
  Serial.print("y: ");
  Serial.println(analogRead(PIN_ANALOG_Y));
  SentMessage[1] = analogRead(PIN_ANALOG_Y);
  radio.write(SentMessage, 1);
 
  delay(500);
}
