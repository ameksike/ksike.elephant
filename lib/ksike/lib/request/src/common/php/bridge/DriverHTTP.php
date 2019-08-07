<?php
/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: helpers
 * @version: 0.1

 * @description: Request es una libreria para el trabajo con las peticiones realizadas por el modulo cliente
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 02/06/2010
 * @update-Date: 02/06/2010
 * @license: GPL v3
 *
 */
namespace Ksike\base\common\iom;
class Request
{
	protected $input;
	protected $value;
	public $option;

	public function __construct($option=array()){
		$this->option = $option;
		$this->value = false;
	}

	public function at($id=false){
		$val = $id ? $this->byMethod("PRETTY", $id) : false;
		$val = ($id && !is_string($val)) ? $this->byMethod("REQUEST", $id) : $val;
		return ($id && !is_string($val)) ? false :  $val;
	}

	public function in($id=false, $method=false){
		$method = $method ? $method : $_SERVER["REQUEST_METHOD"];
		$val = $this->byMethod($method, $id);
		return ($id && !is_string($val)) ? false :  $val;
	}

	public function isPrettyURL(){
		return (isset($_SERVER['PATH_INFO'])) ? true : false;
	}
	
	public function readPrettyURL(&$container, $format=0, $force=true){
		$lst = explode("/", $_SERVER['PATH_INFO']);
		unset($lst[0]); $l = 1;
		if($lst[count($lst)] == "") unset($lst[count($lst)]);
		if(isset($this->option["alias"][$lst[1]])){
			$alias = $this->option["alias"][$lst[1]];
			unset($lst[1]);
			$l++;
		}else $alias = &$this->option;
		$pattern = explode("/", $alias["url"]["pattern"]);
		
		if(isset($alias["key"])) $container = (!$force) ? $container + $alias["key"] : $alias["key"] + $container;
		foreach($lst as $k=>$i){
			$key = explode(":", $pattern[$k-$l]);
			if(count($key) == 2) $container[$key[0]][$key[1]] = $i;
			else $container[$pattern[$k-$l]] = $i;
		}
	}

	public function read($asArray=false){	
		if(empty($this->input))
		{//... Protocolos y Envolturas soportadas
			$raw  = '';
			$httpContent = fopen('php://input', 'r');
			while ($kb = fread($httpContent, 1024)) $raw .= $kb;
			fclose($httpContent);
			$this->input = json_decode(stripslashes($raw), $asArray);
		}
		return $this->input;
	}

	public function value($force=true)
	{
		if(!$this->value || $force){
			if(isset($this->option["key"]) ){
				$this->value = array();
				if(!$this->isPrettyURL()){
					foreach($this->option["key"] as $k=>$i){
						$value = $this->at($k, 'REQUEST');
						$this->value[$k] = ($value) ? $value : $i;
					}
				}else $this->readPrettyURL($this->value, $this->option["key"]);
			}
		}return $this->value;
	}
	
	public function byMethod($method='POST', $key=false){
		switch($method){
			case 'POST': 	return ($key && isset($_POST[$key])) ? stripslashes($_POST[$key]) : $_POST; break;
			case 'GET':	return ($key && isset($_GET[$key])) ? stripslashes($_GET[$key]) : $_GET; break;
			case 'REQUEST': return ($key && isset($_REQUEST[$key])) ? stripslashes($_REQUEST[$key]) : $_REQUEST; break;
			case 'PRETTY': 	return ($key && isset($this->value[$key])) ? $this->value[$key] : $this->value; break;
			default : 
				$obj = $this->read(); 
				//return ($key && isset($this->value[$key])) $obj->{$key} : $obj; 
			break;
		}
	}
}
