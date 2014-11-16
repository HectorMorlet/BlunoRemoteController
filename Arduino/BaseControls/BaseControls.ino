
//
// Remote Control Software for a Bluno Vehicle
// Hector Morlet
// Last revision 21/10/2014
//

#include <Servo.h>


#define UPDATES_PER_SECOND 4
#define SECONDS_PER_MINUTE 60

#define SERVO_PIN 9
#define SERVO_DEFAULT_ANGLE 90

#define MOTOR_DEFAULT_STATE LOW

#define MOTOR_ONE_PIN 5
#define MOTOR_ONE_SET_HIGH "1HIGH"
#define MOTOR_ONE_SET_LOW "1LOW"

#define MOTOR_TWO_PIN 6
#define MOTOR_TWO_SET_HIGH "2HIGH"
#define MOTOR_TWO_SET_LOW "2LOW"

#define PORT 115200


Servo servo;
uint8_t motorOne = MOTOR_DEFAULT_STATE;
uint8_t motorTwo = MOTOR_DEFAULT_STATE;


// ----------------------------------------------------------------
// |                            SETUP                             |
// ----------------------------------------------------------------

void setup() {
  // Init motor pins
  pinMode(MOTOR_ONE_PIN, OUTPUT);
  pinMode(MOTOR_TWO_PIN, OUTPUT);
  
  // Init servo pin
  servo.attach(SERVO_PIN);
  
  // Init the Serial
  Serial.begin(PORT);
}


// ----------------------------------------------------------------
// |                            UPDATE                            |
// ----------------------------------------------------------------

void receivedCommand(String command) {
  if (command == MOTOR_ONE_SET_HIGH) {
    // Second motor on
Serial.println("M1H");
    digitalWrite(MOTOR_ONE_PIN, 0);
  } else if (command == MOTOR_ONE_SET_LOW) {
    // Second motor off
//    Serial.println("MOTOR ONE LOW");
    digitalWrite(MOTOR_ONE_PIN, 0);
  } else if (command == MOTOR_TWO_SET_HIGH) {
    // Second motor on
//    Serial.println("MOTOR TWO HIGH");
    digitalWrite(MOTOR_TWO_PIN, 0);
  } else if (command == MOTOR_TWO_SET_LOW) {
    // Second motor off
//    Serial.println("MOTOR TWO LOW");
    digitalWrite(MOTOR_TWO_PIN, 0);
  } else {
    // It has sent a servo angle
    int angle = command.toInt();
    if (angle >= 45 && angle <= 135) {
      servo.write(angle);
//      Serial.println(angle);
    }
  }
}


int shouldNewLine = 0;
String activeCommand = "";


void loop() {
    digitalWrite(MOTOR_ONE_PIN, 0);
  digitalWrite(MOTOR_TWO_PIN, 0);
  
  if (Serial.available()) {
    activeCommand += String(char(Serial.read()));
    shouldNewLine = 1;
  } else {
    if (shouldNewLine) {
      shouldNewLine = 0;
      receivedCommand(activeCommand);
      activeCommand = "";
    } 
  }
}
