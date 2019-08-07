<?php
/**
 *
 * @framework: Ksike
 * @package: front
 * @subpackage: decorator
 * @version: 0.1

 * @description: FrontController es una libreria para controlar la llamada de una accion para determinado modulo 
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 09/07/2011
 * @update-Date: 20/08/2011
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\package\front\decorator;
use Ksike\ksl\base\handlers\Handler;
use Ksike\ksl\package\front\base\DecoratorFC;
class LinkerDFC  extends DecoratorFC
{
	protected function doAccess($controller, $action, $params, $certificate=null)
	{
		$this->doAtCondition($controller, $action, $params, $certificate, "getPrecondition");
		$params = ($out=$this->front->doAccess($controller, $action, $params, $certificate)) ? $out : $params;
		$this->doAtCondition($controller, $action, $params, $certificate, "getPoscondition");
		return $params;
	}

	protected function doAtCondition($controller, $action, $params, $certificate, $condition){
		$linker = Handler::module()->linker;
		if($linker){
			$lst = $linker->$condition($controller, $action);
			foreach($lst as $i) $this->doAccess($i['class'], $i['slot'], $params, $certificate);
		}
		//... falta la gestion del linker cuando el modulo es de tipo app
	}
}
