#ifndef _ROS_beginner_tutorials_Num_h
#define _ROS_beginner_tutorials_Num_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace beginner_tutorials
{

  class Num : public ros::Msg
  {
    public:
      typedef int64_t _num_type;
      _num_type num;

    Num():
      num(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_num;
      u_num.real = this->num;
      *(outbuffer + offset + 0) = (u_num.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_num.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_num.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_num.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_num.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_num.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_num.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_num.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->num);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_num;
      u_num.base = 0;
      u_num.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_num.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_num.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_num.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_num.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_num.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_num.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_num.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->num = u_num.real;
      offset += sizeof(this->num);
     return offset;
    }

    const char * getType(){ return "beginner_tutorials/Num"; };
    const char * getMD5(){ return "57d3c40ec3ac3754af76a83e6e73127a"; };

  };

}
#endif