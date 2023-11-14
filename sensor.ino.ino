int bottleCount = 0; // Initialize bottle count to zero

const int sensor1Pin = 2; // Sensor 1 PIN = 2
const int sensor2Pin = 3;
const int sensor3Pin = 4; // Assuming this was meant for the third sensor
// You can adjust the pin number accordingly for your setup

int sensor1Value; // Variable to store the sensor value
int sensor2Value;
int sensor3Value;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(sensor1Pin, INPUT); // Set sensor pins as input
  pinMode(sensor2Pin, INPUT);
  pinMode(sensor3Pin, INPUT);
}

void loop() {
  sensor1Value = digitalRead(sensor1Pin);
  sensor2Value = digitalRead(sensor2Pin);
  sensor3Value = digitalRead(sensor3Pin);

  if (sensor1Value == LOW || sensor2Value == LOW || sensor3Value == LOW) {
    if (sensor1Value == LOW) {
      Serial.println("Sensor1 Object Detected!");
      Serial.println("------------------------");
    }
    if (sensor2Value == LOW) {
      Serial.println("Sensor2 Object Detected!");
      Serial.println("------------------------");
    }
    if (sensor3Value == LOW) {
      Serial.println("Sensor3 Object Detected!");
      Serial.println("------------------------");
    }

    bottleCount++;
    Serial.print("Count = ");
    Serial.println(bottleCount);
  }
  delay(500); // Add a small delay for stability
}
