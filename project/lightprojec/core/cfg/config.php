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
	$config["router"]["plugins"] 	= 'project/lightprojec/plugins/';
	$config["router"]["plugins_a"] 	= 'plugins/';
	$config["router"]["lib_a"] 	= 'project/lightprojec/lib/'; 
	$config["router"]["app"] 	= 'project/lightprojec/app/';

	$config["loader"]["base"]["patterns"][]   		= 'Factory';
	$config["loader"]["base"]["patterns"][]   		= 'Singleton';
	$config["loader"]["cfg"]["load"]			= "manual";
	$config["loader"]["base"]["bundles"][]		 	= 'Bundles';
	//$config["loader"]["base"]["bundles"][]		= 'Driver';
	$config["loader"]["base"]["bundles"][]		 	= 'Package';
	$config["loader"]["base"]["handlers"][]   		= 'Handler';
	$config["loader"]["base"]["helpers"][] 			= 'Assist';
	//$config["loader"]["base"]["messages"][] 		= 'Log';

	$config["loader"]["filter"]["control"]["Module"][] 	= 'Primal';
	$config["loader"]["filter"]["control"]["Main"][]   	= 'App';
	$config["loader"]["filter"]["control"]["Plugin"][] 	= 'Plugin';

	$config["package"]["front"]["mod"]["proxy"] 		= 'UniqueFC';
	$config["package"]["front"]["cfg"]["type"] 		= "object";
	$config["package"]["front"]["cfg"]["load"] 		= "auto";
	
	/*$config["loader"]["base"]["bundles"][]			= 'DriverManager';
	$config["package"]["out"]["mod"]["proxy"] 		= 'Out';
	$config["package"]["out"]["mod"]["driver"][] 		= 'html';
	$config["package"]["out"]["mod"]["driver"][] 		= 'json';
	$config["package"]["out"]["mod"]["driver"][] 		= 'img';
	$config["package"]["out"]["mod"]["driver"][] 		= 'xml';
	$config["package"]["out"]["mod"]["base"][] 		= 'OutDriver';
	$config["package"]["out"]["cfg"]["type"] 		= "object";
	$config["package"]["out"]["cfg"]["load"] 		= "manual";*/

	return $config;
