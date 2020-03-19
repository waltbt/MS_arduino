
#include "Adafruit_VL6180X.h"
#include <Wire.h>  //Allows it to talk to I2C

//Adafruit_VL6180X vl[3] = {Adafruit_VL6180X(),Adafruit_VL6180X(),Adafruit_VL6180X()};

Adafruit_VL6180X vl = Adafruit_VL6180X();

//for(int i=0;i<3;i++){
//  Adafruit_VL6180X vl[i] = Adafruit_VL6180X();
//}



void tcaselect(uint8_t i);

// Defines

#define TCAADDR 0x70 //Adress for the multiplexor


void setup() {
  Serial.begin(115200);
   while (!Serial) {
    delay(1);
  }
  Wire.begin();
  int i = 0;
//for(int i=0;i<3;i++){
  //vl[i].begin();
  tcaselect(i);
    Serial.println("Adafruit VL6180x test!");
  while (! vl.begin()) {
    Serial.println("Failed to find sensor");
    //while (1);
  }
  Serial.println("Sensor found!");
//}

}


void loop(){
 int i = 0;
    //for(int i=0;i<3;i++){
     // tcaselect(i);
      Serial.print("Sensor: "); Serial.println(i);
    //float lux = vl.readLux(VL6180X_ALS_GAIN_5);

  //Serial.print("Lux: "); Serial.println(lux);
  tcaselect(i);
  uint8_t range = vl.readRange();
  uint8_t status = vl.readRangeStatus();
  Serial.print(status);

  if (status == VL6180X_ERROR_NONE) {
    Serial.print("Range: "); Serial.println(range);
  }

  // Some error occurred, print it out!
  
  if  ((status >= VL6180X_ERROR_SYSERR_1) && (status <= VL6180X_ERROR_SYSERR_5)) {
    Serial.println("System error");
  }
  else if (status == VL6180X_ERROR_ECEFAIL) {
    Serial.println("ECE failure");
  }
  else if (status == VL6180X_ERROR_NOCONVERGE) {
    Serial.println("No convergence");
  }
  else if (status == VL6180X_ERROR_RANGEIGNORE) {
    Serial.println("Ignoring range");
  }
  else if (status == VL6180X_ERROR_SNR) {
    Serial.println("Signal/Noise error");
  }
  else if (status == VL6180X_ERROR_RAWUFLOW) {
    Serial.println("Raw reading underflow");
  }
  else if (status == VL6180X_ERROR_RAWOFLOW) {
    Serial.println("Raw reading overflow");
  }
  else if (status == VL6180X_ERROR_RANGEUFLOW) {
    Serial.println("Range reading underflow");
  }
  else if (status == VL6180X_ERROR_RANGEOFLOW) {
    Serial.println("Range reading overflow");
  }
  delay(10);
}

/*
 * Use the TCA9548A I2C multiplexor to shift between sensors
 */
void tcaselect(uint8_t i){
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 <<i );
  Wire.endTransmission(TCAADDR);
  Serial.println("Hello");
  delay(50);
}

 // tcaselect(1);
 // Adafruit_VL6180X vl1 = Adafruit_VL6180X();
//  tcaselect(1);
//  Adafruit_VL6180X vl2 = Adafruit_VL6180X();
//  tcaselect(2);
//  Adafruit_VL6180X vl3 = Adafruit_VL6180X();















//void setup()
//{
//  Wire.begin(); //Initialize Wire
//  Serial.begin(115200);
//
//}





//void loop()
//{
//  
//    
// tcaselect(2);
// Adafruit_VL6180X vl1 = Adafruit_VL6180X();
// vl1.begin();
// uint8_t range = vl1.readRange();
//  Serial.print("Range: "); Serial.println(range);
//// TOF_sensor_msg.lux_reading[0] = vl1.readLux(VL6180X_ALS_GAIN_5);
////  tcaselect(1);
////  Adafruit_VL6180X vl2 = Adafruit_VL6180X();
//// TOF_sensor_msg.range_reading[1] = vl2.readRange();
//// TOF_sensor_msg.lux_reading[1] = vl2.readLux(VL6180X_ALS_GAIN_5);
//// tcaselect(2);
//// Adafruit_VL6180X vl3 = Adafruit_VL6180X();
//// TOF_sensor_msg.range_reading[2] = vl2.readRange();
//// TOF_sensor_msg.lux_reading[2] = vl2.readLux(VL6180X_ALS_GAIN_5);
//}
