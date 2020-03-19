#ifndef _ROS_gt_py_color_sensor_data_h
#define _ROS_gt_py_color_sensor_data_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace gt_py
{

  class color_sensor_data : public ros::Msg
  {
    public:
      int32_t rgb_values[4];
      typedef int32_t _color_temp_type;
      _color_temp_type color_temp;
      typedef float _lux_type;
      _lux_type lux;

    color_sensor_data():
      rgb_values(),
      color_temp(0),
      lux(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_rgb_valuesi;
      u_rgb_valuesi.real = this->rgb_values[i];
      *(outbuffer + offset + 0) = (u_rgb_valuesi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rgb_valuesi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rgb_valuesi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rgb_valuesi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rgb_values[i]);
      }
      union {
        int32_t real;
        uint32_t base;
      } u_color_temp;
      u_color_temp.real = this->color_temp;
      *(outbuffer + offset + 0) = (u_color_temp.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_color_temp.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_color_temp.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_color_temp.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->color_temp);
      union {
        float real;
        uint32_t base;
      } u_lux;
      u_lux.real = this->lux;
      *(outbuffer + offset + 0) = (u_lux.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_lux.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_lux.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_lux.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->lux);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_rgb_valuesi;
      u_rgb_valuesi.base = 0;
      u_rgb_valuesi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rgb_valuesi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rgb_valuesi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rgb_valuesi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->rgb_values[i] = u_rgb_valuesi.real;
      offset += sizeof(this->rgb_values[i]);
      }
      union {
        int32_t real;
        uint32_t base;
      } u_color_temp;
      u_color_temp.base = 0;
      u_color_temp.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_color_temp.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_color_temp.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_color_temp.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->color_temp = u_color_temp.real;
      offset += sizeof(this->color_temp);
      union {
        float real;
        uint32_t base;
      } u_lux;
      u_lux.base = 0;
      u_lux.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_lux.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_lux.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_lux.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->lux = u_lux.real;
      offset += sizeof(this->lux);
     return offset;
    }

    const char * getType(){ return "gt_py/color_sensor_data"; };
    const char * getMD5(){ return "7c8cfe28df9aa44956a941b8c260653a"; };

  };

}
#endif