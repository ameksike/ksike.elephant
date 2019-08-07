<?php
/**
 *
 * @framework: Ksike
 * @package: error
 * @subpackage: control
 * @version: 0.1

 * @description: ErrorHandler es una libreria para el trabajo con 
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 08/09/2010
 * @update-Date: 08/09/2010
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\package\error\control;
use Ksike\ksl\package\error\base\ErrorHandler;
use Ksike\ksl\base\helpers\Assist;
class BugHandler extends ErrorHandler
{
	public static $config;

	public static function on($config)
	{
		error_reporting(E_ALL | E_STRICT);
		static::$handler = set_error_handler('Ksike\\ksl\\package\\error\\control\\BugHandler::onCatch');
		static::$config  = $config["bug"];
	}

	public static function onCatch($errno, $errstr, $errfile, $errline) 
	{	
		$info = static::getInfo(array("errno"=>$errno, "errstr"=>$errstr, "errfile"=>$errfile, "errline"=>$errline));
		$path = static::getPath($info["type"]);
		$logi = static::getLogFormat($info);
		Assist::package("log")->save($logi, $info["mode"], $path);
		static::dispatch($info);		
	}

	protected static function getPath($type)
	{
		return parent::getPath($type).KCL_ERROR;
	}

	protected static function getInfo($lst)
	{
		$info = pathinfo($lst["errfile"]);
		$info["path"]  = Assist::router()->relative($lst["errfile"], Assist::router("base"));
		$info["mode"]  = (!isset(static::$config[$lst["errno"]])) ? "bug" : static::$config[$lst["errno"]]['name'];
		$info["type"]  = static::getype($lst["errfile"]);
		$info["str"]   = $lst["errstr"];
		$info["line"]  = $lst["errline"];
		$info["no"]    = $lst["errno"];
		$info["trace"] = false;
		return $info;
	}
}
