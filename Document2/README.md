# 深層学習を用いた物体認識
# はじめに
本資料では深層学習を用いた物体認識のチュートリアルになります。<br>
シミュレーション環境内のハードの問題から認識のみにはなりますが、Documentで画像特徴から認識した箇所をDocument2の内容に置き換えるだけで深層学習を用いてピッキングできるようになります。<br>
なお、Document2の内容はDocumentに記載された内容をすべて実行したあとに行ってください
# 環境の立ち上げ
ターミナル上で以下のように入力
~~~
cd catkin_ws
source devel/setup.bash
roslaunch FasterR-CNN_Recognition
~~~

