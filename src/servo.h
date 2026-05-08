#include <arduino.h>
#ifndef SERVO_H 
#define SERVO_H

const int servoPin = 13; // Chân điều khiển servo, thay đổi theo chân bạn dùng
const int servoChannel = 2; // Kênh PWM cho servo
const int servoFreq = 50; // Tần số PWM 50Hz cho servo
const int servoResolution = 16; // Độ phân giải PWM

// Giới hạn góc servo (microseconds)
const int servoMinPulse = 500; // 0 độ
const int servoMaxPulse = 2500; // 180 độ

void setupServo() {
  ledcSetup(servoChannel, servoFreq, servoResolution);
  ledcAttachPin(servoPin, servoChannel);
}

void setServoAngle(int angle) {
  // Giới hạn góc từ 0 đến 180
  angle = constrain(angle, 0, 180);
  
  // Tính toán duty cycle cho góc
  int pulseWidth = map(angle, 0, 180, servoMinPulse, servoMaxPulse);
  int dutyCycle = (pulseWidth * (1 << servoResolution)) / (1000000 / servoFreq);
  
  ledcWrite(servoChannel, dutyCycle);
}

#endif // SERVO_H