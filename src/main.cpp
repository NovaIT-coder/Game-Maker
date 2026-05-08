#include <Arduino.h>
#include "motor.h"
#include "sensor.h"
#include "line.h"
int baseSpeed = 150;

void setup() {
  Serial.begin(115200);
  delay(500);

  setupMotor();
  setupSensor();

  Serial.println("Line follower ready");
}

void loop() {
  followLine();
  delay(10);
}
