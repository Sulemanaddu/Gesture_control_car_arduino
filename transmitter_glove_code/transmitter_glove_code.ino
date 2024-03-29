
//Include necessary libraries
#include <SPI.h>        //SPI library for communication with the nRF24L01+
#include "RF24.h"       //Library for the nRF24L01+
#include "Wire.h"       //Library for I2C communication
#include "I2Cdev.h"     //Library for MPU6050 communication
#include "MPU6050.h"    //Library for MPU6050 sensor

//Define MPU6050 object
MPU6050 mpu;
int16_t ax, ay, az; //Acceleration values
int16_t gx, gy, gz; //Gyroscopic values

//Packet for transmitting direction (X axis and Y axis)
int data[2];

//RF24 object with CE and CSN pin configurations
RF24 radio(9,10);

//Pipe address for communication
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(void){
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();              //Initialize MPU6050
  radio.begin();                 //Initialize NRF24L01
  radio.openWritingPipe(pipe);   //Set receiver's address
}

void loop(void){
  //Read acceleration and gyro values
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  //Map acceleration values to control robot movement
  data[0] = map(ax, -17000, 17000, 300, 400 ); //Map X axis data for forward/backward movement
  data[1] = map(ay, -17000, 17000, 100, 200);  //Map Y axis data for right/left turn
  radio.write(data, sizeof(data)); //Transmit data
}
