/*This code connects the arduino to the computer and interacts via ROS.
 * It controls the pressure regulator to open and close the gripper.
 * It collects data from the various sensors and sends it to the computer
 * for logging.
 */


#include <Wire.h>  //Allows it to talk to I2C
#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include "Adafruit_VL6180X.h"


Adafruit_VL6180X vl = Adafruit_VL6180X();

void gripper_CB( const std_msgs::Bool& gripper_msg);
//void messageCb2( const std_msgs::Float32& pressure_msg);
void sensor_CB(const std_msgs::Empty& sensor_req_msg);


// Defines:

//Assumes A0 is pulled low which is default
#define MCP4725_ADDR 0x60 //A2, A1,A0 = 0 thus 0110 0000
#define WRITE_CMD 0x40 //c0, c2 = 0, c1 = 1 thus 0100 0000
#define GREEN 6
#define RED 5
//#define PWR 4

//debounce variables
// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int RedState;             // the current reading from the input pin
int GreenState;             // the current reading from the input pin
int lastRedState = LOW;   // the previous reading from the input pin
int lastGreenState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastGreenTime = 0;  // the last time the output pin was toggled
unsigned long lastRedTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


// Node handler
ros::NodeHandle nh;

// Publishers
//std_msgs::Float32 temp_msg;
//ros::Publisher pub_temp("press_ret", &temp_msg);

std_msgs::String error_msg;
ros::Publisher pub_error("error_ret", &error_msg);

std_msgs::Float32 sensor_msg;
ros::Publisher pub_sensor("sensor_ret", &sensor_msg);

std_msgs::Bool button_msg;
ros::Publisher pub_button("button_ret", &button_msg);

//Subcribers
ros::Subscriber<std_msgs::Bool> gripper_sub("toggle_gripper", &gripper_CB );
//ros::Subscriber<std_msgs::Float32> sub_2("pressure_data", &messageCb2 );
ros::Subscriber<std_msgs::Empty> sensor_sub("reading_req", &sensor_CB );



void gripper_CB( const std_msgs::Bool& gripper_msg){
  int pressure_sig = 0;
  if (gripper_msg.data == true){
    float pressure_d = 5.0; //Setting close pressure in psi
    pressure_sig = (int)((pressure_d/50.0) * 4096);
  
  }
//  Wire.beginTransmission(MCP4725_ADDR);
//  Wire.write(WRITE_CMD);
//  Wire.write(pressure_sig >> 4);
//  Wire.write((pressure_sig && 15) << 4);
//  Wire.endTransmission();
   
}

//void messageCb2( const std_msgs::Float32& pressure_msg){
//  temp_msg.data = pressure_msg.data;
//  pub_temp.publish(&temp_msg);
//}

void sensor_CB(const std_msgs::Empty& sensor_req_msg){

  

error_msg.data = "Sensor found!!!!";
  pub_error.publish(&error_msg);
  //float lux = vl.readLux(VL6180X_ALS_GAIN_5);

  //Serial.print("Lux: "); Serial.println(lux);
}

void setup()
{
//  Wire.begin(); //Initialize Wire
//  //Set the pressure to zero at start
//  Wire.beginTransmission(MCP4725_ADDR);
//  Wire.write(WRITE_CMD);
//  Wire.write(0);
//  Wire.write(0);
//  Wire.endTransmission();

  
  //pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(gripper_sub);
  nh.subscribe(sensor_sub);
  //nh.advertise(pub_temp);
  nh.advertise(pub_sensor);
  nh.advertise(pub_error);
  nh.advertise(pub_button);

  error_msg.data = "Adafruit VL6180x test!";
//  pub_error.publish(&error_msg);
//  if (! vl.begin()) {
//    error_msg.data = "Failed to find sensor";
//    pub_error.publish(&error_msg);
//    while (1);
//  }
//  error_msg.data = "Sensor found!";
//  pub_error.publish(&error_msg);

  pinMode(GREEN, INPUT);
  pinMode(RED, INPUT);
  //pinMode(PWR, OUTPUT);
  //digitalWrite(PWR, HIGH);
  //pinMode(13, OUTPUT);
  //digitalWrite(13, HIGH);
}

void loop()
{  int greenReading = digitalRead(GREEN);
  //int redReading = digitalRead(RED);
  int pressed = 0;
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (greenReading != lastGreenState) {
    // reset the debouncing timer
    lastGreenTime = millis();
  }
  // If the switch changed, due to noise or pressing:
//  if (redReading != lastRedState) {
//    // reset the debouncing timer
//    lastRedTime = millis();
 // }
  if ((millis() - lastGreenTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (greenReading != GreenState) {
      GreenState = greenReading;

      // only toggle the LED if the new button state is HIGH
      if (GreenState == HIGH) {
        pressed = 1;
       // ledState = !ledState;
            }
    }
  }

//if ((millis() - lastRedTime) > debounceDelay) {
//    // whatever the reading is at, it's been there for longer than the debounce
//    // delay, so take it as the actual current state:
//
//    // if the button state has changed:
//    if (redReading != RedState) {
//      RedState = redReading;
//
//      // only toggle the LED if the new button state is HIGH
//      if (RedState == HIGH) {
//        pressed = 2;
//       // ledState = !ledState;
//            }
//    }
//  }
  
  if (pressed == 1){
    button_msg.data = true;
    pub_button.publish(&button_msg);
  }
//  else if (pressed == 2){
//    button_msg.data = false;
//    pub_button.publish(&button_msg);
//  }
  //digitalWrite(13,ledState);
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastGreenState = greenReading;
//  lastRedState = redReading;
  nh.spinOnce();
  delay(1);
}
