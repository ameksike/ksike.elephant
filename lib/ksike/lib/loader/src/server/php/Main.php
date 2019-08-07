<?php
/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: helpers
 * @version: 0.1

 * @description: Loader es una libreria para carga dinamica de los elementos que componen el framework
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 01/06/2010
 * @update-Date: 05/07/2011
 * @license: GPL v3
 *
 */
namespace Ksike\lib\loader\src\server\php {
use Ksike\base\common\patterns\Singleton;
class Main
{
	public $option;
	public $tmp;
	protected $loaders;
	
	public function __construct($option=false){
		$this->option  = false;
		$this->loaders = false;
		$this->register();
	}

	public function register(){
		ini_set('unserialize_callback_func', 'spl_autoload_call');
        	spl_autoload_register(array(__CLASS__ ,'__autoload'));
	}
	
	public function supply($catcher)
	{
		if(!$this->loaders) $this->loaders = array();
		$this->loaders[] = $catcher;
	}

	public function dispatch($class)
	{
		if($this->loaders) foreach($this->loaders as $i) 
			if(method_exists($i, "onLoad")) Assist::exec($i, "onLoad", $class);
	}

	public function cfg($path, $fileName="config", $search="self")
	{
		$pathf = Router::this($path, $search, "valid");
		$data = (!Assist::package("config")) ? file_exists($pathf.$fileName.KCL_EXT) ? @include $pathf.$fileName.KCL_EXT  : false : Assist::package("config")->load($pathf, $fileName);
		return (is_array($data)) ? $data : array();
	}

	public function includes($class=KCL_MAIN, $path=false)
	{
		if(!$path) $path = Router::this()->module($class).KCL_INCLUDE;
		if(Assist::package("dir")) Assist::package("dir")->scan($path, "-r", $this);  
	}

	public function module($class=KCL_MAIN){
		if(!class_exists($class, false)){
			$file = Router::this("module", $class).'server/'.$class.KCL_EXT;
			if(file_exists($file)){
				if($this->mode()!= "auto") $this->filter($class);
				$this->includes($class);
				require_once $file;
			}else return false;
		}return true;
	}

	public function filter($class=KCL_MAIN)
	{
		foreach($this->option["filter"] as $k=>$i){	
			if(isset($i["Module"])) $this->dependency($i["Module"], KCL_SRC."ksl/filter/$k/");
			if($class!=KCL_MAIN && isset($i["Plugin"])) $this->dependency($i["Plugin"], KCL_SRC."ksl/filter/$k/");
			if(isset($i[$class])) $this->dependency($i[$class], KCL_SRC."ksl/filter/$k/");
		}
	}

	public function dependency($lst, $path)
	{
		if(!is_array($lst)) $this->required($path.$lst);
		else foreach($lst as $k=>$i){
			if(is_array($i)) $this->dependency($i, $path."$k/");
			else $this->required($path.$i);
		}
	}

	public function onFind($lst, $path, $params, $item, $type)
	{
		if(Assist::package("dir")->is_php($path.$item)) require_once $path.$item; 
	}

	public function onbase()
	{
		if(isset($this->option["base"])) $this->dependency($this->option["base"], KCL_SRC."ksl/base/");
	}

	public function required($path, $search="self", $verify="file")
	{
		$file = Router::this()->at($path.KCL_EXT, $search, $verify);
		return ($file) ? @include_once $file : false;
	}
		
	protected function __this($key=false, $params=false)
	{
		if(is_string($key)){
			$hand = $this->$key($params);
			return ($hand) ? $hand : false;
		}
	}

	public function mode()
	{
		if(isset($this->option["cfg"]["load"]))	
			return 	$this->option["cfg"]["load"];
		else return "auto";
	}
	
	static function __autoload($class){
		if(self::this("mode")=="auto"){
			$class = str_replace("\\", "/", $class); //... DIRECTORY_SEPARATOR
			$class = str_replace("Ksike/", KCL_SRC, $class);
			self::this("required", $class); 
		}else throw new \Exception("Class <<$class>> was not found, and autoload mode has not be set");
		self::this()->dispatch($class);
	}
	
	public function library($name, $iface=0, $type="module"){
		
	}
}}
