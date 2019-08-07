<?php
/**
 *
 * @framework: Ksike
 * @package: config
 * @subpackage: driver
 * @version: 0.1

 * @description: ConfigDriverXML es una libreria para el trabajo con ...
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 15/06/2010
 * @update-Date: 15/06/2010
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\package\config\driver;
use Ksike\ksl\package\config\base\ConfigDriver;
class ConfigDriverINI extends ConfigDriver
{
	private $fileConf;
	public function __construct($path="") 
	{ 
		parent::__construct($path); 
		$this->fileConf = 0;
	}
	public function load($path=0, $force=0)
	{
		$path = $path ? $path : $this->file;
		if(!$this->fileConf || $force) $this->fileConf = parse_ini_file($path, true);
		return $this->fileConf;
	}
}
