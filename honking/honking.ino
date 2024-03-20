#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address to 0x27 for a 16 chars and 2 line display

const int buttonPin = D0;  // Pin connected to the button
unsigned long lastPressTime = 0;
int buttonState = 0;
int lastButtonState = 0;
int buttonPressCount = 0;
unsigned long totalPressedTime = 0;

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
}
