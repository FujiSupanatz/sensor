#include <Key.h>
#include <Keypad.h>
#include <hd44780.h>
#include <Wire.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

int bottleCount = 0;
SoftwareSerial esp8266(10, 11); // Define SoftwareSerial object for ESP8266 (Connect ESP8266 RX to Arduino pin 10, and ESP8266 TX to Arduino pin 11)
String phoneNumber = "";

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'}, // key pad 
  {'*', '0', '#', 'D'}
};

const int sensor1Pin = 2;
const int sensor2Pin = 3;
const int sensor3Pin = 4; 
const int sensor4Pin = 5;
const int sensor5Pin = 6;
const int sensor6Pin = 7;
const int sensor7Pin = 8;

const int buttonPin = 13;

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
const char* serverUrl = "http://yourwebsite.com/api/endpoint"; // Replace with your website's API endpoint

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int lastButtonState = LOW;

int sensor1Value;
int sensor2Value;
int sensor3Value;
int sensor4Value;
int sensor5Value;
int sensor6Value;
int sensor7Value;



byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool runSensor = false;


void saveCountToEEPROM(int count, String number);
void readCountFromEEPROM();
void saveFunction();
void saveButton();
void checkSensors();

void setup() {
  Serial.begin(9600);
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
  pinMode(sensor3Pin, INPUT);
  pinMode(sensor4Pin, INPUT);
  pinMode(sensor5Pin, INPUT);
  pinMode(sensor6Pin, INPUT);
  pinMode(sensor7Pin, INPUT);
  pinMode(buttonPin, INPUT);
 
  Serial.println("Ready");
  Wire.begin();
  Serial.begin(9600);
  lcd.init();
  
  // Turn on the backlight (if available)
  lcd.backlight();
   lcd.setCursor(0, 0);
  lcd.print("Enter your phone:");

  Serial.println("phone : ");
 
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Your data to send
  String dataToSend = "YourDataHere";

  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(dataToSend);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  } else {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }

  http.end();



}


void loop() {
  // Code to send commands to ESP8266 when '1' is received from Serial
  if (Serial.available()) {
    char c = Serial.read(); // Read the incoming data from Arduino

    if (c == '1') {
      Serial.println("Sending WiFi command to NodeMCU...");
      esp8266.write("1"); // Send command to NodeMCU (ESP8266) for WiFi action
    }
  }

char key = keypad.getKey();

  if (key != NO_KEY && isDigit(key)) {
    phoneNumber += key;
    lcd.setCursor(phoneNumber.length() - 1, 1); // Set cursor at the end of the phone number on the LCD
    lcd.print(key);
    delay(150);
     Serial.print(key);
  }
    

  
  saveButton();
  if (runSensor) {
    checkSensors();
  }
}

void saveFunction() {
  saveCountToEEPROM(bottleCount, phoneNumber);
  readCountFromEEPROM();
}

void saveButton() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != lastButtonState) {
      lastButtonState = reading;
      if (reading == HIGH) {
        saveFunction();
        Serial.println("Button was pressed");
        delay(200);
        runSensor = !runSensor;
      }
    }
  }
}

void checkSensors() {
  sensor1Value = digitalRead(sensor1Pin);
  sensor2Value = digitalRead(sensor2Pin);
  sensor3Value = digitalRead(sensor3Pin);
  sensor4Value = digitalRead(sensor4Pin);
  sensor5Value = digitalRead(sensor5Pin);
  sensor6Value = digitalRead(sensor6Pin);
  sensor7Value = digitalRead(sensor7Pin);
  
  if (sensor1Value == LOW) {
    Serial.println("------------------------");
    Serial.println("Sensor1 Object Detected!");
    Serial.println("------------------------");
    delay(250);
    bottleCount++;
    saveCountToEEPROM(bottleCount, phoneNumber);
    readCountFromEEPROM();   
    Serial.print("Count = ");
    Serial.println(bottleCount);
  }
  // ... (similar blocks for other sensors)
}

void saveCountToEEPROM(int count, String number) {
  int addressCount = 0;
  int addressPhone = sizeof(int);
  EEPROM.put(addressCount, count);
  for (unsigned int i = 0; i < number.length(); ++i) {
    EEPROM.put(addressPhone + i, number[i]);
  }
  EEPROM.put(addressPhone + number.length(), '\0');
}

void readCountFromEEPROM() {
  int addressCount = 0;
  int addressPhone = sizeof(int);
  EEPROM.get(addressCount, bottleCount);
  String tempPhone = "";
  char ch;
  do {
    EEPROM.get(addressPhone + tempPhone.length(), ch);
    if (ch != '\0') {
      tempPhone += ch;
    }
  } while (ch != '\0');
  phoneNumber = tempPhone;
  Serial.print("Stored Count: ");
  Serial.println(bottleCount);
  Serial.print("Stored Phone Number: ");
  Serial.println(phoneNumber);
}