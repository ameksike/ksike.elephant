<?php
/**
 *
 * @framework: Ksike
 * @package: Core
 * @subpackage: php
 * @version: 0.1

 * @description: Common Access Point of Ksike framework 
 * @authors: ing. Antonio Membrides Espinosa
 * @making: 01/06/2010
 * @update: 22/08/2011
 * @license: GPL v3
 *
 */
	$version = '5.3.0';
	if (version_compare(PHP_VERSION, $version, '<'))
	    echo "this framework require PHP version: <b>$version</b>, 
		  and current server has: <b> ".PHP_VERSION." </b> \n";

 	if(!defined('KCL_EXT'))	 	define('KCL_EXT',	'.php');
	if(!defined('KCL_NEXT')) 	define('KCL_NEXT',	'.php~');
	if(!defined('KCL_MAIN')) 	define('KCL_MAIN',	'Main');
	if(!defined('KCL_SRC')) 	define('KCL_SRC',	'core/src/php/');
	if(!defined('KCL_PROJ')) 	define('KCL_PROJ', 	getcwd()."/");
	if(!defined('KCL_WEB')) 	define('KCL_WEB', 	$_SERVER["SCRIPT_FILENAME"]);	
	if(!defined('KCL_CONFIG')) 	define('KCL_CONFIG',	'cfg/');
	if(!defined('KCL_LOG')) 	define('KCL_LOG',	'log/');
	if(!defined('KCL_INCLUDE')) 	define('KCL_INCLUDE',	'server/include/');
	if(!defined('KCL_PHPERROR')) 	define('KCL_ERROR',	'php_error/');
	if(!defined('KCL')) 		define('KCL', 		realpath('../../../../../../')."/");

	include 'src/server/php/Main'.KCL_EXT;
	$ksike = new Ksike\src\server\php\Main;
	$ksike->on();
