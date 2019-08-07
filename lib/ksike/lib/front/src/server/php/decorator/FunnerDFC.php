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
use Ksike\ksl\package\front\base\DecoratorFC;
class FunnerDFC  extends DecoratorFC
{
	protected function doAccess($controller, $action, $params, $certificate=null)
	{
		$params = ($out = $this->front->doAccess(KCL_MAIN, "in", $params, $certificate)) ? $out : $params;
		$params = ($out = $this->front->doAccess($controller, $action, $params, $certificate)) ? $out : $params;
		$this->front->doAccess(KCL_MAIN, "out", $params, $certificate);
		return $params;
	}
}
