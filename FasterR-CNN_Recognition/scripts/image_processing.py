#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import Image
from geometry_msgs.msg import Point
from cv_bridge import CvBridge
import cv2
import numpy as np
import matplotlib.pyplot as plt
import torch
import torchvision
from torchvision import transforms
from torchvision.transforms import v2 as T

def get_transform(train):
    transforms = []
    if train:
        transforms.append(T.RandomHorizontalFlip(0.5))
    # transforms.append(T.ToDtype(torch.float, scale=True))
    transforms.append(T.ToTensor())
    return T.Compose(transforms)

def generate_colors(num_colors):
    # カラーマップを指定
    colormap = plt.cm.get_cmap('hsv', num_colors)

    # カラーマップから色を生成
    colors = [colormap(i) for i in np.linspace(0, 1, num_colors)]

    return colors

colors = generate_colors(91)
device = torch.device('cuda') if torch.cuda.is_available() else torch.device('cpu')
model = torchvision.models.detection.fasterrcnn_resnet50_fpn_v2(pretrained = True, progress=True, num_classes = 91, pretrained_backbone=True)
model.to(device)
model.eval()
eval_transform = get_transform(train=False)

COCO_INSTANCE_CATEGORY_NAMES = [
    '__background__', 'person', 'bicycle', 'car', 'motorcycle', 'airplane', 'bus',
    'train', 'truck', 'boat', 'traffic light', 'fire hydrant', 'N/A', 'stop sign',
    'parking meter', 'bench', 'bird', 'cat', 'dog', 'horse', 'sheep', 'cow',
    'elephant', 'bear', 'zebra', 'giraffe', 'N/A', 'backpack', 'umbrella', 'N/A', 'N/A',
    'handbag', 'tie', 'suitcase', 'frisbee', 'skis', 'snowboard', 'sports ball',
    'kite', 'baseball bat', 'baseball glove', 'skateboard', 'surfboard', 'tennis racket',
    'bottle', 'N/A', 'wine glass', 'cup', 'fork', 'knife', 'spoon', 'bowl',
    'banana', 'apple', 'sandwich', 'orange', 'broccoli', 'carrot', 'hot dog', 'pizza',
    'donut', 'cake', 'chair', 'couch', 'potted plant', 'bed', 'N/A', 'dining table',
    'N/A', 'N/A', 'toilet', 'N/A', 'tv', 'laptop', 'mouse', 'remote', 'keyboard', 'cell phone',
    'microwave', 'oven', 'toaster', 'sink', 'refrigerator', 'N/A', 'book',
    'clock', 'vase', 'scissors', 'teddy bear', 'hair drier', 'toothbrush']

depth_image = np.zeros((360, 680))

def depth_chatch(msg):
    try:
        depth_bridge = CvBridge()
        global depth_image
        depth_image = depth_bridge.imgmsg_to_cv2(msg, "passthrough")
    except Exception as err:
        print(err)
        
def prediction(msg):
    try:
        #　RGB画像の取得
        #-----------------------------------------------------------------------------------------------------------------------------------------------------        
        bridge = CvBridge()
        original = bridge.imgmsg_to_cv2(msg, "bgr8")
        image = original
        #-----------------------------------------------------------------------------------------------------------------------------------------------------       
        
        #　faster R-CNNの推論
        #-----------------------------------------------------------------------------------------------------------------------------------------------------       
        with torch.no_grad():
            x = eval_transform(original)
            x = x[:3, ...].to(device)
            predictions = model([x, ])
            
            boxes = [x.detach().to('cpu').numpy().tolist() for i, x in enumerate(predictions[0]['boxes'])]
            labels = [x.detach().to('cpu').numpy().tolist() for i, x in enumerate(predictions[0]['labels'])]
            scores = [x.detach().to('cpu').numpy().tolist() for i, x in enumerate(predictions[0]['scores'])]
        #-----------------------------------------------------------------------------------------------------------------------------------------------------
                
        #　予測した中で最も確率が高いバウンディングボックスのみ表示する
        #-----------------------------------------------------------------------------------------------------------------------------------------------------
        color = (0, 255, 0)  # BGR形式の色（緑）
        thickness = 2  # 描画の太さ
        image = cv2.rectangle(image,(int(boxes[0][0]), int(boxes[0][1])), (int(boxes[0][2]), int(boxes[0][3])), color, thickness)

        # 確率とクラス名を表示
        text = f'{COCO_INSTANCE_CATEGORY_NAMES[labels[0]]}: {scores[0]:.2f}'
        font = cv2.FONT_HERSHEY_SIMPLEX
        font_scale = 1
        font_thickness = 3
        text_size, _ = cv2.getTextSize(text, font, font_scale, font_thickness)
        text_position = (int(boxes[0][0]), int(boxes[0][1]) - 5)
        cv2.putText(image, text, text_position, font, font_scale, color, font_thickness)
        center_x = (int(boxes[0][2]) + int(boxes[0][0])) // 2
        center_y = (int(boxes[0][3]) + int(boxes[0][1])) // 2
        cv2.circle(image, (center_x, center_y), 5, (0, 0, 255), -1)
        
        Z = depth_image[center_x][center_y]
        X = (center_x-640/2)*(Z)/381.362467
        Y = (center_y-360/2)*(Z)/381.362467
        print("X: ", X, " Y: ", Y, " Z: ", Z)
        #-----------------------------------------------------------------------------------------------------------------------------------------------------
        
        #複数物体が存在する場合にもそれぞれ推論可能(一つしか物体がないときは重複して推論するのがめんどくさい)
        #-----------------------------------------------------------------------------------------------------------------------------------------------------
        # for x in range(len(boxes)):
        #     color = (0, 255, 0)  # BGR形式の色（緑）
        #     thickness = 2  # 描画の太さ
        #     image = cv2.rectangle(image,(int(boxes[x][0]), int(boxes[x][1])), (int(boxes[x][2]), int(boxes[x][3])), colors[labels[x]], thickness)

        #     # 確率とクラス名を表示
        #     text = f'{COCO_INSTANCE_CATEGORY_NAMES[labels[x]]}: {scores[x]:.2f}'
        #     font = cv2.FONT_HERSHEY_SIMPLEX
        #     font_scale = 1
        #     font_thickness = 3
        #     text_size, _ = cv2.getTextSize(text, font, font_scale, font_thickness)
        #     text_position = (int(boxes[x][0]), int(boxes[x][1]) - 5)
        #     cv2.putText(image, text, text_position, font, font_scale, colors[labels[x]], font_thickness)
        #     center_x = (int(boxes[x][2]) + int(boxes[x][0])) // 2
        #     center_y = (int(boxes[x][3]) + int(boxes[x][1])) // 2
        #     cv2.circle(image, (center_x, center_y), 5, (0, 0, 255), -1)
            
        #     Z = depth_image[center_x][center_y]
        #     X = (center_x-640/2)*(Z)/467.742703
        #     Y = (center_y-360/2)*(Z)/467.742703
        #     print(X, Y, Z)
        #-----------------------------------------------------------------------------------------------------------------------------------------------------
        imgMsg = bridge.cv2_to_imgmsg(image, "bgr8")
        pub = rospy.Publisher('/mask_img', Image, queue_size=10)
        pub.publish(imgMsg)
    except Exception as err:
        print(err)

def start_node():
    # nodeの初期化
    rospy.init_node('img_proc')
    rospy.loginfo('img_proc node started')
    # 画像をシミュレーションからsubscribeする
    rospy.Subscriber("/depth_camera/depth/image_raw", Image, depth_chatch)
    rospy.Subscriber("/depth_camera/color/image_raw", Image, prediction)
    rospy.spin()

if __name__ == '__main__':
    try:
        start_node()
    except rospy.ROSInterruptException:
        pass
