#include <Arduino.h>
#include <SPEED_CTRL.h>
int speed_run = 150; 
SPEED_CTRL speedCtrl;
int flag = 0;
int inter() {
  if (digitalRead(11) == HIGH && digitalRead(12) == LOW) {
    return 1;
  }
  else if(digitalRead(12) == HIGH && digitalRead(11) == LOW){
    return 2;
  }
  else if(digitalRead(12) == HIGH && digitalRead(11) == HIGH){
    return 3;
  }
  return 0; // 添加返回语句
}

void run_t(int speed_=speed_run,int time_=0){
  speedCtrl.motor_ctrl(0, 0); // 设置左电机速度为200
  speedCtrl.motor_ctrl(1, 0); // 设置左电机速度为200
  speedCtrl.motor_ctrl(2, 0); // 设置左电机速度为200
  speedCtrl.motor_ctrl(3, 0); // 设置左电机速度为200
}

void run_q(int speed_=speed_run,int time_=0){
  speedCtrl.motor_ctrl(0, speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(1, speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(2, speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(3, speed_); // 设置左电机速度为200
    if (time_ != 0){
    delay(time_);
    run_t();
  }
}

void run_h(int speed_=speed_run,int time_=0){
  speedCtrl.motor_ctrl(0, -speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(1, -speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(2, -speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(3, -speed_); // 设置左电机速度为200
    if (time_ != 0){
    delay(time_);
    run_t();
  }
}

void run_z(int speed_=speed_run,int time_=0){
  speedCtrl.motor_ctrl(0, speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(1, -speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(2, -speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(3, speed_); // 设置左电机速度为200
  if (time_ != 0){
    delay(time_);
    run_t();
  }
}

void run_y(int speed_=speed_run,int time_=0){
  speedCtrl.motor_ctrl(0, -speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(1, speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(2, speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(3, -speed_); // 设置左电机速度为200
    if (time_ != 0){
    delay(time_);
    run_t();
  }
}

void turn_right(){
  run_y();
  while (analogRead(A1)<700){
  run_y();
  }
  while (analogRead(A1)-analogRead(A2)<100){
      run_t();
  }
}

void turn_left(){
  run_z();
  while (analogRead(A2)<700){
  run_z();
  }
  while (analogRead(A1)-analogRead(A2)<100){
      run_t();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  speedCtrl.start();
  //turn_right();
  //run_(70,550);
}
void loop() {
  //Serial.println(digitalRead(11));
  //speedCtrl.line();

if (inter() == 0) {
  speedCtrl.line();
}
else if (inter() == 1)
{
    turn_right();
}
else if (inter() == 2)
{
    turn_left();
}
else if (inter() == 3){run_t();}
}