
const int ON =  HIGH ;
const int OFF = LOW ;

int latchPin = 5;
int clockPin = 4;
int dataPin = 2;

int ledState = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
void loop() {
  int delayTime = 100 ;
  for(int i=0;i<256;i++)
  {
     updateLEDs(i);
     delay(delayTime);
  }
}
void updateLEDs(int value)
{
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, value);
  digitalWrite(latchPin,HIGH);
}

void updateLEDsLong(int value)
{
  digitalWrite(latchPin,LOW);
  for(int i=0;i<8;i++)
  {
    int bit = value&B10000000;
    value = value<<1;
    if(bit==128)
    {  
        digitalWrite(dataPin,HIGH);
    }
    else
    {  
        digitalWrite(dataPin,LOW);
    }
    digitalWrite(clockPin,HIGH);
    delay(1);
    digitalWrite(clockPin,LOW);
  }
  digitalWrite(latchPin,HIGH);
}

int bits[] = {B00000001,B00000010,B00000100,B00001000,B00010000,B00100000,
B01000000,B10000000};
int masks[] = {B11111110,B11111101,B11111011,B11110111,B11101111,B11011111,
B10111111,B01111111};
void changeLED(int led,int state)
{
  ledState = ledState & masks[led];
  if(state == ON){ ledState = ledState|bits[led]; }
  updateLEDs(ledState);
}
