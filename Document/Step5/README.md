# 物体把持ノードの作成
物体把持ノードでは画像処理ノードから送信される"/picking_position"というトピックからの情報をもとに把持を行います。<br>
# 物体把持ノードの実行方法
- 新しいターミナルを開く
- cd ~/catkin_ws
- source devel/setup.bash
- rosrun pick_and_place pick_and_place
