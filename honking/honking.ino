#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address to 0x27 for a 16 chars and 2 line display
int analogSensorCount = 0;  // Pin connected to the button
const int analogPin = A0;   // Pin connected to the analog sensor
const int threshold = 465;
unsigned long honk_start = 0;
unsigned long honk_dur = 0;
unsigned long total_dur = 0;



void setup() {
  Serial.begin(9600);
  lcd.backlight();
}

void loop() {
  int sensorValue = analogRead(analogPin);
  if (sensorValue < threshold) {
        honk_start = millis();
        while(sensorValue < threshold){
          sensorValue = analogRead(analogPin);
          if(sensorValue > threshold){
            analogSensorCount = analogSensorCount +1;
            honk_dur = millis() - honk_start;
            break;
          }
        }
  }
    total_dur = total_dur + honk_dur;
    lcd.setCursor(0, 2);
    lcd.print("Sensor Count: ");
    lcd.print(analogSensorCount);
    lcd.print(", Duration: ");
    lcd.print(total_dur / 1000); // Convert milliseconds to seconds
    lcd.print("s");
    } 
