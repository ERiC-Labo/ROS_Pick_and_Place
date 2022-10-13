# シミュレーション環境の解説
## シミュレーション環境起動方法
- Ctrl+Alt+Tでターミナルを開く
- cd ~/catkin_ws/
- source devel/setup.bash
- roslaunch pick_and_place spawn_gazebo_pick_and_place.launch
- 下の図のような画面が表示されたら成功です。
- 注意：起動時に赤い箱が机の下に落ちている場合がありますがその場合はCtrl+Cでプログラムを終了し、もう一度シミュレーションを起動してください。
![default_gzclient_camera(1)-2022-06-17T11_01_53 327123](https://user-images.githubusercontent.com/75206988/174207494-5a5d43cc-2f23-40b3-b2fd-4db18103a361.jpg)
## シミュレーション環境の説明
本シミュレーションで利用するロボットはUniversal Robot社のUR3というロボットで、ロボットハンドはRobotiq社のRobotiq-HandEを使います。<br>
ロボットは高さ0.7mの机に取り付けられています。ロボットに頭上にある正方形の物体はカメラで、このカメラから取得した画像をもとに赤い直方体の特徴点を求め、
赤い物体を把持し、奥にある箱に入れることを目標とします。<br>
# Moveit!の実行方法
先程シミュレーション環境を起動しましたがこのままではロボットを動かすことはできません。<br>
ロボットを動かすためには逆運動解を求める必要がありますが、Moveit!を使うと簡単にロボットを動かすことができます。<br>
- 新しいターミナルを開く
- cd ~/catkin_ws/
- source devel/setup.bash
- roslaunch moveit_pick_and_place move_group.launch sim:=true
