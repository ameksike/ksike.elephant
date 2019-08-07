<?php
/**
 *
 * @framework: Ksike
 * @package: cfg
 * @subpackage: config
 * @version: 0.1

 * @description: Este es el cargador inicial que rige el comportamiento de un proyecto generico
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 01/06/2010
 * @update-Date: 01/09/2010
 * @license: GPL v3
 *
 */

	$config["extends"] 		= null;
	$config["project"] 		= null; 
	$config["controller"] 	= 'Main';
	$config["action"] 		= 'index';
	$config["params"] 		= null;
	$config["outFormat"] 	= 'html';
	$config["outInfo"] 		= null;
	$config["outOption"] 	= null;
	$config["response"] 	= null;
	

	$config["lib"]["request"]["default"]["key"]["proj"] 		= false; 
	$config["lib"]["request"]["default"]["key"]["controller"] 	= 'Main';
	$config["lib"]["request"]["default"]["key"]["action"] 		= 'index';
	$config["lib"]["request"]["default"]["key"]["params"] 		= '';
	$config["lib"]["request"]["default"]["key"]["outFormat"] 	= 'html';
	$config["lib"]["request"]["default"]["key"]["outInfo"] 		= 'void';
	$config["lib"]["request"]["default"]["key"]["outOption"] 	= 'none';
	$config["lib"]["request"]["default"]["url"]["pattern"]		= 'controller/action/params/outFormat/outInfo/outOption';

	$config["lib"]["request"]["web"]["url"]["pattern"]		= 'proj/controller/action/params/outFormat/outInfo/outOption';	
	$config["lib"]["request"]["web"]["key"]["controller"] 	= 'Main';
	$config["lib"]["request"]["web"]["key"]["action"] 		= 'index';
	$config["lib"]["request"]["web"]["key"]["outFormat"] 	= 'js';
	$config["lib"]["request"]["web"]["key"]["outInfo"] 		= 'void';
	$config["lib"]["request"]["web"]["key"]["outOption"] 	= 'none';
	$config["lib"]["request"]["web"]["key"]["proj"] 		= 'atipic';

	$config["lib"]["request"]["publisher"]["url"]["pattern"]	= 'params:type/outFormat';
	$config["lib"]["request"]["publisher"]["key"]["controller"]	= 'Main';
	$config["lib"]["request"]["publisher"]["key"]["action"] 	= 'contents';
	$config["lib"]["request"]["publisher"]["key"]["outFormat"] 	= 'js';
	$config["lib"]["request"]["publisher"]["key"]["outInfo"] 	= 'void';
	$config["lib"]["request"]["publisher"]["key"]["outOption"] 	= 'none';
	//...........................................................
	$config["lib"]["router"]["app"] 	= 'app/';
	$config["lib"]["router"]["plugins"]	= 'plugins/';
	$config["lib"]["router"]["lib"]	= 'lib/';
	$config["lib"]["router"]["web"] 	= '';	
	//...........................................................
	$config["lib"]["cfg"]["load"]					= "auto";
	$config["lib"]["filter"]["iface"]["Module"][] 	= 'Security';
	$config["lib"]["filter"]["iface"]["Module"][]   	= 'Error';
	$config["lib"]["filter"]["control"]["Module"][] 	= 'Primal';
	$config["lib"]["filter"]["control"]["Main"][]   	= 'App';
	$config["lib"]["filter"]["control"]["Plugin"][] 	= 'Plugin';
	$config["lib"]["filter"]["resource"]["Main"][]   = 'Linker';
	$config["lib"]["filter"]["decorate"]["Main"][]   = 'Linker';
	$config["lib"]["filter"]["decorate"]["Main"][]   = 'ModControl';
	$config["lib"]["filter"]["decorate"]["Main"][]   = 'Publisher';
	//...........................................................
	$config["lib"]["config"]["mod"]["proxy"] 		= 'Config';
	$config["lib"]["config"]["cfg"]["driver"][] 	= 'php';
	$config["lib"]["config"]["cfg"]["driver"][] 	= 'json';
	$config["lib"]["config"]["cfg"]["driver"][] 	= 'xml';
	$config["lib"]["config"]["cfg"]["driver"][] 	= 'ini';
	$config["lib"]["config"]["mod"]["base"][] 	= 'ConfigDriver';
	$config["lib"]["config"]["cfg"]["type"] 		= "object";
	$config["lib"]["config"]["cfg"]["load"] 		= "manual";
	$config["lib"]["config"]["cfg"]["order"][] 	= "php";
	$config["lib"]["config"]["cfg"]["order"][] 	= "xml";
	$config["lib"]["config"]["cfg"]["order"][] 	= "ini";
	$config["lib"]["config"]["cfg"]["order"][] 	= "json";

	$config["lib"]["log"]["mod"]["proxy"] 		= 'Log';
	$config["lib"]["log"]["cfg"]["load"] 		= "manual";
	$config["lib"]["log"]["cfg"]["type"] 		= "object";
	$config["lib"]["log"]["cfg"]["format"]['@<'] 	= '"';
	$config["lib"]["log"]["cfg"]["format"]['@>'] 	= '"';
	$config["lib"]["log"]["cfg"]["format"]['#<']  	= ': "';
	$config["lib"]["log"]["cfg"]["format"]['#>'] 	= '"';
	$config["lib"]["log"]["cfg"]["format"]['|'] 	= ', ';
	$config["lib"]["log"]["cfg"]["format"]['>'] 	= '},';
	$config["lib"]["log"]["cfg"]["dateFormat"]  	= 'Y/m/d H:i:s';
	$config["lib"]["log"]["cfg"]["ext"] 		= '.log';
	
	$config["lib"]["session"]["mod"]["proxy"] 	= 'ProxySession';
	$config["lib"]["session"]["cfg"]["load"] 		= "manual";
	$config["lib"]["session"]["cfg"]["type"] 		= "object";

	$config["lib"]["dir"]["mod"]["proxy"] 		= 'Dir';
	$config["lib"]["dir"]["cfg"]["load"] 		= "manual";
	$config["lib"]["dir"]["cfg"]["type"] 		= "object";

	$config["lib"]["out"]["mod"]["proxy"] 		= 'Out';
	$config["lib"]["out"]["cfg"]["driver"][] 		= 'html';
	$config["lib"]["out"]["cfg"]["driver"][] 		= 'json';
	$config["lib"]["out"]["cfg"]["driver"][] 		= 'img';
	$config["lib"]["out"]["cfg"]["driver"][] 		= 'xml';
	$config["lib"]["out"]["cfg"]["driver"][] 		= 'js';
	$config["lib"]["out"]["mod"]["base"][] 		= 'OutDriver';
	$config["lib"]["out"]["cfg"]["type"] 		= "object";
	$config["lib"]["out"]["cfg"]["load"] 		= "manual";

	$config["lib"]["ioc"]["mod"]["proxy"] 		= 'IOC';
	$config["lib"]["ioc"]["cfg"]["driver"][] 		= 'class';
	$config["lib"]["ioc"]["cfg"]["driver"][] 		= 'object';
	$config["lib"]["ioc"]["cfg"]["driver"][] 		= 'config';
	$config["lib"]["ioc"]["cfg"]["driver"][] 		= 'driver';
	$config["lib"]["ioc"]["cfg"]["driver"][] 		= 'package';
	$config["lib"]["ioc"]["mod"]["base"][] 		= 'IOCDriver';
	$config["lib"]["ioc"]["cfg"]["type"] 		= "object";
	$config["lib"]["ioc"]["cfg"]["load"] 		= "manual";

	$config["lib"]["front"]["mod"]["proxy"] 		= 'ProxyFC';
	$config["lib"]["front"]["mod"]["control"] 	= 'OrdinaryFC';
	$config["lib"]["front"]["mod"]["decorator"][] 	= 'SecureDCF';
	$config["lib"]["front"]["mod"]["decorator"][] 	= 'LinkerDFC';
	$config["lib"]["front"]["mod"]["decorator"][] 	= 'FunnerDFC';
	$config["lib"]["front"]["mod"]["base"][] 		= 'FrontController';
	$config["lib"]["front"]["mod"]["base"][] 		= 'DecoratorFC';
	$config["lib"]["front"]["cfg"]["type"] 		= "object";
	$config["lib"]["front"]["cfg"]["load"] 		= "auto";

	$config["lib"]["error"]["mod"]["proxy"] 		= 'Error';
	$config["lib"]["error"]["mod"]["control"][] 	= 'BugHandler';
	$config["lib"]["error"]["mod"]["control"][] 	= 'ExceptHandler';
	$config["lib"]["error"]["mod"]["base"][] 		= 'ErrorHandler';
	$config["lib"]["error"]["cfg"]["load"] 		= "auto";
	$config["lib"]["error"]["cfg"]["type"] 		= "object";
	$config["lib"]["error"]["cfg"]["bug"][E_ERROR] 			= array('name'=>'E_ERROR', 		'desc'=>'Error');
	$config["lib"]["error"]["cfg"]["bug"][E_WARNING] 			= array('name'=>'E_WARNING', 		'desc'=>'Advertencia');
	$config["lib"]["error"]["cfg"]["bug"][E_PARSE] 			= array('name'=>'E_PARSE', 		'desc'=>'Error de Intérprete');
	$config["lib"]["error"]["cfg"]["bug"][E_NOTICE] 			= array('name'=>'E_NOTICE', 		'desc'=>'Anotación');
	$config["lib"]["error"]["cfg"]["bug"][E_CORE_ERROR] 		= array('name'=>'E_CORE_ERROR', 	'desc'=>'Error de Núcleo');
	$config["lib"]["error"]["cfg"]["bug"][E_CORE_WARNING] 		= array('name'=>'E_CORE_WARNING', 	'desc'=>'Advertencia de Núcleo');
	$config["lib"]["error"]["cfg"]["bug"][E_COMPILE_ERROR] 		= array('name'=>'E_COMPILE_ERROR',	'desc'=>'Error de Compilación');
	$config["lib"]["error"]["cfg"]["bug"][E_COMPILE_WARNING] 		= array('name'=>'E_COMPILE_WARNING', 	'desc'=>'Advertencia de Compilación');
	$config["lib"]["error"]["cfg"]["bug"][E_STRICT] 			= array('name'=>'E_STRICT', 		'desc'=>'Anotación de tiempo de ejecución');
	$config["lib"]["error"]["cfg"]["bug"][E_USER_ERROR] 		= array('name'=>'E_USER_ERROR', 	'desc'=>'Error de Usuario');
	$config["lib"]["error"]["cfg"]["bug"][E_USER_WARNING] 		= array('name'=>'E_USER_WARNING', 	'desc'=>'Advertencia de Usuario');
	$config["lib"]["error"]["cfg"]["bug"][E_USER_NOTICE] 		= array('name'=>'E_USER_NOTICE', 	'desc'=>'Anotación de Usuario');
	return $config;
