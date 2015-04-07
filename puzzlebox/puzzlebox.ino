/*
 *  By
 *  Andrew Wallace, Jose Del Villar, and Austin Jackson
 *
 *  https://github.com/au5ton/arduino-puzzlebox
 *
 */



#define DIAL_R A2
#define DIAL_G A1
#define DIAL_B A0
#define LED_R 11
#define LED_G 10
#define LED_B 9
#define IND_R_CORRECT 2
#define IND_R_INCORRECT 5
#define IND_G_CORRECT 3
#define IND_G_INCORRECT 6
#define IND_B_CORRECT 4
#define IND_B_INCORRECT 7

int guess_r = 0;
int guess_g = 0;
int guess_b = 0;
int rand_red = 0;
int rand_green = 0; 
int rand_blue = 0;

boolean correct_r = false, correct_g = false, correct_b = false;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A5));
  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  pinMode(LED_B,OUTPUT);
  
  pinMode(IND_R_CORRECT,OUTPUT);
  pinMode(IND_R_INCORRECT,OUTPUT);
  pinMode(IND_G_CORRECT,OUTPUT);
  pinMode(IND_G_INCORRECT,OUTPUT);
  pinMode(IND_B_CORRECT,OUTPUT);
  pinMode(IND_B_INCORRECT,OUTPUT);

  Serial.print("Generating a random color...");
  rand_red = random(0,255);
  rand_green = random(0,255);
  rand_blue = random(0,255);
  Serial.println("Done.");
  
  
}

void loop() {
  guess_r = analogRead(DIAL_R);
  guess_g = analogRead(DIAL_G);
  guess_b = analogRead(DIAL_B);
  
  if(floor(guess_r/10.0) == floor(rand_red/10.0)) {
    digitalWrite(IND_R_CORRECT,HIGH);
    digitalWrite(IND_R_INCORRECT,LOW);
    correct_r = true;
  }
  else {
    digitalWrite(IND_R_CORRECT,LOW);
    digitalWrite(IND_R_INCORRECT,HIGH);
    correct_r = false;
  }
  
  if(floor(guess_g/10.0) == floor(rand_green/10.0)) {
    digitalWrite(IND_G_CORRECT,HIGH);
    digitalWrite(IND_G_INCORRECT,LOW);
    correct_g = true;
  }
  else {
    digitalWrite(IND_G_CORRECT,LOW);
    digitalWrite(IND_G_INCORRECT,HIGH);
    correct_g = false;
  }
  
  if(floor(guess_b/10.0) == floor(rand_blue/10.0)) {
    digitalWrite(IND_B_CORRECT,HIGH);
    digitalWrite(IND_B_INCORRECT,LOW);
    correct_b = true;
  }
  else {
    digitalWrite(IND_B_CORRECT,LOW);
    digitalWrite(IND_B_INCORRECT,HIGH);
    correct_b = false;
  }
  
}
