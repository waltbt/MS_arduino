/*
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float32.h>

std_msgs::Float32 temp_msg;
ros::Publisher pub_temp("press_ret", &temp_msg);
ros::NodeHandle nh;

void messageCb( const std_msgs::Empty& toggle_msg){
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}

void messageCb2( const std_msgs::Float32& pressure_msg){
  temp_msg.data = pressure_msg.data;
  pub_temp.publish(&temp_msg);
}



ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb );
ros::Subscriber<std_msgs::Float32> sub_2("pressure_data", &messageCb2 );


void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(sub_2);
  nh.advertise(pub_temp);
}

void loop()
{
  nh.spinOnce();
  delay(1);
}
