//Add the necessary libraries
#include <SPI.h>      //SPI library for communication with the nRF24L01+
#include "RF24.h"     //The main library of the nRF24L01+

//Define enable pins of the Motors
const int enbA = 3;
const int enbB = 5;
const int enbC = 9;
const int enbD = 10;

//Define control pins of the Motors
//If the motors rotate in the opposite direction, you can change the positions of the following pin numbers
const int IN1 = 2;    //Right Motor (-)
const int IN2 = 4;    //Right Motor (+)
const int IN3 = 7;    //Left Motor (+)
const int IN4 = 6;    //Right Motor (-)
const int IN5 = 11;   //Front Motor (-)
const int IN6 = 12;   //Front Motor (+)
const int IN7 = 13;   //Rear Motor (+)
const int IN8 = 8;    //Rear Motor (-)

//Define variable for the motors speeds
int RightSpd = 130;
int LeftSpd = 150;
int FrontSpd = 180;
int RearSpd = 200;

//Define packet for the direction (X axis and Y axis)
int data[2];

//Define object from RF24 library - 9 and 10 are digital pin numbers to which signals CE and CSN are connected
RF24 radio(9,10);

//Create a pipe addresses for the communicate
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(){
  //Define the motor pins as OUTPUT
  pinMode(enbA, OUTPUT);
  pinMode(enbB, OUTPUT);
  pinMode(enbC, OUTPUT);
  pinMode(enbD, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
  
  Serial.begin(9600);
  radio.begin();                    //Start the nRF24 communicate            
  radio.openReadingPipe(1, pipe);   //Sets the address of the transmitter to which the program will receive data.
  radio.startListening();             
}

void loop(){
  if (radio.available()){
    radio.read(data, sizeof(data));

    if(data[0] > 380){
      //forward
      analogWrite(enbA, RightSpd);
      analogWrite(enbB, LeftSpd);
      analogWrite(enbC, FrontSpd);
      analogWrite(enbD, RearSpd);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      digitalWrite(IN5, HIGH);
      digitalWrite(IN6, LOW);
      digitalWrite(IN7, HIGH);
      digitalWrite(IN8, LOW);
    }
    
    if(data[0] < 310){
      //backward
      analogWrite(enbA, RightSpd);
      analogWrite(enbB, LeftSpd);
      analogWrite(enbC, FrontSpd);
      analogWrite(enbD, RearSpd);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      digitalWrite(IN5, LOW);
      digitalWrite(IN6, HIGH);
      digitalWrite(IN7, LOW);
      digitalWrite(IN8, HIGH);
    }
     
    if(data[1] > 180){
      //left
      analogWrite(enbA, RightSpd);
      analogWrite(enbB, LeftSpd);
      analogWrite(enbC, FrontSpd);
      analogWrite(enbD, RearSpd);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      digitalWrite(IN5, HIGH);
      digitalWrite(IN6, LOW);
      digitalWrite(IN7, LOW);
      digitalWrite(IN8, HIGH);
    }

    if(data[1] < 110){
      //right
      analogWrite(enbA, RightSpd);
      analogWrite(enbB, LeftSpd);
      analogWrite(enbC, FrontSpd);
      analogWrite(enbD, RearSpd);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      digitalWrite(IN5, LOW);
      digitalWrite(IN6, HIGH);
      digitalWrite(IN7, HIGH);
      digitalWrite(IN8, LOW);
    }

    if(data[0] > 330 && data[0] < 360 && data[1] > 130 && data[1] < 160){
      //stop car
      analogWrite(enbA, 0);
      analogWrite(enbB, 0);
      analogWrite(enbC, 0);
      analogWrite(enbD, 0);
    }
  }
}
