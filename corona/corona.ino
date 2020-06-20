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
  servo.write(90);
  delay(1000);

  digitalWrite(motor1Dir1, HIGH);
  digitalWrite(motor2Dir1, HIGH);
  digitalWrite(motor1Dir2, LOW);
  digitalWrite(motor2Dir2, LOW);
  analogWrite(motor1Pwm, 512);
  analogWrite(motor2Pwm, 512);
  delay(1000);
  
  analogWrite(motor1Pwm, 0);
  analogWrite(motor2Pwm, 0);
  delay(1000);

  digitalWrite(motor1Dir1, LOW);
  digitalWrite(motor2Dir1, LOW);
  digitalWrite(motor1Dir2, HIGH);
  digitalWrite(motor2Dir2, HIGH);
  analogWrite(motor1Pwm, 512);
  analogWrite(motor2Pwm, 512);
  delay(1000);

  analogWrite(motor1Pwm, 0);
  analogWrite(motor2Pwm, 0);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available) {
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
      analogWrite(motor1Pwm, 1023);
      analogWrite(motor2Pwm, 1023);
     }

     if(state == "notSoGamerTime") {
      digitalWrite(motor1Dir1, HIGH);
      digitalWrite(motor2Dir1, LOW);
      digitalWrite(motor1Dir2, LOW);
      digitalWrite(motor2Dir2, HIGH);
      analogWrite(motor1Pwm, 512);
      analogWrite(motor2Pwm, 512);
     }
  }
}
