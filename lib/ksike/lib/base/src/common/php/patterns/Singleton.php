<?php
/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: patterns
 * @version: 0.1

 * @description: Singleton es una libreria para la ... 
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 06/11/2010
 * @update-Date: 05/12/2010
 * @license: GPL v2
 *
 */
namespace Ksike\lib\base\src\common\php\patterns;
class Singleton
{
	protected static $__this = false;
	protected static function buildObj($class, $args)
	{
		$option = (isset($args[0])) ? $args[0] : false;
		return Factory::build($class, array($option));	
	}
	public static function this()
	{
		$args = func_get_args();
		if(!static::$__this) static::$__this = static::buildObj(get_called_class(), $args);
		$out = call_user_func_array(array(static::$__this, "__this"), $args);
		if(isset($out)) return $out;
		else return static::$__this;
	}
	protected function __this(){}
}
