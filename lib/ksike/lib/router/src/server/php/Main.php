<?php
/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: helpers
 * @version: 0.1

 * @description: Router es una libreria para el trabajo con el direccionamiento dentro del framework
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 01/06/2010
 * @update-Date: 19/09/2010
 * @license: GPL v3
 *
 */
namespace Ksike\lib\router\src\server\php;
use Ksike\base\common\iom\Request;
class Main
{
	public $option;
	public $request;
	
	public function __construct($option=false, $type="web"){
		$this->request = ($type=="web") ? new Request() : false;
		$this->option  = is_array($option) ? $option : array();
	}
	
	public function __get($key){
		if ($key == "this") {
			$class = Assist::whoCallme();
			return $this->module($class);
		}
	}

	protected function __this($key=false, $params=false, $tmp=false){
		if(is_string($key)){
			if ($key == "this") {
				$class = Assist::whoCallme();
				$hand = $this->module($class);
			}else if($key == "option") $hand = ($params && isset($this->option[$params])) ? $this->option[$params] : $this->option;
			else if (method_exists($this, $key)) {
				if($key == "relative") $params = Assist::whoCallme(4);
				$hand = $this->$key($params);
			}
			else $hand = $this->at($key, $params, $tmp);
			return ($hand) ? $hand : false;
		}
	}
	
	public function module($class=false){
		if(!$class) $class = Assist::whoCallme();
		if($class==KCL_MAIN) return $this->app();			
		else{
			$path = $this->plugins();
			return is_string($path) ? $path.$class.DIRECTORY_SEPARATOR : $this->path($path, "$class".DIRECTORY_SEPARATOR, $this->proj());
		}
		return false;
	}

	public function base(){
		return KCL;
	}

	public function core(){
		return KCL.'core'.DIRECTORY_SEPARATOR;
	}

	public function libs(){
		if(isset($this->option['lib'])){
			return !is_string($this->option['lib']) ? $this->option['lib'] : $this->proj().$this->option['lib'];
		}else return $this->proj()."lib".DIRECTORY_SEPARATOR;
	}

	public function plugins(){
		if(isset($this->option['plugins'])){
			return !is_string($this->option['plugins']) ? $this->option['plugins'] : $this->proj().$this->option['plugins'];
		}else return $this->proj()."plugins".DIRECTORY_SEPARATOR;
	}

	public function proj(){
		if(isset($this->option['proj']) && $this->option['proj']){
			if(isset($this->option["alias"])){
				if(isset($this->option["alias"][$this->request->at("proj")])) 
					return realpath($this->option["alias"][$this->request->at("proj")]).DIRECTORY_SEPARATOR;
			}
			return  $this->option['proj'];
		}
		else if(defined('KCL_PROJ')) return constant('KCL_PROJ');
		else return false;
	}

	public function web(){
		if($this->option && isset($this->option['web'])) 
			return $this->option['web'];
		else if(defined('KCL_WEB')) return constant('KCL_WEB');
		else return $_SERVER["SCRIPT_FILENAME"];
	}
	
	public function app(){
		return !isset($this->option['app']) ? $this->proj()."app".DIRECTORY_SEPARATOR : $this->proj().$this->option['app'];
	}

	public function at($file, $search="self", $verify="file"){
		switch($search){
			case "self": 
				$path = $this->verify($this->proj().$file, "valid");
				if(!$path) return $this->verify(KCL.$file, "valid");
				else return $path;
			break;
			case "none": return $this->verify($file, $verify); break;
			default: return $this->verify($this->$search().$file, $verify); break;
		}
	}

	public function load($option=false, $force=false){
		if($option){
			if(isset($option["request"]))
				$this->request->option = $option["request"] + $this->request->option;
		}else $option = $this->request->value();
		if(empty($this->option)) $force = true;
		$this->option = (!$force) ? $option + $this->option : $option;
		if(isset($this->option['proj']) && $this->option['proj']!="")$this->option['proj'] = realpath ($this->option['proj']).DIRECTORY_SEPARATOR;
	}

	public function relative($destiny=false, $origin=KCL_WEB){
		if(!$destiny) $destiny = Assist::whoCallme();
		if(!is_dir($destiny) && !is_file($destiny)) $destiny = $this->module($destiny);
		$detach = '/';
		$cout = "";
		$origin = $this->absolute($origin);
		$destiny = $this->absolute($destiny);
		
		$out = str_replace($origin, "", $destiny, $count);
		if(!$count){
			$count = strlen($destiny); $i = 0;
			while($i<$count && $destiny[$i]==$origin[$i]) $i++;
			$origin = explode($detach, substr($origin, $i));
			$out = substr($destiny, $i); 
			$out = DIRECTORY_SEPARATOR == "\\" ? str_replace("\\", "/", $out) : $out;
			$out = $out[0] == "/" ? substr($out, 1) : $out;
			foreach($origin as $i) if($i) $out = "../".$out;
			return $out;
		}else return $out;
	}

	public function path($container, $resource="", $origen=""){
		if(!is_array($container)){
			$path = $origen.$container.$resource;
			if(file_exists($path)) return $path;
		}else foreach($container as $dir){
			$path = $origen.$dir.$resource;
			if(file_exists($path)) return $path;
		}return false;
	}

	public function absolute($path){
		if(is_file($path)) $path = dirname($path);	
		return realpath($path)."/";
	}

	public function verify($path, $type="file"){
		if($type == "file"){ 
			if(is_file($path)) return $path;
		}else if($type == "path"){
			if(is_dir($path)) return $path;
		}else if($type == "valid"){
			if(is_dir($path) || is_file($path)) return $path;
		}else return $path;
		return false;
	}
}
