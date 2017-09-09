#include <VarSpeedServo.h>

VarSpeedServo sheight;//右側 my
VarSpeedServo sshift;//下myservo
VarSpeedServo slength;//左myservo2
VarSpeedServo sfude; //myservo3
int SPEED1 = 20;


boolean state = false;

void setup() {
  Serial.begin(9600);
  sheight.attach(8);
  sshift.attach( 9 );
  slength.attach( 10 );
  sfude.attach( 11 );// Port 9 にサーボモーター制御線をつなぐ


}

void loop() {

  if (Serial.available() > 0) {//データ来てるかチェック
    int data = Serial.read();//データを１バイト読み込む
    //データaがきたら、関数servomovingを実行。そうでないときは初期値？
    if (data == 'b' ) {
      startset();
    }

    if (data == 'm') {
      servoloop();
    }
    if (data == 's') {
      supply();
    }

    if (data == 'f') {
      finish();
    }


  }

}



void startset() {
  delay(1000);
  //初期値に持っていく
  sfude.write(38, SPEED1);//減らすと左、足すと右 初期値
  slength.write(100, SPEED1);
  sheight.write(80, SPEED1);
  delay(1000);
  sshift.write(90, SPEED1);
  slength.wait();
  sshift.wait();
  sheight.wait();
  sfude.wait();


  //筆を位置まで持っていく
  sshift.write(105, SPEED1);
  sshift.wait();
  //delay(1000);
  slength.write(50, SPEED1); //足すと短くなる
  sheight.write(45, SPEED1);//足すと下がる
  //sfude.write(70, SPEED1);
  slength.wait();
  sshift.wait();
  sheight.wait();
  delay(2000);

  //墨
  sfude.write(107, SPEED1);//右

  sfude.wait();

  //筆を下げる
  sheight.write(55,50); //足すと下がる
  //sfude.write(70, SPEED1);
  sheight.wait();
  delay(500);

  //筆をあげる
  sheight.write(45);//足すと下がる
  //sfude.write(70, SPEED1);
  sheight.wait();

  //油
  sfude.write(15, SPEED1);//左
  sfude.wait();
  delay(1000);

  //筆を下げる
  sheight.write(57, 40); //足すと下がる
  //sfude.write(70, SPEED1);
  sheight.wait();
  delay(500);

  //筆をあげる
  sheight.write(45);//足すと下がる
  //sfude.write(70, SPEED1);
  sheight.wait();

}

/*
  void servomoving() {
  //筆を位置まで持っていく
  sshift.write(105, SPEED1);
  sshift.wait();
  //delay(1000);
  slength.write(50, SPEED1); //足すと短くなる
  sheight.write(40, SPEED1);//足すと下がる
  //sfude.write(70, SPEED1);
  slength.wait();
  sshift.wait();
  sheight.wait();
  delay(2000);

  }
*/


void servoloop() {



  //筆を位置まで持っていく
  sfude.write(38, SPEED1);//減らすと左、足すと右 初期値
  sfude.wait();

  sshift.write(105, SPEED1);
  sshift.wait();
  //delay(1000);
  slength.write(50, SPEED1); //足すと短くなる
  sheight.write(45, SPEED1);//足すと下がる
  //sfude.write(70, SPEED1);
  slength.wait();
  sshift.wait();
  sheight.wait();
  delay(2000);

  //墨
  sfude.write(107, SPEED1);//右
  sfude.wait();

  //筆を下げる
  sheight.write(57, 40); //足すと下がる
  //sfude.write(70, SPEED1);
  sheight.wait();
  delay(500);

  //筆をあげる
  sheight.write(45);//足すと下がる
  //sfude.write(70, SPEED1);
  sheight.wait();

  //油
  sfude.write(15, SPEED1);//左
  sfude.wait();
  delay(1000);

  //筆を下げる
  sheight.write(57, 40); //足すと下がる
  //sfude.write(70, SPEED1);
  sheight.wait();
  delay(500);

  //筆をあげる
  sheight.write(45);//足すと下がる
  //sfude.write(70, SPEED1);
  sheight.wait();


}

void supply() {
  //初期値に持っていく土台なし
  //sfude.write(38, SPEED1);//減らすと左、足すと右 初期値

  slength.write(100, SPEED1);
  sheight.write(80, SPEED1);
  delay(1000);
  sfude.write(90, SPEED1);
  sfude.wait();
  delay(500);
  sfude.write(43, SPEED1);
  sfude.wait();
  //sshift.write(90, SPEED1);
  slength.wait();
  //sshift.wait();
  sheight.wait();
  sfude.wait();
  delay(1000);

  //供給位置まで行く
  sshift.write(140, SPEED1);
  sshift.wait();
  delay(500);



  //筆下げる
  slength.write(80, SPEED1);
  slength.wait();
  delay(500);
  sheight.write(96, 10); //足すと下がる
  sheight.wait();
  delay(1000);

  //筆あげる
  sheight.write(80, 10); //足すと下がる
  sheight.wait();
  delay(500);
  slength.write(100, SPEED1);
  slength.wait();
  delay(1000);

  //供給位置に戻る
  sshift.write(105, SPEED1);
  sshift.wait();
  delay(500);

  //筆を位置まで持っていく
  sshift.write(105, SPEED1);
  sshift.wait();
  //delay(1000);
  slength.write(50, SPEED1); //足すと短くなる
  sheight.write(45, SPEED1);//足すと下がる
  //sfude.write(70, SPEED1);
  slength.wait();
  sshift.wait();
  sheight.wait();
  delay(2000);

  //墨
  sfude.write(107, SPEED1);//右
  sfude.wait();

  //筆を下げる
  sheight.write(57, 40); //足すと下がる
  //sfude.write(70, SPEED1);
  sheight.wait();
  delay(500);

  //筆をあげる
  sheight.write(45);//足すと下がる
  //sfude.write(70, SPEED1);
  sheight.wait();

  //油
  //油
  sfude.write(15, SPEED1);//左
  sfude.wait();
  delay(1000);

  //筆を下げる
  sheight.write(57, 40); //足すと下がる
  //sfude.write(70, SPEED1);
  sheight.wait();
  delay(500);

  //筆をあげる
  sheight.write(45);//足すと下がる
  //sfude.write(70, SPEED1);
  sheight.wait();
  delay(500);

}


void finish(){
  delay(1000);
  //初期値に持っていく
  //sfude.write(38, SPEED1);//減らすと左、足すと右 初期値
  slength.write(100, SPEED1);
  sheight.write(80, SPEED1);
  delay(1000);
  sshift.write(90, SPEED1);
  slength.wait();
  sshift.wait();
  sheight.wait();
   sfude.write(90, SPEED1);
  sfude.wait();
  delay(500);
  sfude.write(43, SPEED1);
  sfude.wait();
}



