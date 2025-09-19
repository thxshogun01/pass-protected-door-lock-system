#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

// LCD with I2C Address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; // connect to R1-R4
byte colPins[COLS] = {5, 4, 3, 2}; // connect to C1-C4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

Servo lockServo;

String password = "1234";  // Set your password here
String input = "";

void setup() {
  lcd.init();
  lcd.backlight();

  lockServo.attach(10);
  lockServo.write(0); // Locked position

  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      if (input == password) {
        lcd.clear();
        lcd.print("Access Granted");
        lockServo.write(90); // Unlock
        delay(3000);
        lockServo.write(0);  // Lock
      } else {
        lcd.clear();
        lcd.print("Wrong Password");
        delay(2000);
      }
      input = "";
      lcd.clear();
      lcd.print("Enter Password:");
    }
    else if (key == '*') {
      input = ""; // Clear input on *
      lcd.setCursor(0, 1);
      lcd.print("Cleared         ");
    }
    else {
      input += key;
      lcd.setCursor(0, 1);
      lcd.print(input);
    }
  }
}