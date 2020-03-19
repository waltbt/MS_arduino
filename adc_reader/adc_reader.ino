#include <Wire.h>

#define SLAVE_ADDRESS 0x04

int number = 0;
int state = 0;

void setup() {
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);

  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);

}

void loop() {
  delay(100);

}


void receiveData(int byteCount) {

  while (Wire.available()) {
    number = Wire.read();
//    Serial.print("data received: ");
//    Serial.println(number);
//
//    if (number == 1) {
//
//      if (state == 0) {
//        digitalWrite(13, HIGH); // set the LED on
//        state = 1;
//      }
//      else {
//        digitalWrite(13, LOW); // set the LED off
//        state = 0;
//      }
//    }
  }
}

// callback for sending data
void sendData() {
  // Read the three pins
//  int val1 = analogRead(A0);
//  int val2 = analogRead(A1);
//  int val3 = analogRead(A2);
  byte stuff[3];
  stuff[0] = 10;
  stuff[1] =12;
  stuff[2] = 45;
  Wire.beginTransmission(SLAVE_ADDRESS);
  //Wire.write(number);
  //Wire.write(45);
  Wire.send(stuff, 3);
  Wire.endTransmission(SLAVE_ADDRESS);
}
