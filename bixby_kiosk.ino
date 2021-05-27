#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int bc1 = 0; // button counter 1 
int bc2 = 0; // button counter 2

const int b1 = 2; // button 1
const int b2 = 3; // button 2
const int b3 = 4; // button 3

int state1 = LOW;
int laststate1 = LOW;
int state2 = LOW;
int laststate2 = LOW;
int state3 = LOW;
int laststate3 = LOW;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  lcdSetup();
          
  pinMode(b3, INPUT);
  pinMode(b1, INPUT);
  //attachInterrupt(digitalPinToInterrupt(b1), bc1up, FALLING);
  pinMode(b2, INPUT);
  //attachInterrupt(digitalPinToInterrupt(b2), bc2up, FALLING);
}

void loop() { 
  state1 = digitalRead(b1);
  state2 = digitalRead(b2);
  state3 = digitalRead(b3);
  
  if (state1 != laststate1) {
    if (state1 == LOW) {
      bc1up();
      delay(10);
    }
  }
  if (state2 != laststate2) {
    if (state2 == LOW) {
      bc2up();
      delay(10);
    }
  }
  if (state3 != laststate3) {
    if (state3 == LOW) {
      printLCD();
      delay(10);
    }
  }
  
  Serial.print(digitalRead(b1));
  Serial.print(state2);
  Serial.println(state3);

  laststate1 = state1;
  laststate2 = state2;
  laststate3 = state3;
  delay(1000);
}

void lcdSetup()
{
  Serial.println("\nCoogether Kiosk");
  lcd.init();
  lcd.backlight();
  lcd.print("electronic");
  lcd.setCursor(8,1);
  lcd.print("scale");
  delay(1000);
  lcd.clear();
  lcd.print("Coogether Kiosk");
}

void bc1up()
{
  if(state1 == false)
  {
    bc1 = (bc1 % 3) + 1;
    state1 = true;
    Serial.print("bc1 = ");
    Serial.println(bc1);
  }
  else
  {
    bc1 = (bc1 % 3) + 1;
    state1 = false;
    Serial.print("bc1 = ");
    Serial.println(bc1);
  }
}

void bc2up()
{
  if(state2 == false)
  {
    bc2 = (bc2 % 3) + 1;
    state2 = true;
    Serial.print("bc2 = ");
    Serial.println(bc2);
  }
  else
  {
    bc2 = (bc2 % 3) + 1;
    state2 = false;
    Serial.print("bc2 = ");
    Serial.println(bc2);
  }
}

void printLCD()
{
  Serial.println("clear");
  lcd.clear();
  lcd.print("bc1 = ");
  lcd.print(bc1);
  lcd.setCursor(0,1);
  lcd.print("bc2 = ");
  lcd.print(bc2);
}
