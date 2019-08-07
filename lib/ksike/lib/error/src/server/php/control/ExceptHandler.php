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
class ExceptHandler extends ErrorHandler
{
	public static function on()
	{
		static::$handler = set_exception_handler('Ksike\\ksl\\package\\error\\control\\ExceptHandler::onCatch');
	}

	public static function onCatch($obj) 
	{
		$info = static::getInfo($obj);
		$path = static::getPath($info["type"]);
		$logi = static::getLogFormat($info);
		Assist::package("log")->save($logi, $info["mode"], $path);
		static::dispatch($info);
	}

	protected static function getPath($type)
	{
		return parent::getPath($type)."exception/";
	}

	protected static function getInfo($obj)
	{
		$info = pathinfo($obj->getFile()); //... dirname|basename|extension|filename
		$info["path"] = Assist::router()->relative($obj->getFile(), Assist::router("base"));
		$info["mode"]  = "exception";
		$info["type"] = static::getype($obj->getFile());
		$info["str"]  = $obj->getMessage();
		$info["line"] = $obj->getLine();
		$info["no"]   = $obj->getCode();
		$info["trace"]= $obj->getTrace();
		return $info;
	}
}
