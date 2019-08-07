<?php
/**
 *
 * @framework: Ksike
 * @package: out
 * @subpackage: driver
 * @version: 0.1

 * @description: ConfigDriverJSON es una libreria para el trabajo con ...
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 15/06/2010
 * @update-Date: 20/12/2010
 * @license: GPL v2
 *
 */
namespace Ksike\ksl\package\out\driver;
use Ksike\ksl\package\out\base\OutDriver;
use Ksike\ksl\base\bundles\Driver;
class OutDriverXML extends OutDriver
{
	public function getOut($data=false)
	{
		if(!$data) return '';
		else return Driver::this('XML')->Array2XML($data);
	}
}
