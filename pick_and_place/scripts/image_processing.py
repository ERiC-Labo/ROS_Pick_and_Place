#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import Image
from geometry_msgs.msg import Point
from cv_bridge import CvBridge
import cv2
import numpy as np




# コールバック関数
def process_image(msg):
    try:
        bridge = CvBridge()
        # subscribeしたImage型のmsgをopencvで扱える形式に変換
        original = bridge.imgmsg_to_cv2(msg, "bgr8")
        # HSV画像の作成
        img = cv2.cvtColor(original, cv2.COLOR_BGR2HSV)
        # マスク画像作成
        mask_img = cv2.inRange(img, (0, 127, 0), (10, 255, 255))
        mu = cv2.moments(mask_img, False)
        x, y = int(mu["m10"]/mu["m00"]), int(mu["m01"]/mu["m00"])
        X = (x-640/2)*(1.24)/381.362467 + 0.3
        Y = (y-360/2)*(1.24)/381.362467
        Z = 1.0
        
        picking_point = Point()
        picking_point.x = X
        picking_point.y = -Y
        picking_point.z = Z
        # opencv型からImage型のmsgに変換
        imgMsg = bridge.cv2_to_imgmsg(mask_img, "mono8")
        
        # publish
        pub = rospy.Publisher('mask_img', Image, queue_size=10)
        pub.publish(imgMsg)
        position_pub = rospy.Publisher('/picking_position', Point, queue_size = 10)
        position_pub.publish(picking_point)
    except Exception as err:
        print(err)

def start_node():
    # nodeの初期化
    rospy.init_node('img_proc')
    rospy.loginfo('img_proc node started')
    # subscribeする
    rospy.Subscriber("/camera/image_raw", Image, process_image)
    rospy.spin()

if __name__ == '__main__':
    try:
        start_node()
    except rospy.ROSInterruptException:
        pass