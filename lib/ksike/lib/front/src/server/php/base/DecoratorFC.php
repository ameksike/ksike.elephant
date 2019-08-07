<?php
/**
 *
 * @framework: Ksike
 * @package: front
 * @subpackage: base
 * @version: 0.1

 * @description: FrontController es una libreria para controlar la llamada de una accion para determinado modulo 
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 09/07/2011
 * @update-Date: 20/08/2011
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\package\front\base;
class DecoratorFC extends FrontController
{
	protected $front;
	public function __construct(FrontController $front=null) 
	{
		$this->front = $front;
	}
	protected function send(){
		 $this->front->send(); 
	}
	protected function save($value, $mod=KCL_MAIN, $action="do"){ 
		$this->front->save($value, $mod, $action);
	}
}
