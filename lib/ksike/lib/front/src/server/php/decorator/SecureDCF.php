<?php
/**
 *
 * @framework: Ksike
 * @package: front
 * @subpackage: decorator
 * @version: 0.1

 * @description: SecureDCF es una libreria para controlar la llamada de una accion para determinado modulo 
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 09/07/2011
 * @update-Date: 20/08/2011
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\package\front\decorator;
use Ksike\ksl\base\handlers\Handler;
use Ksike\ksl\package\front\base\DecoratorFC;
class SecureDCF  extends DecoratorFC
{
	public function doAccess($controller, $action, $params, $certificate=null)
	{
		$obj  = Handler::module($controller);
		$auth = true;
		if(method_exists($obj, 'accessAllow')) $auth = $obj->accessAllow($certificate, $action);
		if($auth)
		{
			$params = ($out=$this->front->doAccess($controller, $action, $params, $certificate)) ? $out : $params;
		} else if(method_exists($obj, 'accessRefuse')) $result = $obj->accessRefuse($certificate, $action);
		return $params;
	}
}
