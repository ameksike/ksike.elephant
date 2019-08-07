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
use Ksike\ksl\base\bundles\Package;
use Ksike\ksl\package\ioc\base\IOCDriver;
class IocDriverPACKAGE extends IOCDriver
{
	public function factory($option)
	{
		return Package::this($option["name"]);
	}
}
