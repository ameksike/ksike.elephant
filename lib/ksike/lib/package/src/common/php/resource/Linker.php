<?php
/**
 *
 * @framework: Ksike
 * @package: Core
 * @subpackage: php
 * @version: 0.1

 * @escription: Linker es una libreria que implementa el mecanismos de Señales y Ranuras 
 * @authors: ing. Antonio Membrides Espinosa
 * @making Date: 02/06/2010
 * @update Date: 02/06/2010
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\filter\resource;
use Ksike\ksl\base\helpers\Loader;
use Ksike\ksl\base\helpers\Router;
class Linker
{
	private $units;

	public function __construct() 
	{
		$this->units = false;
	}

	public function connect($signal, $classSignal, $slot, $classSlot, $type='pos', $handle=null)
	{
		if(!$this->units) $this->units = array('pos'=>array(),'pre'=>array());
		$this->units[$type][$classSignal][$signal][] = array(
		      'handle'=>$handle,
		      'slot'=>$slot,
		      'class'=>$classSlot
		);
	}

	public function disconnect($signal, $classSignal, $slot, $classSlot, $type='pos')
	{
		//... falta
		unset($this->units[$type][$classSignal][$signal]);
	}

	public function getPrecondition($controller, $action)
	{
		if(isset($this->units['pre'][$controller][$action])){
			$result = $this->units['pre'][$controller][$action];
			if($result) return $result;
		}
		return array();
	}

	public function getPoscondition($controller, $action)	
	{
		if(isset($this->units['pos'][$controller][$action])){
			$result = $this->units['pos'][$controller][$action];
			if($result) return $result;
		}
		return array();
	}

	public function load($fileName="config")
	{
		$conf = Loader::this()->cfg(Router::this("app").KCL_CONFIG, $fileName, "none");
		if(!isset($conf["linker"])) $conf = Loader::this()->cfg(Router::this("app").KCL_CONFIG, "linker", "none");
		$this->addUnits($conf["linker"]);
	}

	public function addUnits($lst)
	{
		if(is_array($lst)) $this->units = (!$this->units) ?  $lst : array_merge_recursive($this->units, $lst);
	}
}
