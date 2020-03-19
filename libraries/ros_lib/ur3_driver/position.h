#ifndef _ROS_ur3_driver_position_h
#define _ROS_ur3_driver_position_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ur3_driver
{

  class position : public ros::Msg
  {
    public:
      uint32_t position_length;
      typedef float _position_type;
      _position_type st_position;
      _position_type * position;
      typedef bool _isReady_type;
      _isReady_type isReady;

    position():
      position_length(0), position(NULL),
      isReady(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->position_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->position_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->position_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->position_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->position_length);
      for( uint32_t i = 0; i < position_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->position[i]);
      }
      union {
        bool real;
        uint8_t base;
      } u_isReady;
      u_isReady.real = this->isReady;
      *(outbuffer + offset + 0) = (u_isReady.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->isReady);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t position_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      position_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      position_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      position_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->position_length);
      if(position_lengthT > position_length)
        this->position = (float*)realloc(this->position, position_lengthT * sizeof(float));
      position_length = position_lengthT;
      for( uint32_t i = 0; i < position_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_position));
        memcpy( &(this->position[i]), &(this->st_position), sizeof(float));
      }
      union {
        bool real;
        uint8_t base;
      } u_isReady;
      u_isReady.base = 0;
      u_isReady.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->isReady = u_isReady.real;
      offset += sizeof(this->isReady);
     return offset;
    }

    const char * getType(){ return "ur3_driver/position"; };
    const char * getMD5(){ return "86ad7fb432e90c4fcc2fa98c89466a9b"; };

  };

}
#endif