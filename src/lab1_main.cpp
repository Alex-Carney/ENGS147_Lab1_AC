#include <SPI.h>
#include "ArduinoMotorShieldR3.h"
#include "ArduinoMotorEncoder.h"
#include "motor_characterization.h"
#include <Arduino.h>

//*****************************************************
/*
@see motor_characterization.h
@file lab1_main.cpp
@author Alex Carney


Entry point for Lab1 project. This program will run the motor characterization script
for the motor. The motor will be run at 20 different speeds, defined in the MOTOR_SPEEDS
array. The motor will be run in both directions, and the encoder will be read from
the encoder specified in the ENCODER_READ_VALUE variable. The data will be printed
to the serial monitor.

Note that velocity was not fully calculated in this program. The velocity was calculated
afterwards in MATLAB. The MATLAB script is located in the MATLAB folder.

*/
//*****************************************************

// Variable Definitions
ArduinoMotorShieldR3 md;
bool shouldRun = true;

// Constant Definitions
const int MOTOR_SPEEDS[] = {25, 50, 75, 100, 150, 200, 250, 300, 350, 400, -25, -50, -75, -100, -150, -200, -250, -300, -350, -400};
int ENCODER_READ_VALUE = 2;


void setup() {
  //Peripheral Initialization
  Serial.begin(115200);           //Initialize the Serial Port to view information on the Serial Monitor
  //I2C.begin();                    //Initialize I2C communication to the let the library communicate with the sensor. 
  
  //Axis Encoder Initiallization
  pinMode(encoder::chipSelectPin3, OUTPUT);
  digitalWrite(encoder::chipSelectPin3, HIGH);
  encoder::LS7366_Init();

  //Motor Shield Initiallization
  md.init();
  
  
  Serial.println("%Streaming in..."); //Countdown
  Serial.print("%3...");
  delay(1000);  //Wait for a second
  Serial.print("%2...");
  delay(1000);  //Wait for a second
  Serial.println("%1...");
  delay(1000);  //Wait for a second
}

void loop() {
    if(shouldRun == true) {
        // Loop in here
        for(int i = 0; i < 20; i++) {
            // @see motor_characterization.h
            motor_characterization::printMotorCharacterization(MOTOR_SPEEDS[i], ENCODER_READ_VALUE, md);
        }
    }
    shouldRun = false;
}