#include <Servo.h>

//declare pins
//fuck this orginization
const int servoPin = 3;

const int motor1Pwm = 11;
const int motor2Pwm = 5; //why the hell can this not work on pin 10 wtf

const int motor1Dir1 = 12;
const int motor1Dir2 = 13;
const int motor2Dir1 = 9;
const int motor2Dir2 = 8;


Servo servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(servoPin, OUTPUT);
  pinMode(motor1Pwm, OUTPUT);
  pinMode(motor2Pwm, OUTPUT);
  pinMode(motor1Dir1, OUTPUT);
  pinMode(motor1Dir2, OUTPUT);
  pinMode(motor2Dir1, OUTPUT);
  pinMode(motor2Dir2, OUTPUT);

  //startup sequence
  servo.attach(servoPin);
  servo.write(0);
  delay(1000);

  digitalWrite(motor1Dir1, HIGH);
  digitalWrite(motor2Dir1, HIGH);
  digitalWrite(motor1Dir2, LOW);
  digitalWrite(motor2Dir2, LOW);
  analogWrite(motor1Pwm, 128);
  analogWrite(motor2Pwm, 128);
  delay(1000);
  
  analogWrite(motor1Pwm, 0);
  analogWrite(motor2Pwm, 0);
  delay(1000);

  digitalWrite(motor1Dir1, LOW);
  digitalWrite(motor2Dir1, LOW);
  digitalWrite(motor1Dir2, HIGH);
  digitalWrite(motor2Dir2, HIGH);
  analogWrite(motor1Pwm, 128);
  analogWrite(motor2Pwm, 128);
  delay(1000);

  analogWrite(motor1Pwm, 0);
  analogWrite(motor2Pwm, 0);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
     char state = Serial.read();
     if(state == "stop") {
      analogWrite(motor1Pwm, 0);
      analogWrite(motor2Pwm, 0);
      servo.write(90);
     }
     
     if(state == "gamerTime") {
      //HAHAHAHAHAHHAHAHAHA
      digitalWrite(motor1Dir1, HIGH);
      digitalWrite(motor2Dir1, HIGH);
      digitalWrite(motor1Dir2, LOW);
      digitalWrite(motor2Dir2, LOW);
      analogWrite(motor1Pwm, 255);
      analogWrite(motor2Pwm, 255);
      servo.write(90);
     }

     if(state == "notSoGamerTime") {
      digitalWrite(motor1Dir1, HIGH);
      digitalWrite(motor2Dir1, LOW);
      digitalWrite(motor1Dir2, LOW);
      digitalWrite(motor2Dir2, HIGH);
      analogWrite(motor1Pwm, 128);
      analogWrite(motor2Pwm, 128);
      servo.write(90);
     }
  }
}
