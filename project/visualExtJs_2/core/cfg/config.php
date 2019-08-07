<?php
/**
 *
 * $framework: Ksike
 * $package: Core
 * $subpackage: config
 * $version: 0.1

 * $description: Este es el cargador inicial para todos los modulos del framework Ksike
 * $authors: ing. Antonio Membrides Espinosa
 * $making-Date: 01/06/2010
 * $update-Date: 01/09/2010
 * $license: GPL v3
 *
 */
	unset ($config);
	$config['router']['plugins'] 	= 'plugins/';
	$config['router']['lib'] 	= 'lib/';
	$config['router']['app'] 	= 'app/';
	return $config;
?>
