
Description of Arduino2DatabaseProxy
------------------------------------
This program acts as a message exchanging service between the serial port of
the Arduino and a MySQL database. The messages must be text based.

Messages send and received by the Arduino must be delimited by a start and
an end character. By default these are '#' and '%' (not visible in the database).

Messages send by the Arduino are put in the 'from_arduino' table of the 'test'
database. Messages that are put in the 'for_arduino' table of the 'test'
database will be send to the Arduino. You can edit the database and table
names.

The SQL tables are created by the query
DROP TABLE IF EXISTS table_name ; CREATE TABLE table_name (id SERIAL, message VARCHAR(255) NOT NULL, status INT DEFAULT '0',  PRIMARY KEY (id));

Description of the columns:

Field     Type            Description
-----     ------------    -------------
id        SERIAL          Auto generated: unique and increasing id
message   VARCHAR(255)    The message
status    INT             Auto generated: the read status of the message

Example of message to Arduino : "TURN_LED_ON"
Example of message to the database: "BUTTON_WAS_PRESSED"

The status field can have the values
0 : message is not read, must be processed
1 : message is being read and processing of the message is taking place.
2 : message is read, and can be deleted.

Installation
------------
Please install the setup file. It should run out-of-the-box.

Testing of this application was done using a local MySQL database.
The database was installed by using WampServer 2.5, see
 * http://www.wampserver.com/en/


If you have any problems running the program because of missing DLL's
then please install the MySQL Connector/Net libraries from here
 * http://dev.mysql.com/doc/connector-net/en/connector-net-installation-binary-windows-installer.html


