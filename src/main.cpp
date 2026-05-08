#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>
#include "motor.h"
#include "sensor.h"
#include "line.h"
#include "servo.h"

const char* apSSID = "XeLineFollower"; // Tên mạng WiFi của xe
const char* apPassword = "12345678"; // Mật khẩu WiFi của xe (ít nhất 8 ký tự)

WebServer server(80);

bool manualMode = false;
int baseSpeed = 150;

void handleRoot() {
  File file = LittleFS.open("/index.html", "r");
  if (!file) {
    server.send(404, "text/plain", "File not found");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void handleForward() {
  if (manualMode) {
    setMotorSpeeds(150, 150);
  }
  server.send(200, "text/plain", "Forward");
}

void handleBackward() {
  if (manualMode) {
    setMotorSpeeds(-150, -150);
  }
  server.send(200, "text/plain", "Backward");
}

void handleLeft() {
  if (manualMode) {
    setMotorSpeeds(-100, 100);
  }
  server.send(200, "text/plain", "Left");
}

void handleRight() {
  if (manualMode) {
    setMotorSpeeds(100, -100);
  }
  server.send(200, "text/plain", "Right");
}

void handleStop() {
  setMotorSpeeds(0, 0);
  server.send(200, "text/plain", "Stop");
}

void handleFollow() {
  manualMode = false;
  server.send(200, "text/plain", "Follow Line Mode");
}

void handleManual() {
  manualMode = true;
  setMotorSpeeds(0, 0);
  server.send(200, "text/plain", "Manual Mode");
}

void setup() {
  Serial.begin(115200);
  delay(500);

  setupMotor();
  setupSensor();
  setupServo();

  // Khởi tạo LittleFS
  if (!LittleFS.begin()) {
    Serial.println("LittleFS mount failed");
    return;
  }

  // Chạy ESP32 ở chế độ Access Point (SoftAP)
  WiFi.mode(WIFI_AP);
  if (!WiFi.softAP(apSSID, apPassword)) {
    Serial.println("SoftAP start failed");
    return;
  }
  IPAddress apIP = WiFi.softAPIP();
  Serial.print("SoftAP SSID: ");
  Serial.println(apSSID);
  Serial.print("SoftAP IP: ");
  Serial.println(apIP);

  // Thiết lập các route
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/stop", handleStop);
  server.on("/follow", handleFollow);
  server.on("/manual", handleManual);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  if (!manualMode) {
    followLine();
  }
  delay(10);
}
