#include <LiquidCrystal.h>
#include <SimpleDHT.h>

// Initialize the LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Initialize the DHT sensor
int pinDHT11 = 2;               // DHT11 data pin connected to Arduino Pin 2
SimpleDHT11 dht11(pinDHT11);    // Create a SimpleDHT11 object

// Soil moisture sensor pin
const int soilMoisturePin = A0; // Connect AOUT pin of soil sensor to A0

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

  // Read soil moisture sensor value
  int soilValue = analogRead(soilMoisturePin); // Get raw analog value (0-1023)
  int soilPercent = map(soilValue, 1023, 0, 0, 100); // Map to percentage (dry to wet)

  String soilLevel;
  if(soilPercent <= 50){
    soilLevel = "LOW";
  }else if(soilPercent <= 75){
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