
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
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  
  analogWrite(MOTOR_ONE_PIN, LOW);
  analogWrite(MOTOR_TWO_PIN, LOW);
  
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(7, LOW);
  
  // Init servo pin
  servo.attach(SERVO_PIN);
  
  // Init the Serial
  Serial.begin(PORT);
  
  Serial.println("I LIKE TRAINS AND MAYONAISAE");
}


// ----------------------------------------------------------------
// |                            UPDATE                            |
// ---------------------------------------------------------- ------

void receivedCommand(String command) {
  Serial.println(command);
  
  if (command[1] == 'H') {
    // Second motor on
    Serial.println("1H");
    analogWrite(MOTOR_ONE_PIN, 255);
  } else if (command[1] == 'L') {
    // Second motor off
    Serial.println("1L");
    analogWrite(MOTOR_ONE_PIN, 0);
  }
  
  if (command[3] == 'H') {
    // Second motor ons
    Serial.println("2H");
    analogWrite(MOTOR_TWO_PIN, 255);
  } else if (command[3] == 'L') {
    // Second motor off
    Serial.println("2L");
    analogWrite(MOTOR_TWO_PIN, 0);
  }
  // It has sent a servo angle
  int angle = (String(command[4]) + String(command[5]) + String(command[6])).toInt();
  Serial.println(angle);
  if (angle >= 45 && angle <= 135) {
    servo.write(angle);
  }
}


int shouldNewLine = 0;
String activeCommand = "";


void loop() {
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
  
  delay(50);
}
