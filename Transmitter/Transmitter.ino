/*
SimpleSend
This sketch transmits a short text message using the VirtualWire library
connect the Transmitter data pin to Arduino pin 12
*/

int buttonr = 2;
int buttong = 3;
int buttonb = 4;
int potentio1 = 1;
String blinkspeedmap;

char red[5] = {'0','0','r','e','d'};
char green[5] = {'0','0','g','r','e'};
char blue[5] = {'0','0','b','l','u'};
char blinkspeed[5] = {'1','0','0','0','0'};
char hello[5] = {'h','e','l','l','o'};

#include <VirtualWire.h>

void setup()
{
  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec
  Serial.begin(9600);
  Serial.println("Transmitter started succesfully!");
}
void loop()
{
  
  if (digitalRead(buttonr) == HIGH) {
    vw_send((uint8_t *)red, 5);
    vw_wait_tx(); // Wait until the whole message is gone
    Serial.println("Message Sent!");
    delay(500);
    sendblinkspeed();
    //delay(100);
  }
  /*if (digitalRead(buttong) == HIGH) {
    send("00gre");
    delay(200);
  }
  if (digitalRead(buttonb) == HIGH) {
    send("00blu");
    delay(200);
  }
  */
}
      /*void send (char *message)
      {
        vw_send((uint8_t *)message, strlen(message));
        
      }
      */
void sendblinkspeed()
{
  blinkspeedmap = String(map( analogRead(potentio1), 0, 1024, 100, 999) + 10000);
  //blinkspeed[2] = (char)blinkspeedmap.substring(0,1).toInt();
  //blinkspeed[3] = (char)blinkspeedmap.substring(1,2).toInt();
  //blinkspeed[4] = (char)blinkspeedmap.substring(2).toInt();
  
  blinkspeedmap.toCharArray(blinkspeed,6);
  
  Serial.println(blinkspeedmap);
  Serial.println(blinkspeed);
    //for (int i = 0; i < 5; i = i + 1) {
    //  Serial.println(String(blinkspeed[i]));
    //}
  vw_send((uint8_t *)blinkspeed, 5);
  vw_wait_tx(); // Wait until the whole message is gone
  
  
}

