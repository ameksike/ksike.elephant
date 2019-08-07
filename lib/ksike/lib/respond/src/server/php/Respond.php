<?php
/**
 *
 * @framework: Ksike
 * @package: out
 * @subpackage: driver
 * @version: 0.1

 * @description: OutManager es una libreria para el trabajo con los formatos de exportacion de datos del controldor frontal...
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 16/06/2010
 * @update-Date: 24/08/2011
 * @license: GPL v2
 *
 */
namespace Ksike\ksl\package\out\proxy;
use Ksike\ksl\base\bundles\DriverManager;
class Respond extends DriverManager
{
	public $data;
	public $option;

	public function __construct($option=false) {
		parent::__construct($option);
		$this->data = "";
	}

	public function getOut($data=false)
	{
		$data = $data ? $data : $this->data;
		$obj = $this->getDriver($this->option["cfg"]["format"], $this->option["cfg"]["option"]);
		if($obj) return $obj->getOut($data);
		else $data;
	}

	public function __toString() {
		return $this->getOut();
	}
}
