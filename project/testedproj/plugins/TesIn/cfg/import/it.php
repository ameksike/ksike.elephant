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
	$config["import"]["router"] = "mst";
	$config["import"]["ins"]    = "info";
	$config["tim"]["app"] 					= 'sasasasas/app/';
	$config["tim"]["plugins"] 				= 'plugins/';
	$config["tim"]["lib"]					= 'lib/';
	$config["tim"]["web"] 					= '';
	$config["tim"]["request"]["key"]["proj"] 		= false; 
	$config["tim"]["request"]["key"]["controller"] 		= 'Main';
	$config["tim"]["request"]["key"]["action"] 		= 'index';
	$config["tim"]["request"]["key"]["params"] 		= '';
	return $config;
