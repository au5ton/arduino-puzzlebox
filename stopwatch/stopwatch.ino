#define LATCH 10
#define CLOCK 8
#define DATA 6
#define ALL B11111111
#define NONE B00000000

const int digits[] = {3, 159, 37, 13, 153, 73, 65, 31, 1, 25};
const int t = 12;

void setup()
{
  Serial.begin(9600);
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(t, INPUT);

}

void loop()
{
  for (int i = 0; i < 60; i++)
  {
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, digits[i % 10]);
    shiftOut(DATA, CLOCK, LSBFIRST, digits[i / 10]);
    digitalWrite(LATCH, HIGH);
    delay(1000);
  }


}



