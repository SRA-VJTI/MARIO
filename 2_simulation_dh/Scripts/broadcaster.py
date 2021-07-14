#!/usr/bin/env python3
import rospy
import tf_conversions
import tf
import geometry_msgs.msg
import math

if __name__ == "__main__":
    #node initialized
    rospy.init_node('tf2_broadcaster')

    #tf broadcaster defined
    link1_to_base = tf.TransformBroadcaster()
    mobile1_to_link1 = tf.TransformBroadcaster()
    link2_to_link1 = tf.TransformBroadcaster()
    mobile2_to_link2 = tf.TransformBroadcaster()
    link3_to_link2 = tf.TransformBroadcaster()
    mobile3_to_link3 = tf.TransformBroadcaster()
    link4_to_link3 = tf.TransformBroadcaster()
    mobile4_to_link4 = tf.TransformBroadcaster()
    
    #DH parameters for link 1
    alpha1 = math.pi/2
    link1_orientation = tf.transformations.quaternion_from_euler(alpha1, 0, 0)
    new_alpha1 = 0 
    d1 = 0.5
    new_d1 = 0
    
    #DH parameters for link 2
    a2 = 0.5
    new_a2 = 0
    link2_orientation = tf.transformations.quaternion_from_euler(0, 0, 0)
    
    #DH parameters for link 3
    theta3 = math.pi/2
    new_theta3 = 0
    alpha3 = math.pi/2
    new_alpha3 = 0
    dummy_a3 = 0.1
    new_dummy_a3 = 0
    link3_orientation = tf.transformations.quaternion_from_euler(alpha3, 0, theta3)

    #DH parameters for link 4
    d4 = 0.5
    new_d4 = 0
    link4_orientation = tf.transformations.quaternion_from_euler(0, 0, 0)
    
    while not rospy.is_shutdown():
        try:            
            #Transform data is sent 
            link1_to_base.sendTransform((0, 0, d1), link1_orientation, rospy.Time.now(), "link1", "base")
            link2_to_link1.sendTransform((a2, 0, 0), link2_orientation, rospy.Time.now(), "link2", "link1")
            link3_to_link2.sendTransform((dummy_a3, 0, 0), link3_orientation, rospy.Time.now(), "link3", "link2")
            link4_to_link3.sendTransform((0, 0, d4), link4_orientation, rospy.Time.now(), "link4", "link3")
            
            # Tracing from base and link1
            if new_d1 < d1:
                new_d1 = new_d1 + 0.005
                rospy.sleep(0.1)
                print("new_d1 updated", new_d1)
                new_link1_orientation = tf.transformations.quaternion_from_euler(new_alpha1, 0, 0)
                mobile1_to_link1.sendTransform((0, 0, new_d1), new_link1_orientation, rospy.Time.now(), "mobile1", "base")            
            if new_alpha1 < alpha1 and new_d1>= d1:
                print("mobile1_to_link1")
                new_alpha1 = new_alpha1 + 0.015
                rospy.sleep(0.1)
                print("new_alpha1 updated", new_alpha1)
                new_link1_orientation = tf.transformations.quaternion_from_euler(new_alpha1, 0, 0)
                mobile1_to_link1.sendTransform((0, 0, new_d1), new_link1_orientation, rospy.Time.now(), "mobile1", "base")            
            
            # Tracing from link1 and link2
            if new_alpha1 >= alpha1 and new_d1 >= d1 and new_a2 < a2 :            
                print("mobile2_to_link2")
                if new_a2 < a2:
                    new_a2 = new_a2 + 0.005
                    rospy.sleep(0.1)
                    print("new_a2 updated", new_a2)
                    mobile2_to_link2.sendTransform((new_a2, 0, 0), link2_orientation, rospy.Time.now(), "mobile2", "link1")
                
            # Tracing from link2 and link3
            if new_alpha1 >= alpha1 and new_d1 >= d1 and new_a2 >= a2 :            
                print("mobile3_to_link3")
                if new_theta3 < theta3:
                    new_theta3 = new_theta3 + 0.015
                    new_link3_orientation = tf.transformations.quaternion_from_euler(new_alpha3, 0, new_theta3)
                    mobile3_to_link3.sendTransform((0, 0, 0), new_link3_orientation, rospy.Time.now(), "mobile3", "link2")
                    rospy.sleep(0.1)
                    print("new_theta3 updated", new_theta3)
                if new_alpha3 < alpha3 and new_theta3 >= theta3:
                    new_alpha3 = new_alpha3 + 0.015
                    new_dummy_a3 = new_dummy_a3 + 0.00095493
                    new_link3_orientation = tf.transformations.quaternion_from_euler(new_alpha3, 0, new_theta3)
                    mobile3_to_link3.sendTransform((new_dummy_a3, 0, 0), new_link3_orientation, rospy.Time.now(), "mobile3", "link2")
                    rospy.sleep(0.1)
                    print("new_alpha3 updated", new_alpha3)
            
            # Tracing from link3 and link4
            if new_alpha1 >= alpha1 and new_d1 >= d1 and new_a2 >= a2 and new_theta3 >= theta3 and new_alpha3 >= alpha3 and new_d4 < d4:
                     new_d4 = new_d4 + 0.005
                     rospy.sleep(0.1)
                     print("new_d4_updated", new_d4)
                     mobile4_to_link4.sendTransform((0, 0, new_d4), link4_orientation, rospy.Time.now(), "mobile4", "link3")       

            # All parameters values are reset
            if new_alpha1 >= alpha1 and new_d1 >= d1 and new_a2 >= a2 and new_theta3 >= theta3 and new_alpha3 >= alpha3 and new_d4 >= d4:
                print("all values of theta,d,alpha,a rest")
                new_alpha1 = 0
                new_d1 = 0
                new_a2 = 0
                new_theta3 = 0
                new_alpha3 = 0
                new_d4 = 0
                new_dummy_a3 = 0

        except:
            continue

    # rospy.spin()
