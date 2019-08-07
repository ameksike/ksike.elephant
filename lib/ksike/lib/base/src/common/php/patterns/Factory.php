<?php 
/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: patterns
 * @version: 0.1

 * @description: Factory es una libreria para la creacion dinamica de instancias 
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 06/11/2010
 * @update-Date: 05/12/2010
 * @license: GPL v2
 *
 */
namespace Ksike\lib\base\src\common\php\patterns;
class Factory
{
	public static function decorate($lst, &$obj=false, $ns="Ksike\\ksl\\filter\\decorate\\")
	{
		foreach($lst as $i) $obj = self::build($i, $obj, $ns);
		return $obj;
	}

	public static function &build($class, $params=0, $ns="")
	{
		$class = $ns.$class;
		if(class_exists($class)){
			if($params){
				if(is_array($params)){
					$count = count($params);
					if($count == 1) $obj = new $class($params[0]);
					else $obj = self::strBuild($class, $params, $count);
				}else $obj = new $class($params);
			}else $obj = new $class;
			return $obj;
		}else throw new \Exception("Class << $class >> was not loaded");
	}

	protected static function &strBuild($class, $params, $count=0)
	{
		$count = $count ? $count : count($params);
		$code  = '$obj = new '.$class.'(';
		$code .= self::implode($params, $count);
		$code .= ');';
		eval($code);		
		return $obj;
	}

	protected static function implode($params, $count=0)
	{
		$in = 0;
		foreach($params as $i){
			if(!$in){
				$code = self::getData($i);
				$in = 1;
			}else{
				$atribute = self::getData($i);
				if($atribute) $code .= ', '.$atribute;
			}
		} return $code;
	}

	protected static function getData($data)
	{
		if(!is_string($data)) return $data;
		else return "'".$data."'";
	}
}
