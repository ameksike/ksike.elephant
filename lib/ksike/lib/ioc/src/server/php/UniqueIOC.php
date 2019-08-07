<?php
/**
 *
 * @framework: Ksike
 * @package: IOC
 * @subpackage: proxy
 * @version: 0.1

 * @escription: IOC es una libreria que implementa la publicacion de archivos
 * @authors: ing. Antonio Membrides Espinosa
 * @making Date: 22/08/2011
 * @update Date: 24/08/2011
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\package\ioc\proxy;
use Ksike\ksl\base\helpers;
class IOC
{
	protected $option;

	public function __construct($option=false){
		$this->load($option);
	}

	public function __get($key){
		return $this->doit($key);
	}

	public function load($option=false)
	{
		if($option) $this->option += $option;
		else $this->option = Loader::fileconf(Router::app().KCL_CONFIG, "ioc", "none");
	}

	public function save($key)
	{

	}

	protected function doit($key)
	{
		if(!isset($this->option[$key])) return false;
		switch($this->option[$key]["type"]){
			case "class":
				if(!isset($this->option[$key]["obj"])){
					$path = $this->option[$key]["path"].$this->option[$key]["file"];
					Loader::required($path, $this->option[$key]["point"], "file");
					$this->option[$key]["obj"] = true;
				}
				if(isset($this->option[$key]["action"])){
					$params = (isset($this->option[$key]["params"])) ? $this->option[$key]["params"] : false;
					$hand = $this->option[$key]["name"];
					$action = $this->option[$key]["action"];
					return $hand::$action($params);
					return "caca";
				}else return  $this->option[$key]["name"];
			break;
			case "object":
				if(!isset($this->option[$key]["obj"])){
					$params = (isset($this->option[$key]["params"])) ? $this->option[$key]["params"] : false;
					$path = $this->option[$key]["path"].$this->option[$key]["file"];
					Loader::required($path, $this->option[$key]["point"], "file");
					$this->option[$key]["obj"] = Factory::instantiate($this->option[$key]["name"], $params );
				}return $this->option[$key]["obj"];
			break;
			case "config":
				if(!isset($this->option[$key]["obj"])){
					$point = $this->option[$key]["point"];
					$path = ($point!="none") ? Router::$point().KCL_CONFIG : $this->option[$key]["path"] ;
					$this->option[$key]["obj"] = Loader::fileconf($path, $this->option[$key]["file"], "none");
				}return $this->option[$key]["obj"];
			break;
			default: return $this->option[$key]; break;
		}
	}

	protected static $__this = false;
	public static function this($ask=false, $params=false)
	{
		if(!self::$__this){
			if(is_array($ask)){
				$option = $ask;
				$ask = false;
			}else $option=false;
			self::$__this = new self($option);
		}
		if($ask){
			$out = self::$__this->__this($ask, $params);
			if($out) return $out;
		} 
		return self::$__this;
	}
	protected function __this($ask, $params=false){
		return self::$__this->doit($ask);
	}
}
