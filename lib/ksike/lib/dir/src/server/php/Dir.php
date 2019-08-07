<?php
/**
 *
 * @framework: Ksike
 * @package: dir
 * @subpackage: proxy
 * @version: 0.1

 * @escription: Dir es una libreria que implementa una abstracion para el trabajo con directorios y archivos
 * @authors: ing. Antonio Membrides Espinosa
 * @making Date: 02/06/2010
 * @update Date: 01/07/2012
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\package\dir\proxy;
use Ksike\ksl\base\helpers\Assist;
class Dir
{
	public function is_dir($dirname)
	{
		$ignore = array ('.', '..', '.svn');
		if(!in_array($dirname, $ignore)) return true;
		return false;			
	}

	public function is_php($filename)
	{
		$php = stristr($filename, KCL_EXT);
		$tmp = stristr($filename, KCL_NEXT);
		if($php && !$tmp) return true;
		return false;
	}

	public function scan($path, $mode="-i", $caller=false, $params=false, $onfind="onFind", $onfinish="onFinish")
	{
		if(file_exists($path)){
			if(!$caller) $caller= Assist::whoCallme();
			$out = false;
			$lst = array("cmd"=>"in", "sys"=>array(), "file"=>array(), "dir"=>array());
			$handle = opendir($path);
			if($handle){
			        while (($lst["cmd"]!="exit") && ($i = readdir($handle))) if(self::is_dir($i)){	
					if(is_dir($path.$i)) $key = "dir";
					else $key = "file";
					$this->exec($caller, $onfind, $lst, $path, $params, $i, $key);
					$lst[$key][] = $i;
					if($key=="dir" && $mode=="-r"){
						$tmp = $this->scan($path.$i."/", $mode, $caller, $params, $onfind, false);
						foreach($tmp as $k=>$e){
							if($k=="sys") $lst[$k][$i] = $e;
							else if($k!="cmd"){
								$lst[$k] = array_merge($lst[$k], $e);
							}
						}
					}else $lst["sys"][$i] = $key;
				}
			    closedir($handle);
				$out = $onfinish ? $this->exec($caller, $onfinish, $lst, $path, $params) : 0;
			}
			return $out ? $out : $lst;
		}
	}

	public function find($item, $dir, $type="", $mode="-r", $caller=false, $onfind="onFind", $onfinish="onFinish"){
		return $this->scan($dir, $this, $mode, array(
			"item"=>$item,
			"type"=>$type,
			"caller"=>$caller,
			"onfind"=>$onfind,
			"onfinish"=>$onfinish,
		));
	}

	protected function onFind(&$lst, &$path, &$params, $item, $type){
		if(!isset($lst["found"])) $lst["found"] = array();  
		if($this->cmp($params["item"], $item, $params["type"])){
			if($params["type"]=="strict") $lst["cmd"] = "exit";
			$lst["found"][] = $path.$item;
			$this->exec($params["caller"], $params["onfind"], $lst, $path, $params, $item, $type);
		}
	}
	
	protected function onFinish(&$lst, &$path, &$params){
		$out = $this->exec($params["caller"], $params["onfinish"], $lst, $path, $params);
		return $out ? $out : isset($lst["find"]) ? $lst["find"] : $lst;
	}

	protected function cmp($str1, $str2, $type="strict")
	{
		if($type == "strict"){
			if(strcmp( $str1, $str2 )==0 ) return true;
		}else{
			$com = ($type == "sstrict") ? "\b" : $type;
			if (preg_match("/$com".$str1."$com/i", $str2)) return true;
		}return false;
	}

	protected function exec($caller, $action, &$lst, &$path, &$params, $item=false, $type=false)
	{
		if(method_exists($caller, $action)){
			if(is_string($caller)) return $caller::$action($lst, $path, $params, $item, $type);
			else return $caller->{$action}($lst, $path, $params, $item, $type);
		}
	}
}