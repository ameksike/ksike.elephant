<?php
/**
 *
 * @framework: Ksike
 * @package: Lib
 * @subpackage: Template
 * @version: 0.1 

 * @description: Esta libreria esta diseñada para manejar plantillas basado en el Templates Engine Twig
 * @authors: Yadir Hernandez Batista
 * @making-Date: 09/12/2011
 * @update-Date: 09/12/2011
 * @license: GPL v3
 *
 */ 
require_once 'Twig/Autoloader.php';
class Twig extends Twig_Autoloader
{
		protected static $loader;              //Usado para localizar los templates
		protected static $compilation_cache;
		protected static $enviroment;          //Usado para almacenar la configuración
		protected static $tplPath;
        
		public function __construct(){
			self::register();
		}
		
        public function tplString2Doc($tpl="",$content= array("content"=>"Twig generated template"))
        {
            try{
                self::$loader = new Twig_Loader_String();            
                return self::generate($tpl, $content);
            }
            catch(Exception $e){
                throw new Exception("Error during the document creation, cause: " .$e->getMessage(), $e->getCode(), $previous);
            }
        }
        
        public function tplFile2Doc($tpl="tpl.twig",$path="",$content= array("content"=>"Twig generated template"))
        {
            try{
                self::$loader = new Twig_Loader_Filesystem($path);            
                return self::generate($tpl, $content);
            }
            catch(Exception $e){
                throw new Exception("Error during the document creation, cause: " .$e->getMessage(), $e->getCode(), $previous);
            }
        }
        
        private static function generate($tpl,$content){
            self::$enviroment = new Twig_Environment(self::$loader);
            return self::$enviroment->render($tpl,$content);
        }
        
}
/*
 //* How to use Twig Driver
  
// Content to generate documents
$content = array(
    'BHTemplate'=>array(
        'Type'=>'Project',
        'Version'=>'1.0'
    ),
    'content'=>"This is a fire test on Twig Driver"
);
// Using the capability of generating documents from a template file
$folder = "/var/www/";  // Source folder for templates
$tpl = 'tpl.twig';      // template file
Twig::setTplPath($folder); 
$res = Twig::tplFile2Doc($tpl,$content); // returns the created document data
file_put_contents("/var/www/out.xml", $res); // creates a file and puts the data in
$tplInfo = file_get_contents($folder.$tpl);

echo "Document create successfuly with content: \n".$res."form template: \n".$tplInfo;
 /*
 * TEMPLATE /var/www/tpl.twig
{#  
    Template for an little Twig sample of use
#}
<?xml version='1.0' encoding='utf-8'?>
<BHTemplate Type="{{ BHTemplate.Type }}" Version="{{ BHTemplate.Version }}">
	{{ content|raw }}
</BHTemplate>
 
 // OUTPUT 
<?xml version='1.0' encoding='utf-8'?>
<BHTemplate Type="Project" Version="1.0">
	This is a fire test on Twig Driver
</BHTemplate>
 */
/**/
 
