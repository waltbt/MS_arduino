/*This code connects the arduino to the computer and interacts via ROS.
   It controls the pressure regulator to open and close the gripper.
   It collects data from the various sensors and sends it to the computer
   for logging.
*/

#include <ros.h>

//#include <std_msgs/Int32MultiArray.h>
#include <gt_py/IR_sensor_data.h>


// Function Prototypes



// Defines


// Node handler
ros::NodeHandle nh;

// Publishers

//std_msgs::Int32MultiArray sensor_msg;
gt_py::IR_sensor_data sensor_msg;
ros::Publisher pub_sensor("sensor_ret", &sensor_msg);








void setup()
{

 // Serial.begin(9600); 
//sensor_msg.data_length = 3;

  nh.initNode();
  // Init Subs

  // Init Pubs

  nh.advertise(pub_sensor);



}





void loop()
{




sensor_msg.sensor_reading[0] = (int32_t)analogRead(A0);  // read the input pin

sensor_msg.sensor_reading[1] = (int32_t)analogRead(A1);  // read the input pin

sensor_msg.sensor_reading[2] = (int32_t)analogRead(A2);  // read the input pin


//Serial.println(sensor_msg.sensor_reading[0]);

//Serial.println(sensor_msg.sensor_reading[1]);
//Serial.println(sensor_msg.sensor_reading[2]);
delay(200);

pub_sensor.publish(&sensor_msg);

  

 
  nh.spinOnce();
  //delay(1);
}
