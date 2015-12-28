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
int presetColor = 1;
int animType = 1;
String ledState = "off";
// time functions
unsigned long previousMillis = 0;
int interval = 200;

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

    if ((String((char *)message).substring(0, 2)) == "00") { // check the contents of the recieved message for type
      if ((String((char *)message)) == "00red") // if message reads [color], set this color
      {
        setBlinkColor((String((char *)message)).substring(2, 5));
      }
    }
    else if ((String((char *)message).substring(0, 2)) == "10") // if the content is "10", set the speed
    {
      int bpm = (String((char *)message).substring(2, 5)).toInt();
      interval = 1000 / (bpm / 60);
      Serial.println(bpm);
    }
    else if ((String((char *)message).substring(0, 2)) == "20") // if the content is "20", set the animationtype
    {
      animType = ((String((char *)message).substring(2, 5)).toInt());
    }
    else {
      Serial.println("errorcode 0: Wrong format parsing!");
    }


  }

  updateTime();
}

void setBlinkColor(String color)
{
  if (color == "red")
  {
    presetColor = 1;
  }
  else if (color == "blu")
  {
    presetColor = 2;
  }
  else if (color == "gre")
  {
    presetColor = 3;
  }
  else if (color == "yel")
  {
    presetColor = 4;
  }
  else if (color == "pin")
  {
    presetColor = 5;
  }
  else if (color == "pur")
  {
    presetColor = 6;
  }
  else {
    Serial.println("errorcode 1: Undefined Color!");
  }
}

void updateTime()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    updateLed();
  }
}

void updateLed()
{
  // Turning ON the LEDS
  if (ledState == "on")
  {
    ledState == "off";
  }
  // Turning OFF the LEDS based on animtype
  else
  {
    ledState == "on";
  }
}

void softReset() // Restarts program from beginning but does not reset the peripherals and registers
{
  asm volatile ("  jmp 0");
}

