<?php
/**
 *
 * @framework: Ksike
 * @package: config
 * @subpackage: proxy
 * @version: 0.1

 * @description: ConfigManager es una libreria para el trabajo con ficheros de configuracion
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 16/06/2010
 * @update-Date: 16/06/2010
 * @license: GPL v3
 *
 */
namespace Ksike\lib\config\src\server\php;
use Ksike\lib\base\src\common\php\patterns\Bridge;
use Ksike\lib\base\src\server\php\helpers\Assist;
class Main extends Bridge
{
	public function __construct($option) 
	{
		parent::__construct($option);
		if(!isset($this->option["cfg"]["order"])) 
			$this->option["cfg"]["order"] = array("php","xml","ini","json");
	}

	public function setOrderPriory($order) 
	{
		$this->option["cfg"]["order"] = $order;
	}

	public function __get($key)
	{
		if($key == "this") $key = Assist::whoCallme();
		return $this->load($key, "config");
	}

	public function load($path=0, $file=false, $type=0, $force=true)
	{
		if($dr = $this->driver($type, $path, $file, $force)){
			$data = $dr->load();
			if(isset($data["import"])){
				if(!is_array($data["import"])) { if($data["import"]!="") $data = array_merge_recursive ($this->load($path, $data["import"], 0, $force), $data);
				}else foreach($data["import"] as $file) if($file!="") $data = array_merge_recursive ($this->load($path, $file, 0, $force), $data);
				unset ($data["import"]);
			}return $data;
		}
	}
	
	public function save($data=0, $path=0, $file="config", $type=0, $force=0)
	{
		$dr = $this->driver($type, $path, $file, $force);
		$dr->save($data, "$path$file.$type");
	}

	public function driver($type=0, $path=0, $file="config", $force=0)
	{
		if($path){
			if(is_file($path)){
				$tmp = pathinfo($path);
				$type = $tmp['extension'];
				$path = $tmp['dirname']."/";
				$file = $file ? $file : $tmp['filename'];
			}else{
				if(!is_dir($path)) {
					if(!$path || $path == ""){
						$elem = Assist::whoCallme();
						$elem = ($elem!="Ksike\ksl\package\config\proxy\Config") ? $elem : Assist::whoCallme(3);
					} else  $elem = $path;
					$path = Assist::router("module", $elem)."cfg/";
				}
				if(!$type) {
					$type = $this->searchExt($path.$file); 
					$type = $type["type"];
				}
			}
			return $this->getDriver($type, "$path$file.$type", $force);		
		}
	}

	private function searchExt($path)
	{
		$inf = pathinfo($path);
		if(!empty($inf['extension'])) return array("type"=>$inf['extension'], "ext"=>"");
		else foreach($this->option["cfg"]["order"] as $i)
			if(file_exists($path.".".$i)) return array("type"=>$i, "ext"=>".".$i);
		return -1;
	}
}
