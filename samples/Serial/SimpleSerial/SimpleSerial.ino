// Simple test routine to generate random numbers and output them on the serial port
// Used to test basic comms with the receiving program
//
// Flashes an LED if some data received on the serial port

const int LED = 13;
int rnum;


void setup()
{
  pinMode(LED, OUTPUT);
  
  // This should match the baud rate of the receiver
  Serial.begin(9600);
  
  // Initialse the random number generator
  randomSeed(analogRead(7));  
}



void loop()
{

  rnum = random(1,100);
  
  Serial.println(rnum);
  
  delay(200);
  
  int innum = Serial.read();
  
   
  if (innum) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
    
  delay(2000);
  digitalWrite(LED, LOW);
}
