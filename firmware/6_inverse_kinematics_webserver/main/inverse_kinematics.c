#include "inverse_kinematics.h"
#include "tuning_http_server.h"

static double allPossibleAngles[6]; // Array to store all possible values of angles
const double d0 = 2.5;  // Base to shoulder link length
const double a1 = 12.0; // Shoulder to elbow link length
const double d3 = 9.5;  // Elbow to end effector link length
const double ROUNDING_ERROR = 2;


double Round(double n)
{
    int i = ROUNDING_ERROR;
    return floor(pow(10, i) * n) / pow(10, i);
}


double degrees(double rad)
{
    return (rad * (180 / 3.1415));
}

/*
X  =  cos(0_base) [d3 * cos(0_shoulder)sin(0_elbow) + d3 * sin(0_shoulder)cos(0_elbow) + a1 * cos(0_shoulder)]    
Y  =  sin(0_base) [d3 * cos(0_shoulder)sin(0_elbow) + d3 * sin(0_shoulder)cos(0_elbow) + a1 * cos(0_shoulder)]  
Z  =  d3 * sin(0_shoulder)sin(0_elbow) - d3 * cos(0_shoulder)cos(0_elbow) + a1 * sin(0_shoulder) + d0

---------------------------------------------------------------------------------------------------------------------
On applying Inverse Kinematics calculations :
 
θbase = tan-1 (y / x)
θelbow = sin-1( [x² + y² + (z - d0)² - a1² - d3²] / [2 * a1 * d3] )

If 0_base is not 90:
θshoulder =  sin-1( [(z - d0) * (a1 + d3 * sin(θ_elbow) + d3 * cos(θ_elbow) * x / cos(θ_base)] / [x² + y² + (z - d0)²] )
 
If 0_base is not 0:
θshoulder =  sin-1( [(z - d0) * (a1 + d3 * sin(θ_elbow) + d3 * cos(θ_elbow) * y / sin(θ_base)] / [x² + y² + (z - d0)²] )

*/
double *applyInverseKinematics(double X, double Y, double Z)
{
    double theta_base = Round(atan2(Y, X));
    double sin_theta_elbow = Round(((X * X + Y * Y + (Z - d0) * (Z - d0)) - a1 * a1 - d3 * d3) / (2 * a1 * d3));
    double theta_shoulder = 0, theta_shoulder_possible = 0, theta_elbow = 0, theta_elbow_possible = 0;

    if (sin_theta_elbow <= 1 && sin_theta_elbow >= -1)
    {
        ESP_LOGI("First if passed \n","%f\n",sin_theta_elbow);

         theta_elbow = Round(asin(sin_theta_elbow));
         theta_elbow_possible = Round(3.1415 - theta_elbow);

        double denominator = X * X + Y * Y + (Z - d0) * (Z - d0);

        if (theta_base != 90)
        {
            ESP_LOGI("Entered if theta_base != 90\n" , "%f %f\n", degrees(theta_elbow),degrees(theta_elbow_possible));
            // Calculate x / cos(theta_base)
            double numerator_theta_shoulder = (Z - d0) * (a1 + d3 * sin(theta_elbow)) + d3 * cos(theta_elbow) * X / cos(theta_base);

            double numerator_theta_shoulder_possible = (Z - d0) * (a1 + d3 * sin(theta_elbow_possible)) + d3 * cos(theta_elbow_possible) * X / cos(theta_base);

            theta_shoulder = Round(asin(numerator_theta_shoulder / denominator));
            theta_shoulder_possible = Round(asin(numerator_theta_shoulder_possible / denominator));
        }
        else if (theta_base != 0)
        {
            ESP_LOGI("Entered if theta_base != 0\n", "%f %f\n", degrees(theta_elbow),degrees(theta_elbow_possible));
            // Calculate y / sin(theta_base)
            double numerator_theta_shoulder = (Z - d0) * (a1 + d3 * sin(theta_elbow)) + d3 * cos(theta_elbow) * Y / sin(theta_base);

            double numerator_theta_shoulder_possible = (Z - d0) * (a1 + d3 * sin(theta_elbow_possible)) + d3 * cos(theta_elbow_possible) * Y / sin(theta_base);

            theta_shoulder = Round(asin(numerator_theta_shoulder / denominator));
            theta_shoulder_possible = Round(asin(numerator_theta_shoulder_possible / denominator));
        }
    }
    else
    {
        // Point is not in range of constraints
        for (int i = 0; i < 6; i++)
        {
            allPossibleAngles[i] = -9.0;
        }
        return allPossibleAngles; 
    }
     ESP_LOGI("AppInvK Function : ", "%f %f %f %f %f %f\n",degrees(theta_base),degrees(theta_shoulder),degrees(theta_elbow),degrees(theta_base),degrees(theta_shoulder_possible),degrees(theta_elbow_possible));

    // Store all possible values of angles after converting to degrees
    allPossibleAngles[0] = degrees(theta_base);
    allPossibleAngles[1] = degrees(theta_shoulder);
    allPossibleAngles[2] = degrees(theta_elbow);
    allPossibleAngles[3] = degrees(theta_base);
    allPossibleAngles[4] = degrees(theta_shoulder_possible);
    allPossibleAngles[5] = degrees(theta_elbow_possible);

    return allPossibleAngles;
}