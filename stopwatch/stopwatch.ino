/*
 *
 * Stopwatch
 *
 * Austin Jackson, Jose Del Villar, Andrew Wallace
 *
 */

#define LATCH 10
#define CLOCK 8
#define DATA 6
#define BRIDGE_OUT 12
#define BRIDGE_IN 7
#define BUZZER 13

const int digits[] = {3, 159, 37, 13, 153, 73, 65, 31, 1, 25};
const int t = 12;

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
  pinMode(t, INPUT);
  digitalWrite(BRIDGE_OUT,LOW);
  digitalWrite(BUZZER,LOW);
}

void loop(){
  for (int i = 60; i > 0; i--)
  {
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, digits[i % 10]);
    shiftOut(DATA, CLOCK, LSBFIRST, digits[i / 10]);
    digitalWrite(LATCH, HIGH);
    if(digitalRead(BRIDGE_IN) == HIGH) {
      gameWon = true;
      break;
    }
    delay(1000);
  }
  //Game over
  if(gameWon == false){
    digitalWrite(BRIDGE_OUT, HIGH);
    digitalWrite(BUZZER,HIGH);
  }
  while(true){
    //wait for gameState to change from "win" to "lose"
  }
}



