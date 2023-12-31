#include <AFMotor.h>
#include <NewPing.h>
#include<Servo.h>
#define TRIGGER_PIN A1
#define ECHO_PIN A0
#define MAX_DISTANCE 1000
#define IR A5

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

Servo myservo;



String voice;

void setup() {
Serial.begin(9600);
myservo.attach(10);
myservo.write(90);
pinMode(IR, INPUT);
//int distance = sonar.ping_cm();
}

void loop() {
  int distance = sonar.ping_cm();
  
if(Serial.available()>0) {
  voice="";
  delay(2);
  voice = Serial.readString();
  delay(2);
  Serial.println(voice);

  

if (voice == "turn left") {
  left();
}else if (voice == "left") {
  left();
}else if(voice == "turn right") {
  right();
}else if(voice == "right") {
  right();
}else if(voice == "about turn") {
  roll();
}else if(voice == "go crazy") {
  crazy();
}else if(voice == "snake"){
  snake();
}

 
}
while(voice == "move forward") {
  forward();
}
while(voice == "move backward") {
  backward();
}
}



void forward() {
  int distance = sonar.ping_cm();
  
 if(distance < 20){
  Stop();
  voice="";
 }else {
  motor1.setSpeed(200); 
  motor1.run(FORWARD); 
  motor2.setSpeed(200);
  motor2.run(FORWARD);
  motor3.setSpeed(200); 
  motor3.run(FORWARD); 
  motor4.setSpeed(200); 
  motor4.run(FORWARD); 
}
}
void backward() {
  int IR_Sensor = digitalRead(IR);
  if(IR_Sensor == 0) {
    Stop();
    voice="";
  }else {
  motor1.setSpeed(200); 
  motor1.run(BACKWARD); 
  motor2.setSpeed(200); 
  motor2.run(BACKWARD); 
  motor3.setSpeed(200); 
  motor3.run(BACKWARD);
  motor4.setSpeed(200); 
  motor4.run(BACKWARD); 
 
}
}
void left() {
  myservo.write(180);
  delay(300);
  myservo.write(90);
  delay(300);
  motor1.run(BACKWARD);
  motor1.setSpeed(150);
  motor2.run(BACKWARD);
  motor2.setSpeed(150);
  motor3.run(FORWARD);
  motor3.setSpeed(150);
  motor4.run(FORWARD);
  motor4.setSpeed(150);
  delay(700);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void right() {
  myservo.write(0);
  delay(300);
  myservo.write(90);
  delay(300);
  motor1.run(FORWARD);
  motor1.setSpeed(150);
  motor2.run(FORWARD);
  motor2.setSpeed(150);
  motor3.run(BACKWARD);
  motor3.setSpeed(150);
  motor4.run(BACKWARD);
  motor4.setSpeed(150);
  delay(500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
void roll(){
  myservo.write(180);
  delay(300);
  myservo.write(90);
  delay(300);
  myservo.write(0);
  delay(300);
  myservo.write(90);
  delay(300);
  motor1.run(BACKWARD);
  motor1.setSpeed(200);
  motor2.run(BACKWARD);
  motor2.setSpeed(200);
  motor3.run(FORWARD);
  motor3.setSpeed(200);
  motor4.run(FORWARD);
  motor4.setSpeed(200);
  delay(700);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  voice="";
  Stop();
}
void crazy(){
  int distance = sonar.ping_cm();
  int IR_Sensor = digitalRead(IR);
  while((distance>20) || (IR_Sensor !=0 )){
  forward();
  delay(100);
  left();
  delay(100);
  backward();
  delay(100);
  right();
  delay(100);
  backward();
  delay(100);
  roll();
  }
}

void snake(){
  int distance = sonar.ping_cm();
  while(1){
  forward();
  delay(100);
  left();
  delay(100);
  if (distance>20){
  forward();
  }
  else{
    Stop();
    break;
  }
  delay(100);
  right();
  delay(100);
  if (distance>20){
  forward();
  }
  else{
    Stop();
    break;
  }
  delay(100);
  right();
  delay(100);
  if (distance>20){
  forward();
  }
  else{
    Stop();
    break;
  }
  delay(100);
  left();
  }
}

void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
