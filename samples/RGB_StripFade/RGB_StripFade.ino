  /*
 Fade
 
 This example shows how to colour cycle an RGB LED strip
 
 This example code is in the public domain.
 
 Liam Friel
 CoderDojo Bray
 */

// PWM pins used to drive the colours
// Assumes that there are actually transistors connected to these PWM pins to drive the strip
int RGB[] = { 3,5,6};


// the setup routine runs once when you press reset:

void setup()  { 

  // Set all the PWM pins to be outputs
  int i;
  for( i-0; i<3; i++)
  {  
    pinMode(RGB[i], OUTPUT);
  }
  
  // Initialise the PWM outputs to zero
  analogWrite(RGB[0], 0);
  analogWrite(RGB[1], 0);
  analogWrite(RGB[2], 0);
  
} 

// the loop routine runs over and over again forever:
void loop()  { 

  int r,g,b;
  int fadeDirection = 1;
  
  // Fade in RED  
  doFade(RGB[0], 0, 255);
  delay(1000);
  
  // Fade out RED again
  doFade(RGB[0], 255, 0);
  delay(1000);
  
  // ... and various other colour fade tricks ... 
  doFade(RGB[1], 0, 255);
  delay(1000);
  doFade(RGB[1], 255, 0);
  delay(1000);

  doFade(RGB[2], 0, 255);
  delay(1000);
  doFade(RGB[2], 255, 0);
  delay(1000);

  doFade(RGB[0], 0, 255);
  delay(1000);
  doFade(RGB[1], 0, 255);
  delay(1000);
  doFade(RGB[2], 0, 255);
  delay(1000);
  
  doFade(RGB[1], 255, 0);
  delay(1000);
}

// Fades the LED from startCol to endCol
// Makes sure to "fade" in the correct direction!
void doFade(int LED, int startCol, int endCol)
{
  int i;
  int fadeDir = 1;
  
  if( startCol < endCol ) fadeDir = -1;
  for( i=startCol; i != endCol; i += fadeDir)
  {
    analogWrite(LED, i);
    delay(20);
  }
}
