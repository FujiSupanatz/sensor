#include <Wire.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int bottleCount = 0;
String phoneNumber = "0909090900";
void saveCountToEEPROM(int count, String number);
void readCountFromEEPROM();
void saveFunction();
void saveButton();
void checkSensors();


const int sensor1Pin = 2; // Sensor 1 PIN = 2
const int sensor2Pin = 3;
const int sensor3Pin = 4; 
const int sensor4Pin = 5;
const int sensor5Pin = 6;
const int sensor6Pin = 7;
const int sensor7Pin = 8;
const int ledPin = 9;

const int  buttonPin = 13; // button pin set 13 na ikuy
bool buttonPressed = false;
unsigned long previousMillis = 0;
const long interval = 200; // Interval for sensor checking in milliseconds


int sensor1Value;
int sensor2Value;
int sensor3Value;
int sensor4Value;
int sensor5Value;
int sensor6Value;
int sensor7Value;





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
  pinMode(ledPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello world");
}


void saveFunction() { // SAVE
  saveCountToEEPROM(bottleCount, phoneNumber);
  readCountFromEEPROM();
}



void saveButton() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && !buttonPressed) {
    saveFunction();
    Serial.println("Button was pressed");
    buttonPressed = true;
    delay(200);
  } else {
    buttonPressed = false;
  }
}



void checkSensors() {
   saveButton();

  if (buttonPressed) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

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
      
      bottleCount++;
      saveCountToEEPROM(bottleCount, phoneNumber);
      readCountFromEEPROM();   
      Serial.print("Count = ");
      Serial.println(bottleCount);
    
    }
    if (sensor2Value == LOW) {
      Serial.println("------------------------");
      Serial.println("Sensor2 Object Detected!");
      Serial.println("------------------------");
      
      bottleCount++;
     saveCountToEEPROM(bottleCount, phoneNumber);  
     readCountFromEEPROM();
      Serial.print("Count = ");
      Serial.println(bottleCount);
      
  
    } 
  }
}
void loop() {
   
    
  
    
  


}


void saveCountToEEPROM(int count, String number) {
  // Calculate the EEPROM addresses to store the integer count and phone number
  int addressCount = 0; // Starting address in EEPROM for count
  int addressPhone = sizeof(int); // Next address after count for phone number

  EEPROM.put(addressCount, count); // Store count at the calculated address
  for (unsigned int i = 0; i < number.length(); ++i) {
    EEPROM.put(addressPhone + i, number[i]); // Store each character of the phone number
  }
  EEPROM.put(addressPhone + number.length(), '\0'); // Null-terminate the phone number string
}

void readCountFromEEPROM() {
  int addressCount = 0; // Starting address in EEPROM to read for count
  int addressPhone = sizeof(int); // Next address after count for phone number

  EEPROM.get(addressCount, bottleCount); // Retrieve count from EEPROM

  // Retrieve phone number character by character until a null terminator is encountered
  String tempPhone = "";

  char ch;

  do {
    EEPROM.get(addressPhone + tempPhone.length(), ch);
    if (ch != '\0') {
      tempPhone += ch;
    }
  } while (ch != '\0');

  phoneNumber = tempPhone; // Update the global phone number variable

  // Print the stored data to Serial monitor
  Serial.print("Stored Count: ");
  Serial.println(bottleCount);
  Serial.print("Stored Phone Number: ");
  Serial.println(phoneNumber);
}