/* 

  Simple serial command handler
  
  This is a sample of a basic command handler, using the SerialEvent handler
  
  It waits for a command on the serial port
  On receipt of the command, it will do something.
  
  This implements a simple protocol in the serial link: 
  
  <sync><length><cmd>
  
  Liam Friel
  CoderDojo Bray
  
*/

#define SYNCBYTE           0xFC

// 64 bytes is enough for anyone
#define MAXCOMMANDLENGTH   64

// Simple states of our protocol handler
#define WAITFORSYNC     1
#define WAITFORLENGTH   2
#define WAITFORDATA     3

// State of our command reception
boolean commandReceived = false; 
int commandBuffer[MAXCOMMANDLENGTH];
int commandBufferIndex = 0;
int commandLength = 0;

// Current state of the protocol handler
int protocolState = WAITFORSYNC;

unsigned long lastCommandTime = 0;

// Some configuration for this board
// Note that this is hardcoded
// We could improve this: we could send the configuration to the Arduino using our command handler
// And setup the inputs/outputs based on what the other computer told us to setup ...

// Trigger and Echo pins for our ultrasonics
int uSensorTrig[] = {12,11};
int uSensorEcho[] = {8,9};

// LED pins
#define NUMLEDS      3
int ledPINs[] = {5,6,7};

boolean ledOn = false;

// sends a pulse to one of our HC-SR04 sensors and returns the raw distance
long readDistanceSensor(int uSensor)
{
    long duration;
    
    digitalWrite( uSensorTrig[uSensor], LOW);
    delayMicroseconds(2);
    digitalWrite( uSensorTrig[uSensor], HIGH);
    delayMicroseconds(10);
    digitalWrite( uSensorTrig[uSensor], LOW);
    
    duration = pulseIn(uSensorEcho[uSensor], HIGH);
    
    return duration;
}

// Detects and executes the command passed
// Each command is a simple single byte, followed by a two by
// Proper complex parsers (JSON for instance) exist for Arduino, but are memory hungry
// This will do for a teeny simple demo
// Commands can be repeated in the buffer, if this makes sense
void executeCommandBuffer() {
  int nextByte = 0;
  int uSensor;
  int led;
  int ledBrightness;
  int distance;
  
  while( nextByte < commandLength ) {
      switch( commandBuffer[nextByte++] )
      {
          case 'U':
              // Ultrasonic sensor read: next byte defines the Sensor to read
              uSensor = (int)commandBuffer[nextByte++];
              
              // We only have 2 sensors in this code: this is hardcoded
              // We could improve this - we could read in our configuration ... 
              if( uSensor <= 1 ) {
                distance = readDistanceSensor(uSensor);   
                
                // TODO: improve this to have a formatted command going back
                // Should identify the sensor 
                Serial.print(distance);
                Serial.println();
              }
              else {
                // Probably we should print an error message here to the serial port
                // For now, just ignore it
              }
              break;
              
          case 'L':
              // Control a LED
              // The next byte defines the LED to control (which PIN)
              // The byte after defines the brightness of the LED from 0-255
              led = (int)commandBuffer[nextByte++];
              ledBrightness = (int)commandBuffer[nextByte++];
              
              if( led < NUMLEDS )
              {
                analogWrite(ledPINs[led], ledBrightness);
              }
              break;
              
          default:
              // Ignore a command we don't recognise
              nextByte++;
              break;
      }
  }  
}



void setup() {
  
  int i;
  
  // This serial data rate has to match the serial rate setup on the computer side
  Serial.begin(115200);
  
  // Setup the pins
  pinMode(uSensorEcho[0], INPUT);
  pinMode(uSensorEcho[1], INPUT);
  pinMode(uSensorTrig[0], OUTPUT);
  pinMode(uSensorTrig[1], OUTPUT);
  
  for( i=0; i < NUMLEDS; i++ ) {
    pinMode(ledPINs[i], OUTPUT);
  }
}

// This is our processing loop
void loop() {
  
  unsigned long now;
  now = millis();
  
  if( commandReceived) {
    
    commandReceived = false;
    
    executeCommandBuffer();
    
    lastCommandTime = now;
    
  }
  else
  {
      // Just in case ... no command received in 60 seconds ... do we want to do soemthing here?
      if( (now - lastCommandTime) > 60000 )
      {
          // Do something here on a 60 second timeout ...
          // Actually ... here we do nothing ... 
          
          lastCommandTime = now;
      }
  }
  
}


/*
   Read in the data available, and deal with it appropriately
   This is a simple command protocol reader
   
   Note that in this simple protocol the command buffer is restricted to 255 bytes long
   This is plenty for most simple purposes.
   
   It expects <sync byte><length byte><command bytes>
      
*/

void serialEvent() {
  int i;
  
  while (Serial.available()) {
    
      // get the new byte (read in as an int value)
      int inChar = Serial.read(); 
      
      switch( protocolState )
      {
          case WAITFORSYNC:
             if( (int)inChar == SYNCBYTE ) {
               protocolState = WAITFORLENGTH;
             }
             
             // Otherwise, unexpected byte, wait for sync
             break;
                     
          // If we're waiting for the length byte, then this must be it
          // Read it in
          case WAITFORLENGTH:
              commandLength = inChar;
              protocolState = WAITFORDATA;
              
              // Paranoia: zero all the data we've got already
              for(i=0; i<MAXCOMMANDLENGTH; commandBuffer[i++] = 0);
              
              break;
        
          case WAITFORDATA:
              commandBuffer[commandBufferIndex++] = inChar;
              if( commandBufferIndex == commandLength || commandBufferIndex == MAXCOMMANDLENGTH )
              {
                  protocolState      = WAITFORSYNC;
                  
                  // Note: this could be improved
                  // Here we reset the command buffer again and start waiting for a sync
                  
                  // What would happen if a new command comes in before we are done with the old command?
                  // How might you improve this code to handle that?
                  commandBufferIndex = 0;
                  commandReceived    = true;
              }
              break;
              
          default:
              break;
      }  
  }
}
