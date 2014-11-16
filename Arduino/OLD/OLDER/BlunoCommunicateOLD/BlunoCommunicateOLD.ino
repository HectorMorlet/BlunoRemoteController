
//
// IOS Communicate
// Hector Morlet and Jason Chu
// 31/7/2014
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Servo.h>


#define TRUE 1
#define FALSE 0

#define UPDATES_PER_SECOND 4
#define SECONDS_PER_MINUTE 60

#define SERVO_PIN 9
#define SERVO_DEFAULT_ANGLE 90
#define SERVO_DATA_PERFIX "servo:"

#define MOTOR_ONE_PIN 8
#define MOTOR_ONE_DATA_PREFIX "motorone:"
#define MOTOR_TWO_PIN 7
#define MOTOR_TWO_DATA_PREFIX "motortwo:"
#define MOTOR_DEFAULT_STATE LOW

#define PORT 115200
//#define PORT 9600


void updatePins();

void setPinsFromData(int *rawData);

void setPinsFromAI(int *lengthTime);
int getAIState(int *data);

char *sendData(char *data);
int *recieveData(void);
int getServoState(int *data);
int getMotorOneState(int *data);
int getMotorTwoState(int *data);


Servo servo;

int servoAngle = 0;
uint8_t motorOneState = MOTOR_DEFAULT_STATE;
uint8_t motorTwoState = MOTOR_DEFAULT_STATE;

int outputData[3];


void setup() {
	// Configuring motor pins as output
//	pinMode(MOTOR_ONE_PIN, OUTPUT);
//	pinMode(MOTOR_TWO_PIN, OUTPUT);
//	
//	// Setting the servo's pin
//	servo.attach(SERVO_PIN);
	
	// Initialise the Serial
	Serial.begin(PORT);
}


void loop() {
	// Getting raw data
	int *data = recieveData();

	// If commanded to let AI take over, do so
	if (getAIState(data) == TRUE) {
		setPinsFromAI(data);
	} else {
		setPinsFromData(data);
	}

	delay(SECONDS_PER_MINUTE / UPDATES_PER_SECOND);
}

void updatePins() {
//	// Writing servo angle
//	servo.write(servoAngle);
//
//	// Writing motor one state
//	digitalWrite(MOTOR_ONE_PIN, motorOneState);
//
//	// Writing motor two state
//	digitalWrite(MOTOR_TWO_PIN, motorTwoState);
}

void setPinsFromData(int *rawData) {
	// Setting servo state from data
	servoAngle = getServoState(rawData);

	// Setting motor one state from data
	motorOneState = getMotorOneState(rawData);

	// Setting motor two state from data
	motorTwoState = getMotorTwoState(rawData);

	// Updating what the pins output
	updatePins();
}

void setPinsFromAI(int *lengthTime) {
	// Sample code for how directions in moving will work (for Devin)

	// Setting both motors on
	motorOneState = HIGH;
	motorTwoState = HIGH;

	// Looping four times
	for (int i = 0; i < 4; i++) {
		// Going straight
		servoAngle = 90;
		// Updating output
		updatePins();
		// For 1 second
		delay(1000);

		// Going left
		servoAngle = 0;
		// Updating output
		updatePins();
		// For 1000 milliseconds
		delay(1000);
	}
}

int getAIState(int *data) {
	return FALSE;
}

// ------------------------------------------------------------
//							 Send
// ------------------------------------------------------------

char *sendData(char *data) {
	if (Serial.available()) {
		// Write data
		Serial.write(data);
	}
}


// ------------------------------------------------------------
//							Receive
// ------------------------------------------------------------

// Data will come in form of example:
//	 motorOne will be 0 or 1
//	 motorTwo will be 2 or 3
//	 servo will be 4 through to p (in ascii values)

int *recieveData(void) {
	// Recieve raw byte
	int data = Serial.read();

	// If data has actually been received
	if (data != -1) {
		// Minus all the stuff before the 0 character
		data = data - 48;

		if (data < 2) {
			// motorOne
			outputData[0] = data;
		} else if (data < 4) {
			// motorTwo
			outputData[1] = data;
		} else {
			// servo
			outputData[2] = (data - 4) * 3;
		}
	}
	
	return outputData;
}

int getServoState(int *data) {
	// Return third item in list
	return data[2];
}

int getMotorOneState(int *data) {
	// LOW by default
	uint8_t motorOneState = LOW;

	// If motor one state is 1 motor one is high
	if (data[0] == 1) {
		motorOneState = HIGH;
	}

	return motorOneState;
}

int getMotorTwoState(int *data) {
	// LOW by default
	uint8_t motorTwoState = LOW;

	// If motor two state is 1 motor two is high
	if (data[1] == 1) {
		motorTwoState = HIGH;
	}

	return motorTwoState;
}
