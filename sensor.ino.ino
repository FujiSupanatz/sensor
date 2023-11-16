#include <Wire.h>
#include <EEPROM.h>
int bottleCount = 0; // Initialize bottle count to zero
String phoneNumber = "0909090900";
void saveCountToEEPROM(int count, String number);
void readCountFromEEPROM();

const int sensor1Pin = 2; // Sensor 1 PIN = 2
const int sensor2Pin = 3;
const int sensor3Pin = 4; // Assuming this was meant for the third sensor
const int sensor4Pin = 5;
const int sensor5Pin = 6;
const int sensor6Pin = 7;
const int sensor7Pin = 8;

const int  buttonPin = 13; // button pin set 13 na ikuy

// You can adjust the pin number accordingly for your setup

int sensor1Value; // Variable to store the sensor value
int sensor2Value;
int sensor3Value;
int sensor4Value;
int sensor5Value;
int sensor6Value;
int sensor7Value;

int buttonState = 0;

bool runSensor = false;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(sensor1Pin, INPUT); // Set sensor pins as input
  pinMode(sensor2Pin, INPUT);
  pinMode(sensor3Pin, INPUT);
  pinMode(sensor4Pin, INPUT);
  pinMode(sensor5Pin, INPUT);
  pinMode(sensor6Pin, INPUT);
  pinMode(sensor7Pin, INPUT);
  pinMode(buttonPin, INPUT);

}
void loop(){
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH) {
    // Toggle the flag state when the button is pressed
    runSensor = !runSensor;
    delay(200); // Delay for debouncing
  }
  
  if (runSensor) {
    sensor(); // Run sensor function while the flag is true
  }
  
  // Additional code as needed
  
  delay(200); // Add a small delay for stability
}

void sensor() {
  sensor1Value = digitalRead(sensor1Pin);
  sensor2Value = digitalRead(sensor2Pin);
  sensor3Value = digitalRead(sensor3Pin);
  sensor4Value = digitalRead(sensor4Pin);
  sensor5Value = digitalRead(sensor5Pin);
  sensor6Value = digitalRead(sensor6Pin);
  sensor7Value = digitalRead(sensor7Pin);
  buttonState =  digitalRead(buttonPin);
  
    
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
    if (sensor2Value == LOW) {
      Serial.println("------------------------");
      Serial.println("Sensor2 Object Detected!");
      Serial.println("------------------------");
      delay(250);
      bottleCount++;
     saveCountToEEPROM(bottleCount, phoneNumber);  
     readCountFromEEPROM();
     
      Serial.print("Count = ");
      Serial.println(bottleCount);
      
  
    } /*
    if (sensor3Value == LOW) {
      Serial.println("------------------------");
      Serial.println("Sensor3 Object Detected!");
      Serial.println("------------------------");
      delay(250);
    }
    if (sensor4Value == LOW) {
      Serial.println("------------------------");
      Serial.println("Sensor4 Object Detected!");
      Serial.println("------------------------");
      delay(250);
    }
    if (sensor5Value == LOW) {
      Serial.println("------------------------");
      Serial.println("Sensor5 Object Detected!");
      Serial.println("------------------------");
      delay(250);
    }
    if (sensor6Value == LOW) {
      Serial.println("------------------------");
      Serial.println("Sensor6 Object Detected!");
      Serial.println("------------------------");
      delay(250);
    }
    if (sensor7Value == LOW) {
      Serial.println("------------------------");
      Serial.println("Sensor7 Object Detected!");
      Serial.println("------------------------");
      delay(250);
    } */

     
     
  delay(200); // Add a small delay for stability
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