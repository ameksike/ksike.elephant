<?php
	unset($config);

	$config["metas"]["type"] = "class";
	$config["metas"]["name"] = "Person";
	$config["metas"]["file"] = "Person";
	$config["metas"]["path"] = "server/elemes/";
	$config["metas"]["point"] = "app";
	$config["metas"]["action"] = "this";
	$config["metas"]["params"] = "metas";

	$config["users"]["type"] = "object";
	$config["users"]["name"] = "Person";
	$config["users"]["file"] = "Person";
	$config["users"]["path"] = "server/elemes/";
	$config["users"]["point"] = "app";
	$config["users"]["behavior"] = "singleton";
	$config["users"]["params"] = array("name"=>"tusa", "age"=>"12", "sex"=>"f");

	$config["agent"]["type"] = "class";
	$config["agent"]["name"] = "Manage";
	$config["agent"]["file"] = "Manage";
	$config["agent"]["path"] = "server/elemes/";
	$config["agent"]["point"] = "app";

	$config["tusas"]["type"] = "config";
	$config["tusas"]["file"] = "linker";
	$config["tusas"]["point"] = "app";

	$config["intim"]["type"] = "config";
	$config["intim"]["file"] = "config";
	$config["intim"]["point"] = "core";

	$config["getim"]["type"] = "config";
	$config["getim"]["file"] = "config";
	$config["getim"]["path"] = "/var/www/Ksike_v1.0/project/lightprojec/core/cfg/";
	$config["getim"]["point"] = "none";

	$config["mista"]["type"] = "driver";
	$config["mista"]["name"] = "File";
	$config["mista"]["params"][] = "index.php";

	$config["intro"]["type"] = "package";
	$config["intro"]["name"] = "config";
	
	$config["modAc"]["type"] = "module";
	$config["modAc"]["name"] = "TesDriv";
	$config["modAc"]["acction"] = "getFileByHelper";
	$config["modAc"]["params"]["name"] = "timp";
	
	$config["modss"]["type"] = "module";
	$config["modss"]["name"] = "TesDriv";	
	
	return $config;
?>
