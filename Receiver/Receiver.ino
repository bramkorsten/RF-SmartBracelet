#include <VirtualWire.h>

/*
 * Reciever module (slave)
 * RF-SmartBracelet
 * This program recieves incoming commands using the VirtualWire Library.
 * The code handles the request onboard, and sends the correct information to the leds.
 */

byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
// set led IO ports
int redLed = 9;
int greenLed = 10;
int blueLed = 11;

int resetPin = 12;
// set default blinkspeed and color
int animType = 100;
byte ledState = 0;
int presetArray = 0;
// time functions
unsigned long previousMillis = 0;
int interval = 60;
// presetcolors
int off[3] = {255, 255, 255};
int red[3] = {0, 255, 255};
int gre[3] = {0, 255, 0};
int blu[3] = {0, 0, 255};
int yel[3] = {255, 255, 0};
int pin[3] = {255, 0, 255};
int pur[3] = {128, 0, 128};
int ora[3] = {255, 165, 0};
int whi[3] = {255, 255, 255};
int *pre1[3] = {ora, pin, gre};
int *pre2[3] = {blu, pin, gre};
int *pre3[3] = {red, ora, yel};
int *presetColor = red;

void setup() // code to run once
{
  // set the led IO ports as outputs
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, HIGH); // Set the Resetpin to high
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
        //int *messageInt = message;
        //setBlinkColor(messageInt);
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

void setBlinkColor(int *color)
{
  //if (color.length() == 3)
  //{
  //  *presetColor = color;
  //}
  //else {
  //  Serial.println("errorcode 1: Wrong color format!");
  //}
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
  if (animType == 100)
  {
    // Turning OFF the LEDs
    if (ledState == 1)
    {
      analogWrite(redLed, 255);
      analogWrite(greenLed, 255);
      analogWrite(blueLed, 255);
      ledState = 0;
    }
    // Turning ON the LEDs based on animtype
    else if (ledState == 0)
    {
      analogWrite(redLed, presetColor[0]);
      analogWrite(greenLed, presetColor[1]);
      analogWrite(blueLed, presetColor[2]);
      ledState = 1;
    }
  }
  else if (animType == 200)
  {

  }
  /*else if (animType == 301)
  {
    nextPresetColor(1);
    analogWrite(redLed, presetColor[0]);
    analogWrite(greenLed, presetColor[1]);
    analogWrite(blueLed, presetColor[2]);
  }
  else if (animType == 302)
  {
    nextPresetColor(2);
    analogWrite(redLed, presetColor[0]);
    analogWrite(greenLed, presetColor[1]);
    analogWrite(blueLed, presetColor[2]);
  }
  else if (animType == 303)
  {
    nextPresetColor(3);
    analogWrite(redLed, presetColor[0]);
    analogWrite(greenLed, presetColor[1]);
    analogWrite(blueLed, presetColor[2]);
  }*/
}
/*
void nextPresetColor(int type)
{
  presetArray++;
  if (presetArray == 3)
  {
    presetArray = 0;
  }
  if (type == 1)
  {
    presetColor = pre1[presetArray];
  }
  if (type == 2)
  {
    presetColor = pre2[presetArray];
  }
  if (type == 3)
  {
    presetColor = pre3[presetArray];
  }
}
*/
void softReset() // Restarts program from beginning but does not reset the peripherals and registers
{
  asm volatile ("  jmp 0");
}

void hardReset() // Restarts the complete arduino
{
  digitalWrite(resetPin, LOW);
}

