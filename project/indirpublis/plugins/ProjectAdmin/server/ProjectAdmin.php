<?php

use Ksike\ksl\filter\control\Plugin;
use Ksike\ksl\base\helpers\Assist as kassist;

class ProjectAdmin extends Plugin {
    /*
     * build a project fisicly
     */
    public function __construct() {
        kassist::loader("supply", new ProjLoader);
    }

    public function makeProject($params) {
        $date = date(DATE_RFC822);
        //$date = date(DATE_ATOM, mktime(date("h"), date("min"), date("s"),date("m")-1,date("d"),date("Y")));
        $params->proj->serial = md5($params->proj->name.'-'.$date);
        $params->proj->creation_date = $date;
        $path = kassist::router("this") . "server/";
        $myproj = new Dev_Project(
                        $this->objToArray($params->proj),
                        $params->proj->path,
                        $params->proj->tpl,
                        $params->proj->optionalDir,
                        $params->app->tpl,
                        $params->app->optionalDir,
                        $path . $params->proj->tplPath
        );

        //print_r(json_encode($params->proj->optionalDir));die;
        foreach ($params->plugins as $i) {
            $data = $this->objToArray($i->data);
            $myproj->addPugin($data, $i->tpl, $i->optionalDir, $path . $i->tplPath);
        }

        $myproj->build();

        return array(
            //"action"=>"makeProject",
            "success" => true,
            "name" => $params->proj->name,
            "pathPro" => $params->proj->path
        );
    }

    /* This section is for handeling trees and it has the asociated functions with it
     */

    public function treeGateway($params) {
        $typeOfNode = kassist::request("typeOfNode", "REQUEST");
        
        switch ($typeOfNode) {
            case 'category':
                return $this->getCategories($typeOfNode);
            case 'subcategory':
                return $this->getSubCategories();
            case 'folder':
                return $this->getFolderContent();
            case 'appSourceConfig':
                return $this->getAppSourceFolderConfig();
            default:
                return 0;
        }
    }

    public function getProjectInfo($params) {
        /* $objConfigManager = DriverManager::factory("ConfigManager");

          $projConfig = $objConfigManager->loadConfigFrom($params->path);
          $tmp = split('/', $params->path);
          //die(print_r($tmp));
          $projectPath = "";
          for ( $i = 0 ; $i < count($tmp)-2 ; $i++)
          $projectPath .= $tmp[$i]."/";

          $appConfig = $objConfigManager->loadConfigFrom($projectPath.'/'.$projConfig['vars']['projectName'].'/'."saveApp.");
          //print_r($projectPath)
          $projConfig['vars']['projectPath'] = $projectPath;

          return array(
          'data'=> array(
          'projectInfo'=>$projConfig,
          //'projectPath' =>$projectPath,
          'appInfo'=>$appConfig
          )
          ); */
        //
        $result = kassist::loader()->fileconf($params->path.'.bhproj/', "info", "none");
        $result['proj']['path'] = $params->path;
        //print_r($result);
        return array("data"=>$result);
    }
    
    public function getProjectPhysicContent($params) {
        $res = kassist::scanDir($params->path, $this, 'dir');
        $lst = array();
        if ($res != false) {
                $array = array();
                foreach ($res['dir'] as $d)
                    if($d != '.bhproj'){
                        $array['text'] = $d;
                        $array['path'] = $params->path.$d."/";
                        $lst[] = $array;
                    }
                foreach ($res['file'] as $d)
                {
                    $array['text'] = $d;
                    $array['path'] = $params->path.$d;
                    $array['leaf'] = true;
                    $lst[] = $array;
                }    
            }   
        return array("data"=>array('children'=>$lst,'guest'=>$params->guest));
    }

    //This function it for getting the info related with project dependencies
    public function getDependencies() {
        $lst = array();
        $lst['info'] = array(
            array(
                'name' => 'kiske',
                'version' => '1.0',
                'category' => 'core',
                'state' => true,
                'url' => 'var/www/ksike/core/ksike1/',
                'icon' => 'icon',
                'description' => 'Ksike-Larva or Ksike version 1.0, represents the statesments of the Ksike Platform, it implements the base structure and logic of the framework.'
            ),
            array(
                'name' => 'kiske',
                'version' => '1.1',
                'category' => 'core',
                'state' => true,
                'url' => 'var/www/ksike/core/ksike1-01/',
                'icon' => 'icon',
                'description' => 'Ksike-Elephant or Ksike version 1.1, brings completely support to PHP server-side.'
            ),
            array(
                'name' => 'kiske',
                'version' => '1.2',
                'category' => 'core',
                'state' => true,
                'url' => 'var/www/ksike/core/ksike1-02/',
                'icon' => 'icon',
                'description' => 'Ksike-Rynho or Ksike version 1.2,  brings completely support to PHP server-side and allow to develop over JavaScript server-side blah blah.'
            ),
            array(
                'name' => 'kiske',
                'version' => '1.4',
                'category' => 'core',
                'state' => true,
                'url' => 'var/www/ksike/core/ksike1-04/',
                'icon' => 'icon',
                'description' => 'Ksike-Snake or Ksike version 1.4, is the latest version of the Ksike Platform. Inserts the desktop criterion enteraly, it is because althought its inherits the support to PHP and JavaScript of previus versions, in this one insert the Python languaje for server-side in web tecnologies and for both sides in the desktop building of applications. '
            ),
            array(
                'name' => 'ExtJS',
                'version' => '3.0',
                'category' => 'lib',
                'state' => true,
                'url' => 'var/www/ksike/lib/',
                'icon' => 'icon',
                'description' => 'Get more info at <a href="www.sencha.com">here</a>'
            ),
            array(
                'name' => 'ExtJS',
                'version' => '4.0',
                'category' => 'lib',
                'state' => true,
                'url' => 'var/www/ksike/lib/',
                'icon' => 'icon',
                'description' => 'Get more info at <a href="www.sencha.com">here</a>'
            ),
            array(
                'name' => 'ACDC',
                'version' => '4.0',
                'category' => 'lib',
                'state' => true,
                'url' => 'var/www/ksike/lib/',
                'icon' => 'icon',
                'description' => 'Get more info at <a href="www.sencha.com">here</a>'
            )
        );
        return $lst;
    }

    private function getCategories($params) {
        $path = kassist::router("this") . "server/templates/";
        $result = kassist::scanDir($path, $this, 'category');
        $lst = array();
        foreach ($result['dir'] as $i) {
            Tpl_Admin::$path = $path;
            $res = Tpl_Admin::getInfo($i, 'project', 'default');
            //$res!=false? $lst[]= $res : $res=false;
            if ($res != false) {
                $array = array();
                foreach ($res as $key => $val)
                    $array[$key] = $val;
                $array['text'] = $res['category'];
                $array['typeOfNode'] = "subcategory";
                $lst[] = $array;
            }
        }
        return $lst;
    }

    private function getSubCategories() {
        $cat = kassist::request("category", "REQUEST");
        $tpl = kassist::request("type", "REQUEST");
        $path = kassist::router("this") . "server/templates/";
        $result = kassist::scanDir($path . "$cat/$tpl/", $this, 'category');
        $lst = array();
        foreach ($result["dir"] as $i)
            if ($i != 'default') {
                Tpl_Admin::$path = $path;
                $res = Tpl_Admin::getInfo($cat, 'project', $i);
                if ($res != false) {
                    $array = array();
                    foreach ($res as $key => $val)
                        $array[$key] = $val;
                    $array['text'] = $res['name'];
                    $array['typeOfNode'] = "subcategory";
                    $array['leaf'] = true;
                    $lst[] = $array;
                }
            }
           throw new \Exception("vavava");
            
        return $lst;
    }

    public function getAppTemplates() {
        $cat = kassist::request("category", "REQUEST");
        $projTpl = kassist::request("projTpl", "REQUEST");
        $path = kassist::router("this") . "server/templates/";
        Tpl_Admin::$path = $path;
        $result = Tpl_Admin::getAsociations($cat, 'project', $projTpl);
        if (isset($result['app'])) {
            $lst = array();
            foreach ($result["app"]as $app) {
                $res = Tpl_Admin::getInfo($cat, 'app', $app);
                if ($res != false) {
                    $array = array();
                    foreach ($res as $key => $val)
                        $array[$key] = $val;
                    $array['proj'] = $projTpl;
                    $array['size'] = rand(1, 100);
                    if ($res['image'] != false)
                        $image = $res['image'];
                    else
                        $image = "plugins/ProjectAdmin/client/img/defaults/icons/icon.png";
                    $array['image'] = $image;
                    $lst['info'][] = $array;
                }
            }
            return $lst;
        }else
            return false;
    }

    private function getFolderContent($cat=0, $proj=0, $app=0, $branch=0) {
        $cat = kassist::request("tplCat", "REQUEST");
        $proj = kassist::request("tplProj", "REQUEST");
        $app = kassist::request("tplApp", "REQUEST");
        $branch = kassist::request("branch", "REQUEST");
        $path = kassist::router("this") . "server/templates/";
        $lst = array();
        Tpl_Admin::$path = $path;
        if ($branch == '/') {
            $lst[] = $this->getAppFolderContent($cat, $proj, $app, $branch);
            $result = Tpl_Admin::getChildren($cat, 'project', $proj);
            if ($result != false) {
                $child = array();
                foreach ($result as $key => $dir) {
                    $required = ($dir['required'] == 'true') ? true : false;
                    $child['text'] = $dir['name'];
                    $child['typeOfNode'] = 'folder';
                    $child['description'] = $dir['description'];
                    $child['tplCat'] = $cat;
                    $child['tplProj'] = $proj;
                    $child['tplApp'] = $app;
                    $child['branch'] = $branch . $dir['name'] . '/';
                    $child['leaf'] = (count($dir['child']) > 0) ? false : true;
                    $child['checked'] = $required;
                    $child['required'] = $required;
                    $child['iconCls'] = ($dir['name'] != 'app') ? "src-folder" : "";

                    $lst[] = $child;
                }
            }else
                return false;
        }else {
            $br = split("/", $branch);
            $result = Tpl_Admin::getChildren($cat, 'project', $proj);
            for ($i = 1; $i < (count($br) - 1); $i++) {
                if ($br[$i] == 'app')
                    $result['child'] = Tpl_Admin::getChildren($cat, 'app', $app);
                else
                    $result = $this->findChildByName($br[$i], $result['child']); ///mirar aquiiii!!!
            }
            if ($result != false) {
                $child = array();
                foreach ($result['child'] as $key => $dir)
                    if (isset($dir['name'])) {
                        $required = ($dir['required'] == 'true') ? true : false;
                        $child['text'] = $dir['name'];
                        $child['description'] = $dir['description'];
                        $child['typeOfNode'] = 'folder';
                        $child['tplCat'] = $cat;
                        $child['tplProj'] = $proj;
                        $child['tplApp'] = $app;
                        $child['branch'] = $branch . $dir['name'] . '/';
                        $child['leaf'] = (count($dir['child']) > 0) ? false : true;
                        $child['checked'] = $required;
                        $child['required'] = $required;
                        $child['iconCls'] = "src-folder";

                        $lst[$key] = $child;
                    }
            }
        }
        return $lst;
    }

    private function getAppFolderContent($cat, $proj, $app, $branch) {
        return array(
            'text' => 'app',
            'typeOfNode' => 'folder',
            'description' => 'App directory is used for ...',
            'tplCat' => $cat,
            'tplProj' => $proj,
            'tplApp' => $app,
            'branch' => '/app/',
            'leaf' => false,
            'checked' => true,
            'required' => true,
            'iconCls' => ''
        );
    }

    private function findChildByName($name, $node) {
        foreach ($node as $k => $v) {
            if ($v['name'] == $name)
                return $v;
        }
        return false;
    }

    /* This section is for method that helps
     */

    private function objToArray($obj) {
        $lst = array();
        foreach ($obj as $key => $i)
            $lst[$key] = $i;
        return $lst;
    }

    public function onFindDir($item, $path, $type, $params='') {
        //if($type == "dir") kassist::scanDir($path.$item."/", $this, "rere");
    }

    public function onCloseDir($lst, $path) {
        return $lst;
    }

}

?>
