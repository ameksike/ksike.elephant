<?php
/**
 *
 * @framework: Ksike
 * @package: out
 * @subpackage: driver
 * @version: 0.1

 * @description: ConfigDriverPHP es una libreria para el trabajo con ...
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 15/06/2010
 * @update-Date: 15/06/2010
 * @license: GPL v2
 *
 */
namespace Ksike\ksl\package\out\driver;
use Ksike\ksl\package\out\base\OutDriver;
class OutDriverIMG extends OutDriver
{
	public function __construct($option="png") 
	{ 
		parent::__construct($option); 
	}

	public function getOut($data)
	{
		$this->buildHead("image/".$this->option);
	}
}
