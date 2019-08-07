<?php
	$config["mod"]["proxy"] 	= 'Out';
	$config["mod"]["base"][] 	= 'OutDriver';
	$config["cfg"]["driver"][] 	= 'html';
	$config["cfg"]["driver"][] 	= 'json';
	$config["cfg"]["driver"][] 	= 'img';
	$config["cfg"]["driver"][] 	= 'xml';
	$config["cfg"]["type"] 		= "object";
	$config["cfg"]["load"] 		= "manual";
	
	return $config;