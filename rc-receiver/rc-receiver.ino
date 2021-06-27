#include "RF24.h"

RF24 radio(9,10);

const int SERVO_PIN = 10;
const int ESC_PIN = 11;

int ReceivedMessage[1] = {000}; // Used to store value received by the NRF24L01

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 

void setup() {
  Serial.begin(9600);
    
  radio.begin(); // Start the NRF24L01
  radio.openReadingPipe(1, pipe); // Get NRF24L01 ready to receive
  radio.startListening(); // Listen to see if information received

  // ESC arming sequence
  analogWrite(ESC_PIN, 255);
  delay(500);
  analogWrite(ESC_PIN, 0);
}

void loop() {
  while (radio.available()) {
    radio.read(ReceivedMessage, 1); // Read information from the NRF24L01

    // set motor power
    analogWrite(SERVO_PIN, ReceivedMessage[0]);
    // set steering angle
    analogWrite(ESC_PIN, ReceivedMessage[1]);
  }
}
