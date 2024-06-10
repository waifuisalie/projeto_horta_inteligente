#include <Arduino.h>
#include <Wire.h>
//#include <LiquidCrystal_I2C.h>

// Defining the sensors
int sensor1 = 34;
int sensor2 = 35;
int sensor3 = 36;
int sensor4 = 39;

// Defining the relay outputs
int irrigationPin1 = 16; 
int irrigationPin2 = 17;
int irrigationPin3 = 18;
int irrigationPin4 = 19;

// Replace these values with your calibration readings
int drySoil1 = 2250;
int wetSoil1 = 1000;

int drySoil2 = 2250; // Replace with actual calibration values
int wetSoil2 = 1000; // Replace with actual calibration values

int drySoil3 = 2250; // Replace with actual calibration values
int wetSoil3 = 1000; // Replace with actual calibration values

int drySoil4 = 2250; // Replace with actual calibration values
int wetSoil4 = 1000; // Replace with actual calibration values

// Variables to manage irrigation timing
unsigned long irrigationStartTime1 = 0;
unsigned long irrigationStartTime2 = 0;
unsigned long irrigationStartTime3 = 0;
unsigned long irrigationStartTime4 = 0;

bool isIrrigating1 = false;
bool isIrrigating2 = false;
bool isIrrigating3 = false;
bool isIrrigating4 = false;

const unsigned long irrigationDuration = 3000; // Irrigation duration in milliseconds

// LCD setup
//LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD I2C address

unsigned long lastLCDUpdateTime = 0;
const unsigned long lcdUpdateInterval = 2000; // 2 seconds interval to update LCD display
int currentPlant = 1;

void setup() {
  Serial.begin(115200);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);

  pinMode(irrigationPin1, OUTPUT);
  digitalWrite(irrigationPin1, LOW);  // Ensure the irrigation is off initially

  pinMode(irrigationPin2, OUTPUT);
  digitalWrite(irrigationPin2, LOW);  // Ensure the irrigation is off initially

  pinMode(irrigationPin3, OUTPUT);
  digitalWrite(irrigationPin3, LOW);  // Ensure the irrigation is off initially

  pinMode(irrigationPin4, OUTPUT);
  digitalWrite(irrigationPin4, LOW);  // Ensure the irrigation is off initially

  /*lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Irrigation System");*/
  delay(2000);
}

void loop() {
  int humid1 = analogRead(sensor1); 
  /*int humid2 = analogRead(sensor2);  
  int humid3 = analogRead(sensor3);  
  int humid4 = analogRead(sensor4);  */

  int porcentage1 = map(humid1, drySoil1, wetSoil1, 0, 100);
  /*int porcentage2 = map(humid2, drySoil2, wetSoil2, 0, 100);
  int porcentage3 = map(humid3, drySoil3, wetSoil3, 0, 100);
  int porcentage4 = map(humid4, drySoil4, wetSoil4, 0, 100);*/

  // Irrigation logic 1
  if (porcentage1 <= 30 && !isIrrigating1) {
    Serial.println("Moisture 1 below 30%. Irrigating...");
    digitalWrite(irrigationPin1, HIGH);  // Turn on the irrigation
    irrigationStartTime1 = millis();     // Record the start time
    isIrrigating1 = true;                // Set the irrigating flag
    /*lcd.clear();
    lcd.print("Plant 1: Irrigating");*/
  }

  // Check if irrigation duration has passed for sensor 1
  if (isIrrigating1 && (millis() - irrigationStartTime1 >= irrigationDuration)) {
    digitalWrite(irrigationPin1, LOW);   // Turn off the irrigation
    isIrrigating1 = false;               // Reset the irrigating flag
    /*lcd.clear();
    lcd.print("Plant 1: Done");*/
  }

  /*// Irrigation logic 2
  if (porcentage2 <= 30 && !isIrrigating2) {
    Serial.println("Moisture 2 below 30%. Irrigating...");
    digitalWrite(irrigationPin2, HIGH);  // Turn on the irrigation
    irrigationStartTime2 = millis();     // Record the start time
    isIrrigating2 = true;                // Set the irrigating flag
    lcd.clear();
    lcd.print("Plant 2: Irrigating");
  }

  // Check if irrigation duration has passed for sensor 2
  if (isIrrigating2 && (millis() - irrigationStartTime2 >= irrigationDuration)) {
    digitalWrite(irrigationPin2, LOW);   // Turn off the irrigation
    isIrrigating2 = false;               // Reset the irrigating flag
    lcd.clear();
    lcd.print("Plant 2: Done");
  }

  // Irrigation logic 3
  if (porcentage3 <= 30 && !isIrrigating3) {
    Serial.println("Moisture 3 below 30%. Irrigating...");
    digitalWrite(irrigationPin3, HIGH);  // Turn on the irrigation
    irrigationStartTime3 = millis();     // Record the start time
    isIrrigating3 = true;                // Set the irrigating flag
    lcd.clear();
    lcd.print("Plant 3: Irrigating");
  }

  // Check if irrigation duration has passed for sensor 3
  if (isIrrigating3 && (millis() - irrigationStartTime3 >= irrigationDuration)) {
    digitalWrite(irrigationPin3, LOW);   // Turn off the irrigation
    isIrrigating3 = false;               // Reset the irrigating flag
    lcd.clear();
    lcd.print("Plant 3: Done");
  }

  // Irrigation logic 4
  if (porcentage4 <= 30 && !isIrrigating4) {
    Serial.println("Moisture 4 below 30%. Irrigating...");
    digitalWrite(irrigationPin4, HIGH);  // Turn on the irrigation
    irrigationStartTime4 = millis();     // Record the start time
    isIrrigating4 = true;                // Set the irrigating flag
    lcd.clear();
    lcd.print("Plant 4: Irrigating");
  }

  // Check if irrigation duration has passed for sensor 4
  if (isIrrigating4 && (millis() - irrigationStartTime4 >= irrigationDuration)) {
    digitalWrite(irrigationPin4, LOW);   // Turn off the irrigation
    isIrrigating4 = false;               // Reset the irrigating flag
    lcd.clear();
    lcd.print("Plant 4: Done");
  }

  // Update LCD display with moisture levels periodically
  if (millis() - lastLCDUpdateTime >= lcdUpdateInterval) {
    lastLCDUpdateTime = millis();
    lcd.clear();
    switch (currentPlant) {
      case 1:
        lcd.print("Plant 1: ");
        lcd.print(porcentage1);
        lcd.print("%");
        currentPlant = 2;
        break;
      case 2:
        lcd.print("Plant 2: ");
        lcd.print(porcentage2);
        lcd.print("%");
        currentPlant = 3;
        break;
      case 3:
        lcd.print("Plant 3: ");
        lcd.print(porcentage3);
        lcd.print("%");
        currentPlant = 4;
        break;
      case 4:
        lcd.print("Plant 4: ");
        lcd.print(porcentage4);
        lcd.print("%");
        currentPlant = 1;
        break;
    }
  }*/

  // Print sensor readings
  Serial.print("Sensor 1: ");
  Serial.print(porcentage1);
  Serial.print("%\t");

  /*Serial.print("Sensor 2: ");
  Serial.print(porcentage2);
  Serial.print("%\t");

  Serial.print("Sensor 3: ");
  Serial.print(porcentage3);
  Serial.print("%\t");

  Serial.print("Sensor 4: ");
  Serial.print(porcentage4);
  Serial.print("%\n");*/

  delay(500);                         
}
