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
	$config["import"] 					    = "inst";
	$config["sxx"]["app"] 					= 'mstttapp/';
	$config["sxx"]["plugins"] 				= 'plugins/';
	$config["sxx"]["lib"]					= 'lib/';
	$config["sxx"]["web"] 					= '';
	$config["zxx"]["request"]["key"]["proj"] 		= false; 
	$config["zxx"]["request"]["key"]["controller"] 	= 'Main';
	$config["zxx"]["request"]["key"]["action"] 		= 'index';
	$config["zxx"]["request"]["key"]["params"] 		= '';
	$config["zxx"]["request"]["key"]["params"] 		= 'RR';
	return $config;
