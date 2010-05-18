<?php include("include/config.php"); ?>
<?php include("include/synonym.php")?>
<?php //GLOBAL VARS
//print_r($_REQUEST);
global $QUERY;
//$SYNS[$word] = array(offset, array(syn->enabled))...))
global $SYNS;
global $SYNQUERY;
$QUERY = $_REQUEST['query'];
$SYNS = storeAllSyns($QUERY);
//init $SYNS
if(isset($SYNS) && isset($_REQUEST["syns"])) {
	foreach($SYNS as $word => $vale) {
		$sarray = $SYNS[$word]["syns"];
		if(isset($_REQUEST["syns"][$word])) {
			foreach($sarray as $sw => $e) {
				$SYNS[$word]["syns"][$sw] = isset($_REQUEST["syns"][$word][$sw]) ? 1 : 0;
			}
		}
	}
}

$SYNQUERY = generateSynQuery($QUERY);

function generateSynForms($syns) {
	if(!isset($syns))
		return;
	foreach($syns as $word => $vale) {
		$sarray = $syns[$word]["syns"];
		echo "<div id=\"syn\"><strong>".$word.":</strong>";
		foreach($sarray as $sw => $e) {
			echo "<input type=\"checkbox\" name=\"syns[".$word."][".$sw."]\" value=\"1\" ".($e == 1 ? "checked = \"1\"" : "")."/>".$sw." ";
		}
		echo "</div>";
	}
}
?>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">

<head>
<meta http-equiv="Content-Type" content="text/html;charset=utf-8" > 
<title>SEFH<?php
$q = $QUERY;
if(isset($q) && $q != "")
echo " - ", $q  
?></title>
<link rel="stylesheet" type="text/css" href="style/style.css" title="stylesheet" />
</head>
<body>

<div id="content">
  <?php include("include/header.php"); ?>

  <form action="index.php" method="post">
    <div id="query">
     <input name="query" size="70" value="<?= $QUERY ?>"><a href=<?= $indri_param['search_text'] ?>> </input><img alt="Indri Query Language" src="img/qm.png" height="20px"></a><br/>
     <?php generateSynForms($SYNS); ?>
     <input type="submit" value="Keresés"><br/>
     <br/>
     
    </div> <!-- query -->
   </form>

	<?php include("query.php");?>

  <?php include("include/footer.php"); ?>
</div> <!-- content -->

</body>
</html>

