<?php
/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: bundles
 * @version: 0.1

 * @escription: Singleton es una libreria que infiere el patron Singleton
 * @authors: ing. Antonio Membrides Espinosa
 * @making Date: 02/06/2010
 * @update Date: 02/06/2010
 * @license: GPL v3
 *
 */
namespace Ksike\lib\base\src\common\php\patterns;
class Bridge
{
	protected $driver;
	protected $option;
	public function __construct($option=false){
		$this->option = $option;
		$this->driver = array();
	}

	public function getDriver($type, $params=false, $force=false)
	{
		if(!isset($this->driver[$type]) || $force){
			if(!$this->build($type, $params)) throw new \Exception("Driver << $type >> is not exist");  
		} return $this->driver[$type];
	}

	protected function isValid($class=false)
	{
		if( isset($this->option["cfg"]["driver"]) && in_array($class, $this->option["cfg"]["driver"])) return true;
		return false;
	}

	protected function build($type, $params=false)
	{
		if($type){
			$class = str_replace("Ksike\ksl\package\\", "", get_class($this));
			$class = substr($class, 0, strpos($class, "\\"));
			$class = "Ksike\ksl\\package\\$class\\driver\\".ucfirst($class).'Driver'.strtoupper($type);
			if(!$this->isValid($type)) return false;
			$this->driver[$type] = new $class($params);
			return true;
		}else return false;
	}
}
