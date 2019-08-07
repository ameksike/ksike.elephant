<?php
/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: messages
 * @version: 0.1

 * @description: FrontController es una libreria para controlar la llamada de una accion para determinado modulo 
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 09/07/2011
 * @update-Date: 20/08/2011
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\base\messages;
use Ksike\ksl\base\patterns\Singleton;
class Debuger extends Singleton
{
	public function tryOn($msg, $arg, $function, $class, $file){
		/*if($msg == "acces"){
			echo "<pre>";
			echo "$class::$function >> $msg ";
			print_r($arg); echo " <br> -------------------- <br> ";
		}*/
	}
}