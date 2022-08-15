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
2. 新規仮想マシンの作成をクリック
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 13_12_23](https://user-images.githubusercontent.com/75206988/184590409-93d82fc4-7e7a-4680-bbc6-802dd8ac0d71.png)<br>
3. 参照をクリックし先ほどダウンロードしたISOファイルを選択
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 13_13_18](https://user-images.githubusercontent.com/75206988/184590521-dfe148d2-2ef9-4995-9c80-1c7c85cde673.png)<br>
4. ユーザー名とパスワードを入力
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 13_14_36](https://user-images.githubusercontent.com/75206988/184590571-59936667-e08d-475c-88bc-4a8a05189d26.png)<br>
5. 仮想環境の名前を入力
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 14_41_28](https://user-images.githubusercontent.com/75206988/184590667-99a11ea6-29ed-4ba4-98ed-6a370ddcc9ec.png)<br>
6. 特に変更する必要はなし
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 13_15_35](https://user-images.githubusercontent.com/75206988/184590743-6eb63ebc-82bd-4083-a498-b78d8af8a0f3.png)<br>
7. 完了
![VMware Workstation 16 Player (非営利目的の使用のみ) 2022_08_15 13_15_46](https://user-images.githubusercontent.com/75206988/184590805-60c72201-d16e-47df-b264-962c661f93a7.png)<br>
## Ubuntuの初期設定
1. 先ほど設定したパスワードを入力してログインしてください．<br>
