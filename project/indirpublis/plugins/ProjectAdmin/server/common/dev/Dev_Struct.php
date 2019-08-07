<?php

/**
 *
 * @framework: Merma
 * @package: Tools
 * @subpackage: Develop
 * @version: 0.1 

 * @description: Dev_Struct es una libreria para el trabajo con ...
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 10/10/2010
 * @update-Date: 12/10/2010
 * @license: GPL v2
 *
 */
use Ksike\base\helpers\Assist as kcl;

//include_once "Dev_Manager.php";
//include_once "../hard/Hard_Manager.php";
class Dev_Struct implements Dev_Manager {

    public $extJS;
    public $extPHP;
    public $extTPL;
    public $data;
    public $optionalDir;
    protected $dir;
    protected $files;
    protected $proj;
    protected $tpl;
    protected $path;

    public function __construct($data, $tpl, $path, $optionalDir=null) {
        $this->extJS = "js";
        $this->extPHP = "php";
        $this->extTPL = "tpl";
        $this->data = $data;
        $this->path = $path;
        $this->tpl = $tpl;
        $this->proj = $proj;
        $this->dir = array();
        $this->files = array();
        $this->optionalDir = $optionalDir;
    }

    public function build() {
        $this->buildObligatoryDir();
        $this->buildOptionalDir($this->optionalDir);
        $this->buildObligatoryFiles();
        $this->copyDependency();
    }

    protected function buildObligatoryFiles() {

        foreach ($this->files as $tpl => $file)
            Hard_Manager::createFileFromTpl($this->tpl . $tpl, $this->path . $file, $this->data);
    }

    protected function buildObligatoryDir() {
        Hard_Manager::makeDir($this->path, $this->dir);
    }

    protected function buildOptionalDir($optionalDir) {
        if ($optionalDir)
            foreach ($optionalDir as $i)
                $this->makeOptionalDir($i, $this->path);
    }

    protected function makeOptionalDir($dir) {
        switch ($dir) {
            case 'plugins' : Hard_Manager::makeDir($this->path, "plugins/");
                break;
            case 'lib' : Hard_Manager::makeDir($this->path, "lib/");
                break;
            case 'tools' : Hard_Manager::makeDir($this->path, "tools/");
                break;
            case 'log' : Hard_Manager::makeDir($this->path, "log/");
                break;
            case 'include' : Hard_Manager::makeDir($this->path, "server/include");
                break;
            case 'cfg' : Hard_Manager::makeDir($this->path, "cfg/");
                break;
            case 'img' : Hard_Manager::makeDir($this->path, "client/img");
                break;
            case 'css' : Hard_Manager::makeDir($this->path, "client/css");
                break;
            case 'controllers' : Hard_Manager::makeDir($this->path, "client/js/controllers");
                break;
            case 'views' : Hard_Manager::makeDir($this->path, "client/js/views");
                break;
            case 'common' : Hard_Manager::makeDir($this->path, array("client/js/common", "server/common"));
                break;
        }
    }

    protected function copyDependency() {
        $list = $this->getConf("dependency");
        if ($list)
            foreach ($list as $Key => $i) {
                Hard_Manager::makeDir($this->path, $i);
                copy($this->tpl . "dependency/" . $Key, $this->path . $i . $Key);
            }
    }

    protected function getConf($id) {
        $driv = kcl::package("config");
        if (!$this->conf)
            $this->conf = $driv->loadFrom($this->tpl . "cfg/config.");
        return $this->conf[$id];
    }

}

?>
