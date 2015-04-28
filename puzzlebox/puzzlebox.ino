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
#define BRIDGE_OUT 12 //Used to send data to the stopwatch
#define BRIDGE_IN 8 //Used to receive data from stopwatch

int guess_r = 0; //Your guess of the R value
int guess_g = 0; //Your guess of the G value
int guess_b = 0; //Your guess of the B value
int rand_red = 0; //The randomly generated R value you're trying to find
int rand_green = 0; //The randomly generated G value you're trying to find
int rand_blue = 0; //The randomly generated B value you're trying to find

boolean super_impossible_mode = false;

boolean correct_r = false, correct_g = false, correct_b = false;

//DO NOT SET AS 0, IT WILL DIVIDE BY 0 AND THATS BAD
double tolerance = 32.0;
/*
TOLERANCE DIFFICULTIES

1.0 is impossible mode
2.0 is expert mode
4.0 is hard mode
8.0 is medium mode
16.0 is easy mode
32.0 is beginner mode

*/

void setup() {
  Serial.begin(9600); //Needed to use the Serial monitor
  randomSeed(analogRead(A5)); //Needed for random numbers
  pinMode(LED_R, OUTPUT); //Setup the pins for input/output
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  pinMode(IND_R_CORRECT, OUTPUT);
  pinMode(IND_R_INCORRECT, OUTPUT);
  pinMode(IND_G_CORRECT, OUTPUT);
  pinMode(IND_G_INCORRECT, OUTPUT);
  pinMode(IND_B_CORRECT, OUTPUT);
  pinMode(IND_B_INCORRECT, OUTPUT);
  
  pinMode(BRIDGE_OUT, OUTPUT);
  pinMode(BRIDGE_IN, INPUT);
  digitalWrite(BRIDGE_OUT,LOW); //Writes low to the other Arduino so it doesn't think that the game is over yet

  Serial.print("Generating a random color...");
  if (super_impossible_mode == true) {
    //Generates a more difficult random "color"
    rand_red = random(0, 1023);
    rand_green = random(0, 1023);
    rand_blue = random(0, 1023);
  }
  else {
    //Generates the random color
    rand_red = random(0, 255);
    rand_green = random(0, 255);
    rand_blue = random(0, 255);
  }
  Serial.println("Done.\n\n");


}

void loop() {
  
  //Saves the data from the Dials into variables
  guess_r = analogRead(DIAL_R);
  guess_g = analogRead(DIAL_G);
  guess_b = analogRead(DIAL_B);

  //SHOWS TO THE RGB LED
  //SHOWS TO THE RGB LED
  //SHOWS TO THE RGB LED
  //Writes the color you're guessing to the RGB LED, so you can see your guess
  //Divides by 4.0 so that 1024 (dial reading) can fit into 256 (random color)
  analogWrite(LED_R, (int)floor((double)guess_r / 4.0));
  analogWrite(LED_G, (int)floor((double)guess_g / 4.0));
  analogWrite(LED_B, (int)floor((double)guess_b / 4.0));
  
  //(WHEN YOU LOSE)
  //When the timer times out it sends a signal
  //If the signal is received, ...
  if(digitalRead(BRIDGE_IN) == HIGH) {
    // ... then turn all the Indicators to RED
    digitalWrite(IND_R_INCORRECT,HIGH);
    digitalWrite(IND_R_CORRECT,LOW);
    digitalWrite(IND_G_INCORRECT,HIGH);
    digitalWrite(IND_G_CORRECT,LOW);
    digitalWrite(IND_B_INCORRECT,HIGH);
    digitalWrite(IND_B_CORRECT,LOW);
    
    //Changes the random color to something that's un-guessable
    rand_red = -10;
    rand_green = -10;
    rand_blue = -10;
    
    //Infinite loop that waits for you to reset the Arduino
    while(true){
      //wait for reset
      Serial.println("puzzlebox done...");
      digitalWrite(BRIDGE_OUT,LOW);
    }
    
  }
  
  //If you've guessed all of them correctly, send a signal to the timer to stop
  if(correct_r == true && correct_g == true && correct_b == true) {
    digitalWrite(BRIDGE_OUT,HIGH);
  }

  if (super_impossible_mode == true) {
    Serial.print("r: ");
    Serial.print(guess_r);
    Serial.print(" g: ");
    Serial.print(guess_g);
    Serial.print(" b: ");
    Serial.print(guess_b);
    Serial.print("    rr: ");
    Serial.print(rand_red);
    Serial.print(" rg: ");
    Serial.print(rand_green);
    Serial.print(" rb: ");
    Serial.print(rand_blue);

    //If your guess is correct
    if (guess_r == rand_red) {
      //Turn on the indicators and set the variable to true
      digitalWrite(IND_R_CORRECT, HIGH);
      digitalWrite(IND_R_INCORRECT, LOW);
      correct_r = true;
    } //Otherwise..
    else {
      digitalWrite(IND_R_CORRECT, LOW);
      digitalWrite(IND_R_INCORRECT, HIGH);
      correct_r = false;
    }

    if (guess_g == rand_green) {
      digitalWrite(IND_G_CORRECT, HIGH);
      digitalWrite(IND_G_INCORRECT, LOW);
      correct_g = true;
    }
    else {
      digitalWrite(IND_G_CORRECT, LOW);
      digitalWrite(IND_G_INCORRECT, HIGH);
      correct_g = false;
    }

    if (guess_b == rand_blue) {
      digitalWrite(IND_B_CORRECT, HIGH);
      digitalWrite(IND_B_INCORRECT, LOW);
      correct_b = true;
    }
    else {
      digitalWrite(IND_B_CORRECT, LOW);
      digitalWrite(IND_B_INCORRECT, HIGH);
      correct_b = false;
    }
  }
  else {
    Serial.print("r: ");
    Serial.print(floor(floor((double)guess_r / 4.0) / tolerance));
    Serial.print(" g: ");
    Serial.print(floor(floor((double)guess_g / 4.0) / tolerance));
    Serial.print(" b: ");
    Serial.print(floor(floor((double)guess_b / 4.0) / tolerance));
    Serial.print("    rr: ");
    Serial.print(floor(rand_red / tolerance));
    Serial.print(" rg: ");
    Serial.print(floor(rand_green / tolerance));
    Serial.print(" rb: ");
    Serial.println(floor(rand_blue / tolerance));

    //If the guess is the same as the random number
    //IN THE MATH:
    //Proportionally scales from 0/1024 form to 0/256 form, by dividing by 4.0
    //Divides by the `tolerance` value and uses floor() to make an adjustable tolerance setting
    if (floor(floor((double)guess_r / 4.0) / tolerance) == floor(rand_red / tolerance)) {
      //Mark the guess as correct
      digitalWrite(IND_R_CORRECT, HIGH);
      digitalWrite(IND_R_INCORRECT, LOW);
      correct_r = true;
    }
    else {
      digitalWrite(IND_R_CORRECT, LOW);
      digitalWrite(IND_R_INCORRECT, HIGH);
      correct_r = false;
    }

    if (floor(floor((double)guess_g / 4.0) / tolerance) == floor(rand_green / tolerance)) {
      digitalWrite(IND_G_CORRECT, HIGH);
      digitalWrite(IND_G_INCORRECT, LOW);
      correct_g = true;
    }
    else {
      digitalWrite(IND_G_CORRECT, LOW);
      digitalWrite(IND_G_INCORRECT, HIGH);
      correct_g = false;
    }

    if (floor(floor((double)guess_b / 4.0) / tolerance) == floor(rand_blue / tolerance)) {
      digitalWrite(IND_B_CORRECT, HIGH);
      digitalWrite(IND_B_INCORRECT, LOW);
      correct_b = true;
    }
    else {
      digitalWrite(IND_B_CORRECT, LOW);
      digitalWrite(IND_B_INCORRECT, HIGH);
      correct_b = false;
    }
  }

}
