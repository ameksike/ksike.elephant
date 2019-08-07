<?php

/**
 *
 * @framework: Merma
 * @package: Tools
 * @subpackage: Develop
 * @version: 0.1 

 * @description: Dev_Project es una libreria para el trabajo con ...
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 10/10/2010
 * @update-Date: 12/10/2010
 * @license: GPL v2
 *
 */
//include_once "Dev_App.php";
//include_once "Dev_Module.php";
//include_once "../hard/HardManager.php";

class Dev_Project extends Dev_Struct {

    private $app;
    private $plugins;

    public function __construct($data, $path="../../", $tpl="defaultProject/", $optionalDir=array(
        "lib",
        "tools",
        "core",
        "core/cfg",
        "plugins"
    ), $apptpl="../app/defaultApp/", $optionalDirApp=array(
        "css",
        "img",
        "log",
        "common",
        "cfg",
        "include"
    ), $tplPath="templates/ksike/project/") {
        //print_r(json_encode($optionalDir));//die;
        parent::__construct($data, $tplPath . $tpl, $path . $data["name"] . "/", $optionalDir);
        $this->dir = array(
            "app",
            "core",
            "core/cfg",
            
            //bhike project statements
            ".bhproj"
        );
        $this->files = array(
            "index.tpl" => "index.php",
            "init.js.tpl"  => "core/cfg/init.js",
            "config.php.tpl" => "core/cfg/config.php",
            
            //bhike project data 
            "inf/save.php.tpl" => ".bhproj/".$data['name'].".php",
            "inf/info.xml" => '.bhproj/info.xml'
        );
        $this->app = new Dev_App($data, $apptpl, $this->path, $optionalDirApp, $tplPath);
    }

    public function build() {
        parent::build();
        $this->app->build();
        if (count($this->plugins) > 0)
            foreach ($this->plugins as $i)
                $i->build();
    }

    public function addPugin($data, $tpl="defaultPlugin/", $optionalDir=null, $tplPath="templates/plugins/") {
        $this->plugins[] = new Dev_Module($data, $tpl, $this->path, $optionalDir, $tplPath);
    }

}

?>
