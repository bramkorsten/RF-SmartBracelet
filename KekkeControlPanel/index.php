<?php
session_destroy();
?>

<!doctype html>
  <html>

  <head>
    <meta charset="utf-8">
    <title>Kekke Control Panel V1.4 | login</title>
    <link rel="stylesheet" href="style.css?v=1.6">
    <link href='https://fonts.googleapis.com/css?family=Roboto:500' rel='stylesheet' type='text/css'>
    <script src="http://code.jquery.com/jquery-latest.min.js"></script>
    <script src="handler.min.js"></script>
  </head>

  <body>
    <div class="container">
      <h1 class="title">
        Kekke Control Panel
      </h1>
      <form class="loginform" action="connection.php" method="POST">
        <fieldset class="login">
          <p>
            Servername:
          </p>
          <input class="loginbar" type="text" name="server" value="" size="20">
          <br>
          <p>
            Username:
          </p>
          <input class="loginbar" type="text" name="user" value="" size="20">
          <br>
          <p>
            Password:
          </p>
          <input class="loginbar" type="password" name="pass" value="">
          <br>
          <p>
            Database:
          </p>
          <input class="loginbar" type="text" name="data" value="" size="20">
          <br>
          <input class="submitbutton loginbutton" type="submit" name="submit" value="Login">
        </fieldset>
      </form>
      
      <a class="sublink" href="http://athena.fhict.nl/users/i344508/proftaak%20website%20festibro">Back to website</a>
      <p class="subright"><i>Kekke Control Panel V1.4 by Bram Korsten</i></p>
      
    </div>
    <a class="submitbutton loginbutton paymentsbutton" href="payments.php">Payments</a>
  </body>

  </html>