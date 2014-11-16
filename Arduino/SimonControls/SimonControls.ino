
//
// Remote Control Software for a Bluno Vehicle
// Hector Morlet
// Last revision 21/10/2014
//

#include <Servo.h>


#define UPDATES_PER_SECOND 4
#define SECONDS_PER_MINUTE 60

#define SERVO_PIN 10
#define SERVO_DEFAULT_ANGLE 90

#define MOTOR_DEFAULT_STATE LOW

#define MOTOR_ONE_PIN 9
#define MOTOR_ONE_SET_HIGH "1HIGH"
#define MOTOR_ONE_SET_LOW "1LOW"

#define MOTOR_TWO_PIN 0
#define MOTOR_TWO_SET_HIGH "2HIGH"
#define MOTOR_TWO_SET_LOW "2LOW"

#define PORT 115200


Servo servo;
Servo motor;
uint8_t motorOne = MOTOR_DEFAULT_STATE;
uint8_t motorTwo = MOTOR_DEFAULT_STATE;


// ----------------------------------------------------------------
// |                            SETUP                             |
// ----------------------------------------------------------------

void setup() {
  // Init motor pins
  pinMode(MOTOR_ONE_PIN, OUTPUT);
  pinMode(MOTOR_TWO_PIN, OUTPUT);
  
  digitalWrite(MOTOR_ONE_PIN, 0);
  digitalWrite(MOTOR_TWO_PIN, 0);
  
  // Init motor one
  motor.attach(MOTOR_ONE_PIN);
  motor.writeMicroseconds(700);
  
  // Init servo pin
  servo.attach(SERVO_PIN);
  
  // Init the Serial
  Serial.begin(PORT);
}


// ----------------------------------------------------------------
// |                            UPDATE                            |
// ---------------------------------------------------------- ------

void receivedCommand(String command) {
  Serial.println(command);
  
  // It has sent a servo angle
  int angle = (String(command[0]) + String(command[1]) + String(command[2])).toInt();
  Serial.println(angle);
  if (angle >= 45 && angle <= 135) {
    servo.write(angle);
  }
}


int shouldNewLine = 0;
String activeCommand = "";


void loop() {
  if (Serial.available()) {
    char currentCharacter = char(Serial.read());
    
    if (currentCharacter == 'B' || currentCharacter == 'C' || currentCharacter == 'D') {
      Serial.println("ON");
      motor.writeMicroseconds(1500);
    } else if (currentCharacter == 'A') {
      Serial.println("OFF");
      motor.writeMicroseconds(750);
    } else {
     activeCommand = activeCommand +  String(currentCharacter);
    }
    
    shouldNewLine = 1;
  } else {
    if (shouldNewLine) {
      shouldNewLine = 0;
      receivedCommand(activeCommand);
      activeCommand = "";
    } 
  }
  
  delay(25);
}
