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
namespace Ksike\lib\package\src\common\php;
use Ksike\lib\base\src\common\php\patterns\Singleton;
class Bundle extends Singleton
{
	protected $driver;
	protected $option;
	public function __construct($option=false)
	{
		$this->option = $option;
		$this->driver = array();
	}
	
	public function getDriver($type, $params=false, $force=false)
	{
		if(!isset($this->driver[$type]) || $force){
			$this->build($type, $params);
		} return $this->driver[$type];
	}
	
	protected function isValid($class=false, $type=false)
	{
		if( isset($this->option["mod"]["driver"]) && in_array($class, $this->option["mod"]["driver"])) return true;
		return false;
	}

	protected function build($type, $params=false)
	{
			$class = get_class($this).'Driver'.strtoupper($type);
			if(!$this->isValid($class, $type)) return false;
			$this->driver[$type] = new $class($params);
	}
}
