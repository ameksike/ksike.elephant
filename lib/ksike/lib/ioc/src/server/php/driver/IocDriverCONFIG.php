<?php
/**
 *
 * @framework: Ksike
 * @package: IOC
 * @subpackage: driver
 * @version: 0.1

 * @escription: IOC es una libreria que implementa la publicacion de archivos
 * @authors: ing. Antonio Membrides Espinosa
 * @making Date: 22/08/2011
 * @update Date: 24/08/2011
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\package\ioc\driver;
use Ksike\ksl\base\helpers\Loader;
use Ksike\ksl\base\helpers\Router;
use Ksike\ksl\package\ioc\base\IOCDriver;
class IocDriverCONFIG extends IOCDriver
{
	public function factory($option)
	{
		if(!isset($option["obj"])){
			$point = $option["point"];
			$path = ($point!="none") ? Router::this($point).KCL_CONFIG : $option["path"] ;
			$option["obj"] = Loader::this()->cfg($path, $option["file"], "none");
		}return $option["obj"];
	}
}
