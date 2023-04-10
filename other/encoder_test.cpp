/*
* @file encoder_test.cpp
* @brief Test program for the Arduino Motor Shield R3 and the LS7366R Quadrature Encoder
* @author  ENGS 147 - Refactored by Alex Carney
*/

#include <Arduino.h>
#include <SPI.h>
#include "ArduinoMotorShieldR3.h"
#include "ArduinoMotorEncoder.h"

//*****************************************************
void setup() 
//*****************************************************
{
  Serial.begin(9600);

  pinMode(encoder::chipSelectPin1, OUTPUT);
  pinMode(encoder::chipSelectPin2, OUTPUT);
  pinMode(encoder::chipSelectPin3, OUTPUT);

  // Why am i getting undefined reference to 'encoder::getEncoderValue(int)
    // when i try to use the following line?
    // long encoder1Value = encoder::getEncoderValue(1);

  
  digitalWrite(encoder::chipSelectPin1, HIGH);
  digitalWrite(encoder::chipSelectPin2, HIGH);
  digitalWrite(encoder::chipSelectPin3, HIGH);
 
  encoder::LS7366_Init();

  

  delay(100);
}

//*****************************************************
void loop() 
//*****************************************************
{
        long encoder1Value;
        long encoder2Value;
        long encoder3Value;
        
        
        
        encoder1Value = encoder::getEncoderValue(1);  
        Serial.print("Encoder X= ");
        Serial.print(encoder1Value);
        
        encoder2Value = encoder::getEncoderValue(2);  
        Serial.print(" Encoder Y= ");
        Serial.print(encoder2Value);
        
        encoder3Value = encoder::getEncoderValue(3);  
        Serial.print(" Encoder Z= ");
        Serial.print(encoder3Value);
 
        Serial.print("\r\n");

     delay(100); 
 
}//end loop