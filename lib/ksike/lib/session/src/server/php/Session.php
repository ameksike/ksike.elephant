<?php
/**
 *
 * @framework: Ksike
 * @package: session
 * @subpackage: proxy
 * @version: 0.1

 * @description: ProxyFC es una libreria para ...
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 09/07/2011
 * @update-Date: 20/08/2011
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\package\session\proxy;
class ProxySession
{
	static $type = "object"; //static
	public function __construct() {	
		session_start();
	}

	public function on()
	{
		session_start();
	}

	public function get($key, $obj=false)
	{
		if (isset($_SESSION[$key])){
			if(!$obj) $this->load($key);
			else $obj->load($key);
			return unserialize($_SESSION[$key]);
		} else return false;
	}

	public function save($key, $value)
	{
		$_SESSION[$key] = serialize($value);
	}

	public function load($key) {}
}
