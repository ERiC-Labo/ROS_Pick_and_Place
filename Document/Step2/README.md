# 環境構築
## 初めに
今回のチュートリアルはUbuntu20.04で実行する必要があります．<br>
Ubuntu20.04をOSとして使っているPCで実行することが望ましいですが，Ubuntu20.04の環境を用意することが難しい人はVMWareなどの仮想環境で利用してください．<br>
# Windows上でのUbuntu仮想環境の設定
## VMWareのインストール
1. まずVMWareインストールします．[ここをクリックしてVMWareのサイトに移動してください．](https://customerconnect.vmware.com/jp/downloads/#all_products)<br>
2. 以下の画像の製品をダウンロードをクリック
![VMWare_Install_1png](https://user-images.githubusercontent.com/75206988/184588792-0522b1ea-c657-4a06-b487-6fd301c63eaa.png)<br>
3. ダウンロードするをクリック
![VMWare_Install_2](https://user-images.githubusercontent.com/75206988/184589032-b534d4ca-05ea-48ff-91e3-60b88dd1bb17.png)<br>
4. Windows64bit版をダウンロード
![VMWare_Install_3](https://user-images.githubusercontent.com/75206988/184589357-689d2b94-18d8-4ae2-93fb-8f6fbbf273bc.png)<br>
5. exeファイルを実行
![VMWare_Install_4](https://user-images.githubusercontent.com/75206988/184589454-a0229587-e23a-4c42-afea-8d0aeb00a11a.png)<br>
6. VMWareをインストールする際は非営利使用を選択してください．あとは特に選択するところはありません．
## Ubuntu20.04のインストール
日本語版Ubuntu20.04のISOファイルを入手します．[ここをクリックしてUbuntuのサイトに移動してください．](https://www.ubuntulinux.jp/News/ubuntu2004-ja-remix)<br>
以下の画像の赤い矢印の先のリンクをクリックしてISOファイルを入手します．
![Ubuntu 20 04 LTS 日本語 Remix リリース _ Ubuntu Japanese Team - Google Chrome 2022_08_15 15_54_24](https://user-images.githubusercontent.com/75206988/184589972-c97e0b32-2e38-47f6-8f40-7b1b2d4e4cac.png)<br>
## 仮想環境の作成
1. VMWareを起動
2. 新規仮想マシンの作成をクリック<br>
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 13_12_23](https://user-images.githubusercontent.com/75206988/184590409-93d82fc4-7e7a-4680-bbc6-802dd8ac0d71.png)<br>
3. 参照をクリックし先ほどダウンロードしたISOファイルを選択<br>
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 13_13_18](https://user-images.githubusercontent.com/75206988/184590521-dfe148d2-2ef9-4995-9c80-1c7c85cde673.png)<br>
4. ユーザー名とパスワードを入力<br>
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 13_14_36](https://user-images.githubusercontent.com/75206988/184590571-59936667-e08d-475c-88bc-4a8a05189d26.png)<br>
5. 仮想環境の名前を入力<br>
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 14_41_28](https://user-images.githubusercontent.com/75206988/184590667-99a11ea6-29ed-4ba4-98ed-6a370ddcc9ec.png)<br>
6. 特に変更する必要はなし<br>
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 13_15_35](https://user-images.githubusercontent.com/75206988/184590743-6eb63ebc-82bd-4083-a498-b78d8af8a0f3.png)<br>
7. 完了<br>
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 13_15_46](https://user-images.githubusercontent.com/75206988/184590805-60c72201-d16e-47df-b264-962c661f93a7.png)<br>
## Ubuntuの初期設定
1. 先ほど設定したパスワードを入力してログインしてください．<br>
2. おそらく画面が小さくなっているので設定を変更します．以下の画像の赤い丸で囲んである場所をクリックしてください．<br>
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 15_02_23](https://user-images.githubusercontent.com/75206988/184591622-b2e5cec3-0e9d-4a91-888c-fb8a26b9dfac.png)<br>
4. 設定を探してクリック<br>
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 15_02_33](https://user-images.githubusercontent.com/75206988/184591779-831c9de0-f8b4-412c-a241-deb4f344806e.png)<br>
5. ディスプレイをクリックし，そのあと解像度を1920x1080に変更<br>
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 15_03_31](https://user-images.githubusercontent.com/75206988/184591899-7fc84ad2-4c96-4178-b5ee-91f060d0cd21.png)<br>
6. 画面サイズがちょうどよくなると思います．<br>
7. 次に日本語入力をできるようにします．以下の画像のように画面の右上の場所をクリックしMozocに変更してください．<br>
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 15_04_05](https://user-images.githubusercontent.com/75206988/184592272-3203a8b9-5379-45e1-89c7-e67015d9ecd8.png)<br>
8. 次にUbuntuのバージョンアップをします．そのために，まずはターミナルを開きます．Ubuntuではターミナルから設定を変更したりプログラムを実行したりすることが多いので，いつでもターミナルを開けるようにしておいてください．<br>
9. 端末をクリックしてください．<br>
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 15_05_05](https://user-images.githubusercontent.com/75206988/184592763-80a05441-07a5-46f7-8aab-58b7894615b5.png)<br>
10. ターミナルが開けたら，sudo apt updateと入力し，Enterを押す．その後パスワードを入力してEnter.<br>
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 15_05_30](https://user-images.githubusercontent.com/75206988/184593091-14bbb8e1-19b2-4ee7-bd14-2df12624ebbd.png)<br>
11. その後，以下の画像のようにsudo apt upgradeと入力し実行,しばらく時間がかかると思います．<br> 
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 15_06_09](https://user-images.githubusercontent.com/75206988/184593327-216e6cfb-130a-4cdd-a7e4-880cb4805ccb.png)<br>
12. upgrade が終了したら再起動<br>
## ROSのインストール
1. まずはターミナルを開きます．ターミナルはCtrl+Alt+tでも開けます．<br>
2. sources.listの設定：ターミナルに以下のように入力．<br>
~~~
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
~~~
3. curlがインストールされていないのでインストール：ターミナルに以下のように入力．<br>
~~~
sudo apt install curl
~~~
4. 公開鍵の設定：ターミナルに以下のように入力．<br>
~~~
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
~~~
5. 状態の更新：ターミナルに以下のように入力．<br>
~~~
sudo apt update
~~~
6. ROSのインストール：ターミナルに以下のように入力．<br>
~~~
sudo apt install ros-noetic-desktop-full
~~~
7. 環境設定：ターミナルに以下のように入力．<br>
~~~
echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
~~~
~~~
source ~/.bashrc
~~~
8. ビルドに必要な依存パッケージ：ターミナルに以下のように入力．<br>
~~~
sudo apt install python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential
~~~
9. rosdepの初期化：ターミナルに以下のように入力．<br>
~~~
sudo rosdep init
~~~
~~~
rosdep update
~~~
## gitcloneの仕方
1. このリポジトリのトップに移動．<br>
2. 赤く囲っている部分をクリック．<br>
![ERiC-Labo_ROS_Pick_and_Place - Google Chrome 2022_10_13 18_20_07](https://user-images.githubusercontent.com/75206988/195550360-f1457b98-119a-466d-b81d-20768c06251b.png)
3. 赤く囲っている部分をクリックしてリンクをクリップボードにコピー
![ERiC-Labo_ROS_Pick_and_Place - Google Chrome 2022_10_13 18_20_22](https://user-images.githubusercontent.com/75206988/195550701-41e31820-ea3d-4ede-a161-00c4ec320503.png)
