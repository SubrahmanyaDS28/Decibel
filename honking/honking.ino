#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int button_pin = 6;
unsigned long buttonPressedAt = 0;
unsigned long buttonReleasedAt = 0;
unsigned long duration = 0;
unsigned long cumulativeTime = 0;
bool buttonState = HIGH; 
unsigned long pressCount = 0;

void setup() {
  lcd.begin(16, 2);
  pinMode(button_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int state = digitalRead(button_pin);

  if (state == HIGH && buttonState == LOW) {
    buttonPressedAt = millis();
    buttonState = HIGH; 
  } else if (state == LOW && buttonState == HIGH) {
    buttonReleasedAt = millis();
    duration = buttonReleasedAt - buttonPressedAt;
    cumulativeTime += duration;
    buttonState = LOW; 
    Serial.print(cumulativeTime);
    Serial.println(" ms");
    pressCount++;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Honking: ");
    lcd.print(pressCount/2);
    delay(100);
    lcd.setCursor(0, 1);
    lcd.print("cum_dur: ");
    lcd.print(cumulativeTime/1000);
  }
}
