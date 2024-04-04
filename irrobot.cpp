#include <IRremote.h>


const int PWM_M1 = 5;
const int IN1_M1 = 2;
const int IN2_M1 = 3;

const int PWM_M2 = 6;
const int IN1_M2 = 8;
const int IN2_M2 = 9;

const int IR_RECEIVE_PIN = 11;
const int IR_FEEDBACK_LED_PIN = 12;

int speed = 150;

void setup(){
  Serial.begin(9600);
  Serial.println("Start");

  
  pinMode(PWM_M1,OUTPUT);
  pinMode(PWM_M2,OUTPUT);
  
  pinMode(IN1_M1,OUTPUT);
  pinMode(IN2_M1,OUTPUT);
  
  pinMode(IN1_M2,OUTPUT);
  pinMode(IN2_M2,OUTPUT);
  pinMode(12,OUTPUT);
  IrReceiver.begin(IR_RECEIVE_PIN, true);
}

void loop(){
  if (IrReceiver.decode()) {

    switch(IrReceiver.decodedIRData.command){

      case 1://vol+
      	forward();
      break;
      case 4://|<<
      	turnRight();
      break;
      case 5://>||
      	stop();
      break ;  
      case 6://>>|
      	turnLeft();
      break ;               
      case 8://down arrow
      	speedDown();
      break ;  
      case 9://vol-
      	backward();
      break ;  
      case 10://up arrow
      	speedUp();
      break ;  


    }
    IrReceiver.resume(); 
  }
}



void forward(){
  Serial.println("forward");
  analogWrite(PWM_M1, speed);
  analogWrite(PWM_M2, speed);
  
  digitalWrite(IN1_M1, HIGH);
  digitalWrite(IN2_M1, LOW);
  
  digitalWrite(IN1_M2, HIGH);
  digitalWrite(IN2_M2, LOW);
}

void backward(){
  Serial.println("backward");
  analogWrite(PWM_M1, speed);
  analogWrite(PWM_M2, speed);
  
  digitalWrite(IN1_M1, LOW);
  digitalWrite(IN2_M1, HIGH);
  
  digitalWrite(IN1_M2, LOW);
  digitalWrite(IN2_M2, HIGH);
}

void turnLeft(){
  Serial.println("turnLeft");
  analogWrite(PWM_M1, 0);
  analogWrite(PWM_M2, speed);
  
  digitalWrite(IN1_M1, HIGH);
  digitalWrite(IN2_M1, LOW);
  
  digitalWrite(IN1_M2, HIGH);
  digitalWrite(IN2_M2, LOW);
}

void turnRight(){
  Serial.println("turnRight");
  analogWrite(PWM_M1, speed);
  analogWrite(PWM_M2, 0);
  
  digitalWrite(IN1_M1, HIGH);
  digitalWrite(IN2_M1, LOW);
  
  digitalWrite(IN1_M2, HIGH);
  digitalWrite(IN2_M2, LOW);
}

void stop(){
  Serial.println("stop");
  digitalWrite(IN1_M1, LOW);
  digitalWrite(IN2_M1, LOW);
  
  digitalWrite(IN1_M2, LOW);
  digitalWrite(IN2_M2, LOW);
}

void speedUp(){
  Serial.println("speedUp");
  speed+=10;
  if(speed>255) speed =255;
  analogWrite(PWM_M1, speed);
  analogWrite(PWM_M2, speed);
}

void speedDown(){
  Serial.println("speedDown");
  speed-=10;
  if(speed<0) speed =0;
  analogWrite(PWM_M1, speed);
  analogWrite(PWM_M2, speed);
}