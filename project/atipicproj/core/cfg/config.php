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
	unset ($config);
	$config["router"]["plugins"] = 'plugins/';
	$config["router"]["lib"][] 	= 'lib/'; 
	$config["router"]["lib"][] 	= '../../lib/';
	
	$config["router"]["request"]["key"]["controller"] 	= 'TesCon';
	$config["router"]["request"]["key"]["action"] 		= 'index';
	$config["router"]["request"]["key"]["params"] 		= '';
	$config["router"]["request"]["key"]["outFormat"] 	= 'html';
	$config["router"]["request"]["key"]["outInfo"] 		= 'void';
	$config["router"]["request"]["key"]["outOption"] 	= 'none';
	$config["router"]["request"]["url"]["pattern"]		= 'controller/action/params/outFormat/outInfo/outOption';	

	$config["router"]["request"]["alias"]["web"]["url"]["pattern"]		= 'proj/controller/action/params/outFormat/outInfo/outOption';
	$config["router"]["request"]["alias"]["web"]["key"]["controller"] 	= 'TesCon';
	$config["router"]["request"]["alias"]["web"]["key"]["action"] 		= 'index';
	$config["router"]["request"]["alias"]["web"]["key"]["outFormat"] 	= 'json';
	$config["router"]["request"]["alias"]["web"]["key"]["outInfo"] 		= 'void';
	$config["router"]["request"]["alias"]["web"]["key"]["outOption"] 	= 'none';
	
	$config["router"]["request"]["alias"]["ins"]["url"]["pattern"]		= 'params:name/params:age/params:sex/outFormat';
	$config["router"]["request"]["alias"]["ins"]["key"]["controller"] 	= 'TesIn';
	$config["router"]["request"]["alias"]["ins"]["key"]["action"] 		= 'requestPrettyAlias';
	$config["router"]["request"]["alias"]["ins"]["key"]["params"]["id"]	= 'tusa';
	$config["router"]["request"]["alias"]["ins"]["key"]["outFormat"] 	= 'json';
	$config["router"]["request"]["alias"]["ins"]["key"]["outInfo"] 		= 'void';
	$config["router"]["request"]["alias"]["ins"]["key"]["outOption"] 	= 'none';

	$config["loader"]["cfg"]["load"] = "auto";
	$config["loader"]["filter"]["iface"]["Module"][] 	= 'Security';
	$config["loader"]["filter"]["iface"]["Module"][]   	= 'Error';
	$config["loader"]["filter"]["control"]["Module"][] 	= 'Primal';
	$config["loader"]["filter"]["control"]["Main"][]   	= 'App';
	$config["loader"]["filter"]["control"]["Plugin"][] 	= 'Plugin';
	$config["loader"]["filter"]["iface"]["TesIn"][] 	= 'Loader';

	$config["loader"]["package"]["out"]["mod"]["proxy"] 		= 'Out';
	$config["loader"]["package"]["out"]["cfg"]["driver"][] 		= 'html';
	$config["loader"]["package"]["out"]["cfg"]["driver"][] 		= 'json';
	$config["loader"]["package"]["out"]["cfg"]["driver"][] 		= 'img';
	$config["loader"]["package"]["out"]["cfg"]["driver"][] 		= 'xml';
	$config["loader"]["package"]["out"]["mod"]["base"][] 		= 'OutDriver';
	$config["loader"]["package"]["out"]["cfg"]["type"] 		= "object";
	$config["loader"]["package"]["out"]["cfg"]["load"] 		= "manual";

	$config["loader"]["package"]["config"]["mod"]["proxy"] 		= 'Config';
	$config["loader"]["package"]["config"]["cfg"]["driver"][] 	= 'php';
	$config["loader"]["package"]["config"]["cfg"]["driver"][] 	= 'json';
	$config["loader"]["package"]["config"]["cfg"]["driver"][] 	= 'xml';
	$config["loader"]["package"]["config"]["cfg"]["driver"][] 	= 'ini';
	$config["loader"]["package"]["config"]["mod"]["base"][] 		= 'ConfigDriver';
	$config["loader"]["package"]["config"]["cfg"]["type"] 		= "object";
	$config["loader"]["package"]["config"]["cfg"]["load"] 		= "manual";
	$config["loader"]["package"]["config"]["cfg"]["order"][] 		= "php";
	$config["loader"]["package"]["config"]["cfg"]["order"][] 		= "xml";
	$config["loader"]["package"]["config"]["cfg"]["order"][]		= "ini";
	$config["loader"]["package"]["config"]["cfg"]["order"][] 		= "json";

	$config["loader"]["package"]["front"]["mod"]["proxy"] 		= 'ProxyFC';
	$config["loader"]["package"]["front"]["mod"]["control"] 		= 'OrdinaryFC';
	$config["loader"]["package"]["front"]["mod"]["base"][] 		= 'FrontController';
	$config["loader"]["package"]["front"]["cfg"]["type"] 		= "object";
	$config["loader"]["package"]["front"]["cfg"]["load"] 		= "auto";

	$config["loader"]["package"]["ioc"]["mod"]["proxy"] 		= 'IOC';
	$config["loader"]["package"]["ioc"]["cfg"]["driver"][] 		= 'class';
	$config["loader"]["package"]["ioc"]["cfg"]["driver"][] 		= 'object';
	$config["loader"]["package"]["ioc"]["cfg"]["driver"][] 		= 'config';
	$config["loader"]["package"]["ioc"]["cfg"]["driver"][] 		= 'driver';
	$config["loader"]["package"]["ioc"]["cfg"]["driver"][] 		= 'package';
	$config["loader"]["package"]["ioc"]["mod"]["base"][] 		= 'IOCDriver';
	$config["loader"]["package"]["ioc"]["cfg"]["type"] 		= "object";
	$config["loader"]["package"]["ioc"]["cfg"]["load"] 		= "manual";
	return $config;
