#include <VirtualWire.h>

/*
 * Reciever module (slave)
 * Kekke FestiBracelet
 * This program recieves incoming commands using the VirtualWire Library. 
 * The code handles the request onboard, and sends the correct information to the leds.
 */

byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
// set led IO ports
int red = 7;
int green = 8;
int blue = 9;
// set default blinkspeed and color
int blinkinterval = 200;
String blinkcolor = "";

void setup() // code to run once
{
  // set the led IO ports as outputs
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(4, OUTPUT); // digital pin 4 is used to power the radio module
  digitalWrite(4, HIGH); // power digital pin 4
  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec
  vw_set_rx_pin(3); // set the reciever pin to digital pin 3
  vw_rx_start(); // Start the receiver
  Serial.begin(9600); // Start the serial monitor for debugging
  Serial.println("Slave ready!");
}
void loop() // code to run at all times
{
  if (vw_get_message(message, &messageLength)) // Non-blocking, if the reciever gets a message, run the code
  {

    Serial.print("Message Recieved: "); // this code prints out the message recieved for debugging
    for (int i = 0; i < messageLength; i++)
    {
      Serial.write(message[i]);
    }
    Serial.println();

    /*
     * The message that should be recieved is always five digits long
     * the first 2 digits are used for achieving diferent results
     *  "00" - Set Color
     *  "10" - Set Animation Speed
     *  "20" - Set Animation Type
     */
    if ((String((char *)message).substring(0,2)) == "00") { // check the contents of the recieved message for type
      
      if ((String((char *)message)) == "00red") { // if message reads [color], set this color
        digitalWrite(red, HIGH);
        digitalWrite(green, LOW);
        digitalWrite(blue, LOW);
      }
      if ((String((char *)message)) == "00gre") {
        digitalWrite(red, LOW);
        digitalWrite(green, HIGH);
        digitalWrite(blue, LOW);
      }
      if ((String((char *)message)) == "00blu") {
        digitalWrite(red, LOW);
        digitalWrite(green, LOW);
        digitalWrite(blue, HIGH);
      }
      
    }
    if ((String((char *)message).substring(0,2)) == "10") { // if the content is "10", set the speed
      /*
       * unfinished code
       * blinkinterval = (String((char *)message).substring(2,5)).toInt();
       * Serial.println(blinkinterval);
       */      
    }
  }
}

