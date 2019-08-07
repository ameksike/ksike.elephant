<?php
/**
 *
 * @framework: Ksike
 * @package: front
 * @subpackage: control
 * @version: 0.1

 * @description: FrontController es una libreria para controlar la llamada de una accion para determinado modulo 
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 09/07/2011
 * @update-Date: 20/08/2011
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\package\front\control;
use Ksike\ksl\package\front\base\FrontController;
use Ksike\ksl\base\handlers\Handler;
use Ksike\ksl\base\bundles\Package;
class OrdinaryFC extends FrontController
{
	protected $out;
	public    $outInfo;
	public    $outFormat;
	public    $outOption;

	public function __construct($outFormat="json", $outOption="", $outInfo="embebed") 
	{
		$this->out  = array();
		$this->outInfo = $outInfo ? $outInfo : "embebed"; 
		$this->outFormat = $outFormat ? $outFormat : "json";
		$this->outOption = $outOption;
	}

	protected function doAccess($controller, $action, $params, $certificate=null)
	{
		$obj  = Handler::module($controller);
		if(is_string($params)) $params = json_decode($params, false);
		$params = ($out=$obj->preAction($params, $action)) ? $out : $params; 
		$result = $obj->$action($params);
		if($result == "_lost_") throw new \Exception("Controller << $controller >> or Action << $action >> was not found");
		$result = ($out=$obj->posAction($result, $action)) ? $out : $result;
		$this->save($result, $controller, $action);
		return $result;
	}

	protected function send()
	{
		$count = count($this->out);
		if($count > 0)
		{
			if(Package::this("out")){
				Package::this("out")->option["cfg"]["format"] = $this->outFormat; 
				Package::this("out")->option["cfg"]["option"] = $this->outOption;
				Package::this("out")->data = ($count == 1) ? $this->out[0] : $this->out;
				echo (Package::this("out"));
			}else foreach($this->out as $out) print_r($out);
		}
	}

	protected function save($value, $mod=KCL_MAIN, $action="do")
	{
		if($value) $this->out[] = ($this->outInfo=="embebed") ? $this->insertInfo($value, $mod, $action) : $value;
	}

	protected function insertInfo($value, $mod=KCL_MAIN, $action="do")
	{
		if(!is_array($value)) $value = array("data"=>$value);
		$value["_plugin"]=$mod;
		$value["_action"]=$action;
		return $value;
	}

	public function getOut()
	{
		return $this->out;
	}
}
