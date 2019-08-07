<?php
/**
 *
 * @framework: Ksike
 * @package: error
 * @subpackage: base
 * @version: 0.1

 * @description: ErrorHandler es una libreria para el trabajo con 
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 08/09/2010
 * @update-Date: 08/09/2010
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\package\error\base;
use Ksike\ksl\base\helpers\Router;
use Ksike\ksl\base\helpers\Assist;
class ErrorHandler
{
	protected static $catcher = false;
	protected static $handler = false;

	public static function onCatch($errno, $errstr, $errfile, $errline){}
	public static function on(){}

	public static function supply($catcher)
	{
		if(!static::$catcher) static::$catcher = array();
		static::$catcher[] = $catcher;
	}

	protected static function dispatch($params)
	{
		if(static::$catcher) foreach(self::$catcher as $i) 
			if(method_exists($i,"onCatch")) Assist::exec($i, "onCatch", $params);
	}

	protected static function getype($path)
	{
		if(stripos($path, "/core/") === false) return "app";
		else if(stripos($path, Router::this('proj')) === false) return "core";
		else return "proj";
	}

	protected static function getLogFormat($lst)
	{
		return array(
			'File'=>$lst["basename"], 
			'Line'=>$lst["line"], 
			'Path'=>$lst["path"], 
			'Mode'=>$lst["mode"],
			'Description'=>$lst["str"]
		);
	}

	protected static function getPath($type)
	{
		$tmp = ($type != "proj") ? "" : "core/";
		return Router::this($type).$tmp.KCL_LOG;
	}
}
