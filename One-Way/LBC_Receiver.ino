#include <LiquidCrystal.h>

LiquidCrystal lcd(7,8,9,10,11,12);

const int sensorPin = A0;
const int threshold = 400;
const int bitDelay = 150;

String message = "";
bool receiving = false;

bool readBit() {
  int val = analogRead(sensorPin);
  return val < threshold;   // laser detected
}

byte readByte() {

  // wait for START bit
  while(readBit() == 1);

  delay(bitDelay); // move to middle of first data bit

  byte result = 0;

  for(int i = 7; i >= 0; i--){
    bool bitVal = readBit();
    bitWrite(result, i, bitVal);
    delay(bitDelay);
  }

  // read STOP bit
  readBit();
  delay(bitDelay);

  return result;
}

void setup() {
  lcd.begin(16,2);
  lcd.print("Receiving...");
  Serial.begin(9600);
}

void loop() {

  char c = (char)readByte();

  if(c == '$'){ // CHECKS FOR $ TO START READING THE MESSAGE
    message = "";
    receiving = true;
    return;
  }

  if(c == '#' && receiving){
    lcd.clear();
    lcd.print("Message:");
    lcd.setCursor(0,1);
    lcd.print(message);

    Serial.println(message);

    receiving = false;
    return;
  }

  if(receiving){
    message += c;
  }
}
