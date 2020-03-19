#ifndef _ROS_ur3_driver_gripper_input_h
#define _ROS_ur3_driver_gripper_input_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ur3_driver
{

  class gripper_input : public ros::Msg
  {
    public:
      typedef int32_t _DIGIN_type;
      _DIGIN_type DIGIN;
      typedef float _AIN0_type;
      _AIN0_type AIN0;
      typedef float _AIN1_type;
      _AIN1_type AIN1;

    gripper_input():
      DIGIN(0),
      AIN0(0),
      AIN1(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_DIGIN;
      u_DIGIN.real = this->DIGIN;
      *(outbuffer + offset + 0) = (u_DIGIN.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_DIGIN.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_DIGIN.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_DIGIN.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->DIGIN);
      offset += serializeAvrFloat64(outbuffer + offset, this->AIN0);
      offset += serializeAvrFloat64(outbuffer + offset, this->AIN1);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_DIGIN;
      u_DIGIN.base = 0;
      u_DIGIN.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_DIGIN.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_DIGIN.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_DIGIN.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->DIGIN = u_DIGIN.real;
      offset += sizeof(this->DIGIN);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->AIN0));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->AIN1));
     return offset;
    }

    const char * getType(){ return "ur3_driver/gripper_input"; };
    const char * getMD5(){ return "a4b7d373885d48c37baffd91ce2f1c38"; };

  };

}
#endif