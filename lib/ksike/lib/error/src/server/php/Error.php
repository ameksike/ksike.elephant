<?php
/**
 *
 * @framework: Ksike
 * @package: error
 * @subpackage: proxy
 * @version: 0.1

 * @description: ErrorHandler es una libreria para el trabajo con 
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 08/09/2010
 * @update-Date: 08/09/2010
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\package\error\proxy;
class Error
{
	static $type = "object";
	public function __construct($option){
		foreach($option["mod"]["control"] as $i){
			$i = "Ksike\ksl\\package\\error\\control\\".$i;
			$i::on($option["cfg"]);
		} 
	}

	public function supply($catcher, $control)
	{
		$control = "Ksike\ksl\\package\\error\\control\\".$control;
		$control::supply($catcher);
	}
}
