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
use Ksike\ksl\base\bundles\DriverManager;
use Ksike\ksl\base\helpers\Loader;
use Ksike\ksl\base\helpers\Router;
class IOC extends DriverManager
{
	protected $config;

	public function __construct($option=false){
		$this->loadConfig();
		parent::__construct($option);
	}

	public function __get($key){
		return $this->factory($key);
	}

	public function loadConfig($config=false)
	{		
		if($config) $this->config += $config;
		else $this->config = Loader::this()->cfg(Router::this("app").KCL_CONFIG, "ioc", "none");
	}

	protected function factory($key)
	{
		$obj = $this->getDriver($this->config[$key]["type"]);
		if($obj) return $obj->factory($this->config[$key]);
		else return $this->config[$key];
	}
}
