import numpy as np
import math

# Variables
d0 = 2.5		#Base to shoulder link length
a1 = 12.0		#Shoulder to elbow link length
d3 = 9.5		#Elbow to end effector link length

def compute_angles(x, y, z):
	theta_base = math.atan2(y, x)	

	sin_theta_elbow = ((x * x + y * y + (z - d0) * (z - d0)) - a1 * a1 - d3 * d3) / (2 * a1 * d3)

	if sin_theta_elbow <= 1 and sin_theta_elbow >=- 1:
		
		theta_elbow = math.asin(sin_theta_elbow)
		theta_elbow_possible = math.pi - theta_elbow

		denominator = x * x + y * y + (z - d0) * (z - d0)

		if theta_base != 90:

			numerator_theta_shoulder = (z - d0) * (a1 + d3 * math.sin(theta_elbow)) \
										+ d3 * math.cos(theta_elbow) * x / math.cos(theta_base)

			numerator_theta_shoulder_possible = (z - d0) * (a1 + d3 * math.sin(theta_elbow_possible)) + \
										d3 * math.cos(theta_elbow_possible) * x / math.cos(theta_base)

			theta_shoulder = math.asin(numerator_theta_shoulder / denominator)
			theta_shoulder_possible = math.asin(numerator_theta_shoulder_possible / denominator)
			
		elif theta_base != 0:

			numerator_theta_shoulder = (z - d0) * (a1 + d3 * math.sin(theta_elbow)) \
										+ d3 * math.cos(theta_elbow) * y / math.sin(theta_base)
			numerator_theta_shoulder_possible = (z - d0) * (a1 + d3 * math.sin(theta_elbow_possible)) \
												+ d3 * math.cos(theta_elbow_possible) * y / math.sin(theta_base)
												
			theta_shoulder = math.asin(numerator_theta_shoulder / denominator)
			theta_shoulder_possible = math.asin(numerator_theta_shoulder_possible / denominator)

	else:

		print "Point is not in range due to constrain in link length"
		return [None, None, None]

	result = [[math.degrees(theta_base), math.degrees(theta_shoulder), math.degrees(theta_elbow)], \
			[math.degrees(theta_base), math.degrees(theta_shoulder_possible), math.degrees(theta_elbow_possible)]]

	return result