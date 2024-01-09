# 深層学習を用いた物体認識
# はじめに
本資料では深層学習を用いた物体認識のチュートリアルになります。<br>
シミュレーション環境内のハードの問題から認識のみにはなりますが、Documentで画像特徴から認識した箇所をDocument2の内容に置き換えるだけで深層学習を用いてピッキングできるようになります。<br>
なお、Document2の内容はDocumentに記載された内容をすべて実行したあとに行ってください。<br>
また、このチュートリアルを実行するにはそれなりのGPUを積んだPCが必要になります。適宜用意してください。
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
## RGB画像の表示
カメラで撮影される画像を可視化してみましょう。rvizが起動すると以下のような画面になると思います。
![Screenshot from 2024-01-10 01-35-47](https://github.com/ERiC-Labo/ROS_Pick_and_Place/assets/75206988/70c0cabe-f217-4d83-80e3-634d540b5766)
画面左下のaddを押す。
![Screenshot from 2024-01-10 01-46-59](https://github.com/ERiC-Labo/ROS_Pick_and_Place/assets/75206988/13f84356-a9b0-428e-a1cd-e45edce3b810)
画面中のBy topicを押す。
![Screenshot from 2024-01-10 01-48-49](https://github.com/ERiC-Labo/ROS_Pick_and_Place/assets/75206988/6814fda1-8d3d-4ac0-8745-281d56285307)
画面中のcolor以下のimage_rawを押す。
![Screenshot from 2024-01-10 01-50-53](https://github.com/ERiC-Labo/ROS_Pick_and_Place/assets/75206988/b862f77c-890a-4216-a6af-a7e950791126)
画面中のImageを選択。
![Screenshot from 2024-01-10 01-52-23](https://github.com/ERiC-Labo/ROS_Pick_and_Place/assets/75206988/5beb311f-4e7e-400a-88aa-f8503755cf66)
そうするとRGB画像が表示されます。
## 深度画像の表示
RGBと同様にして深度画像も表示させてみましょう。うまく表示できれば以下のようになります。
![Screenshot from 2024-01-10 01-54-46](https://github.com/ERiC-Labo/ROS_Pick_and_Place/assets/75206988/04791520-abbf-4adc-bcde-09f3a54e0484)
# Faster R-CNNについて
Faster R-CNNは初期の物体検出深層学習モデルになります。今回のモデルはPytorchのtorchvisionにもともと実装されているものを利用しています。<br>
このモデルはCOCODatasetを使って学習しているため、COCODatasetに含まれるクラスの物体として認識します。<br>
例えば、貴方が工場でのピッキング作業を自動化したいと思った場合には、数千枚の対象製品の画像を撮影し、アノテーションした後に学習させることで、目的の製品を認識するようなシステムが作れるようになるでしょう。<br>
自動運転のシステムを作りたい場合は、人や車、道路標識の画像を集めてアノテーションして学習する必要があります。<br>
興味がある方は、アノテーションから実装してみましょう。<br>
# 認識対象の配置
Gazeboにはすぐに使えるシミュレーション用の3Dモデルが多く用意されていますので、今回はそれを利用しましょう。<br>
![Screenshot from 2024-01-10 02-02-54](https://github.com/ERiC-Labo/ROS_Pick_and_Place/assets/75206988/e35da3ca-f9bf-454c-8028-f02a9b103b4a)
Gazeboの画面を開きInsertと書かれている部分を選択します。そうすると、多数のモデルが選択できますが、まずはBowlと書かれている場所を選択し、カメラの下に配置してみてください。気になる方は他のモデルでも大丈夫ですが、カメラから見えるものにしましょう。
![Screenshot from 2024-01-10 02-06-04](https://github.com/ERiC-Labo/ROS_Pick_and_Place/assets/75206988/a4eca1a9-86d5-4b54-b9aa-6fd7bd6b6abe)
そうすると、図のように皿が画像中に見えると思います。
# Mask R-CNNの実行
今回物体検出を行うプログラムは用意しています。物体検出の精度の問題上、一つの物体に複数のバウンディングボックスが出るのがめんどくさいため、今回は最も精度の高いクラスのバウンディングボックスのみ表示していますが、複数物体を推論するプログラムも実装しておりますので、気になる方は、コメントアウトを外して実行してみてください。<br>
では、新しいターミナルを開いて以下のように入力してみましょう。
~~~
cd catkin_ws
source devel/setup.bash
rosrun FasterR-CNN_Recognition image_processing.py 
~~~
続いて認識結果を可視化してみましょう。
RGB画像を表示したのと同様にしてrvizからTopicを確認してください。
![Screenshot from 2024-01-10 02-13-51](https://github.com/ERiC-Labo/ROS_Pick_and_Place/assets/75206988/f461dc4c-c717-4a02-9ce8-538cf3ce4013)
そうすると、画像のように新たなTopicが出てきていると思うのでImageを選択してください。
![Screenshot from 2024-01-10 02-15-28](https://github.com/ERiC-Labo/ROS_Pick_and_Place/assets/75206988/754901e7-87e0-42c6-a963-5fc95df8b28a)<br>
そうするとこのような画面が表示されていると思います。どうやらMask R-CNNちゃんは皿のことをフリスビーと認識してしまっているようですが、位置はちゃんと認識できているんじゃないでしょうか。<br>
画像中の赤い点はバウンディングボックスの中心をあらわしていますが、こうした特徴点を把持位置として利用することで、ロボットハンドの性能によっては最適ではないかもしれませんが、Document1で行った画像特徴からの把持位置認識と同様にしてロボットでピッキングすることができます。<br>
ターミナルに戻ってみましょう。<br>
![Screenshot from 2024-01-10 02-11-47](https://github.com/ERiC-Labo/ROS_Pick_and_Place/assets/75206988/a70de70b-84a4-4e18-a091-7f74718063c9)<br>
ターミナル上に記載されているのは、カメラから見た皿のXYZ座標になります。<br>
ロボットで把持するときにはこの値をロボットの土台部分を原点とする座標系に変換することで、把持ができるようになります。<br>
![Screenshot from 2024-01-10 02-24-25](https://github.com/ERiC-Labo/ROS_Pick_and_Place/assets/75206988/6ba4cc1c-8c3d-4ac5-b5d8-b0e4380bd85c)<br>
コーラの缶をおいても認識自体はできています。皆さんもカメラの位置を変えたり、対象物体を変えてみたりしながら遊んでみてください。
