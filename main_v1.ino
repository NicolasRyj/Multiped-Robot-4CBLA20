#include <Servo.h>

Servo servo1; // Motor controlled by 'a'
Servo servo2; // Motor controlled by 'b'
Servo servo3; // Motor controlled by 'c'
Servo servo4; // Motor controlled by 'd'

// Initial angles for standard servos
int angle1 = 90;
int angle2 = 90;
// For continuous servos, consider these as "speed" variables, though they represent the angle for control purposes
int speed3 = 90; 
int speed4 = 90;

void setup() {
  servo1.attach(9); // Attach the first servo to digital pin 9
  servo2.attach(10); // Attach the second servo to digital pin 10
  servo3.attach(11); // Attach the third servo to digital pin 11
  servo4.attach(12); // Attach the fourth servo to digital pin 12
  Serial.begin(9600); // Start serial communication at 9600 bits per second
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // Read the incoming command until newline

    if (command.startsWith("a")) {
      adjustAngleOrSpeed(command, angle1, servo1, false);
    } else if (command.startsWith("b")) {
      adjustAngleOrSpeed(command, angle2, servo2, false);
    } else if (command.startsWith("c")) {
      adjustAngleOrSpeed(command, speed3, servo3, true);
    } else if (command.startsWith("d")) {
      adjustAngleOrSpeed(command, speed4, servo4, true);
    }
  }
}

void adjustAngleOrSpeed(String command, int &value, Servo myServo, bool isContinuous) {
  if (command.endsWith("+")) {
    if (!isContinuous) {
      value = min(value + 5, 180); // Increase angle for standard servos
    } else {
      value = 180; // Rotate continuously in one direction
    }
  } else if (command.endsWith("-")) {
    if (!isContinuous) {
      value = max(value - 5, 0); // Decrease angle for standard servos
    } else {
      value = 0; // Rotate continuously in the opposite direction
    }
  }
  myServo.write(value);
}
