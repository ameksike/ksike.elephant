<?php
/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: bundles
 * @version: 0.1

 * @escription: Package es una libreria que ...
 * @authors: ing. Antonio Membrides Espinosa
 * @making Date: 15/08/2011
 * @update Date: 24/08/2011
 * @license: GPL v3
 *
 */
namespace Ksike\lib\package\src\server\php;
use ksike\lib\base\src\server\php\helpers\Assist;
class Main extends Bundle
{
	public $packages;
	public $option;
	public static $__this = false;

	public function __construct($option=false)
	{
		$this->option = ($option && !is_string($option)) ?  $option : array();
		$this->packages = false;
	}

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
	
	public function activate()
	{
		if($this->option)foreach($this->option as $key=>$pack) 
			if(isset($pack["cfg"]["load"]) && $pack["cfg"]["load"]=="auto"){
				$this->up($key, false);
			}
	}
	
	public function callthem($action)
	{
		if($this->packages) foreach($this->packages as $pack)
			Assist::exec($pack, $action);				
	}

	protected function load($name)
	{
		if(isset($this->option[$name])){
			if(isset($this->option[$name]["mod"]["base"])) Loader::this()->dependency($this->option[$name]["mod"]["base"], KCL_SRC."ksl/package/$name/base/");
			foreach($this->option[$name]["mod"] as $mod=>$i)
				if($mod!="base") Loader::this()->dependency($i, KCL_SRC."ksl/package/$name/$mod/");
			return true;
		}else return false;
	}

	protected function up($key, $get=true)
	{
		if(!isset($this->packages[$key])) {
			if($this->load($key)){
				$handler  = "Ksike\\ksl\\package\\$key\\proxy\\".$this->option[$key]["mod"]["proxy"];
				if($this->option[$key]["cfg"]["type"] == "static"){
					$this->packages[$key] = $handler;
					if(method_exists($handler, "on"))
						$handler::on($this->option[$key]["cfg"]); 
				}else $this->packages[$key] = new $handler($this->option[$key]);
				unset($this->option[$key]);
			}else return false;
		}
		if($get) return $this->packages[$key];
	}
}
