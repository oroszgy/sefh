<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">

<?php include("include/libindri.php") ?>

<head>
<meta http-equiv="Content-Type" content="text/html;charset=utf-8" > 
<title>Indri: Results for <?= $_REQUEST['query']; ?></title>
<link rel="stylesheet" type="text/css" href="style/style.css" title="stylesheet" />
</head>
<body>

<?php 
   $env = new QueryEnvironment();

   $startdoc = indri_setupenvironment( $indri_param, $env, $_REQUEST );
   $query = indri_cleanquery( $_REQUEST['query'] );

   // run the query
   $start_time = indri_timer();
   $annotatedResults = $env->runAnnotatedQuery( $query, $startdoc + 10 );
   $doc_end = $query_end = indri_timer();
   $results = array();

   if( $annotatedResults ) {
 	 $results = array_slice( $annotatedResults->getResults(), $startdoc );
     $documents = $env->documents( $results );
     $doc_end = indri_timer();        

	   $nodes = indri_getRawNodes( $annotatedResults->getQueryTree() );
   } else {
     include( "include/error.php" );
     return;
   }

   $query_time = $query_end - $start_time;
   $doc_time = $doc_end - $query_end;
   $total_time = $doc_end - $start_time;
?>

<div id="content">
  <?php include( "include/header.php" ) ?>

  <div id="resultbanner">
    <h3>Erre voltál kíváncsi: <i><?= $_REQUEST['query']; ?></i></h3> 
    ennyire gyors voltam: [<strong>lekérdezés</strong><? printf("%5.2fs", $query_time ); ?>, 
    <strong>dokmentumgenerálás</strong><? printf("%5.2fs", $doc_time ); ?>,
    <strong>összesen</strong><? printf("%5.2fs", $total_time ); ?>]
  </div>

  <div id="results">
  <?php
  if(empty($documents))
  {
  	echo "<center><h2>Nincs találat! :(</h2></center>";
  }
  else
  {
     for( $i=0; $i<count($results); $i++ ) {
       $doc = $documents[$i];
       $meta = $doc->metadata;
       $range = new position( $results[$i]->begin, $results[$i]->end );

       $matches = indri_documentMatches( $results[$i]->document,
													  $annotatedResults->getAnnotations(),
													  $nodes, 
                            $range );

       $snippet = indri_buildsnippet( $doc->text, $matches, $doc->positions, $indri_param['snippet_length'], $range );
       //memory management
       unset($doc);

       $title = substr( $snippet, 0, 50 ) . "...";
       $title = isset($meta["docno"]) ? $meta["docno"] : $title; 
       $title = isset($meta["path"]) ? substr( $meta["path"],
                                               strrpos( $meta["path"], '/' ) + 1,
                                               strlen($meta["path"]) ) : $title; 
       $title = isset($meta["title"]) ? $meta["title"] : $title; 
       $prefix = "";

       if( isset($meta["docno"]) and isset($meta["title"]) ) {
         $prefix = $meta["docno"] . ": ";
       }

       $beginlink = isset($meta["url"]) ? ("<a href=\"" . $meta["url"] . "\">") : "";
       $endlink = isset($meta["url"]) ? "</a>" : "";
       $cachedlink = indri_buildlink( $_REQUEST, $results[$i]->document );
       $nextlink = indri_nextlink( $_REQUEST, $startdoc + 10 );
       
       
  ?>
     <div id="result">
        <h2><?= $prefix . $beginlink . $title . $endlink ?></h2>
        <div id="snippet">
          <?= $snippet ?>
        </div>
        [ <a href="<?= $cachedlink ?>">Tárolt dokumentum</a> ] 
     </div>
  <?php } ?>

  <?= indri_printlinks( $_REQUEST, $startdoc, count($results), $indri_param[ 'page_docs' ] ) ?>
  </div>

  <?php
  }
   include("include/footer.php"); ?>
  <?php 
  	  //memory management
      unset($documents);
      //unset($results);
      //unset($annotatedResults);
  ?>
  <?php $env->close(); ?>
</div> <!-- content -->

</body>
</html>

