<?php
/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: handlers
 * @version: 0.1

 * @description: Handler es una libreria para el trabajo con el acceso y manipulacion de modulos
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 01/06/2010
 * @update-Date: 19/09/2010
 * @license: GPL v3
 *
 */
namespace Ksike\base\common\handlers;
use Ksike\base\common\helpers\Loader;
use Ksike\base\common\patterns\Factory;
use Ksike\base\common\patterns\Singleton;
class Library extends Singleton
{
	public static $__this = false;
	protected static $module = array();
	
	public function __get($key){
		return $this->up($key);
	}
	
	protected function __this($key=false)
	{
		if(is_string($key)){
			$hand = $this->up($key);
			return ($hand) ? $hand : false;
		}
	}
	
	protected function load($name, $iface=0, $type="module"){
	
	}
	
	
	
	
	
	
	
	
	public static function module($class=KCL_MAIN)
	{
		if(!isset(self::$module[$class])){
			if(Loader::this()->module($class)){
				self::$module[$class] = self::instance($class);
			}else throw new \Exception("Module << $class >> was not found.");
		}return self::$module[$class];
	}

	protected static function instance($class=KCL_MAIN, $type="invert")
	{
		$obj = ($type!="invert") ? Factory::build($class) : false;
		if(isset(Loader::this()->option["filter"]["decorate"])){
			if(isset(Loader::this()->option["filter"]["decorate"]["Module"])) 
				Factory::decorate(Loader::this()->option["filter"]["decorate"]["Module"], $obj);
				
			if($class!=KCL_MAIN && isset(Loader::this()->option["filter"]["decorate"]["Plugin"]))
				Factory::decorate(Loader::this()->option["filter"]["decorate"]["Plugin"], $obj); 

			if(isset(Loader::this()->option["filter"]["decorate"][$class]))
				Factory::decorate(Loader::this()->option["filter"]["decorate"][$class], $obj);
		}
		$obj = ($type=="invert") ? Factory::build($class, $obj) : $obj;
		return $obj;
	}
}
