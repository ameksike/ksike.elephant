<?php
/**
 *
 * @framework: Ksike
 * @package: filter
 * @subpackage: decorate
 * @version: 0.1 

 * @description: App es una libreria para el trabajo con ...
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 02/06/2010
 * @update-Date: 12/06/2010
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\filter\decorate;
use Ksike\ksl\base\handlers\Handler;
use Ksike\ksl\base\helpers\Router;
use Ksike\ksl\base\helpers\Loader;
use Ksike\ksl\base\bundles\Package;
use Ksike\ksl\filter\control\Primal;
class ModControl extends Primal
{

	public function onFind($lst, $path, $params, $item, $type){
		if($type=="dir" && $params) $this->call($params, $item);
	}

	public function onFinish($lst, $path)
	{
		return $lst["dir"];
	}

	public function loadModules($params=false) 
	{
		$conf = Loader::this()->cfg(Router::this("app").KCL_CONFIG, "config", "none");
		if(isset($conf['plugins'])){
			if($params) foreach($conf['plugins'] as $i) $this->call($params, $i);
			return array("plugins"=>$conf['plugins']);
		}
		return $this->search($params);
	}

	protected function search($params)
	{
		$path = Router::this()->plugins();
		if(is_string($path)) $out = Package::this("dir")->scan($path, "-i", $this, $params);
		else{
			$out = array();
			foreach($path as $i) $out = array_merge($out, Package::this("dir")->scan($i, "-i", $this, $params));
		} 
		return array("plugins"=>$out);
	}

	protected function call($params, $item)
	{
		$obj = Handler::module($item);
		call_user_func_array(array($obj, $params["action"]), $params["params"]);
	}

	protected function callthem($acction="index", $params=array()) {
		if(!is_array($params)) $params = array($params);
		$this->loadModules(array("action"=>$acction, "params"=>$params));
	}
}
