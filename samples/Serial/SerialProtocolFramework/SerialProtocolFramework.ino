/* 

  Simple serial command handler "framework"
  It doesn't actually do anything, but you could use it as a framework to build a command-driven Arduino
  
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


// Detects and executes the command passed
// Each command is a simple single byte, followed by a two by
// Proper complex parsers (JSON for instance) exist for Arduino, but are memory hungry
// This will do for a teeny simple demo
// Commands can be repeated in the buffer, if this makes sense
void executeCommandBuffer() {
  int nextByte = 0;
  
  while( nextByte < commandLength ) {
      switch( commandBuffer[nextByte++] )
      {
          case 'U':
              // Do something when you detect the command 'U'
              break;
              
          case 'L':
              // Do something when you detect the command 'L'
              break;
              
          default:
              // Ignore a command we don't recognise
              nextByte++;
              break;
      }
  }  
}



void setup() {
  
  // This serial data rate has to match the serial rate setup on the computer side
  Serial.begin(115200);
  
  // Here you could setup any hardware (pins, etc) that you need
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
