#ifndef _ROS_arm_control_command_h
#define _ROS_arm_control_command_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace arm_control
{

  class command : public ros::Msg
  {
    public:
      int32_t pose[6];

    command():
      pose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 6; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_posei;
      u_posei.real = this->pose[i];
      *(outbuffer + offset + 0) = (u_posei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_posei.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_posei.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_posei.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pose[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 6; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_posei;
      u_posei.base = 0;
      u_posei.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_posei.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_posei.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_posei.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pose[i] = u_posei.real;
      offset += sizeof(this->pose[i]);
      }
     return offset;
    }

    const char * getType(){ return "arm_control/command"; };
    const char * getMD5(){ return "1a1a3549ea1fbd90af851784fda8677a"; };

  };

}
#endif