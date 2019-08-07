<?php
/**
 *
 * @framework: Ksike
 * @package: front
 * @subpackage: base
 * @version: 0.1

 * @description: FrontController es una libreria para controlar la llamada de una accion para determinado modulo 
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 02/06/2010
 * @update-Date: 09/07/2011
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\package\front\base;
class FrontController
{
	public function dispatch($controller=KCL_MAIN, $action="in", $params=null, $certificate=null)
	{
		$this->doAccess($controller, $action, $params, $certificate);
		$this->send();
	}
	protected function doAccess($controller, $action, $params, $certificate=null){}
	protected function send(){}
	protected function save($value, $mod=KCL_MAIN, $action="do"){}
}
