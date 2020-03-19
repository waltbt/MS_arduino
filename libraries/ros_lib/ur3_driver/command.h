#ifndef _ROS_ur3_driver_command_h
#define _ROS_ur3_driver_command_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ur3_driver
{

  class command : public ros::Msg
  {
    public:
      uint32_t destination_length;
      typedef float _destination_type;
      _destination_type st_destination;
      _destination_type * destination;
      typedef float _v_type;
      _v_type v;
      typedef float _a_type;
      _a_type a;
      typedef bool _io_0_type;
      _io_0_type io_0;

    command():
      destination_length(0), destination(NULL),
      v(0),
      a(0),
      io_0(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->destination_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->destination_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->destination_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->destination_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->destination_length);
      for( uint32_t i = 0; i < destination_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->destination[i]);
      }
      offset += serializeAvrFloat64(outbuffer + offset, this->v);
      offset += serializeAvrFloat64(outbuffer + offset, this->a);
      union {
        bool real;
        uint8_t base;
      } u_io_0;
      u_io_0.real = this->io_0;
      *(outbuffer + offset + 0) = (u_io_0.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->io_0);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t destination_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      destination_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      destination_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      destination_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->destination_length);
      if(destination_lengthT > destination_length)
        this->destination = (float*)realloc(this->destination, destination_lengthT * sizeof(float));
      destination_length = destination_lengthT;
      for( uint32_t i = 0; i < destination_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_destination));
        memcpy( &(this->destination[i]), &(this->st_destination), sizeof(float));
      }
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->v));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->a));
      union {
        bool real;
        uint8_t base;
      } u_io_0;
      u_io_0.base = 0;
      u_io_0.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->io_0 = u_io_0.real;
      offset += sizeof(this->io_0);
     return offset;
    }

    const char * getType(){ return "ur3_driver/command"; };
    const char * getMD5(){ return "c8890f8a9e9a6dc32b97081f6283bc11"; };

  };

}
#endif