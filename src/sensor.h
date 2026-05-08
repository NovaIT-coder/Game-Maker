#include <Arduino.h>
#ifndef SENSOR_H
#define SENSOR_H

const int S1 = 25;
const int S2 = 33;
const int S3 = 32;
const int S4 = 35;
const int S5 = 34;

// Thay đổi theo module sensor của bạn:
// - nếu module trả LOW khi nhìn thấy vạch thì giữ false
// - nếu module trả HIGH khi nhìn thấy vạch thì đổi thành true
const bool LINE_ACTIVE_HIGH = false; // true nếu cảm biến trả HIGH khi phát hiện line, false nếu trả LOW

void setupSensor() {
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
}



#endif // SENSOR_H