//Header File for Inverse Kinematics Module
#ifndef INVERSE_KINEMATICS_H
#define INVERSE_KINEMATICS_H

#include<math.h>

//Sturcture to store data of X,Y,Z co-ordinates received from webserver
typedef struct invK_coords
{
    double x;
    double y;
    double z;
} xyz_coords;

//Rounding Function
double Round(double n); 

//Takes X,Y,Z co-ordinates as input and returns an array of all possible angles of base,shoulder and elbow
double* applyInverseKinematics(double,double,double);

//Radians to Degrees Function
double degrees(double rad);


#endif
