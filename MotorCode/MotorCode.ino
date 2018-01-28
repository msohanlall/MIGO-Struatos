#include <AFMotor.h>
// Motor with 200 steps per rev (1.8 degree)
// to motor port #1 (M1 and M2)
AF_Stepper motor(200, 2);
void setup() {
  // set up Serial library at 9600 bps
  Serial.begin(9600);
  Serial.println("Stepper test!");
  motor.setSpeed(50); // 50 rpm  
}
void loop() {
  Serial.println("Single coil steps");
  motor.step(200, FORWARD, DOUBLE);
  motor.step(200, FORWARD, DOUBLE);
  motor.step(200, FORWARD, DOUBLE);
  motor.step(200, FORWARD, DOUBLE);
  motor.step(200, FORWARD, DOUBLE);
  motor.step(200, FORWARD, DOUBLE);
  motor.step(200, FORWARD, DOUBLE);
  motor.step(200, FORWARD, DOUBLE);
  motor.step(200, FORWARD, DOUBLE);
  motor.step(200, FORWARD, DOUBLE);
  motor.step(200, FORWARD, DOUBLE);
  motor.step(200, FORWARD, DOUBLE);
  motor.step(200, FORWARD, DOUBLE);
  motor.step(200, FORWARD, DOUBLE);
  motor.step(200, FORWARD, DOUBLE);
  motor.step(200, FORWARD, DOUBLE);
  motor.step(200, FORWARD, DOUBLE);
delay(10000);
  Serial.println("Double coil steps");
  motor.step(200, BACKWARD, DOUBLE);
  motor.step(200, BACKWARD, DOUBLE);
  motor.step(200, BACKWARD, DOUBLE);
  motor.step(200, BACKWARD, DOUBLE);
  motor.step(200, BACKWARD, DOUBLE);
  motor.step(200, BACKWARD, DOUBLE);
  motor.step(200, BACKWARD, DOUBLE);
  motor.step(200, BACKWARD, DOUBLE);
  motor.step(200, BACKWARD, DOUBLE);
  motor.step(200, BACKWARD, DOUBLE);
  motor.step(200, BACKWARD, DOUBLE);
  motor.step(200, BACKWARD, DOUBLE);
  motor.step(200, BACKWARD, DOUBLE);
  motor.step(200, BACKWARD, DOUBLE);
delay(10000);
}
