#include <Arduino.h>
#include <MsTimer2.h>
#include <SPEED_CTRL.h>
#include <Servo.h>

Servo servo_2;
Servo servo_6;
Servo servo_7;

int speed_run = 80; 
SPEED_CTRL speedCtrl;
volatile int time_100ms;
int inter_left = 0;
int inter_right = 0;
int inter_all = 0;

void msTimer2_func() {
  time_100ms = time_100ms + 1;
  //Serial.println(time_100ms);
  
}
void setup() {
  Serial.begin(9600);
  servo_2.attach(2);
  servo_6.attach(6);
  servo_7.attach(7);
  servo_6.write(60);
  servo_7.write(90);
  time_100ms = 0;
  speedCtrl.start();
  MsTimer2::set(100, msTimer2_func);
  MsTimer2::start();
}

void read_m8() {
  for (int i = 110; i >= 30; i = i + (-1)) {
    servo_2.write(i);
    delay(10);
  }
  delay(1000);
  for (int i = 30; i <= 110; i = i + (1)) {
    servo_2.write(i);
    delay(10);
  }
}

void run_t(int speed_=speed_run,int time_=0){
  speedCtrl.motor_ctrl(0, 0); // 设置左电机速度为200
  speedCtrl.motor_ctrl(1, 0); // 设置左电机速度为200
  //speedCtrl.motor_ctrl(2, 0); // 设置左电机速度为200
  //speedCtrl.motor_ctrl(3, 0); // 设置左电机速度为200
  if (time_ != 0){
  delay(time_);
  }
}

void run_q(int speed_=speed_run,int time_=400){ 
  time_100ms = 0; 
  do{
    speedCtrl.line();
  }while(time_100ms <= time_/100);
  speedCtrl.motor_ctrl(0, speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(1, speed_); // 设置左电机速度为200
  //  speedCtrl.motor_ctrl(2, speed_); // 设置左电机速度为200
  //  speedCtrl.motor_ctrl(3, speed_); // 设置左电机速度为200
  //  if (time_ != 0){
  //  delay(time_);
  //  run_t();
  }

void run_h(int speed_=speed_run,int time_=0){
  speedCtrl.motor_ctrl(0, -speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(1, -speed_); // 设置左电机速度为200
  //speedCtrl.motor_ctrl(2, -speed_); // 设置左电机速度为200
  //speedCtrl.motor_ctrl(3, -speed_); // 设置左电机速度为200
    if (time_ != 0){
    delay(time_);
    run_t();
  }
}

void run_y(int speed_=speed_run,int time_=0){
  speedCtrl.motor_ctrl(0, speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(1, -speed_); // 设置左电机速度为200
  //speedCtrl.motor_ctrl(2, -speed_); // 设置左电机速度为200
  //speedCtrl.motor_ctrl(3, speed_); // 设置左电机速度为200
  if (time_ != 0){
    delay(time_);
    run_t();
  }
}

void run_z(int speed_=speed_run,int time_=0){
  speedCtrl.motor_ctrl(0, -speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(1, speed_); // 设置左电机速度为200
  //speedCtrl.motor_ctrl(2, speed_); // 设置左电机速度为200
  //speedCtrl.motor_ctrl(3, -speed_); // 设置左电机速度为200
    if (time_ != 0){
    delay(time_);
    run_t();
  }
}

void turn_right(int rq = 300){
  while (analogRead(A2)<500){
  run_y();
  }
  while (analogRead(A1)-analogRead(A2)>150){
    run_y();
  }
  run_q();
}

void turn_left(int rq = 300){
  while (analogRead(A1)<500){
  run_z();
  }
  while (analogRead(A1)-analogRead(A2)>150){
    run_z();
  }
  run_q();
}

void turn_around(int rq = 300){
 while (analogRead(A2)<500){
  run_y();
  }
  while (analogRead(A1)-analogRead(A2)>150){
    run_y();
  }
  run_y(70,300);
   while (analogRead(A2)<500){
  run_y();
  }
  while (analogRead(A1)-analogRead(A2)>150){
    run_y();
  }
  run_q();
}

// int inter(){
//   if (digitalRead(12) == LOW && digitalRead(11) == HIGH) {
//     inter_right = inter_right + 1;
//     return 1;
//   }
//   else if(digitalRead(12) == HIGH){
//     //delay(10);
//     if (digitalRead(11) == LOW){
//     inter_left = inter_left + 1;
//     return 2;
//     }
//     if (digitalRead(11) == HIGH){
//     inter_all = inter_all + 1;
//     return 3;
//     }
//   }
//   return 0; // 添加返回语句
// }

void part_1(){
  for (int i = 1; i <= 4; i = i + (1)) {
  do{
    speedCtrl.line();
  }while(digitalRead(12) == LOW);
  run_t(0,1000);
  //read_m8();
  run_q();
  }//m8,m1,m2,m3
  do{
    speedCtrl.line();
  }while(digitalRead(12) == LOW);
  turn_left();//s2_1
  do{
    speedCtrl.line();
  }while(digitalRead(12) == LOW);
  run_t(0,1000);//s2_2
  turn_around();
  do{
    speedCtrl.line();
  }while(digitalRead(12) == LOW);
  turn_left(10);//s2-1
    time_100ms = 0; 
  do{
    speedCtrl.line();
  }while(time_100ms <= 3);
  
}
void part_2(){
  do{
    speedCtrl.line();
  }while(digitalRead(12) == LOW);
  turn_left(50);//右上角
  time_100ms = 0;
  do{
    speedCtrl.line();
  }while(time_100ms <= 25);//弯道
  do{
    speedCtrl.line();
  }while(digitalRead(12) == LOW);
  turn_left(0);//左上角
  do{
    speedCtrl.line();
  }while(digitalRead(11) == LOW);
  run_t(0,1000);//m7_1
  run_q();
    do{
    speedCtrl.line();
  }while(digitalRead(11) == LOW);
  run_t(0,1000);//m7_2
  run_q();
    do{
    speedCtrl.line();
  }while(digitalRead(11) == LOW);
  run_t(0,1000);//m9
  run_q();
}

void part_3(){
  do{
    speedCtrl.line();
  }while(digitalRead(12) == LOW);
  turn_left();//左转进停车位
  time_100ms = 0;
  do{
  speedCtrl.line();
  }while(time_100ms <= 15);
  run_y(70,1320);
  run_t(0,3000);//停车位等待
  time_100ms = 0;
  do{
    speedCtrl.line();
  }while(time_100ms <= 50);

}

void part_4(){
  do{
    speedCtrl.line();
  }while(digitalRead(12) == LOW);
  turn_left(0);//左下角
  time_100ms = 0;
  do{
    speedCtrl.line();
  }while(time_100ms <= 23);
  run_t(0,2000);//斑马线
    time_100ms = 0;
  do{
    speedCtrl.line();
  }while(time_100ms <= 37);
  run_t(0,3600);//起点

}


void fangxia() {
  servo_7.write(90);
  delay(300);
  for (int i = 160; i >= 60; i = i + (-1)) {
    servo_6.write(i);
    delay(10);
  }
  delay(300);
}

void jiaqu_0() {
  servo_7.write(0);
  delay(300);
  for (int i = 60; i <= 160; i = i + (1)) {
    servo_6.write(i);
    delay(10);
  }
  delay(300);
  fangxia();
}

void jiaqu_180() {
  servo_7.write(180);
  delay(300);
  for (int i = 60; i <= 160; i = i + (1)) {
    servo_6.write(i);
    delay(10);
  }
  delay(300);
  fangxia();
}

void loop(){
  //speedCtrl.line();
  part_1();
  part_2();
  part_3();
  part_4();
  //run_t(0,10000);
  //delay(500);
  //Serial.println(analogRead(A1));
  //Serial.println(analogRead(A2));
  //Serial.println(digitalRead(11));
  //Serial.println(digitalRead(12));
  
}