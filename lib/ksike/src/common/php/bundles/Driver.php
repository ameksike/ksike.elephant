<?php
/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: bundles
 * @version: 0.1

 * @description: DriverManager es una libreria para cargar dinamicamente los drivers del framework
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 06/11/2010
 * @update-Date: 09/07/2011
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\base\bundles;
use Ksike\ksl\base\helpers\Router;
use Ksike\ksl\base\patterns\Factory;
class Driver extends Bundles
{
	public static $__this = false;
	protected $drivers;
	public function __construct(){
		$this->drivers = array();
	}

	public function factory($class, $params=0, $path=0) 
	{
		if(!isset($this->drivers[$class]["obj"])){
			$this->load($class, $path);
			$this->drivers[$class]["obj"] = Factory::build($class, $params);
		}
		return $this->drivers[$class]["obj"];
	}

	public function load(&$driver, $path=0)
	{
		if(!isset($this->drivers[$driver])){
			if(is_array($driver)){
				$resource = $driver["file"];
				$driver   = $driver['class'];
			}else   $resource = $driver."/".$driver.KCL_EXT;
		
			if(!$path) $path = Router::this("libs");
			$origen = is_array($path) ? KCL : "";
			$file = Router::this()->path($path, $resource, $origen);
			if(!$file) $file = Router::this()->path($path, "Dv".$resource, $origen);
			if(include_once $file) $this->drivers[$driver] = array('file'=>$file);
			else throw new \Exception("Driver <<$driver>> was not found");
		}
	}

	public static function getList()
	{
		return $this->drivers;
	}

	protected function __this($ask=false, $params=false, $path=0)
	{
		return $this->factory($ask, $params, $path);
	}
}
