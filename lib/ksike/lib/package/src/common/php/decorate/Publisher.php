<?php
/**
 *
 * @framework: Ksike
 * @package: filter
 * @subpackage: decorate
 * @version: 0.1

 * @escription: Publisher es una libreria que implementa la publicacion de archivos
 * @authors: ing. Antonio Membrides Espinosa
 * @making Date: 02/06/2010
 * @update Date: 02/06/2010
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\filter\decorate;
use Ksike\ksl\filter\control\Primal;
use Ksike\ksl\base\helpers\Assist;
class Publisher extends Primal
{
	protected $cache;

	protected function loadContents($file, $type="open"){
		if($type == "open"){
			$data = file_get_contents($file);
			return $data;
		}else header("Location: ".$file);
	}

	protected function loadCache($path=0){
		if(Assist::package("config")){
			$path = $path ? $path : Assist::router("app").KCL_CONFIG;
			$this->cache = Assist::package("config")->load($path, "publisher", "json");
		}else throw new \Exception("Package << config >> was not found.");
	}

	protected function saveCache($path=0){
		if(Assist::package("config")){
			$path = $path ? $path : Assist::router("app").KCL_CONFIG;
			Assist::package("config")->save($this->cache, $path, "publisher", "json");
			//file_put_contents($path."publisher.json", stripcslashes(json_encode($this->cache)));
		}else throw new \Exception("Package << config >> was not found.");
	}

	protected function searchByLocate($elem, $locate, $param=""){
		$outs = array("found"=>false);
		$path = Assist::router($locate);
		if(is_string($path))
			$outs = Assist::dir()->find($elem, $path.$param, $type="strict");
		else foreach($path as $i)
			if(empty($outs["found"])) $outs = Assist::dir()->find($elem,  Assist::router("base").$i, $type="strict");
		return $outs["found"];
	}

	protected function find($file){
		$outs = $this->searchByLocate($file, "app",  "client/");
		if(empty($outs)) $outs = $this->searchByLocate($file, "plugins"); 
		if(empty($outs)) $outs = $this->searchByLocate($file, "libs");	

		if(empty($outs)) $outs = $this->searchByLocate($file, "proj",  "core/src/js/");
		if(empty($outs)) $outs = $this->searchByLocate($file, "proj",  "core/cfg/");
		if(empty($outs)) $outs = $this->searchByLocate($file, "core",  "src/js/");
		if(empty($outs)) $outs = $this->searchByLocate($file, "core",  "cfg/");

		if(!empty($outs)){
			$this->cache[$file]["point"] = "proj";
			$this->cache[$file]["file"] = $file;
			$this->cache[$file]["path"] = Assist::router()->relative($outs[0], Assist::router("proj"));
			$this->saveCache();
		}
	}
		
	protected function search($file, $ext, $type)
	{
		$this->loadCache();

		if(!isset($this->cache[$file])) $this->find($file);

		if(isset($this->cache[$file]["point"])){
			if($this->cache[$file]["point"] == "module") 
				$path = Assist::router("module", $this->cache[$file]["mod"]);
			else $path = Assist::router($this->cache[$file]["point"]); 
		}else $path = "";

		$path .= isset($this->cache[$file]["path"]) ? $this->cache[$file]["path"] : "";
		$path .= isset($this->cache[$file]["file"]) ? $this->cache[$file]["file"] : "";

		$data  = $this->loadContents($path, $type);	
		return $data;
	}

	public function contents($params)	
	{
		$in = Assist::request("fl");
		$of = Assist::request("outFormat");
		$ty = $params["type"];

		$in = (!stristr($in, ".$of")) ? "$in.$of" : $in;

		$il = explode(".", $in);
		//"core/src/" para busqueda explisita
		return $this->search($in, $il[count($il)-1], $ty);
	}
}
