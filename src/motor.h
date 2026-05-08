#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

// --- CẤU HÌNH CHÂN CẮM (Pinout) ---
const int IN1 = 16;// Chân điều khiển motor Trái 1
const int IN2 = 17;// Chân điều khiển motor Trái 2
const int IN3 = 18;// Chân điều khiển motor Phải 1
const int IN4 = 19;// Chân điều khiển motor Phải 2
const int ENA = 22; // Chân PWM motor Trái
const int ENB = 23; // Chân PWM motor Phải

// --- CẤU HÌNH PWM CHO ESP32 ---
const int pwmFreq = 5000;    // 5kHz để motor chạy êm hơn 1kHz
const int pwmResolution = 8; // 0-255
const int pwmChannelA = 0;   // Kênh cho bánh Trái
const int pwmChannelB = 1;   // Kênh cho bánh Phải

// --- HÀM KHỞI TẠO MOTOR ---
void setupMotor() { 
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // Thiết lập PWM
    ledcSetup(pwmChannelA, pwmFreq, pwmResolution);
    ledcSetup(pwmChannelB, pwmFreq, pwmResolution);

    // Gắn chân ENA, ENB vào kênh PWM
    ledcAttachPin(ENA, pwmChannelA);
    ledcAttachPin(ENB, pwmChannelB);
}

// --- HÀM ĐIỀU KHIỂN TỐC ĐỘ (Cốt lõi) ---
void setMotorSpeeds(int speedL, int speedR) {
    // Giới hạn trong khoảng -255 đến 255
    speedL = constrain(speedL, -255, 255);
    speedR = constrain(speedR, -255, 255);

    // Điều khiển Motor TRÁI (IN1, IN2)
    if (speedL > 0) {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        ledcWrite(pwmChannelA, speedL);
    } else if (speedL < 0) {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        ledcWrite(pwmChannelA, abs(speedL));
    } else {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        ledcWrite(pwmChannelA, 0);
    }

    // Điều khiển Motor PHẢI (IN3, IN4)
    if (speedR > 0) {
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        ledcWrite(pwmChannelB, speedR);
    } else if (speedR < 0) {
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        ledcWrite(pwmChannelB, abs(speedR));
    } else {
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        ledcWrite(pwmChannelB, 0);
    }
}

// --- CÁC HÀM TIỆN ÍCH ---
void stopRobot() {
    setMotorSpeeds(0, 0);
}

void turnLeft(int speed) {
    setMotorSpeeds(-speed, speed);
}

void turnRight(int speed) {
    setMotorSpeeds(speed, -speed);
}

void moveForward(int speed) {
    setMotorSpeeds(speed, speed);
}

void moveBackward(int speed) {
    setMotorSpeeds(-speed, -speed);
}

#endif // MOTOR_H