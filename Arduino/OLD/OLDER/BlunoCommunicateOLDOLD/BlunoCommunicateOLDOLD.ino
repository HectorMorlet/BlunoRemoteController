
//
// Gyro Glove
// Hector Morlet and Jason Chu
// 31/7/2014
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Servo.h>

#include "I2Cdev.h"
#include "MPU6050.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif


#define TRUE 1
#define FALSE 0

#define UPDATES_PER_SECOND 4
#define SECONDS_PER_MINUTE 60

#define SERVO_PIN 9
#define SERVO_DEFAULT_ANGLE 90
#define SERVO_DATA_PERFIX "servo:"

#define MOTOR_ONE_PIN 8
#define MOTOR_TWO_PIN 7
#define MOTOR_DEFAULT_STATE LOW

#define PORT 115200


Servo servo;

// Accelerometer gyroscope
MPU6050 accelgyro;

// The dimentions of the accelerometer
int16_t accelX, accelY, accelZ;
int16_t gyroX, gyroY, gyroZ;


void updatePins();

void setPinsFromData(int *rawData);

void setPinsFromAI(int *lengthTime);
int getAIState(int *data);

char *sendData(char *data);
int *recieveData(void);
int getServoState(int *data);
int getMotorOneState(int *data);
int getMotorTwoState(int *data);

int MPU6050_read(int start, uint8_t *buffer, int size);
int MPU6050_write(int start, const uint8_t *pData, int size);


int servoAngle = 0;
uint8_t motorOneState = MOTOR_DEFAULT_STATE;
uint8_t motorTwoState = MOTOR_DEFAULT_STATE;


void setup() {
    // Configuring motor pins as output
    pinMode(MOTOR_ONE_PIN, OUTPUT);
    pinMode(MOTOR_TWO_PIN, OUTPUT);
    
    // Setting the servo's pin
    servo.attach(SERVO_PIN);
    
    // Initialise the Serial
    Serial.begin(PORT);
    
    setupGyros();
}


void setupGyros() {
	#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
    
    // Init gyros
    accelgyro.initialize();
}


void loop() {
    // Getting raw data
    int *rawData = setGyroData();
	
	// Sending back to phone
    sendData(rawData);

    delay(SECONDS_PER_MINUTE / UPDATES_PER_SECOND);
}

void updatePins() {
    servo.write(servoAngle);
    digitalWrite(MOTOR_ONE_PIN, motorOneState);
    digitalWrite(MOTOR_TWO_PIN, motorTwoState);
    Serial.print(servoAngle);
    Serial.print(motorOneState);
    Serial.print(motorTwoState);
}

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
//                            Gyros
// ------------------------------------------------------------


// Output will come in the form
// 		"accelX accelY accelZ gyroX gyroY gyroZ"
// With all variables being ints

void setGyroData() {
	accelgyro.getMotion6(&accelX, &accelY, &accelZ, 
						 &gyroX, &gyroY, &gyroZ);

	String outputData = "";
	
	// Concat accelerometer X
	outputData.concat(accelX);
	outputData.concat(" ");
	
	// Concat accelerometer Y
	outputData.concat(accelY);
	outputData.concat(" ");
	
	// Concat accelerometer Z
	outputData.concat(accelZ);
	outputData.concat(" ");
	
	// Concat gyroscope X
	outputData.concat(gyroX);
	outputData.concat(" ");
	
	// Concat gyroscope Y
	outputData.concat(gyroY);
	outputData.concat(" ");
	
	// Concat gyroscope Z
	outputData.concat(gyroZ);
	
	char *output = convertStringToCharStar(outputData);
	
	sendData(output);
}

char *convertStringToCharStar(String string) {
	// TODO
}
