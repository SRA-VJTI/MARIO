import numpy as np
import math

# Variables
d0 = 10		#Base to shoulder link length
a1 = 6		#Shoulder to elbow link length
d3 = 13		#Elbow to end effector link length

ROUNDING_ERROR = 10

def compute_angles(x, y, z):
	theta_base = round(math.atan2(y, x), ROUNDING_ERROR)

	sin_theta_elbow = round(((x * x + y * y + (z - d0) * (z - d0)) - a1 * a1 - d3 * d3) / (2 * a1 * d3), ROUNDING_ERROR)

	if (sin_theta_elbow) <= 1 and (sin_theta_elbow) >=- 1:

		theta_elbow = round(math.asin(sin_theta_elbow), ROUNDING_ERROR)
		theta_elbow_possible = round(math.pi - theta_elbow, ROUNDING_ERROR)

		r = math.sqrt(x * x + y * y)
		dz = z - d0

		def get_shoulder(theta_elbow_val):
			A = d3 + a1 * math.sin(theta_elbow_val)
			B = a1 * math.cos(theta_elbow_val)
			return math.atan2(A * r + B * dz, B * r - A * dz) - theta_elbow_val

		theta_shoulder = round(get_shoulder(theta_elbow), ROUNDING_ERROR)
		theta_shoulder_possible = round(get_shoulder(theta_elbow_possible), ROUNDING_ERROR)

	else:

		print ("Point is not in range due to constraint in link length")
		return [[None, None, None],[None, None, None]]

	result = [[math.degrees(theta_base), math.degrees(theta_shoulder), math.degrees(theta_elbow)], \
			[math.degrees(theta_base), math.degrees(theta_shoulder_possible), math.degrees(theta_elbow_possible)]]

	# Return set of possible angles in degrees
	return result
