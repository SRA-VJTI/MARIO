#ifndef _ROS_shape_msgs_Plane_h
#define _ROS_shape_msgs_Plane_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace shape_msgs
{

  class Plane : public ros::Msg
  {
    public:
      double coef[4];

    Plane():
      coef()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      union {
        double real;
        uint32_t base;
      } u_coefi;
      u_coefi.real = this->coef[i];
      *(outbuffer + offset + 0) = (u_coefi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_coefi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_coefi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_coefi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->coef[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      union {
        double real;
        uint32_t base;
      } u_coefi;
      u_coefi.base = 0;
      u_coefi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_coefi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_coefi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_coefi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->coef[i] = u_coefi.real;
      offset += sizeof(this->coef[i]);
      }
     return offset;
    }

    const char * getType(){ return "shape_msgs/Plane"; };
    const char * getMD5(){ return "2c1b92ed8f31492f8e73f6a4a44ca796"; };

  };

}
#endif