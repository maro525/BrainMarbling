# DataDrivenArt

## openframeworks
- srcフォルダの中身はopenframeworksのソースコード

### 内容
- OpenBCIのAppから、oscでBands Powerを受け取る
- 整形
- 描写
- pythonにudp通信でBands Powerのデータを送る
- pythonから機械学習の予測したデータを受け取る
- それを元にArduinoにシリアル通信

## Python

### 内容
- kmeansを用いてデータをクラスタリング
- そのモデルを元に予測
- ofに送り返す(未実装)

## Arduino

### 内容
- ロボットの動きの記述
- シリアル通信でデータを読んで、それに基づいて動きが決まるようなプログラム
