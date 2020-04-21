#ifndef _ROS_trainer_IR_sensor_data_h
#define _ROS_trainer_IR_sensor_data_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace trainer
{

  class IR_sensor_data : public ros::Msg
  {
    public:
      int32_t sensor_reading[3];

    IR_sensor_data():
      sensor_reading()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 3; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_sensor_readingi;
      u_sensor_readingi.real = this->sensor_reading[i];
      *(outbuffer + offset + 0) = (u_sensor_readingi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_sensor_readingi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_sensor_readingi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_sensor_readingi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sensor_reading[i]);
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
      } u_sensor_readingi;
      u_sensor_readingi.base = 0;
      u_sensor_readingi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_sensor_readingi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_sensor_readingi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_sensor_readingi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->sensor_reading[i] = u_sensor_readingi.real;
      offset += sizeof(this->sensor_reading[i]);
      }
     return offset;
    }

    const char * getType(){ return "trainer/IR_sensor_data"; };
    const char * getMD5(){ return "a614798fa533ba4b6588423e50c5f7ae"; };

  };

}
#endif