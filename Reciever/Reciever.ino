#include <VirtualWire.h>

/*
SimpleReceive
This sketch displays text strings received using VirtualWire
Connect the Receiver data pin to Arduino pin 11
*/
byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message

bool ledon = false;
int red = 7;
int green = 8;
int blue = 9;

int blinkinterval = 200;
String blinkcolor = "";

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec
  vw_set_rx_pin(3);
  vw_rx_start(); // Start the receiver
  Serial.begin(9600);
  Serial.println("Reciever is ready");
}
void loop()
{
  //blinker(blinkcolor);
  if (vw_get_message(message, &messageLength)) // Non-blocking
  {

    //strcpy((char *)message, "");
    //String messagestring = String((char *)message);

    Serial.print("Message Recieved: ");
    for (int i = 0; i < messageLength; i++)
    {
      Serial.write(message[i]);
    }
    Serial.println();

    if ((String((char *)message).substring(0,2)) == "00") {
      
      if ((String((char *)message)) == "00red") {
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
    if ((String((char *)message).substring(0,2)) == "10") {
      
        blinkinterval = (String((char *)message).substring(2,5)).toInt();
        //Serial.println(blinkinterval);
        
    }
  }
}

/*void blinker(color)
{
  if (color == "red") {
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
  }
}
*/
