#ifndef _ROS_sensor_msgs_FluidPressure_h
#define _ROS_sensor_msgs_FluidPressure_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace sensor_msgs
{

  class FluidPressure : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef double _fluid_pressure_type;
      _fluid_pressure_type fluid_pressure;
      typedef double _variance_type;
      _variance_type variance;

    FluidPressure():
      header(),
      fluid_pressure(0),
      variance(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        double real;
        uint32_t base;
      } u_fluid_pressure;
      u_fluid_pressure.real = this->fluid_pressure;
      *(outbuffer + offset + 0) = (u_fluid_pressure.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_fluid_pressure.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_fluid_pressure.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_fluid_pressure.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->fluid_pressure);
      union {
        double real;
        uint32_t base;
      } u_variance;
      u_variance.real = this->variance;
      *(outbuffer + offset + 0) = (u_variance.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_variance.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_variance.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_variance.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->variance);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        double real;
        uint32_t base;
      } u_fluid_pressure;
      u_fluid_pressure.base = 0;
      u_fluid_pressure.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_fluid_pressure.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_fluid_pressure.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_fluid_pressure.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->fluid_pressure = u_fluid_pressure.real;
      offset += sizeof(this->fluid_pressure);
      union {
        double real;
        uint32_t base;
      } u_variance;
      u_variance.base = 0;
      u_variance.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_variance.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_variance.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_variance.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->variance = u_variance.real;
      offset += sizeof(this->variance);
     return offset;
    }

    const char * getType(){ return "sensor_msgs/FluidPressure"; };
    const char * getMD5(){ return "804dc5cea1c5306d6a2eb80b9833befe"; };

  };

}
#endif