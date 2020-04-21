#ifndef _ROS_arm_control_position_h
#define _ROS_arm_control_position_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace arm_control
{

  class position : public ros::Msg
  {
    public:
      float point[4];

    position():
      point()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      union {
        float real;
        uint32_t base;
      } u_pointi;
      u_pointi.real = this->point[i];
      *(outbuffer + offset + 0) = (u_pointi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pointi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pointi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pointi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->point[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      union {
        float real;
        uint32_t base;
      } u_pointi;
      u_pointi.base = 0;
      u_pointi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pointi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pointi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pointi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->point[i] = u_pointi.real;
      offset += sizeof(this->point[i]);
      }
     return offset;
    }

    const char * getType(){ return "arm_control/position"; };
    const char * getMD5(){ return "c8e7818df37db2cf138689cbda172d04"; };

  };

}
#endif