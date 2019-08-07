<?php
/**
 *
 * @framework: Ksike
 * @package: filter
 * @subpackage: control
 * @version: 0.1

 * @description: Primal es una libreria para el trabajo con ...
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 01/06/2010
 * @update-Date: 01/06/2010 
 * @license: GPL v3
 *
 */
namespace Ksike\filter\common\control;
class Primal 
{
	protected $_mate;
	public function preAction(){}
	public function posAction(){}
	public function __construct($_mate=false){
		$this->_mate = $_mate;
	}

	public function __call($action, $params)
	{
		if(!method_exists($this, $action) ) {
			if($this->_mate) return call_user_func_array(array($this->_mate, $action), $params);	
			else return "_lost_";
		}
	}

	public function __get($key)
	{
		if(!property_exists($this, $key)){
			if(!$this->_mate) return false;
			else return $this->_mate->$key;
		}
	}

	public function __set($key, $value)
	{
		if(!property_exists($this, $key) && $this->_mate){
			$this->_mate->$key = $value;
		}
	}

	public function __isset($key)
	{
		if(!property_exists($this, $key) && $this->_mate){
			return isset($this->_mate->$key);
		}
	}

	public function __unset($key)
	{
		if(!property_exists($this, $key) && $this->_mate){
			unset($this->_mate->$key);
		}
	}
}
