# -*- coding: utf-8 -*-
import math
import numpy as np

'''
+-----------------------+--------------+--------------+----------+--+
| Transformation Matrix |              |              |          |  |
+-----------------------+--------------+--------------+----------+--+
| cosθ                  | -cosα * sinθ | sinα * sinθ  | a * cosθ |  |
| sinθ                  | cosα * cosθ  | -sinα * cosθ | a * sinθ |  |
| 0                     | sinα         | cosα         | d        |  |
| 0                     | 0            | 0            | 1        |  |
+-----------------------+--------------+--------------+----------+--+
+-------------------+-----------------------------+------------------+-----------------------------+--+
|  θ (about Z axis) |      d (along Z axis)       | α (about X axis) |      a (along X axis)       |  |
+-------------------+-----------------------------+------------------+-----------------------------+--+
| theta_base        | d0 (base to shoulder - 2.5) | π/2              | 0                           |  |
| theta_shoulder    | 0                           | 0                | a1 (shoulder to elbow - 12) |  |
| theta_elbow       | 0                           | π/2              | 0                           |  |
| 0                 | d3 (elbow to end - 9.5)     | 0                | 0                           |  |
+-------------------+-----------------------------+------------------+-----------------------------+--+
'''

def compute_coordinates(theta, d, alpha, a):
    
    #Converting angles to radians
    for index in range(len(theta)):
        theta[index] = math.radians(theta[index])	
    
    transformation_matrix_0_to_4 = [[1,0,0,0], [0,1,0,0], [0,0,1,0], [0,0,0,1]]		#initialization of transformation matrix

    #Multiplication of tranformation matrices
    for index in range(len(theta)):

        row1 = [math.cos(theta[index]), -math.cos(alpha[index]) * math.sin(theta[index]), \
        		math.sin(alpha[index]) * math.sin(theta[index]), a[index] * math.cos(theta[index])]

        row2 = [math.sin(theta[index]), math.cos(alpha[index]) * math.cos(theta[index]), \
        		-math.sin(alpha[index]) * math.cos(theta[index]), a[index] * math.sin(theta[index])]

        row3 = [0, math.sin(alpha[index]), math.cos(alpha[index]), d[index]]

        row4 = [0,0,0,1]

        transformation = np.matrix([row1, row2, row3, row4])
        transformation_matrix_0_to_4 = transformation_matrix_0_to_4 * transformation

    return transformation_matrix_0_to_4