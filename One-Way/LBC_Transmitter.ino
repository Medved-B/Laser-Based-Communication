const int laserPin = 9;
const int bitDelay = 150;
const char *message = "Hello"; // CHANGE YOUR MESSAGE HERE

void sendBit(bool bitVal){ // SETS LASER TO ON OR OFF DEPENDING ON VALUE OF BIT 1 OR 0
  digitalWrite(laserPin, bitVal ? HIGH : LOW);
  delay(bitDelay);
}

void sendByte(byte data){ // SENDS EACH BYTE

  sendBit(0); // START BIT

  for(int i=7;i>=0;i--){
    sendBit(bitRead(data,i));
  }

  sendBit(1); // STOP BIT
}

void sendMessage(const char *msg){ 

  sendByte('$');  // start marker

  while(*msg){
    sendByte(*msg++);
  }

  sendByte('#');  // end marker
}

void setup(){ // SETUP
  pinMode(laserPin,OUTPUT);
  digitalWrite(laserPin,LOW);
}

void loop(){
  sendMessage(message); // SENDS THE MESSAGE

  digitalWrite(laserPin,LOW); // TURNS THE LASER OFF
  analogWrite(A1, 255); // TURNS ON THE LED TO SHOW THE MESSAGE IS COMPLETED

  while(true){}
}
