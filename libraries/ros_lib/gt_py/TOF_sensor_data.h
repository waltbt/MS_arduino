#ifndef _ROS_gt_py_TOF_sensor_data_h
#define _ROS_gt_py_TOF_sensor_data_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace gt_py
{

  class TOF_sensor_data : public ros::Msg
  {
    public:
      int32_t range_reading[3];
      float lux_reading[3];

    TOF_sensor_data():
      range_reading(),
      lux_reading()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 3; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_range_readingi;
      u_range_readingi.real = this->range_reading[i];
      *(outbuffer + offset + 0) = (u_range_readingi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_range_readingi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_range_readingi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_range_readingi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->range_reading[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        float real;
        uint32_t base;
      } u_lux_readingi;
      u_lux_readingi.real = this->lux_reading[i];
      *(outbuffer + offset + 0) = (u_lux_readingi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_lux_readingi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_lux_readingi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_lux_readingi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->lux_reading[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 3; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_range_readingi;
      u_range_readingi.base = 0;
      u_range_readingi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_range_readingi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_range_readingi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_range_readingi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->range_reading[i] = u_range_readingi.real;
      offset += sizeof(this->range_reading[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        float real;
        uint32_t base;
      } u_lux_readingi;
      u_lux_readingi.base = 0;
      u_lux_readingi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_lux_readingi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_lux_readingi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_lux_readingi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->lux_reading[i] = u_lux_readingi.real;
      offset += sizeof(this->lux_reading[i]);
      }
     return offset;
    }

    const char * getType(){ return "gt_py/TOF_sensor_data"; };
    const char * getMD5(){ return "3c37e3e2c7851686cb8c295f62489702"; };

  };

}
#endif