/*This code connects the arduino to the computer and interacts via ROS.
   It controls the pressure regulator to open and close the gripper.
   It collects data from the various sensors and sends it to the computer
   for logging.
*/

#include "Adafruit_VL6180X.h"
#include <Wire.h>  //Allows it to talk to I2C
#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Empty.h>
#include <gt_py/TOF_sensor_data.h>


// Function Prototypes
void gripper_CB(const std_msgs::Bool& gripper_msg);
void TOF_sensor_CB(const std_msgs::Empty& sensor_call_msg);
int check_switches();
//void tcaselect(uint8_t i);

// Defines

//Assumes A0 is pulled low which is default
#define MCP4725_ADDR 0x60 //A2, A1,A0 = 0 thus 0110 0000
#define WRITE_CMD 0x40 //c0, c2 = 0, c1 = 1 thus 0100 0000
#define TCAADDR 0x70 //Adress for the multiplexor


// Variables will change:


byte buttons[] = {2, 3, 4, 5};
#define NUMBUTTONS sizeof(buttons)
byte pressed[NUMBUTTONS], buttonState[NUMBUTTONS];
unsigned long lastTime[NUMBUTTONS];
byte previousState[NUMBUTTONS];
byte currentState[NUMBUTTONS];

unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

/*
 * Use the TCA9548A I2C multiplexor to shift between sensors
 */
void tcaselect(uint8_t i){
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 <<i );
  Wire.endTransmission(TCAADDR);
}

 // tcaselect(1);
 // Adafruit_VL6180X vl1 = Adafruit_VL6180X();
//  tcaselect(1);
//  Adafruit_VL6180X vl2 = Adafruit_VL6180X();
//  tcaselect(2);
//  Adafruit_VL6180X vl3 = Adafruit_VL6180X();

// Node handler
ros::NodeHandle nh;

// Publishers
std_msgs::Int32 button_msg;
ros::Publisher pub_button("button_ret", &button_msg);


gt_py::TOF_sensor_data TOF_sensor_msg;
ros::Publisher pub_TOF_sensor("sensor_ret/TOF", &TOF_sensor_msg);


//Subcribers
ros::Subscriber<std_msgs::Bool> gripper_sub("toggle_gripper", &gripper_CB);
ros::Subscriber<std_msgs::Empty> TOF_sensor_sub("sensor_call/TOF", &TOF_sensor_CB);




/*
   A Callback function to control the gripper
*/
void gripper_CB(const std_msgs::Bool& gripper_msg) {
  int pressure_sig = 0;
  if (gripper_msg.data == true) {
    float pressure_d = 5.0; //Setting close pressure in psi
    pressure_sig = (int)((pressure_d / 50.0) * 4096);
  }

  Wire.beginTransmission(MCP4725_ADDR);
  Wire.write(WRITE_CMD);
  Wire.write(pressure_sig >> 4);
  Wire.write((pressure_sig && 15) << 4);
  Wire.endTransmission();

}



/*
   A Callback function that returns the TOF sensor reading
*/

void TOF_sensor_CB(const std_msgs::Empty &sensor_call_msg) {


  
 tcaselect(0);
 Adafruit_VL6180X vl1 = Adafruit_VL6180X();
 TOF_sensor_msg.range_reading[0] = vl1.readRange();
 TOF_sensor_msg.lux_reading[0] = vl1.readLux(VL6180X_ALS_GAIN_5);
  tcaselect(1);
  Adafruit_VL6180X vl2 = Adafruit_VL6180X();
 TOF_sensor_msg.range_reading[1] = vl2.readRange();
 TOF_sensor_msg.lux_reading[1] = vl2.readLux(VL6180X_ALS_GAIN_5);
 tcaselect(2);
 Adafruit_VL6180X vl3 = Adafruit_VL6180X();
 TOF_sensor_msg.range_reading[2] = vl2.readRange();
 TOF_sensor_msg.lux_reading[2] = vl2.readLux(VL6180X_ALS_GAIN_5);


pub_TOF_sensor.publish(&TOF_sensor_msg);

}


void setup()
{
  Wire.begin(); //Initialize Wire
  //Set the pressure to zero at start
  Wire.beginTransmission(MCP4725_ADDR);
  Wire.write(WRITE_CMD);
  Wire.write(0);
  Wire.write(0);
  Wire.endTransmission();

vl.begin();
  nh.initNode();
  // Init Subs
  nh.subscribe(gripper_sub);
  nh.subscribe(TOF_sensor_sub);

  // Init Pubs
  nh.advertise(pub_button);
  nh.advertise(pub_TOF_sensor);

  for (byte i = 0; i < NUMBUTTONS; i++) {
    pinMode(buttons[i], INPUT);
    buttonState[i] = LOW;
    lastTime[i] = 0;
    previousState[i] = LOW;
  }

}



int check_switches() {
  int current_pressed = -1;
  bool flag = false;
  byte total = 0;
  while (flag == false) {
    for (int i = 0; i < NUMBUTTONS; i++) {
      currentState[i] = digitalRead(buttons[i]);

      if (currentState[i] != previousState[i]) {
        lastTime[i] = millis();
      }
      if ((millis() - lastTime[i]) > debounceDelay) {
        // whatever the reading is at, it's been there for longer than the debounce
        // delay, so take it as the actual current state:

        // if the button state has changed:
        if (currentState[i] != buttonState[i]) {
          buttonState[i] = currentState[i];

          if (buttonState[i] == HIGH) {
            pressed[i] = HIGH;
            current_pressed = i;
          }
        }
      }


      previousState[i] = currentState[i];
      total = total + pressed[i];
    }


    if (total <= 1) {
      flag = true;

    }
  }
  return current_pressed;
}


void loop()
{
  
  int button = check_switches();

  

  if (button != -1) {
    button_msg.data = button;
    pub_button.publish(&button_msg);
  }

 
  nh.spinOnce();
  //delay(1);
}
