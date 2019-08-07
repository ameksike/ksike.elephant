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
	$config["df"]["app"] 	= 'app/';
	$config["df"]["plugins"] 	= 'plugins/';
	$config["df"]["lib"]	= 'lib/';
	$config["df"]["web"] 	= '';
	$config["df"]["request"]["key"]["proj"] 		= false; 
	$config["df"]["request"]["key"]["controller"] 		= 'Main';
	$config["df"]["request"]["key"]["action"] 		= 'index';
	$config["df"]["request"]["key"]["params"] 		= '';
	//$config["tim"]["request"]["key"]["params"] 		= 'modificad';
	return $config;
