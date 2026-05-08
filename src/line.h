#include <Arduino.h>
#include "sensor.h"
#include "motor.h"
#ifndef LINE_H
#define LINE_H
extern int baseSpeed;

void handleIntersection(String direction) {
    if (direction == "LEFT") {
        // Xoay trái tại chỗ cho đến khi thoát khỏi vạch ngang
        setMotorSpeeds(-150, 150); 
        delay(200); // Khoảng thời gian đủ để mắt đọc thoát khỏi vạch hiện tại
        
        // Xoay tiếp cho đến khi mắt giữa giả (S2 hoặc S4) bắt được line mới
        // Vì S3 hỏng nên Minh có thể check S2 hoặc S4
        while(digitalRead(S2) == LOW && digitalRead(S4) == LOW); 
        
        stopRobot();
    } 
    else if (direction == "RIGHT") {
        setMotorSpeeds(150, -150);
        delay(200);
        while(digitalRead(S2) == LOW && digitalRead(S4) == LOW);
        stopRobot();
    }
}


void followLine() {
    int s1 = digitalRead(S1);
    int s2 = digitalRead(S2);
    int s4 = digitalRead(S4);
    int s5 = digitalRead(S5);

    // 1. Kiểm tra ngã rẽ TRƯỚC (Ưu tiên cao nhất)
    if (s1 == HIGH && s2 == HIGH) {
        handleIntersection("LEFT");
    }
    else if (s5 == HIGH && s4 == HIGH) {
        handleIntersection("RIGHT");
    }
    // 2. Nếu không phải ngã rẽ mới tính đến chuyện đi thẳng/lệch
    else {
        // Đi thẳng: Vạch nằm ở giữa (S3 giả) hoặc đè cả 2 mắt trong
        if ((s2 == LOW && s4 == LOW) || (s2 == HIGH && s4 == HIGH)) {
            moveForward(baseSpeed);
        }
        // Lệch phải (S2 chạm) -> Chỉnh trái
        else if (s2 == HIGH) {
            setMotorSpeeds(baseSpeed - 35, baseSpeed + 35); // Tăng độ lệch lên một chút nếu xe vẫn lắc
        }
        // Lệch trái (S4 chạm) -> Chỉnh phải
        else if (s4 == HIGH) {
            setMotorSpeeds(baseSpeed + 35, baseSpeed - 35);
        }
    }
}

#endif // LINE_H