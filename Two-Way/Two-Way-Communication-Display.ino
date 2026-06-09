// Tex Bir | MIT license | HANGMAN DISPLAY
#include <LiquidCrystal.h>

LiquidCrystal lcd(7,8,9,10,11,12);

const int sensorPin = A0;
const int laserPin = 4;
const int bitDelay = 10;

String words[] = {"CODE","BYTE","CLARK","TEX","HELLO","YIPPEE","HORSE","BALLET","NICK", "SCIENCE"};

String keyword;
String mask;
String wrongLetters = "";

//READ
bool readBit(){
  return analogRead(sensorPin) < 500;
}

byte readByte(){

  while(readBit() == 1);

  delay(bitDelay / 2);

  byte data = 0;

  for(int i=7;i>=0;i--){
    delay(bitDelay);
    if(readBit()){
      bitWrite(data,i,1);
    }
  }

  delay(bitDelay);
  bool stopBit = readBit();

  if(stopBit == 0){
    return 0;
  }

  return data;
}

//RESET SIGNAL
void sendBit(bool b){
  digitalWrite(laserPin, b);
  delay(bitDelay);
}

void sendByte(byte data){

  sendBit(0); // start

  for(int i=7;i>=0;i--){
    sendBit(bitRead(data,i));
  }

  sendBit(1); // stop
}

//GAME RESET
void resetGame(){
  keyword = words[random(0,9)];

  mask = "";
  for(int i=0;i<keyword.length();i++){
    mask += "_";
  }

  wrongLetters = "";

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(mask);

  Serial.print("WORD: ");
  Serial.println(keyword);
}

//APPLY GUESS
void applyGuess(char c){

  if(c < 'A' || c > 'Z') return;

  bool hit = false;

  for(int i=0;i<keyword.length();i++){
    if(keyword[i] == c){
      mask[i] = c;
      hit = true;
    }
  }

  if(!hit){
    if(wrongLetters.indexOf(c) == -1){
      wrongLetters += c;
    }
  }

  lcd.setCursor(0,0);
  lcd.print(mask);

  // clear leftover characters on line
  for(int i=mask.length(); i<16; i++){
    lcd.print(" ");
  }

  lcd.setCursor(0,1);

  String line = wrongLetters;

  if(line.length() > 16){
    line = line.substring(line.length()-16); // keep last 16 chars
  }

  while(line.length() < 16){
    line += " ";
  }

  lcd.print(line);
}

//CHECK WIN
bool solved(){
  return mask == keyword;
}

// SETUP
void setup(){
  lcd.begin(16,2);
  Serial.begin(9600);

  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, LOW);

  randomSeed(analogRead(A0));

  resetGame();
}

// LOOP
void loop(){

  char c = (char)readByte();
  if(c == 0) return;

  Serial.print("GUESS: ");
  Serial.println(c);

  applyGuess(c);

  if(solved()){
    delay(1000);
    lcd.clear();
    lcd.print("SOLVED!");

    Serial.println("SOLVED");

    delay(500);

    // send RESET to transmitter
    sendByte('R');
    digitalWrite(laserPin, LOW);
    delay(1000);
    resetGame();
  }
}
