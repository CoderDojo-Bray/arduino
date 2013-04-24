/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
  
  This code is the basis for the Dojo Sushi LED challenges for CoderDojo Bray
  It is just the standard "Blink" example, with some comments
  
 */
 
// Pin 13 has an LED connected on most Arduino boards, including the Arduino UNOs we favour in Bray
// 
int LED = 13;

// The setup routine runs once when you press reset, or download the sketch to the board (which also resets it)
void setup() {                
  // initialize the digital pin as an output.
  pinMode(LED, OUTPUT);     
}

// The loop routine runs over and over again forever
void loop() {
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for 1000 miliseconds == 1 second
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for 1000 miliseconds == 1 second
}
