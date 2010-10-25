<?php include("include/libindri.php") ?>

<?php 
function debug($i) {
	//echo date("G:i s");
	//echo " -",$i ," ",memory_get_usage(),"<br>";
}

	$queryRunner = "/home/mee/workspaces/sefh/sefh/indri/simplequery/runSimpleQuery";
	$indexPath = "/home/mee/workspaces/sefh/sefh/testingData/indeces/testIndex";
	$resNo = "10";
   	
   $query = indri_cleanquery( $SYNQUERY );
   if(!isset($query) || $query == "")
   {
   	return;
   }

   // run the query
   	$command = $queryRunner." ".$indexPath." ".$query." ".$resNo;
	$resultArray;
	$retVal;
	$result = "";
   	exec($command,$resultArray,$retVal);
   	foreach ($resultArray as $line) {
   		$result .= $line;
   	}
   	$xml = new SimpleXMLElement($result);
   	
   if( $xml->type == "ok" ) {
	$xmlres = $xml->data;
   } else {
     include( "include/error.php" );
     return;
   }
?>

<div id="results">
  
  <div id="results">
  <?php
  if($xmlres->children()->count() == 0)
  {
  	echo "<center><h2>Nincs találat! :(</h2></center>";
  }
  else
  {
     foreach($xmlres->children() as $item) {
       $snippet = $item->snippet->asXML();

       /*$title = substr( $snippet, 0, 50 ) . "...";
       $title = isset($meta["docno"]) ? $meta["docno"] : $title; 
       $title = isset($meta["path"]) ? substr( $meta["path"],
                                               strrpos( $meta["path"], '/' ) + 1,
                                               strlen($meta["path"]) ) : $title; 
       $title = isset($meta["title"]) ? $meta["title"] : $title;*/
       $title = $item->path->asXML(); 
       //$prefix = "";

       /*if( isset($meta["docno"]) and isset($meta["title"]) ) {
         $prefix = $meta["docno"] . ": ";
       }*/

       $beginlink = ("<a href=\"file://" . $item->path . "\">");
       $endlink = "</a>";
       //$cachedlink = indri_buildlink( $_REQUEST, $results[$i]->document );
       //$nextlink = indri_nextlink( $_REQUEST, $startdoc + 10 );
       
       
  ?>
     <div id="result">
        <h2><?= $prefix . $beginlink . $title . $endlink ?></h2>
        <div id="snippet">
          <?= $snippet ?>
        </div>
        [ <a href="<?= $cachedlink ?>">Tárolt dokumentum</a> ] 
     </div>
  <?php
  } 
  ?>

  <?= indri_printlinks( $_REQUEST, $startdoc, count($results), $indri_param[ 'page_docs' ] ) ?>
  </div>
  <div id="resultbanner">
  <hr></hr> 
  </div>
  <?php
  }
   include("include/footer.php"); ?>
  
</div> <!-- content -->


