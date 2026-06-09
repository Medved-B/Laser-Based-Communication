// Tex Bir | MIT license | Solver
const int laserPin = 4;
const int sensorPin = A0;
const int bitDelay = 10;

// deterministic frequency order (classic hangman strategy, although its just random number generation rn)
const char order[] = {
  'U','T','A','O','I','N','S','H','R','D',
  'L','C','E','M','W','F','G','Y','P','B',
  'V','K','J','X','Q','Z'
};

bool used[26];
int indexPtr = 0;

// SEND
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

// RECEIVE
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

// RESET
void resetSOLVER(){
  for(int i=0;i<26;i++){
    used[i] = false;
  }

  indexPtr = 0;

}

// NEXT LETTER
char nextLetter(){

  while(indexPtr < 26){

    char c = order[indexPtr++];
    if(!used[c - 'A']){
      used[c - 'A'] = true;
      return c;
    }
  }

  // fallback (should never happen again (5/10/26))
  resetSOLVER();
  return 'E';
}

// SETUP
void setup(){
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, LOW);

  Serial.begin(9600);
}

// LOOP
void loop(){

  // watch for reset
  char incoming = (char)readByte();

  if(incoming == 'R'){
    resetSOLVER();
    delay(1000);
    return;
  }

  char guess = nextLetter();

  Serial.print("GUESS: ");
  Serial.println(guess);

  sendByte(guess);

  delay(300);
}
