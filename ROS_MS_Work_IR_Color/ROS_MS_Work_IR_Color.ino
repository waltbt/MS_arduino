/*This code connects the arduino to the computer and interacts via ROS.
   It controls the pressure regulator to open and close the gripper.
   It collects data from the various sensors and sends it to the computer
   for logging.
*/

#include "Adafruit_TCS34725.h"
#include <Wire.h>  //Allows it to talk to I2C
#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Empty.h>
#include <arm_control/IR_sensor_data.h>
#include <arm_control/color_sensor_data.h>

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

// Function Prototypes
void gripper_CB(const std_msgs::Bool& gripper_msg);
void IR_sensor_CB(const std_msgs::Empty& sensor_call_msg);
void color_sensor_CB(const std_msgs::Empty& sensor_call_msg);
int check_switches();


// Defines

//Assumes A0 is pulled low which is default
#define MCP4725_ADDR 0x60 //A2, A1,A0 = 0 thus 0110 0000
#define WRITE_CMD 0x40 //c0, c2 = 0, c1 = 1 thus 0100 0000


// Variables will change:


byte buttons[] = {2, 3, 4, 5};
#define NUMBUTTONS sizeof(buttons)
byte pressed[NUMBUTTONS], buttonState[NUMBUTTONS];
unsigned long lastTime[NUMBUTTONS];
byte previousState[NUMBUTTONS];
byte currentState[NUMBUTTONS];

unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// Node handler
ros::NodeHandle nh;

// Publishers
std_msgs::Int32 button_msg;
ros::Publisher pub_button("button_ret", &button_msg);

//std_msgs::Int32 sensor_range_msg;
//ros::Publisher pub_sensor_range("sensor_range_ret", &sensor_range_msg);

arm_control::IR_sensor_data IR_sensor_msg;
ros::Publisher pub_IR_sensor("sensor_ret/IR", &IR_sensor_msg);

arm_control::color_sensor_data color_sensor_msg;
ros::Publisher pub_color_sensor("sensor_ret/color", &color_sensor_msg);


//Subcribers
ros::Subscriber<std_msgs::Bool> gripper_sub("toggle_gripper", &gripper_CB);
ros::Subscriber<std_msgs::Empty> IR_sensor_sub("sensor_call/IR", &IR_sensor_CB);
ros::Subscriber<std_msgs::Empty> color_sensor_sub("sensor_call/color", &color_sensor_CB);

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
   A Callback function that returns the IR_sensor reading
*/

void IR_sensor_CB(const std_msgs::Empty& sensor_call_msg) {

IR_sensor_msg.sensor_reading[0] = (int32_t)analogRead(A0);  // read the input pin (blue)

IR_sensor_msg.sensor_reading[1] = (int32_t)analogRead(A1);  // read the input pin (black)

IR_sensor_msg.sensor_reading[2] = -1;

pub_IR_sensor.publish(&IR_sensor_msg);

}


/*
   A Callback function that returns the color sensor reading
*/

void color_sensor_CB(const std_msgs::Empty& sensor_call_msg) {
  // How to make this work????
uint16_t r, g, b, c, colorTemp;
float lux;
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);


color_sensor_msg.rgb_values[0] = int(r);  // read the input pin (blue)

color_sensor_msg.rgb_values[1] = int(g); 

color_sensor_msg.rgb_values[2] = int(b); 

color_sensor_msg.rgb_values[3] = int(c);

color_sensor_msg.color_temp = int(colorTemp);  // read the input pin (black)

color_sensor_msg.lux = lux;  // read the input pin (green)

pub_color_sensor.publish(&color_sensor_msg);

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

  tcs.begin();

  nh.initNode();
  // Init Subs
  nh.subscribe(gripper_sub);
  nh.subscribe(IR_sensor_sub);
  nh.subscribe(color_sensor_sub);
  // Init Pubs
  nh.advertise(pub_button);
  nh.advertise(pub_IR_sensor);
  nh.advertise(pub_color_sensor);

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
