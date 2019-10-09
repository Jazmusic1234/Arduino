#include <Servo.h>

int pin = 9;
Servo servo;
int servoAngle = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(pin);
}

void loop() {
  // put your main code here, to run repeatedly:

 /* // Control direction of motor
  servo.write(45);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(135);
  delay(1000);
  servo.write(90);
  delay(1000);*/

  // Control speed of motor
  for(servoAngle = 0; servoAngle < 180; servoAngle++) {
    servo.write(servoAngle);
    delay(1);
  }

  for(servoAngle = 180; servoAngle > 0; servoAngle--)  //now move back the micro servo from 0 degrees to 180 degrees
  {                                
    servo.write(servoAngle);          
    delay(10);      
  }
}
