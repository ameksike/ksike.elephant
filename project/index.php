<?php
/**
 *
 * @framework: Ksike
 * @package: Core
 * @subpackage: php
 * @version: 0.1

 * @description: Script que implementa el controlador frontal del framework Ksike
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 09/07/2011
 * @update-Date: 09/07/2011
 * @license: GPL v3
 *
 */
	$project = "geomobile";
	define('KCL', 		realpath('../')."/");
	define('KCL_PROJ', 	realpath("$project/")."/");
	include KCL.'core/src/php/ksl/Front.php';
?>
