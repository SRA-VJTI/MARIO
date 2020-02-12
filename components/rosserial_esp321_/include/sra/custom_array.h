#ifndef _ROS_sra_custom_array_h
#define _ROS_sra_custom_array_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace sra
{

  class custom_array : public ros::Msg
  {
    public:
      uint32_t array1_length;
      typedef int16_t _array1_type;
      _array1_type st_array1;
      _array1_type * array1;

    custom_array():
      array1_length(0), array1(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->array1_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->array1_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->array1_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->array1_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->array1_length);
      for( uint32_t i = 0; i < array1_length; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_array1i;
      u_array1i.real = this->array1[i];
      *(outbuffer + offset + 0) = (u_array1i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_array1i.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->array1[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t array1_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      array1_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      array1_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      array1_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->array1_length);
      if(array1_lengthT > array1_length)
        this->array1 = (int16_t*)realloc(this->array1, array1_lengthT * sizeof(int16_t));
      array1_length = array1_lengthT;
      for( uint32_t i = 0; i < array1_length; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_st_array1;
      u_st_array1.base = 0;
      u_st_array1.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_array1.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_array1 = u_st_array1.real;
      offset += sizeof(this->st_array1);
        memcpy( &(this->array1[i]), &(this->st_array1), sizeof(int16_t));
      }
     return offset;
    }

    const char * getType(){ return "sra/custom_array"; };
    const char * getMD5(){ return "60e4de506fc8a4ccd83e672730ccb32f"; };

  };

}
#endif