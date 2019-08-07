<?php
/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: helpers
 * @version: 0.1

 * @description: Assist es una libreria para el trabajo con ...
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 02/06/2010
 * @update-Date: 05/09/2011
 * @license: GPL v3
 *
 */
namespace Ksike\lib\base\src\server\php\helpers;
use Ksike\base\common\bundles\Package;
use Ksike\base\common\bundles\Driver;
use Ksike\base\common\handlers\Library;
use Ksike\base\common\messages\Debuger;
class Assist
{	
	public static function library($name, $iface=0, $type="module")	{
		$iface = !$iface ? $name : $iface;
		return Package::this($pack);
	}
	
	public static function module($pack=false)	{
		return Package::this($pack);
	}
	
	public static function package($pack=false)	{
		return Package::this($pack);
	}

	public static function driver($ask=false, $params=false, $path=0){
		return Driver::this($ask, $params, $path);
	}

	public static function loader($key=false, $params=false){
		return Loader::this($key, $params);
	}
	
	public static function router($key=false, $params=false)	{
		if($key=="this"){
			$params = $key;
			$key = "module";
		}else if($key=="relative"){
			$key = self::whoCallme();
			$params=KCL_WEB;
		}if($params=="this") $params = self::whoCallme();
		return Router::this($key, $params);
	}
	
	public static function request($key=false, $params=false) {
		return (!$key) ? Router::this()->request : ((method_exists(Router::this()->request, $key)) ? Router::this()->request->$key($params) : Router::this()->request->at($key, $params));
	}
	
	public static function respond($key=false, $params=false) {
		return (!$key) ? Router::this()->request : ((method_exists(Router::this()->request, $key)) ? Router::this()->request->$key($params) : Router::this()->request->at($key, $params));
	}

	public static function whoCallme($deep=2, $elm="class")
	{   //... elm: [file|line|function|class|object|type|args|all]
		$debug = debug_backtrace();
		if($deep!="all") $infor = ($elm!="all") ? $debug[$deep][$elm] : $debug[$deep];
		else {
			$infor = array();
			foreach ($debug as $i)
				$infor[] = ($elm!="all" && isset($i[$elm])) ? $i[$elm] : $i;
		}
		unset($debug);
		return $infor;
	}
	
	public static function exec($obj, $action, $param=false) {
		if(method_exists($obj, $action)){
			if(is_object($obj)) $obj->$action($param);
			else $obj::$action($param);
		}else return -1;
	}

	public static function debug($msg, $arg, $function=0, $class=0, $file=0){
		$function = $function ? $function : self::whoCallme(2, "function");
		$class = $class ? $class : self::whoCallme(2, "class");
		$file = $file ? $file : self::whoCallme(2, "file");
		return Debuger::this()->tryOn($msg, $arg, $function, $class, $file);
	}	
}
