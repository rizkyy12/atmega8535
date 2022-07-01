#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Pose2D

def pose_Cb(pose_msg):

    global x, y, w
    x = pose_msg.x
    y = pose_msg.y
    w = pose_msg.theta

    rospy.loginfo("x: %f", x)
    rospy.loginfo("y: %f", y)
    rospy.loginfo("w: %f", w)

if __name__ == '__main__':
    try:
        rospy.init_node("pose_sub", anonymous=False)
        rospy.Subscriber('/pose_test', Pose2D, pose_Cb)
        rospy.spin()
    except rospy.ROSInterruptException:
        rospy.loginfo("node terminated.")