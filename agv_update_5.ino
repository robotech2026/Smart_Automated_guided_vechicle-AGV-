#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "thiru";
const char* password = "12345678";

WebServer server(80);

#define ENA 33
#define IN1 25
#define IN2 26

#define ENB 32
#define IN3 27
#define IN4 14

#define LEFT_SENSOR 4
#define RIGHT_SENSOR 5

#define TRIG 18
#define ECHO 19

#define BUZZER 13

int straightSpeed = 255;
int turnSpeed = 255;

bool commandMode = false;
String qrCommand = "";

unsigned long ignoreObstacleUntil = 0;

void forward() {
  ledcWrite(ENA, straightSpeed);
  ledcWrite(ENB, straightSpeed);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void leftTurn() {
  ledcWrite(ENA, turnSpeed);
  ledcWrite(ENB, turnSpeed);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void rightTurn() {
  ledcWrite(ENA, turnSpeed);
  ledcWrite(ENB, turnSpeed);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopRobot() {
  ledcWrite(ENA, 0);
  ledcWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

float getDistance() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);

  if (duration == 0)
    return 999;

  return duration * 0.0343 / 2;
}

// ---------- WEB COMMANDS ----------

void handleLeft() {
  qrCommand = "LEFT";
  commandMode = true;
  ignoreObstacleUntil = millis() + 5000;
  server.send(200, "text/plain", "LEFT OK");
}

void handleRight() {
  qrCommand = "RIGHT";
  commandMode = true;
  ignoreObstacleUntil = millis() + 5000;
  server.send(200, "text/plain", "RIGHT OK");
}

void handleForward() {
  qrCommand = "FORWARD";
  commandMode = true;
  ignoreObstacleUntil = millis() + 5000;
  server.send(200, "text/plain", "FORWARD OK");
}
void handleStop() {
  stopRobot();
  qrCommand = "";
  commandMode = false;
  server.send(200, "text/plain", "STOP OK");
}

void setup() {

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(BUZZER, OUTPUT);

  Serial.begin(115200);

  ledcAttach(ENA, 5000, 8);
  ledcAttach(ENB, 5000, 8);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/forward", handleForward);
  server.on("/stop", handleStop);

  server.begin();

  digitalWrite(BUZZER, LOW);
}

void loop() {

  server.handleClient();

  // QR Command Mode
  if (commandMode) {

    if (qrCommand == "LEFT") {
      leftTurn();
      delay(1000);
    }

    else if (qrCommand == "RIGHT") {
      rightTurn();
      delay(1000);
    }

    else if (qrCommand == "FORWARD") {
      forward();
      delay(1000);
    }

    stopRobot();

    qrCommand = "";
    commandMode = false;

    return;
  }

  // Normal Line Following
  float distance = getDistance();

  if (millis() > ignoreObstacleUntil) {

  if (distance <= 25) {

    stopRobot();

    digitalWrite(BUZZER, HIGH);

    Serial.println("WAITING_QR");

    delay(50);
    return;
  }
}

  digitalWrite(BUZZER, LOW);

  int L = digitalRead(LEFT_SENSOR);
  int R = digitalRead(RIGHT_SENSOR);

  if (L == 1 && R == 1) {

    forward();
  }

  else if (L == 1 && R == 0) {

    leftTurn();
  }

  else if (L == 0 && R == 1) {

    rightTurn();
  }

  else {

    stopRobot();
  }

  delay(5);
}