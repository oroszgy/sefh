<?php 
include("libhunsyn_php.php");

global $QUERY;
//$SYNS[$word] = array(offset, array(syn, enabled)...))
global $SYNS;

function storeAllSyns($query) {
	preg_match_all('/~[a-zA-ZöüóőúéáűíÖÜÓŐÚÉÁŰÍ]+/', $query, $synWords, PREG_OFFSET_CAPTURE);
	$syns = $synWords[0];
	$ret = array();
	for($i=0; $i<count($syns); ++$i) {
		$word = $syns[$i][0];
		$word = substr($word, 1, strlen($word)-1);
		$ret[$word]['offset'] = $syns[$i][1];
		$ret[$word]['syns'] = getSyns($word);
	}
	return $ret;
}


function getSyns($word) {
	$s = new Humor("/home/mee/workspaces/sefh/sefh/testingData/lex");
	$r =  $s->getSyns($word);
	$has = false;
	for($i=0; $i<$r->size(); $i++) {
		$syn = $r->get($i);
		if($syn == $word)
			$has = true;
		$ret[$syn] = true;
	}
	if($has != true) {
		$ret[$word] = true;
	} 
	return $ret;
}

function replaceWithSyns($groups) {
	$word = $groups[0];
	$word = $word = substr($word, 1, strlen($word)-1);
	global $SYNS;
	$synArray = $SYNS[$word]['syns'];
	
	$ret = "#syn(";
	foreach($synArray as $key => $val) {
		if($val)
		{
			$ret .= "#1(".$key.") ";
		}
	}
	//$ret = substr($ret, 0, strlen($ret) -1);
	$ret .= ")";
	return $ret;
}

function generateSynQuery($query) {
	$q = $query;
	$q = preg_replace_callback("/~[a-zA-ZöüóőúéáűíÖÜÓŐÚÉÁŰÍ]+/", replaceWithSyns, $query); 
	return $q;
}
?>