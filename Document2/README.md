# 深層学習を用いた物体認識
# はじめに
本資料では深層学習を用いた物体認識のチュートリアルになります。<br>
シミュレーション環境内のハードの問題から認識のみにはなりますが、Documentで画像特徴から認識した箇所をDocument2の内容に置き換えるだけで深層学習を用いてピッキングできるようになります。<br>
なお、Document2の内容はDocumentに記載された内容をすべて実行したあとに行ってください。
# 環境の立ち上げ
ターミナル上で以下のように入力
~~~
cd catkin_ws
source devel/setup.bash
roslaunch FasterR-CNN_Recognition camera.launch
~~~
そうすると以下のような画面が出力されると思います。
![default_gzclient_camera(1)-2024-01-10T01_30_37 352576](https://github.com/ERiC-Labo/ROS_Pick_and_Place/assets/75206988/440131eb-a208-4335-ab27-f162c5411328)
画面に浮かんでいるのが今回利用するカメラで、上から下を見下ろしているような画角になります。<br>
# rvizの立ち上げ
新しいターミナルを開き以下のように入力。
~~~
cd catkin_ws
source devel/setup.bash
rviz
~~~
カメラで撮影される画像を可視化してみましょう。rvizが起動すると以下のような画面になると思います。
![Screenshot from 2024-01-10 01-35-47](https://github.com/ERiC-Labo/ROS_Pick_and_Place/assets/75206988/70c0cabe-f217-4d83-80e3-634d540b5766)
画面左下のaddを押す。
![Screenshot from 2024-01-10 01-46-59](https://github.com/ERiC-Labo/ROS_Pick_and_Place/assets/75206988/13f84356-a9b0-428e-a1cd-e45edce3b810)
画面中のBy topicを押す。
![Screenshot from 2024-01-10 01-48-49](https://github.com/ERiC-Labo/ROS_Pick_and_Place/assets/75206988/6814fda1-8d3d-4ac0-8745-281d56285307)
画面中のcolor以下のimage_rawを押す。
![Screenshot from 2024-01-10 01-50-53](https://github.com/ERiC-Labo/ROS_Pick_and_Place/assets/75206988/b862f77c-890a-4216-a6af-a7e950791126)
画面中のImageを選択。
