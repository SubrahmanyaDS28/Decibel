#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address to 0x27 for a 16 chars and 2 line display

const int buttonPin = D0;  // Pin connected to the button
const int analogPin = A0;   // Pin connected to the analog sensor
unsigned long lastPressTime = 0;
int buttonState = 0;
int lastButtonState = 0;
int buttonPressCount = 0;
unsigned long totalPressedTime = 0;
int analogSensorCount = 0;
unsigned long aboveThresholdDuration = 0;
unsigned long lastAboveThresholdTime = 0;
const int threshold = 465;
int flag = 1;

void setup() {
  Serial.begin(9600);
 
  lcd.backlight();
  pinMode(buttonPin, INPUT);
  lcd.print("Button Count:");
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      lastPressTime = millis();
    } else {
      totalPressedTime += millis() - lastPressTime;
      buttonPressCount++;
      Serial.print("Button Pressed ");
      Serial.print(buttonPressCount);
      Serial.print(" times, Total Pressed Time: ");
      Serial.print(totalPressedTime / 1000); // Convert milliseconds to seconds
      Serial.println(" seconds");

      lcd.setCursor(0, 1);
      lcd.print("Press: ");
      lcd.print(buttonPressCount);
      lcd.print(", Time: ");
      lcd.print(totalPressedTime / 1000); // Convert milliseconds to seconds
      lcd.print("s");
    }
  }

  lastButtonState = buttonState;

  // Analog sensor reading and processing
  int sensorValue = analogRead(analogPin);
  if (sensorValue < threshold && flag =1) {
    if (analogSensorCount == 0) {
      lastAboveThresholdTime = millis();
    }
    if(flag = 1)
    {
      analogSensorCount++;
      flag =0;
    aboveThresholdDuration = millis() - lastAboveThresholdTime;
    Serial.print("Analog Sensor Count: ");
    Serial.print(analogSensorCount);
    Serial.print(", Above Threshold Duration: ");
    Serial.print(aboveThresholdDuration / 1000); // Convert milliseconds to seconds
    Serial.println(" seconds");

    lcd.setCursor(0, 2);
    lcd.print("Sensor Count: ");
    lcd.print(analogSensorCount);
    lcd.print(", Duration: ");
    lcd.print(aboveThresholdDuration / 1000); // Convert milliseconds to seconds
    lcd.print("s");
    }
    
  }
  else if(sensorValue > threshold)
  {
    flag = 1;
  }
}
