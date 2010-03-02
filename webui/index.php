<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">

<head>
<meta http-equiv="Content-Type" content="text/html;charset=utf-8" > 
<title>Indri search</title>
<link rel="stylesheet" type="text/css" href="style/style.css" title="stylesheet" />
</head>
<body>

<?php include("include/config.php"); ?>

<div id="content">
  <?php include("include/header.php"); ?>

  <form action="query.php" method="post">
    <div id="query">
     <input name="query" size="70"></input><br/>
     <input type="submit" value="Keresés"><br/>
     <br/>
     <?= $indri_param['search_text'] ?>
    </div> <!-- query -->
   </form>

  <?php include("include/footer.php"); ?>
</div> <!-- content -->

</body>
</html>

