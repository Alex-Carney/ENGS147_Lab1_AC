#include <Arduino.h>
#include <SPI.h>
#include "ArduinoMotorShieldR3.h"
#include "ArduinoMotorEncoder.h"
#include "motor_characterization.h"

//@see motor_characterization.h
namespace motor_characterization {
    
    // Namespace Variables - Mutable
    long currentTimeMicros = 0;
    long lastStreamTime = 0;
    
    // Namespace Constants
    const int STREAM_PERIOD = 5000;
    const long SAMPLE_DURATION = 2000000; // 2 seconds
    const int BUFFER_SIZE = (SAMPLE_DURATION / STREAM_PERIOD);


    // define prototype for each private function
    void __sampleEncoder(long time_vec[], long position_vec[], double velocity_vec[], int encoderReadValue, int basePos, int currentArrayIndex);
    template<typename T>
    void __printArray(T arr[]);
    void __printData(int identifier, long time_vec[], long position_vec[], double velocity_vec[]);

    // Public Functions
    void printMotorCharacterization(int pwmCommand, 
                                    int encoderReadValue,
                                    ArduinoMotorShieldR3 md) {
        long timeStartMicros = micros();
        long posStart = encoder::getEncoderValue(encoderReadValue);

        md.setM1Speed(pwmCommand);

        // Set up arrays to store data
        long* time_vec = new long[BUFFER_SIZE];
        long* position_vec = new long[BUFFER_SIZE];
        double* velocity_vec = new double[BUFFER_SIZE];
        int currentArrayIndex = 0;

        do {
            currentTimeMicros = micros() - timeStartMicros;
            if ((currentTimeMicros - lastStreamTime) >= STREAM_PERIOD) {
                lastStreamTime = currentTimeMicros;
                __sampleEncoder(time_vec, position_vec, velocity_vec, encoderReadValue, posStart, currentArrayIndex);
                currentArrayIndex++;
            }

        } while(currentTimeMicros < SAMPLE_DURATION);

        delay(3000);
        Serial.println("%End");
        md.setM1Speed(0);
        lastStreamTime = 0;
        delay(3000);

        __printData(pwmCommand, time_vec, position_vec, velocity_vec);

        // May have gotten carried away here but I swear I was having memory issues...
        delete[] time_vec;
        delete[] position_vec;
        delete[] velocity_vec;
        time_vec = nullptr;
        position_vec = nullptr;
        velocity_vec = nullptr;

    }


    // Private
    void __printData(int identifier, long time_vec[], long position_vec[], double velocity_vec[]) {
        Serial.print("%Time");
        Serial.print(identifier);
        Serial.print(": ");
        __printArray(time_vec);
        Serial.print("%Position");
        Serial.print(identifier);
        Serial.print(": ");
        __printArray(position_vec);
        Serial.print("%Velocity");
        Serial.print(identifier);
        Serial.print(": ");
        __printArray(velocity_vec);
    }

    template<typename T>
    void __printArray(T arr[]) {
        Serial.print("[");
        for (int i = 0; i < BUFFER_SIZE; i++) {
            Serial.print(arr[i]);
            if (i < BUFFER_SIZE - 1) {
                Serial.print(", ");
            }
        }
        Serial.println("];");
    }



    void __sampleEncoder(long time_vec[], long position_vec[], double velocity_vec[], int encoderReadValue, int basePos, int currentArrayIndex) {
        long currentPos = encoder::getEncoderValue(encoderReadValue) - basePos;
        time_vec[currentArrayIndex] = currentTimeMicros;
        position_vec[currentArrayIndex] = currentPos;

        double currentVel;
        if (currentArrayIndex != 0) {
            long delta_x = (position_vec[currentArrayIndex] - position_vec[currentArrayIndex -  1]);
            long delta_time = (time_vec[currentArrayIndex] - time_vec[currentArrayIndex -  1]);
            currentVel = (double)delta_x / delta_time;   
        } else {
            currentVel = 0;
        }
        velocity_vec[currentArrayIndex] = currentVel;
    }

}