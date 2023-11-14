int bottleCount = 0; // Initialize bottle count to zero

const int sensor1Pin = 2; // Sensor 1 PIN = 2
const int sensor2Pin = 3;
const int sensor3Pin = 4; // Assuming this was meant for the third sensor
const int sensor4Pin = 5;
const int sensor5Pin = 6;
const int sensor6Pin = 7;
const int sensor7Pin = 8;

// You can adjust the pin number accordingly for your setup

int sensor1Value; // Variable to store the sensor value
int sensor2Value;
int sensor3Value;
int sensor4Value;
int sensor5Value;
int sensor6Value;
int sensor7Value;


void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(sensor1Pin, INPUT); // Set sensor pins as input
  pinMode(sensor2Pin, INPUT);
  pinMode(sensor3Pin, INPUT);
  pinMode(sensor4Pin, INPUT);
  pinMode(sensor5Pin, INPUT);
}

void loop() {
  sensor1Value = digitalRead(sensor1Pin);
  sensor2Value = digitalRead(sensor2Pin);
  sensor3Value = digitalRead(sensor3Pin);
  sensor4Value = digitalRead(sensor4Pin);
  sensor5Value = digitalRead(sensor5Pin);
  sensor6Value = digitalRead(sensor6Pin);
  sensor7Value = digitalRead(sensor7Pin);
  if (sensor1Value == LOW || sensor2Value == LOW || sensor3Value == LOW || sensor4Value == LOW || sensor5Value == LOW || sensor6Value == LOW || sensor7Value) {
    if (sensor1Value == LOW) {
      Serial.println("------------------------");
      Serial.println("Sensor1 Object Detected!");
      Serial.println("------------------------");
      delay(250);
    }
    if (sensor2Value == LOW) {
      Serial.println("------------------------");
      Serial.println("Sensor2 Object Detected!");
      Serial.println("------------------------");
      delay(250);
    }
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
    }

    bottleCount++;
    Serial.print("Count = ");
    Serial.println(bottleCount);
  }
  delay(200); // Add a small delay for stability
}
