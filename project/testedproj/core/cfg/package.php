<?php
/**
 *
 * @framework: Ksike
 * @package: Core
 * @subpackage: config
 * @version: 0.1

 * @description: Este es el cargador inicial para todos los modulos del framework Merma
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 01/06/2010
 * @update-Date: 01/09/2010
 * @license: GPL v3
 *
 */
 	$config["loader"]["package"]["log"]["mod"]["proxy"] 		= 'Log';
	$config["loader"]["package"]["log"]["cfg"]["load"] 		    = "manual";
	$config["loader"]["package"]["log"]["cfg"]["type"] 		    = "object";
	$config["loader"]["package"]["log"]["cfg"]["format"]['@<'] 	= '"';
	$config["loader"]["package"]["log"]["cfg"]["format"]['@>'] 	= '"';
	$config["loader"]["package"]["log"]["cfg"]["format"]['#<']  = ': "';
	$config["loader"]["package"]["log"]["cfg"]["format"]['#>'] 	= '"';
	$config["loader"]["package"]["log"]["cfg"]["format"]['|'] 	= ', ';
	$config["loader"]["package"]["log"]["cfg"]["format"]['>'] 	= '},';
	$config["loader"]["package"]["log"]["cfg"]["dateFormat"]  	= 'Y/m/d H:i:s';
	$config["loader"]["package"]["log"]["cfg"]["ext"] 			= '.log';

	$config["loader"]["package"]["han"]["mod"]["proxy"] 		= 'Han';
	$config["loader"]["package"]["han"]["cfg"]["type"] 			= "object";
	$config["loader"]["package"]["han"]["cfg"]["load"] 			= "manual";
	
	$config["loader"]["package"]["dir"]["mod"]["proxy"] 		= 'Dir';
	$config["loader"]["package"]["dir"]["cfg"]["load"] 		    = "manual";
	$config["loader"]["package"]["dir"]["cfg"]["type"] 		    = "object";

	$config["loader"]["package"]["out"]["mod"]["proxy"] 		= 'Out';
	$config["loader"]["package"]["out"]["cfg"]["driver"][] 		= 'html';
	$config["loader"]["package"]["out"]["cfg"]["driver"][] 		= 'json';
	$config["loader"]["package"]["out"]["cfg"]["driver"][] 		= 'img';
	$config["loader"]["package"]["out"]["cfg"]["driver"][] 		= 'xml';
	$config["loader"]["package"]["out"]["mod"]["base"][] 		= 'OutDriver';
	$config["loader"]["package"]["out"]["cfg"]["type"] 			= "object";
	$config["loader"]["package"]["out"]["cfg"]["load"] 			= "manual";

	$config["loader"]["package"]["config"]["mod"]["proxy"] 		= 'Config';
	$config["loader"]["package"]["config"]["cfg"]["driver"][] 	= 'php';
	$config["loader"]["package"]["config"]["cfg"]["driver"][] 	= 'json';
	$config["loader"]["package"]["config"]["cfg"]["driver"][] 	= 'xml';
	$config["loader"]["package"]["config"]["cfg"]["driver"][] 	= 'ini';
	$config["loader"]["package"]["config"]["cfg"]["driver"][] 	= 'flow';
	$config["loader"]["package"]["config"]["mod"]["base"][] 	= 'ConfigDriver';
	$config["loader"]["package"]["config"]["cfg"]["type"] 		= "object";
	$config["loader"]["package"]["config"]["cfg"]["load"] 		= "manual";
	$config["loader"]["package"]["config"]["cfg"]["order"][] 	= "php";
	$config["loader"]["package"]["config"]["cfg"]["order"][] 	= "xml";
	$config["loader"]["package"]["config"]["cfg"]["order"][]	= "ini";
	$config["loader"]["package"]["config"]["cfg"]["order"][] 	= "json";
	$config["loader"]["package"]["config"]["cfg"]["order"][] 	= "flow";

	$config["loader"]["package"]["front"]["mod"]["proxy"] 		= 'ProxyFC';
	$config["loader"]["package"]["front"]["mod"]["control"] 	= 'OrdinaryFC';
	$config["loader"]["package"]["front"]["mod"]["base"][] 		= 'FrontController';
	$config["loader"]["package"]["front"]["cfg"]["type"] 		= "object";
	$config["loader"]["package"]["front"]["cfg"]["load"] 		= "auto";

	$config["loader"]["package"]["ioc"]["mod"]["proxy"] 		= 'IOC';
	$config["loader"]["package"]["ioc"]["cfg"]["driver"][] 		= 'class';
	$config["loader"]["package"]["ioc"]["cfg"]["driver"][] 		= 'object';
	$config["loader"]["package"]["ioc"]["cfg"]["driver"][] 		= 'config';
	$config["loader"]["package"]["ioc"]["cfg"]["driver"][] 		= 'driver';
	$config["loader"]["package"]["ioc"]["cfg"]["driver"][] 		= 'package';
	$config["loader"]["package"]["ioc"]["cfg"]["driver"][] 		= 'module';
	$config["loader"]["package"]["ioc"]["mod"]["base"][] 		= 'IOCDriver';
	$config["loader"]["package"]["ioc"]["cfg"]["type"] 			= "object";
	$config["loader"]["package"]["ioc"]["cfg"]["load"] 			= "manual";/**/
	
	$config["loader"]["package"]["error"]["mod"]["proxy"] 		= 'Error';
	$config["loader"]["package"]["error"]["mod"]["control"][] 	= 'BugHandler';
	$config["loader"]["package"]["error"]["mod"]["control"][] 	= 'ExceptHandler';
	$config["loader"]["package"]["error"]["mod"]["base"][] 		= 'ErrorHandler';
	$config["loader"]["package"]["error"]["cfg"]["load"] 		= "auto";
	$config["loader"]["package"]["error"]["cfg"]["type"] 		= "object";
	$config["loader"]["package"]["error"]["cfg"]["bug"][E_ERROR] 			= array('name'=>'E_ERROR', 		'desc'=>'Error');
	$config["loader"]["package"]["error"]["cfg"]["bug"][E_WARNING] 			= array('name'=>'E_WARNING', 		'desc'=>'Advertencia');
	$config["loader"]["package"]["error"]["cfg"]["bug"][E_PARSE] 			= array('name'=>'E_PARSE', 		'desc'=>'Error de Intérprete');
	$config["loader"]["package"]["error"]["cfg"]["bug"][E_NOTICE] 			= array('name'=>'E_NOTICE', 		'desc'=>'Anotación');
	$config["loader"]["package"]["error"]["cfg"]["bug"][E_CORE_ERROR] 		= array('name'=>'E_CORE_ERROR', 	'desc'=>'Error de Núcleo');
	$config["loader"]["package"]["error"]["cfg"]["bug"][E_CORE_WARNING] 		= array('name'=>'E_CORE_WARNING', 	'desc'=>'Advertencia de Núcleo');
	$config["loader"]["package"]["error"]["cfg"]["bug"][E_COMPILE_ERROR] 		= array('name'=>'E_COMPILE_ERROR',	'desc'=>'Error de Compilación');
	$config["loader"]["package"]["error"]["cfg"]["bug"][E_COMPILE_WARNING] 		= array('name'=>'E_COMPILE_WARNING', 	'desc'=>'Advertencia de Compilación');
	$config["loader"]["package"]["error"]["cfg"]["bug"][E_STRICT] 			= array('name'=>'E_STRICT', 		'desc'=>'Anotación de tiempo de ejecución');
	$config["loader"]["package"]["error"]["cfg"]["bug"][E_USER_ERROR] 		= array('name'=>'E_USER_ERROR', 	'desc'=>'Error de Usuario');
	$config["loader"]["package"]["error"]["cfg"]["bug"][E_USER_WARNING] 		= array('name'=>'E_USER_WARNING', 	'desc'=>'Advertencia de Usuario');
	$config["loader"]["package"]["error"]["cfg"]["bug"][E_USER_NOTICE] 		= array('name'=>'E_USER_NOTICE', 	'desc'=>'Anotación de Usuario');

	return $config;
