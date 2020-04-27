#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Empty.h>
#include <arm_control/command.h>

#include <ax12.h>
#include <BioloidController.h>
#include "poses.h"

#include <Servo.h>

BioloidController bioloid = BioloidController(1000000);

Servo wrist_yaw;
Servo wrist_pitch;
Servo wrist_roll;

#define YAW 3
#define PITCH 4
#define ROLL 5

int pos = 0;
int cur_pos[] = {2048, 2020, 2070, 1470, 1450, 1600};

void pose_CB(const arm_control::command& pose_msg);


// Node handler
ros::NodeHandle nh;

ros::Subscriber<arm_control::command> pose_sub("move_command", &pose_CB);

std_msgs::Bool step_complete_msg;
ros::Publisher pub_step_complete("arm_control/step_complete", &step_complete_msg);


void pose_CB(const arm_control::command& des_pos) {




  int set_pose[] = {1, 1, 1, 1, 1, 1};
  int move = 1;
  set_pose[ROLL] = 0;

  step_complete_msg.data = false;
  pub_step_complete.publish(&step_complete_msg);

  while (move > 0) {
    for (int i = 0; i < 3; i++) {
      if (cur_pos[i] < des_pos.pose[i]) {
        cur_pos[i]++;
      } else if (cur_pos[i] > des_pos.pose[i]) {
        cur_pos[i]--;
      } else {
        //Don't change
        set_pose[i] = 0;
      }

    }

    if (cur_pos[YAW] < des_pos.pose[YAW]) {
      cur_pos[YAW]++;
    } else if (cur_pos[YAW] > des_pos.pose[YAW]) {
      cur_pos[YAW]--;
    } else {
      //Don't change
      set_pose[YAW] = 0;
    }

    if (cur_pos[PITCH] < des_pos.pose[PITCH]) {
      cur_pos[PITCH]++;
    } else if (cur_pos[PITCH] > des_pos.pose[PITCH]) {
      cur_pos[PITCH]--;
    } else {
      //Don't change
      set_pose[PITCH] = 0;
    }

//    if (cur_pos[ROLL] < des_pos.pose[ROLL]) {
//      cur_pos[ROLL]++;
//    } else if (cur_pos[ROLL] > des_pos.pose[ROLL]) {
//      cur_pos[ROLL]--;
//    } else {
//      //Don't change
//      set_pose[ROLL] = 0;
//    }
    SetPosition(1, cur_pos[0]);
    SetPosition(2, cur_pos[1]);
    SetPosition(3, cur_pos[2]);
    wrist_yaw.writeMicroseconds(cur_pos[YAW]);
    wrist_pitch.writeMicroseconds(cur_pos[PITCH]);
   // wrist_roll.write(cur_pos[ROLL]);

    move = set_pose[0] + set_pose[1] + set_pose[2] + set_pose[3] + set_pose[4] + set_pose[5];
    delay(3);
  }
  step_complete_msg.data = true;
  pub_step_complete.publish(&step_complete_msg);
}


void MoveCenter() {
  // const uint16_t Center[] = {3, 2048, 2048, 2048};
  delay(100);                    // recommended pause
  bioloid.loadPose(Center);   // load the pose from FLASH, into the nextPose buffer
  bioloid.readPose();            // read in current servo positions to the curPose buffer
  delay(1000);
  bioloid.interpolateSetup(1000); // setup for interpolation from current->next over 1/2 a second
  while (bioloid.interpolating > 0) { // do this while we have not reached our new pose
    bioloid.interpolateStep();     // move servos, if necessary.
    delay(3);
  }
}



void setup() {

  wrist_yaw.attach(3); //Third joint
  wrist_yaw.writeMicroseconds(1470);
 wrist_pitch.attach(15); //Second joint
  wrist_pitch.writeMicroseconds(1450);
  wrist_roll.attach(1); //First joint
  wrist_roll.writeMicroseconds(1600);



  nh.initNode();
  // Init Subs
  nh.subscribe(pose_sub);
  // Init Pub
  nh.advertise(pub_step_complete);
  MoveCenter();

}

void loop() {
  nh.spinOnce();
  delay(1);

}
