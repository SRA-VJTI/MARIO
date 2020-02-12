#ifndef _ROS_geometry_msgs_AccelWithCovariance_h
#define _ROS_geometry_msgs_AccelWithCovariance_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Accel.h"

namespace geometry_msgs
{

  class AccelWithCovariance : public ros::Msg
  {
    public:
      typedef geometry_msgs::Accel _accel_type;
      _accel_type accel;
      double covariance[36];

    AccelWithCovariance():
      accel(),
      covariance()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->accel.serialize(outbuffer + offset);
      for( uint32_t i = 0; i < 36; i++){
      union {
        double real;
        uint32_t base;
      } u_covariancei;
      u_covariancei.real = this->covariance[i];
      *(outbuffer + offset + 0) = (u_covariancei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_covariancei.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_covariancei.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_covariancei.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->covariance[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->accel.deserialize(inbuffer + offset);
      for( uint32_t i = 0; i < 36; i++){
      union {
        double real;
        uint32_t base;
      } u_covariancei;
      u_covariancei.base = 0;
      u_covariancei.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_covariancei.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_covariancei.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_covariancei.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->covariance[i] = u_covariancei.real;
      offset += sizeof(this->covariance[i]);
      }
     return offset;
    }

    const char * getType(){ return "geometry_msgs/AccelWithCovariance"; };
    const char * getMD5(){ return "ad5a718d699c6be72a02b8d6a139f334"; };

  };

}
#endif