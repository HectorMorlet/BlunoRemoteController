
//
// IOSConnection.c
// Hector Morlet and Jason Chu
// 31/7/2014
//


#include <stdio.h>
#include <stdlib.h>
// #include <Servo.h>
#include "IOSConnection.h"


#define HIGH 1
#define LOW 0


Servo servo;


// ------------------------------------------------------------
//                             Send
// ------------------------------------------------------------

char *sendData(char *data) {
    if (Serial.available()) {
        // Send what has been received
        Serial.write(Serial.read());
    }
}


// ------------------------------------------------------------
//                            Recieve
// ------------------------------------------------------------

// Data will come in form of example:
//     motorOne:1|motorTwo:1|servo:45

char *recieveData(void) {
    char *data = Serial.read();

    int outputData = malloc(sizeof(int) * 3); // TOFIX
    sscanf(data, "motorOne:%d|motorTwo:%d|servo:%d",
           &outputData[0], &outputData[1], &outputData[2]);
    return outputData;

    return outputData;
}

int getServoState(int *data) {
    return data[2];
}

int getMotorOneState(int *data) {
    uint8_t motorOneState = LOW;

    if (data[0] == 1) {
        motorOneState = HIGH;
    }

    return motorOneState;
}

int getMotorTwoState(int *data) {
    uint8_t motorTwoState = LOW;

    if (data[1] == 1) {
        motorTwoState = HIGH;
    }

    return motorTwoState;
}
