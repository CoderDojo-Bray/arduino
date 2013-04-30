/* Blink without Delay
 
 Turns on and off a light emitting diode(LED) connected to a digital  
 pin, without using the delay() function.  This means that other code
 can run at the same time without being interrupted by the LED code.
 
 This is useful when you want to write more complex Arduino programs which need to
 do other things as well as just control the LED
 
 The circuit:
 
 * LED attached from pin 13 to ground.
 * Note: on most Arduinos, there is already an LED on the board
   that's attached to pin 13, so no hardware is needed for this example.
 
 
 created 2005
 by David A. Mellis
 modified 8 Feb 2010
 by Paul Stoffregen
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay

 */

// Constants won't change. Used here to set pin numbers:
const int ledPin =  13;      // The pin your LED is connected to

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated

// the following variable is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 1000;           // interval at which to blink (milliseconds)
                                // 1000 milliseconds == 1 second

// Your setup() function runs once                              
void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);      
}

// Your loop() function runs forever
void loop()
{
  // here is where you'd put code that needs to be running all the time.
  // Note that there is no delay() function in this loop ... 

  // check to see if it's time to blink the LED; that is, if the 
  // difference between the current time and last time you blinked 
  // the LED is bigger than the interval at which you want to 
  // blink the LED.
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    }
    else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
}

