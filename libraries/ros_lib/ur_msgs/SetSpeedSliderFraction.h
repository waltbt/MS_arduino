#ifndef _ROS_SERVICE_SetSpeedSliderFraction_h
#define _ROS_SERVICE_SetSpeedSliderFraction_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ur_msgs
{

static const char SETSPEEDSLIDERFRACTION[] = "ur_msgs/SetSpeedSliderFraction";

  class SetSpeedSliderFractionRequest : public ros::Msg
  {
    public:
      typedef float _speed_slider_fraction_type;
      _speed_slider_fraction_type speed_slider_fraction;

    SetSpeedSliderFractionRequest():
      speed_slider_fraction(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->speed_slider_fraction);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->speed_slider_fraction));
     return offset;
    }

    const char * getType(){ return SETSPEEDSLIDERFRACTION; };
    const char * getMD5(){ return "64134244ab4dfc72a3406fe06d580274"; };

  };

  class SetSpeedSliderFractionResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    SetSpeedSliderFractionResponse():
      success(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
     return offset;
    }

    const char * getType(){ return SETSPEEDSLIDERFRACTION; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class SetSpeedSliderFraction {
    public:
    typedef SetSpeedSliderFractionRequest Request;
    typedef SetSpeedSliderFractionResponse Response;
  };

}
#endif
