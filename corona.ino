#include <Servo.h>

//declare pins
//fuck this orginization
const int servoPin = 3;

const int motor1Pwm = 11;
const int motor2Pwm = 10;

const int motor1Dir1 = 9;
const int motor1Dir2 = 8;
const int motor2Dir1 = 12;
const int motor2Dir2 = 13;


Servo servo;

void setup() {
  // put your setup code here, to run once:
  servo.attach(servoPin);
  servo.write(0);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  servo.write(0);
  delay(1000);
  servo.write(180);
  delay(1000);
}
