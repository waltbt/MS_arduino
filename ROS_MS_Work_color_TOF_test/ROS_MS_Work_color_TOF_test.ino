
#include "Adafruit_VL6180X.h"
#include "Adafruit_TCS34725.h"
#include <Wire.h>  //Allows it to talk to I2C

Adafruit_VL6180X vl = Adafruit_VL6180X();

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void tcaselect(uint8_t i);

// Defines

#define TCAADDR 0x70 //Adress for the multiplexor


void setup() {
  Serial.begin(115200);
   while (!Serial) {
    delay(1);
  }
  Wire.begin();
  
  tcaselect(1);
  
 
    Serial.println("Adafruit tcs test!");
  while (! tcs.begin()) {
    Serial.println("Failed to find TCS sensor");
    //while (1);
  }
  Serial.println("TCS Sensor found!");


  tcaselect(0);
  
 
    Serial.println("Adafruit VL6180x test!");
  while (! vl.begin()) {
    Serial.println("Failed to find VL sensor");
    //while (1);
  }
  Serial.println("VL Sensor found!");



}


void loop(){

tcaselect(1);
 uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
     
    tcaselect(0);
     
  //  float lux = vl[i].readLux(VL6180X_ALS_GAIN_5);

   uint8_t range = vl.readRange();

    Serial.print("Range: "); Serial.println(range);
  
  
 
}

/*
 * Use the TCA9548A I2C multiplexor to shift between sensors
 */
void tcaselect(uint8_t i){
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 <<i );
  Wire.endTransmission(TCAADDR);
  //Serial.println("Hello");
  //delay(50);
}
