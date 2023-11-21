#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

SoftwareSerial NodeMCU(D2, D3); // RX | TX

const int sensor1Pin = D5; // sensor 1 pin
const int sensor2Pin = D6; // sensor 2 pin
const int sensor3Pin = D7; // sensor 3 pin

int sensor1Value;
int sensor2Value;
int sensor3Value;
  
void setup() {
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
  pinMode(sensor3Pin, INPUT);

  Serial.begin(9600); // Hardware Serial to display on the Serial Monitor
  NodeMCU.begin(9600); // Software Serial for communication with Arduino Uno
}

void loop() {
  sensor1Value = digitalRead(sensor1Pin);
  sensor2Value = digitalRead(sensor2Pin);
  sensor3Value = digitalRead(sensor3Pin);

  if (sensor1Value == HIGH) {
    NodeMCU.println("1"); // Send "1" to indicate object detection to Arduino Uno
  }
  
  
  delay(1000); // Adjust delay as needed for stability
}
