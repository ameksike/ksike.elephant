<?php

/**
 *
 * @framework: Ksike
 * @package: Tools
 * @subpackage: Develop
 * @version: 0.1 

 * @description: Dev_App es una libreria para el trabajo con ...
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 10/10/2010
 * @update-Date: 12/10/2010
 * @license: GPL v2
 *
 */
//include_once "DevStruct.php";
class Dev_App extends Dev_Struct {

    public function __construct($data, $tpl="defaultApp/", $projPath="../../", $optionalDir=array(
        "css",
        "img",
        "log",
        "common",
        "config",
        "include",
        "controllers",
        "views"
    ), $tplPath="templates/ksike/app/", $path="app/") {
        parent::__construct($data, $tplPath . $tpl, $projPath . $path, $optionalDir);

        $this->data["name"] = "Main";
        $this->dir = array("client/js", "server");
        $this->files = array(
            "client.tpl" => "client/js/Main.js",
            "server.tpl" => "server/Main.php"/*,
            "saveApp.php.tpl" => "../saveApp.php"*/
        );
    }

}

?>
