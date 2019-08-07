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
 * @update-Date: 02/06/2010
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\filter\decorate;
use Ksike\ksl\filter\control\Primal;
use Ksike\ksl\filter\resource\Linker as Link;
class Linker extends Primal
{
	public $linker;
	public function __construct($mate=false) 
	{
		parent::__construct($mate);
		$this->linker = new Link();
	}
}
