  /*
 Ranging
 
 This example shows how to do (raw) ultrasonic ranging, using a HC-SR04 sensor
 
 This is an extremely simple example, which just loops, computing the raw "duration", which is a function of distance,
 and prints this on the serial port - which you can view on the serial monitor.

 The code should be used an example and the basis for computing distance in centimetres after calibration
 
 This example code is in the public domain.
 
 Liam Friel
 CoderDojo Bray
 
 */

int trigPin = 12;
int echoPin = 8;


// the setup routine runs once when you press reset:

void setup()  { 

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  // Data rate needs to match the serial port speed set on the receiving computer
  Serial.begin(115200);  
} 

// the loop routine runs over and over again forever:
void loop()  { 

  long duration;
  
    // To compute the range, you "ping" the trigger pin with a 10uSec high pulse
    // So writing low-high-log sends this "high" pulse
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // use pulseIn() to read in the returned pulse duration
  duration = pulseIn(echoPin, HIGH);  
  
  // and dump it to the serial interface
  Serial.print(duration);
  Serial.println();
  
  // and do this forever, 10 times per second
  delay(100);
}

