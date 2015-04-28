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

//These let us display English alphabet looking numbers to the 7-segment display
//
const int digits[] = {3, 159, 37, 13, 153, 73, 65, 31, 1, 25};
boolean gameWon = false;
const int timerLength = 60; //Maximum of 99
const int secondLength = 1000;


void setup(){
  //Basic setup
  Serial.begin(9600);
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(BRIDGE_OUT, OUTPUT);
  pinMode(BUZZER,OUTPUT);
  pinMode(BRIDGE_IN, INPUT);
  digitalWrite(BRIDGE_OUT,LOW); //Writes low to the other Arduino so it doesn't think that the game is over yet
}

void loop(){
  for (int i = timerLength; i >= 0; i--)
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
    delay(secondLength);
  }
  //If your timer runs out, or the for-loop is broken, the code below will run
  
  //Game over
  if(gameWon == false){
    //Tell the other Arduino that you lost
    digitalWrite(BRIDGE_OUT, HIGH);
    //Make a buzzing sound
    tone(BUZZER,1800,1000); //Buzz on `BUZZER` at 2000Hz in pitch for 1000ms
  }
  else {
    //Beeps twice when you win
    tone(BUZZER,2200);
    delay(500);
    tone(BUZZER,0);
    delay(25);
    tone(BUZZER,2200,500);
  }
  //Infinite loop once the game is over, for winning AND losing
  while(true){
    digitalWrite(BRIDGE_OUT,LOW);
    Serial.println("stopwatch done...");
  }
}



