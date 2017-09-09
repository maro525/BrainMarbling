# DataDrivenArt

## openframeworks
- srcフォルダの中身はopenframeworksのソースコード

### 内容
- OpenBCIのAppから、oscでBands Powerを受け取る
- 受け取ったデータを整形
- 整形したデータを描写
- (整形したデータをcsvにして保存する機能あり. →  機械学習させるデータ用)
- pythonにudp通信でBands Powerのデータを送る
- pythonから機械学習の予測したデータを受け取る
- それを元にArduinoにシリアル通信

## Python

### 内容
- kmeansを用いてデータをクラスタリング(ofで整形して作成したcsvデータで学習)
- そのモデルを元に予測
- ofに送り返す

## Arduino

### 内容
- ロボットの動きの記述
- シリアル通信でデータを読んで、それに基づいて動きが決まるようなプログラム
