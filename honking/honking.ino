#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int button_pin = 0;
int pressCount = 0;
unsigned long lastPressDuration = 0;
unsigned long buttonPressedAt = 0;
unsigned long a = 0;
void setup() {
  lcd.begin(16, 2);
  pinMode(button_pin, INPUT);
}

void loop() {
  int state = digitalRead(button_pin);
  
  static int prevState = LOW;
  static unsigned long prevPressTime = 0;
  
  if (state == HIGH && prevState == LOW) {
    // Button was pressed
    buttonPressedAt = millis();
    prevPressTime = buttonPressedAt;
  } else if (state == LOW && prevState == HIGH) {
    // Button was released
    lastPressDuration = millis() - buttonPressedAt;
    if (lastPressDuration > 50 && lastPressDuration < 3000) { // Valid press duration
      pressCount++;
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("No.of Honks: ");
      lcd.print(pressCount);
      lcd.setCursor(0, 0);
      lcd.print("Duration: ");
      lcd.print(a);
      delay(100);
      
    a = a + lastPressDuration;
    }
  }
  
  prevState = state;
}