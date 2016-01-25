# RF-SmartBracelet
This Repository contains the code for both the Transmitter module as the Reciever module for a school project using multiple arduino's,
433MHz RF radio module transmitter and recievers and RFID reader and scanner modules.

## The Bracelet
The bracelet contains an Arduino Nano, the radio reviever module,LEDs, rechargable batteries and the RFID tag module. The bracelet is a prototype to be used at a festival. Payments can be made using the build in RFID tag, and a light show can be played on every bracelet at a festival trough the radio modules.

## The Transmitter
The transmitter contains an Arduino Uno, the radio transmitter module and some buttons. The module will be used in combination with a pc, and unique color and speed combinations will be written as serial data from the pc to the transmitter, which will send the data as bytes to the bracelet.

# SETUP
To setup a demonstration, install a localhost based server like XAMPP and place the KekkeControl files in the website partition of this server. Visit PHPmyadmin on this server and create a new database. Make sure you write down the passwords, names etc so you dont forget it. You don't have to create tables, because ArduinoToDatabase will take care of this step. To setup for the demonstration, run the executable in ArduinoToDatabase and fill in the information about the database connection on the right. Search the arduino COM port and click connect. You should see connected to database appear in the console. Next login with the database credentials in the controlpanel, and you should be good to go!
