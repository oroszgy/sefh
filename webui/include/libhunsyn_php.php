<?php

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 * 
 * This file is not intended to be easily readable and contains a number of 
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG 
 * interface file instead. 
 * ----------------------------------------------------------------------------- */

/* PHP Proxy Classes */
/* PHP Proxy Classes */
class StringVector {
	public $_cPtr=null;
	protected $_pData=array();

	function __set($var,$value) {
		if ($var === 'thisown') return swig_example_alter_newobject($this->_cPtr,$value);
		$this->_pData[$var] = $value;
	}

	function __isset($var) {
		if ($var === 'thisown') return true;
		return array_key_exists($var, $this->_pData);
	}

	function __get($var) {
		if ($var === 'thisown') return swig_example_get_newobject($this->_cPtr);
		return $this->_pData[$var];
	}

	public function __construct($n=null) {
		if (is_resource($n) && get_resource_type($n) === '_p_std__vectorT_std__string_t') {
			$this->_cPtr=$n;
			return;
		}
		$this->_cPtr=$r;
		switch (func_num_args()) {
		case 0: $this->_cPtr=new_StringVector(); break;
		default: $this->_cPtr=new_StringVector($n);
		}
	}

	public function size() {
		return StringVector_size($this->_cPtr);
	}

	public function capacity() {
		return StringVector_capacity($this->_cPtr);
	}

	public function reserve($n) {
		StringVector_reserve($this->_cPtr,$n);
	}

	public function clear() {
		StringVector_clear($this->_cPtr);
	}

	public function push($x) {
		StringVector_push($this->_cPtr,$x);
	}

	public function is_empty() {
		return StringVector_is_empty($this->_cPtr);
	}

	public function pop() {
		return StringVector_pop($this->_cPtr);
	}

	public function get($i) {
		return StringVector_get($this->_cPtr,$i);
	}

	public function set($i,$val) {
		StringVector_set($this->_cPtr,$i,$val);
	}
}

class Humor {
	public $_cPtr=null;
	protected $_pData=array();

	function __set($var,$value) {
		if ($var === 'thisown') return swig_example_alter_newobject($this->_cPtr,$value);
		$this->_pData[$var] = $value;
	}

	function __isset($var) {
		if ($var === 'thisown') return true;
		return array_key_exists($var, $this->_pData);
	}

	function __get($var) {
		if ($var === 'thisown') return swig_example_get_newobject($this->_cPtr);
		return $this->_pData[$var];
	}

	public function __construct($dir=null) {
		if (is_resource($dir) && get_resource_type($dir) === '_p_Humor') {
			$this->_cPtr=$dir;
			return;
		}
		$this->_cPtr=$r;
		switch (func_num_args()) {
		case 0: $this->_cPtr=new_Humor(); break;
		default: $this->_cPtr=new_Humor($dir);
		}
	}

	public function getSyns($word) {
		$r=Humor_getSyns($this->_cPtr,$word);
		if (is_resource($r)) {
			$c=substr(get_resource_type($r), (strpos(get_resource_type($r), '__') ? strpos(get_resource_type($r), '__') + 2 : 3));
			if (!class_exists($c)) {
				return new StringVector($r);
			}
			return new $c($r);
		}
		return $r;
	}

	public function getClassName() {
		return Humor_getClassName($this->_cPtr);
	}
}

?>
