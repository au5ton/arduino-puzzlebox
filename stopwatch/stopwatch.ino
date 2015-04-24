/*
 *  By
 *  Andrew Wallace, Jose Del Villar, and Austin Jackson
 *
 *  https://github.com/au5ton/arduino-puzzlebox
 *
 */

#define LATCH 10
#define CLOCK 8
#define DATA 6
#define BRIDGE_OUT 12
#define BRIDGE_IN 7
#define BUZZER 3

//These let us display Englsih alphabet looking numbers to the 7-segment display
//
const int digits[] = {3, 159, 37, 13, 153, 73, 65, 31, 1, 25};

void displayNumber(int i) {
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, digits[i % 10]);
  shiftOut(DATA, CLOCK, LSBFIRST, digits[i / 10]);
  digitalWrite(LATCH, HIGH);
}

boolean gameWon = false;



void setup(){
  Serial.begin(9600);
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(BRIDGE_OUT, OUTPUT);
  pinMode(BUZZER,OUTPUT);
  pinMode(BRIDGE_IN, INPUT);
  digitalWrite(BRIDGE_OUT,LOW);
  analogWrite(BUZZER,0);
}

void loop(){
  for (int i = 60; i >= 0; i--)
  {
    //Shows the countdown to the display
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, digits[i % 10]);
    shiftOut(DATA, CLOCK, LSBFIRST, digits[i / 10]);
    digitalWrite(LATCH, HIGH);
    //If the signal from the puzzle is received, that means the game has been won
    if(digitalRead(BRIDGE_IN) == HIGH) {
      gameWon = true;
      break;
    }
    Serial.println("1 SECOND");
    delay(1000);
  }
  //If your time runs out, the code below will run
  
  //Game over
  if(gameWon == false){
    //
    digitalWrite(BRIDGE_OUT, HIGH);
    analogWrite(BUZZER,255);
  }
  while(true){
    //wait for gameState to change from "win" to "lose"
    digitalWrite(BRIDGE_OUT,LOW);
    Serial.println("stopwatch done...");
  }
}



