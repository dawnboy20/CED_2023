// Arduino Line Follower Robot Code
#include <Servo.h>


int mr1=6;                //MotorA  L293 Pin in1 
int mr2=5;                //MotorA  L293 Pin in1 
int ml1=11;                //MotorB  L293 Pin in1 
int ml2=13;               //MotorB  L293 Pin in1

int R_S=3;                //ir sensor Right for line tracing
int L_S=4;                //ir sensor Left for line tracing
int RR_S =2;              //ir sensor Right for direction
int LL_S =7;              //ir sensor Left for direction

int sensor[5];            //current state of ir sensors
int cnt=0;
int LL_S_before;          //memorize previous state of LL_S
int RR_S_before;          //memorize previous state of RR_S
int LL_S_cnt;             //count number of times LL_S changes from 0 to 1
int RR_S_cnt;             //count number of times RR_S changes from 0 to 1

Servo bridge_servo;

int Red_LED = A5;


void setup(){
  pinMode(mr1, OUTPUT); 
  pinMode(mr2, OUTPUT); 
  pinMode(ml1, OUTPUT); 
  pinMode(ml2, OUTPUT); 

  pinMode(R_S, INPUT); 
  pinMode(L_S, INPUT); 
  pinMode(RR_S, INPUT);
  pinMode(LL_S, INPUT);

  pinMode(Red_LED, OUTPUT);

  Serial.begin(9600);  

  analogWrite(mr1, 0);    //Right Motor forword Pin 
  analogWrite(mr2, 0);    //Right Motor backword Pin 
  analogWrite(ml1, 0);    //Left Motor backword Pin 
  analogWrite(ml2, 0);    //Left Motor forword Pin 

  bridge_servo.attach(8);
  bridge_servo.write(10);
  // bridge_servo.write(0);

  wait();
  Stop(1);
  delay(100);
}

void forward(){           //forword
  analogWrite(mr1, 210);  //Right Motor forword Pin 
  analogWrite(mr2, 0);    //Right Motor backword Pin 
  analogWrite(ml1, 190);  //Left Motor forword Pin 
  analogWrite(ml2, 0);    //Left Motor backword Pin 
}

void Left(){              //turnRight
  analogWrite(mr1, 225);  //Right Motor forword Pin 
  analogWrite(mr2, 0);    //Right Motor backword Pin 
  analogWrite(ml1,70);   //Left Motor forword Pin 
  analogWrite(ml2, 0);    //Left Motor backword Pin 
}

void Right(){             //turnLeft
  analogWrite(mr1, 60);   //Right Motor forword Pin 
  analogWrite(mr2, 0);    //Right Motor backword Pin  
  analogWrite(ml1, 220);  //Left Motor forword Pin 
  analogWrite(ml2, 0);    //Left Motor backword Pin 
}

void Stop(int k){         //stop
  analogWrite(mr1, 0);    //Right Motor forword Pin 
  analogWrite(mr2, 0);    //Right Motor backword Pin 
  analogWrite(ml1, 0);    //Left Motor forward Pin 
  analogWrite(ml2, 0);    //Left Motor forword Pin 
  delay(1000);

  if(k==1){
    analogWrite(mr1, 255);  //Right Motor forword Pin 
    analogWrite(mr2, 0);    //Right Motor backword Pin 
    analogWrite(ml1, 255);  //Left Motor forword Pin 
    analogWrite(ml2, 0);    //Left Motor backword Pin 
  }
  else if(k==2){
    analogWrite(mr1, 255);  //Right Motor forword Pin 
    analogWrite(mr2, 0);    //Right Motor backword Pin 
    analogWrite(ml1, 0);    //Left Motor forword Pin 
    analogWrite(ml2, 255);  //Left Motor backword Pin 
  }
  else if(k==3){
    analogWrite(mr1, 0);    //Right Motor forword Pin 
    analogWrite(mr2, 255);  //Right Motor backword Pin 
    analogWrite(ml1, 255);  //Left Motor forword Pin 
    analogWrite(ml2, 0);    //Left Motor backword Pin 
  }
  delay(100);
}

void sensor_scan(){       //Scan current state of sensors
  sensor[1]=digitalRead(LL_S);
  sensor[2]=digitalRead(L_S);
  sensor[3]=digitalRead(R_S);
  sensor[4]=digitalRead(RR_S);
  for(int i=1;i<=4;i++){
    Serial.print(sensor[i]);
    Serial.print('\t');
  }
  Serial.println();
}

void line_tracing(){  
  if(sensor[2]==0 && sensor[3]==0){
    forward();
    // Serial.print("Forward ");
  }
  else if(sensor[2]==1 && sensor[3]==0){
    Left();
    // Serial.print("Turn left ");
  }
  else if(sensor[2]==0 && sensor[3]==1){
    Right();
    // Serial.print("Turn right ");
  }
  // Serial.println("while line tracking");
}

void TurnLeft(){
  
  Stop(2);
  
  while(1){
    //Turn left to find line
    analogWrite(mr1, 200);  //Right Motor forword Pin 
    analogWrite(mr2, 0);    //Right Motor backword Pin  
    analogWrite(ml1, 0);    //Left Motor forword Pin 
    analogWrite(ml2, 125);  //Left Motor backword Pin 
    Serial.println("Turning left to find line");
    
    sensor_scan();
    
    if(sensor[2]==1){                                     //recognize line
      Serial.println("Line founded");
      
      while(1){                                           //set robot to line trace
        
        sensor_scan();
        
        if(sensor[2]==0){
          
          Stop(1);
          
          // Serial.println("Ready to line track again");
              
          LL_S_cnt=0;  RR_S_cnt=0;
          // Serial.println("LL_S_cnt  and  RR_S_cnt  reset");
          // Serial.println(" ");
          break;
        }
        else{
          // Serial.println("sensor2 is still on the line");
        }
      }
      break;
    }
  }
}

void TurnRight(){
  
  Stop(3);
  
  while(1){
    //turn right to find line
    analogWrite(mr1, 0);    //Right Motor forword Pin 
    analogWrite(mr2, 115);  //Right Motor backword Pin 
    analogWrite(ml1, 170);  //Left Motor forward Pin 
    analogWrite(ml2, 0);    //Left Motor forword Pin
    // Serial.println("Turning right to find line");
    
    sensor_scan();
    
    if(sensor[3]==1){                                     //recognize line
      Serial.println("Line founded");
      
      while(1){                                           //set robot to line trace
        
        sensor_scan();

        if(sensor[3]==0){
          
          Stop(1);
          
          Serial.println("Ready to line track again");

          LL_S_cnt=0;  RR_S_cnt=0;
          // Serial.println("LL_S_cnt  and  RR_S_cnt  reset");
          // Serial.println(" ");
          break;
        }
        else{
          // Serial.println("sensor3 is still on the line");
        }
      }
    break;
    }
  }
}

void Left_and_Right(){
  
  Stop(2);
  
  Serial.println("Left and Right");
  while(1){
    analogWrite(mr1, 200);  //Right Motor forword Pin 
    analogWrite(mr2, 0);    //Right Motor backword Pin  
    analogWrite(ml1, 0);    //Left Motor forword Pin 
    analogWrite(ml2, 120);  //Left Motor backword Pin 
    // Serial.println("Turning left to find line");
    
    sensor_scan();
    
    if(sensor[4]==1){                                     //recognize direction mark
      // Serial.println("Direction mark founded");
      
       Stop(0);

      while(sensor[4]==1){
        sensor_scan();
        forward();
      }
      while(sensor[4]==0){
        sensor_scan();
        forward();
      }

      Stop(3);

      while(1){
        analogWrite(mr1, 0);                              //Right Motor forword Pin 
        analogWrite(mr2, 100);                            //Right Motor backword Pin  
        analogWrite(ml1, 165);                            //Left Motor forword Pin 
        analogWrite(ml2, 0);                              //Left Motor backword Pin 
        
        sensor_scan();
        
        if(sensor[3]==1){                                 //line founded
          // Serial.println("line founded");
          while(1){
            
            sensor_scan();

            if(sensor[3]==0){
              
              Stop(1);
              
              // Serial.println("Ready to line track again");
              
              LL_S_cnt=0;  RR_S_cnt=0;
              // Serial.println("LL_S_cnt  and  RR_S_cnt  reset");
              // Serial.println(" ");
              break;
            }
            else{
              // Serial.println("sensor2 is still on the line");
            }
          }
          break;
        }
      }
      break;
    }
  }
}

void Right_and_Left(){
  
  Stop(3);
  
  while(1){
    analogWrite(mr1, 0);    //Right Motor forword Pin 
    analogWrite(mr2, 105);  //Right Motor backword Pin  
    analogWrite(ml1, 200);  //Left Motor forword Pin 
    analogWrite(ml2, 0);    //Left Motor backword Pin 
    // Serial.println("Turning right to find tracking mark");
    
    sensor_scan();
    
    if(sensor[1]==1){                                     //recognize direction mark
      // Serial.println("Direction mark founded");

      Stop(0);

      while(sensor[1]==1){
        sensor_scan();
        forward();
      }
      while(sensor[1]==0){
        sensor_scan();
        forward();
      }
      
      Stop(2);

      while(1){
        analogWrite(mr1, 205);  //Right Motor forword Pin 
        analogWrite(mr2, 0);    //Right Motor backword Pin  
        analogWrite(ml1, 0);    //Left Motor forword Pin 
        analogWrite(ml2, 100);  //Left Motor backword Pin 

        sensor_scan();
        
        if(sensor[2]==1){                                 //line founded
          while(1){

            sensor_scan();
            
            if(sensor[2]==0){
              
              Stop(1);
              
              // Serial.println("Ready to line track again");
              
              LL_S_cnt=0;  RR_S_cnt=0;
              // Serial.println("LL_S_cnt  and  RR_S_cnt  reset");
              // Serial.println(" ");
              break;
            }
            else{
              // Serial.println("sensor2 is still on the line");
            }
          }
          break;
        }
      }
      break;
    }
  }
}

void wait(){
  for(int i=0;i<75;i++){       //<95
    // digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(Red_LED, HIGH);
    delay(1000);
    // digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(Red_LED, LOW);
    delay(1000);
  }
  for(int i=0;i<30;i++){      //<20
    // digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(Red_LED, HIGH);
    delay(500);
    // digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(Red_LED, LOW);
    delay(500);
  }

  // delay(5000);
}

void twist(){
  analogWrite(mr1, 120);
  analogWrite(ml2, 120);
  delay(500);
  analogWrite(mr2, 120);
  analogWrite(ml1, 120);
  delay(500);
}

void loop(){

  sensor_scan();
  
  if(sensor[1]==0&&sensor[4]==0){               //line trace if there's no direction mark
    line_tracing();
  }
  else{                                         //scanning direction mark
    cnt++;
    Serial.println(cnt);

    forward();
    LL_S_before=0;                              //memorize previous state of LL_S
    RR_S_before=0;                              //memorize previous state of RR_S
    LL_S_cnt=0;                                 //count number of times LL_S crosses the black to white line
    RR_S_cnt=0;                                 //count number of times RR_S crosses the black to white line

    if(sensor[1]==1){
      LL_S_cnt++;
    }
    if(sensor[4]==1){
      RR_S_cnt++;
    }

    while(1){
      LL_S_before=sensor[1];  RR_S_before=sensor[4];
      
      sensor_scan();
      
      // Serial.println("Going Forward");

      if(sensor[1]==1 && LL_S_before==0){
        LL_S_cnt++;
      }
      if(sensor[4]==1 && RR_S_before==0){
        RR_S_cnt++;
      }


      if(LL_S_cnt==2){                                     //recognize 'ㄱ' obstacle
        if(cnt==4){
          int tmp1= 0;
          while(1){
            Stop(0);
            if(tmp1 == 0){
              Stop(1);
            }
            tmp1++;
            bridge_servo.write(68);
            delay(5000);
            // twist();
            bridge_servo.write(0);
            delay(500);
          }
        }
        else if(cnt==2){
          Left_and_Right();
          break;
        }
        else{
          TurnLeft();
          break;
        }
      }

      else if(RR_S_cnt==2){                                //recognize 'ㄴ' obstacle
        if(cnt==4){
          int tmp2 = 0;
          while(1){
            Stop(0);
            if(tmp2 == 0){
              Stop(1);
            }
            tmp2++;
            bridge_servo.write(68);
            delay(5000);
            // twist();
            bridge_servo.write(0);
            delay(5000);
          }
        }
        else if(cnt==2){
          Right_and_Left();
          break;
        }
        else{
          TurnRight();
          break;
        }
      }
    }
  }
}
