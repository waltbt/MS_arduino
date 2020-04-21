#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int32.h>

#include <ax12.h>
#include <BioloidController.h>
#include "poses.h"

#include <Servo.h>

BioloidController bioloid = BioloidController(1000000);

Servo myservo;

int pos = 0;

void LED_CB(const std_msgs::Bool& LED_msg);
void servo_CB(const std_msgs::Int32& servo_msg);

// Node handler
ros::NodeHandle nh;

ros::Subscriber<std_msgs::Bool> LED_sub("toggle_LED", &LED_CB);

//ros::Subscriber<std_msgs::Int32> pose_sub("move_pose", &pose_CB);
ros::Subscriber<std_msgs::Int32> servo_sub("move_servo", &servo_CB);


void LED_CB(const std_msgs::Bool& LED_msg) {

if(LED_msg.data == 1){
  ax12SetRegister(1,25, 1);
}else{
  ax12SetRegister(1,25, 0);
}
//ax12SetRegister(1,25, 1);
  
}

void servo_CB(const std_msgs::Int32& servo_msg) {

for(pos = 0;pos<=180;pos++){
  //ax12SetRegister(1,25, 1);
  myservo.write(pos);
  delay(25);
}
for(pos = 180;pos>=0;pos--){
  //ax12SetRegister(1,25, 0);
  myservo.write(pos);
  delay(25);
}
  pos = 0;
}


void mov_ser() {

for(pos = 0;pos<=180;pos++){
  ax12SetRegister(1,25, 1);
  myservo.write(pos);
  delay(25);
}
for(pos = 180;pos>=0;pos--){
  ax12SetRegister(1,25, 0);
  myservo.write(pos);
  delay(25);
}
  pos = 0;
}


void MoveCenter(){
 // const uint16_t Center[] = {3, 2048, 2048, 2048};
    delay(100);                    // recommended pause
    bioloid.loadPose(Center);   // load the pose from FLASH, into the nextPose buffer
    bioloid.readPose();            // read in current servo positions to the curPose buffer   
    delay(1000);
    bioloid.interpolateSetup(1000); // setup for interpolation from current->next over 1/2 a second
    while(bioloid.interpolating > 0){  // do this while we have not reached our new pose
        bioloid.interpolateStep();     // move servos, if necessary. 
        delay(3);
    }
  }



void setup() {
  //myservo.write(0);
  myservo.attach(1);
  myservo.write(0);
  mov_ser();
  nh.initNode();
  // Init Subs
  nh.subscribe(LED_sub);
  nh.subscribe(servo_sub);
  //ax12Init(1000000);
  // MoveCenter();
  

}

void loop() {
  nh.spinOnce();
  delay(1);

}
