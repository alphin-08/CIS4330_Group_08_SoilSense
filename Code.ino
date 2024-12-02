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


unsigned long previousMillis = 0;
const long interval = 4000; //4 seconds for switching screens
bool showActionScreen = false;


void clearLine(int line) {
  lcd.setCursor(0, line);
  lcd.print("                "); // Clear the entire line
}

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
  bool sensorError = false;
  int err = dht11.read(&temperature, &humidity, NULL);
  if (err != SimpleDHTErrSuccess) {
    sensorError = true;
    humidity = 0;
  }

  // Read raw soil moisture sensor value
  int rawValue = analogRead(soilMoisturePin);
  int soilPercent = constrain((rawValue - dryValue) * 100 / (wetValue - dryValue), 0, 100);
  String soilLevel = (soilPercent <= 50) ? "LOW" : (soilPercent <= 75) ? "MED" : "HIGH";

  // Determine action message
  String actionMessage = "N/A";
  if (!sensorError) {
    if (soilLevel == "LOW" && humidity >= 30 && humidity <= 60) {
      actionMessage = "Water Now";
    } else if (soilLevel == "MED" && humidity >= 30 && humidity <= 60) {
      actionMessage = "Water & Air OK";
    } else if (soilLevel == "HIGH" && humidity >= 30 && humidity <= 60) {
      actionMessage = "Don't Water";
    } else if (soilLevel == "LOW" && (humidity < 30 || humidity > 60)) {
      actionMessage = "Water & Move";
    } else if (soilLevel == "MED" && (humidity < 30 || humidity > 60)) {
      actionMessage = "Move Plant";
    } else if (soilLevel == "HIGH" && (humidity < 30 || humidity > 60)) {
      actionMessage = "Don't Water&Move";
    }
  }
  

  // Alternate screens
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    showActionScreen = !showActionScreen;
  }
  

  // Display appropriate screen
  if (showActionScreen) {
    clearLine(0);
    clearLine(1);
    lcd.setCursor(0, 0);
    lcd.print("Action:");
    lcd.setCursor(0, 1);
    lcd.print(sensorError ? "Error!" : actionMessage);
  } else {
    clearLine(0);
    clearLine(1);
    lcd.setCursor(0, 0);
    lcd.print("Hum: ");
    lcd.print(sensorError ? "Error!" : String(humidity) + "%");
    lcd.print(sensorError ? "" : (humidity >= 30 && humidity <= 60 ? " Safe" : " Unsafe"));
    lcd.setCursor(0, 1);
    lcd.print("Soil: ");
    lcd.print(String(soilPercent) + "% " + soilLevel);
  }
}