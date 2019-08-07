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
	$config["router"]["plugins"][] 	= 'plugins/';
	$config["router"]["plugins"][] 	= '../lightprojec/plugins/';
	$config["router"]["plugins"][] 	= '../geomobile/plugins/';
	$config["router"]["lib"][] 	= '../../lib/'; 
	$config["router"]["lib"][] 	= 'lib/'; 
	$config["router"]["app"] 	= 'app/';

	
	$config["router"]["request"]["key"]["proj"] 		= false; 
	$config["router"]["request"]["key"]["controller"] 	= 'Main';
	$config["router"]["request"]["key"]["action"] 		= 'index';
	$config["router"]["request"]["key"]["params"] 		= '';
	$config["router"]["request"]["key"]["outFormat"] 	= 'html';
	$config["router"]["request"]["key"]["outInfo"] 		= 'void';
	$config["router"]["request"]["key"]["outOption"] 	= 'none';
	$config["router"]["request"]["url"]["pattern"]		= 'controller/action/params/outFormat/outInfo/outOption';
	
	$config["router"]["request"]["alias"]["ins"]["url"]["pattern"]		= 'params:name/params:age/params:sex/outFormat';
	$config["router"]["request"]["alias"]["ins"]["key"]["controller"] 	= 'TesIn';
	$config["router"]["request"]["alias"]["ins"]["key"]["action"] 		= 'requestPrettyAlias';
	$config["router"]["request"]["alias"]["ins"]["key"]["params"]["id"]	= 'tusa';
	$config["router"]["request"]["alias"]["ins"]["key"]["outFormat"] 	= 'json';
	$config["router"]["request"]["alias"]["ins"]["key"]["outInfo"] 		= 'void';
	$config["router"]["request"]["alias"]["ins"]["key"]["outOption"] 	= 'none';
	
	$config["router"]["request"]["alias"]["web"]["url"]["pattern"]		= 'proj/controller/action/params/outFormat/outInfo/outOption';	
	$config["router"]["request"]["alias"]["web"]["key"]["controller"] 	= 'Main';
	$config["router"]["request"]["alias"]["web"]["key"]["action"] 		= 'index';
	$config["router"]["request"]["alias"]["web"]["key"]["outFormat"] 	= 'js';
	$config["router"]["request"]["alias"]["web"]["key"]["outInfo"] 		= 'void';
	$config["router"]["request"]["alias"]["web"]["key"]["outOption"] 	= 'none';
	$config["router"]["request"]["alias"]["web"]["key"]["proj"] 		= 'atipic';
	return $config;
