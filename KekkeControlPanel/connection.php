<?php
session_start();

if(isset($_POST['server'])) {
        $_SESSION["server"] = $_POST['server'];
    }
if(isset($_POST['user'])) {
        $_SESSION["user"] = $_POST['user'];
    }
if(isset($_POST['pass'])) {
        $_SESSION["pass"] = $_POST['pass'];
    }
if(isset($_POST['data'])) {
        $_SESSION["data"] = $_POST['data'];
    }

$servername = $_SESSION["server"];
$username = $_SESSION["user"];
$dbname = $_SESSION["data"];
$password = $_SESSION["pass"];

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

$type = $_POST["type"];

if ($type == "color")
{
$value = $_POST["color"];
$sql = "INSERT INTO `for_arduino` (message)
VALUES ('$value*')";
}

if ($type == "speed")
{
$value = $_POST["speed"];
  if ($_POST["speedtype"] == "normal")
  {
    $speedtype = "10";
  }
  else if ($_POST["speedtype"] == "random")
  {
    $speedtype = "11";
  }
$sql = "INSERT INTO `for_arduino` (message)
VALUES ('$speedtype$value*')";
}

if ($type == "mode")
{
$value = $_POST["mode"];
$sql = "INSERT INTO `for_arduino` (message)
VALUES ('$value*')";
}

if ($type == "advanced")
{
$value = $_POST["command"];
$sql = "INSERT INTO `for_arduino` (message)
VALUES ('$value*')";
}


?>

  <!doctype html>
  <html>

  <head>
    <meta charset="utf-8">
    <title>Kekke Control Panel V1.4</title>
    <link rel="stylesheet" href="style.css?v=1.6">
    <link href='https://fonts.googleapis.com/css?family=Roboto:500' rel='stylesheet' type='text/css'>
    <script src="http://code.jquery.com/jquery-latest.min.js"></script>
    <script src="handler.min.js"></script>
  </head>

  <body>
    <div class="container">
      <form class="optionform">
        <fieldset>
          <legend><i>Type of command</i></legend>
          <input class="options" id="color" type="radio" name="type" value="setColor" checked> <i>Set Color</i>
          <br>
          <input class="options" id="speed" type="radio" name="type" value="setSpeed"> <i>Set Speed</i>
          <br>
          <input class="options" id="mode" type="radio" name="type" value="setMode"> <i>Set Mode</i>
          <br>
          <input class="advancedmode" id="advancedmode" type="checkbox" name="type" value=""> <i>Advanced Mode</i>
          <br>
        </fieldset>
      </form>

      <form class="colorform" action="connection.php" method="POST">
        <fieldset>
          <legend><i>Choose a color</i></legend>
          <input type="radio" name="color" value="00000"> <i>Off</i>
          <br>
          <input type="radio" name="color" value="00001" checked> <i>Red</i>
          <br>
          <input type="radio" name="color" value="00002"> <i>Green</i>
          <br>
          <input type="radio" name="color" value="00003"> <i>Blue</i>
          <br>
          <input type="radio" name="color" value="00004"> <i>Yellow</i>
          <br>
          <input type="radio" name="color" value="00005"> <i>Pink</i>
          <br>
          <input type="radio" name="color" value="00006"> <i>Purple</i>
          <br>
          <i class="submessage">only for MK2 Bracelet</i>
          <input type="radio" name="color" value="01000"> <i>RANDOM</i>
          <br>
          <input type="hidden" name="type" value="color">
          <input class="submitbutton" type="submit" name="submit" value="Send color">

        </fieldset>
      </form>

      <form class="speedform" action="connection.php" method="POST">
        <fieldset>
          <legend><i>Choose a speed</i></legend>
          <input class="speed" type="text" name="speed" value="0" size="20"> <i>(bpm)</i>
          <br>
          <input type="radio" name="speedtype" value="normal" checked> <i>normal</i>
          <br>
          <i class="submessage">only for MK2 Bracelet</i>
          <input type="radio" name="speedtype" value="random"> <i>RANDOM (max)</i>
          <br>
          <input type="hidden" name="type" value="speed">
          <br>
          <input class="submitbutton" type="submit" name="submit" value="Send Speed">
        </fieldset>
      </form>

      <form class="modeform" action="connection.php" method="POST">
        <fieldset>
          <legend><i>Choose a mode</i></legend>
          <input type="radio" name="mode" value="20100" checked> <i>Blink color</i>
          <br>
          <input type="radio" name="mode" value="20301"> <i>Preset 1</i>
          <br>
          <input type="radio" name="mode" value="20302"> <i>Preset 2</i>
          <br>
          <input type="radio" name="mode" value="20303"> <i>Preset 3</i>
          <br>
          <input type="hidden" name="type" value="mode">
          <input class="submitbutton" type="submit" name="submit" value="Send mode">
        </fieldset>
      </form>

      <fieldset class="console">
        <legend><i>Console</i></legend>
        <p>
          <?php
          if ($conn->connect_error) {
            echo ("Connection failed: " . $conn->connect_error);
            $connected = false;
          }
          else { $connected = true;}

          if ($conn->query($sql) === TRUE) {
            echo "Message sent succesfully: <br>";
            echo $sql;
          } 
          else {
            echo "Error: " . $sql . "<br>" . $conn->error;
          }
          ?>
        </p>
      </fieldset>

      <fieldset class="advanced">
        <form class="advancedform" action="connection.php" method="POST">
          <input class="command" type="text" name="command" value="" size="20"> <i>Enter command</i>
          <input type="hidden" name="type" value="advanced">
          <i class="submessage">The commands starting with 01 and 11 only work on Mk2 Bracelets and higher</i>
          <br>
          <input class="submitbutton" type="submit" name="submit" value="Send Command">
        </form>
      </fieldset>
      <a class="sublink" href="http://athena.fhict.nl/users/i344508/proftaak%20website%20festibro">Back to website</a>
      <p class="subright"><i>Kekke Control Panel V1.4 by Bram Korsten</i></p>
    </div>
    <div class="connections">
      <?php
        if ($connected == true)
        {
          echo "<div class='connected'></div>";
        }
        else {
          echo "<div class='disconnected'></div>";
          die();
        }
        ?>
    </div>
  </body>

  </html>