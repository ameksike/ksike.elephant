<?php
/**
 *
 * @framework: Ksike
 * @package: front
 * @subpackage: proxy
 * @version: 0.1

 * @description: ProxyFC es una libreria para ...
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 09/07/2011
 * @update-Date: 20/08/2011
 * @license: GPL v3
 *
 */
namespace Ksike\lib\front\src\server\php;
use Ksike\ksl\package\front\base\FrontController;
use Ksike\ksl\base\patterns\Factory;
class Main extends FrontController
{
	protected $front;
	protected $ns;
	protected $option;
	public function __construct($option=false){
		$this->option = $option;
		$this->ns =  str_replace("proxy","", __NAMESPACE__);
	}

	public function dispatch($controller=KCL_MAIN, $action="in", $params=null, $certificate=null)
	{
		$this->front->dispatch($controller, $action, $params, $certificate);
	}

	public function __get($key)
	{
		return $this->front->$key;
	}

	public function __set($key, $value)
	{
		$this->front->$key = $value;
	}

	protected function decorate($lst)
	{
		if($lst)foreach($lst as $i) $this->front = new $i($this->front);
	}

	public function build($outFormat="json", $outOption="", $outInfo="embebed")
	{
		$hand = $this->ns."control\\".$this->option["mod"]["control"];
		$this->front = new $hand($outFormat, $outOption, $outInfo);
		if(isset($this->option["mod"]["decorator"])) 
			Factory::decorate($this->option["mod"]["decorator"], $this->front, $this->ns."decorator\\");
	}
}
