// Getting raw value of soil moisture sensor to calibrate it for more accurate results
// The rawValue which is gotten through the code below is used in Code.ino

// int dryValue = 462;  // Raw value for dry soil
// int wetValue = 200;  // Raw value for wet soil

void setup(){
    Serial.begin(9600);
}

void loop(){
    int rawValue = analogRead(A0);
    Serial.println(rawValue);
    delay(1000);
}