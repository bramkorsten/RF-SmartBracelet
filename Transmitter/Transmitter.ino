#include <VirtualWire.h>

/*
 * Transmitter module (master)
 * Kekke FestiBracelet
 * This program Transmits commands recieved trough serial using the VirtualWire Library. 
 * The code handles the request onboard, and sends the correct commands by radio to all available slaves.
 */

// debugbuttons used for sending commands, this will be replaced by serial requests ASAP
int buttonr = 2;
int buttong = 3;
int buttonb = 4;
int potentio1 = 1;
String blinkspeedmap;
// The messages that can be send, using char arrays, which are converted to bytes by the VirtualWire Library
char red[5] = {'0','0','r','e','d'};
char green[5] = {'0','0','g','r','e'};
char blue[5] = {'0','0','b','l','u'};
char blinkspeed[5] = {'1','0','0','0','0'};
char hello[5] = {'h','e','l','l','o'};



void setup()
{
  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec
  Serial.begin(9600); // Start the serial monitor for debugging purposes
  Serial.println("Master started succesfully!");
}
void loop()
{
  
  if (digitalRead(buttonr) == HIGH) {
    vw_send((uint8_t *)red, 5); // use the VirtualWire command to send the char array variables to the slaves
    vw_wait_tx(); // Wait until the whole message is gone
    Serial.println("Message Sent!");
    delay(500);
    sendblinkspeed(); // set a new blinkspeed based on potentiometer data
  }
}

void sendblinkspeed()
{
  blinkspeedmap = String(map( analogRead(potentio1), 0, 1024, 100, 999) + 10000); // set a string containing a value between 10000 and 10999 based on the value of the potentiometer
  blinkspeedmap.toCharArray(blinkspeed,6); // convert the created string to a char array
  Serial.println(blinkspeedmap);// debug
  Serial.println(blinkspeed); // debug
  vw_send((uint8_t *)blinkspeed, 5); // send the new array
  vw_wait_tx(); // Wait until the whole message is gone
}

