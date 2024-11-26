#include <LiquidCrystal.h>
#include <SimpleDHT.h>

// Initialize the LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Initialize the DHT sensor
int pinDHT11 = 2;               // DHT11 data pin connected to Arduino Pin 2
SimpleDHT11 dht11(pinDHT11);    // Create a SimpleDHT11 object

// Soil moisture sensor pin
const int soilMoisturePin = A0; // Connects AOUT pin of soil sensor to A0

//Calibration values for soil moisture sensor
int dryValue = 462; //Raw value for dry soil
int wetValue = 200; //Raw value for wet soil

void setup() {
  lcd.begin(16, 2); // Set up the LCD with 16 columns and 2 rows
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Variables to store temperature and humidity
  byte temperature = 0;
  byte humidity = 0;

  // Read data from the DHT11 sensor
  int err = dht11.read(&temperature, &humidity, NULL);
  if (err != SimpleDHTErrSuccess) {
    lcd.clear();
    lcd.print("Sensor Error!");
    delay(2000);
    return;
  }

  // Read raw soil moisture sensor value
  int rawValue = analogRead(soilMoisturePin);

  //Calibrates soil moisture value
  int calibratedValue = rawValue - dryValue;
  int soilPercent = (calibratedValue * 100) / (wetValue - dryValue);

  //Forces percentage to be between 0 - 100%
  if(soilPercent < 0)soilPercent = 0;
  if(soilPercent > 100)soilPercent = 100; 

  //Determines Low, Med, or High
  String soilLevel;
  if(soilPercent <= 50){
    soilLevel = "LOW";
  }else if(soilPercent > 50 && soilPercent <= 75){
    soilLevel = "MED";
  }else{
    soilLevel = "HIGH";
  }
  
  // Display humidity and soil moisture on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print((int)humidity);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Soil: ");
  lcd.print(soilPercent);
  lcd.print("% ");
  lcd.print(soilLevel);

  delay(2000); // Update every 2 seconds
}