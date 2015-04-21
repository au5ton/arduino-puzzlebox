int data = 6; 
int latch = 8; 
int clock = 10;
int answer = 0;
int start = 7;
int com15 = 3;


void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  Serial.flush();
  pinMode(data,OUTPUT);
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(start,INPUT);
  pinMode(com15,OUTPUT);

}

int Displayi(int num){
  int t [] = {
  ,37,159,3                           };
  if(num < 10){
    digitalWrite(latch, LOW);    //prepare for shift
    shiftOut(data, clock, LSBFIRST,t[num] );
    shiftOut(data, clock, LSBFIRST,t[0] );    
    digitalWrite(latch, HIGH);   //shift the bits

  }
  else if(num >= 10)
  {
    int left = num%10;
    int right = num/10;
    digitalWrite(latch, LOW);    //prepare for shift
    shiftOut(data, clock, LSBFIRST,t[left] );
    shiftOut(data, clock, LSBFIRST,t[right] );
    digitalWrite(latch, HIGH);   //shift the bits

  }
}
boolean state = false;

void loop()
{ 

    for (int i = 60; i> 0; i--)
    {
      
      //Displayi(i);
      digitalWrite(latch, LOW);    //prepare for shift
    shiftOut(data, clock, LSBFIRST,B00000000 );
    shiftOut(data, clock, LSBFIRST,B00000000 );
    digitalWrite(latch, HIGH);   //shift the bits
      delay(1000);
      
      
    }

  }






















