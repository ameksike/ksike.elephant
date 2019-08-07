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
	$config["loader"]["filter"]["iface"]["Module"][] 	= 'Security';
	$config["loader"]["filter"]["iface"]["Module"][]   	= 'Error';
	$config["loader"]["filter"]["control"]["Module"][] 	= 'Primal';
	$config["loader"]["filter"]["control"]["Main"][]   	= 'App';
	$config["loader"]["filter"]["control"]["Plugin"][] 	= 'Plugin';
	$config["loader"]["filter"]["iface"]["TesIn"][] 	= 'Loader';
	$config["loader"]["filter"]["resource"]["TesIn"][] 	= 'Dir';
	$config["loader"]["filter"]["decorate"]["Main"][]   = 'TusaD';
	$config["loader"]["filter"]["decorate"]["Main"][]   = 'MegaD';
	return $config;