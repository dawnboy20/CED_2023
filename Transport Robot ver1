#include <Servo.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"


Servo bridge;
Servo sub;


const int mr1=5;                //MotorA  L293 Pin in1 
const int mr2=6;                //MotorA  L293 Pin in1 
const int ml1=9;                //MotorB  L293 Pin in1 
const int ml2=10;               //MotorB  L293 Pin in1 
const int R_S=7;                //ir sensor Right for line tracing
const int L_S=8;                //ir sensor Left for line tracing
const int pingPin1 = 11;         // Trigger Pin of Ultrasonic Sensor1
const int echoPin1 = 12;         // Echo Pin of Ultrasonic Sensor1
const int pingPin2 =3;           // Trigger Pin of Ultrasonic Sensor2
const int echoPin2 = 4;          // Echo Pin of Ultrasonic Sensor2


void setup(){ 
  pinMode(R_S, INPUT); 
  pinMode(L_S, INPUT); 
  pinMode(mr1, OUTPUT); 
  pinMode(mr2, OUTPUT); 
  pinMode(ml1, OUTPUT); 
  pinMode(ml2, OUTPUT); 
  pinMode(pingPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(pingPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  //pinMode(LED_BUILTIN, OUTPUT);

  // servo setup
  bridge.attach(4);
  Serial.begin(9600);
  
  delay(1000);
}


void forward(){           //forword
  analogWrite(mr1, 0);    //Right Motor forword Pin 
  analogWrite(mr2, 120);  //Right Motor backword Pin 
  analogWrite(ml1, 0);    //Left Motor forword Pin 
  analogWrite(ml2, 120);  //Left Motor backword Pin 
}

void forward_sub(){
  analogWrite(mr1, 0);    //Right Motor forword Pin 
  analogWrite(mr2, 60);  //Right Motor backword Pin 
  analogWrite(ml1, 0);    //Left Motor forword Pin 
  analogWrite(ml2, 60);  //Left Motor backword Pin 
}


void Right_line(){              //turnLeft
  analogWrite(mr1, 0);    //Right Motor forword Pin 
  analogWrite(mr2, 120);  //Right Motor backword Pin  
  analogWrite(ml1, 120);  //Left Motor forword Pin 
  analogWrite(ml2, 0);    //Left Motor backword Pin 
}

void Left_line(){             //turnRight
  analogWrite(mr1, 120);  //Right Motor forword Pin 
  analogWrite(mr2, 0);    //Right Motor backword Pin 
  analogWrite(ml1, 0);    //Left Motor backword Pin 
  analogWrite(ml2, 120);  //Left Motor forword Pin 
}

void backward(){
  analogWrite(mr1, 150);  //Right Motor forword Pin 
  analogWrite(mr2, 0);    //Right Motor backword Pin 
  analogWrite(ml1, 150);  //Left Motor forword Pin 
  analogWrite(ml2, 0);    //Left Motor backword Pin 
}

void Stop(){              //stop
  analogWrite(mr1, 0);    //Right Motor forword Pin 
  analogWrite(mr2, 0);    //Right Motor backword Pin 
  analogWrite(ml1, 0);    //Left Motor backword Pin 
  analogWrite(ml2, 0);    //Left Motor forword Pin 
}


//void line_tracing(a,b){
//  if(a==0 && b==0){
//    forward()
//  }
//  else if(a==1 && b==0){
//    Left_line()
//  }
//  else if(a==0 && b==1){
//    Right_line()
//  }
//  else{
//    forward_sub()
//  }
//}

int Ultrasonic1(){
  long duration, distance;
  digitalWrite(pingPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin1, HIGH);
  delayMicroseconds(2);
  digitalWrite(pingPin1, LOW);

  duration = pulseIn(echoPin1, HIGH);

  distance = duration*17/1000;
  return distance;
}

int Ultrasonic2(){
  long duration, distance;
  digitalWrite(pingPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin2, HIGH);
  delayMicroseconds(2);
  digitalWrite(pingPin2, LOW);

  duration = pulseIn(echoPin2, HIGH);

  distance = duration*17/1000;
  return distance;
}


void loop(){
  int LS_value = digitalRead(L_S);
  int RS_value = digitalRead(R_S);
  int distance1 = Ultrasonic1();
  int distance2 = Ultrasonic2();

//  while(distance1 >=3 && distance2 >=3){
//    line_tracing(LS_value, RS_value);
//  }
  if(distance1 >=3 && distance2 >=3){
    line_tracing(LS_value, RS_value);
  }
  else{
    Stop();
  }
}

void line_tracing(int a, int b){
  if(a==0 && b==0){
    forward();
  }
  else if(a==1 && b==0){
    Left_line();
  }
  else if(a==0 && b==1){
    Right_line();
  }
  else{
    forward_sub();
  }
}
