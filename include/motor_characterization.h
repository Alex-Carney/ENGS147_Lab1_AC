/**
 * @file motor_characterization.h
 * @brief Contains the motor characterization functions
 * @author Alex Carney
*/

#ifndef MotorCharacterization_h
#define MotorCharacterization_h

#include <Arduino.h>

namespace motor_characterization {
    // Public Functions
    /**
     * @brief Prints the motor characterization data to the serial monitor
     * @param pwmCommand The PWM command to send to the motor
     * @param encoderReadValue The encoder to read from
     * @param md The motor shield object
     * @return void
    */
    extern void printMotorCharacterization(int pwmCommand,
                                           int encoderReadValue,
                                           ArduinoMotorShieldR3 md);


}

#endif 