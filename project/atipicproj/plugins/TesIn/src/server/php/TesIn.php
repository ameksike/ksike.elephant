<?php
use Ksike\ksl\filter\control\Plugin; 
use Ksike\ksl\base\helpers\Assist as kcl;
class TesIn extends Plugin 
{
	public function index(){
		return "Acceder a la configuracion del modulo principal";
	}
/*      -------------------------------------------------- Package Config
	Acceder a la configuracion del modulo principal
*/
	public function mainConfig($params) {
		echo "<pre>";
		$co = kcl::package("config")->Main;
		return $co;
	}
/*
	Obtener la configuracion del modulo TesCon
*/
	public function loadConfig($params) {
		echo "<pre>";
		$co = kcl::package("config")->load("TesCon");
		return $co;
	}
/*
	Obtener la configuracion propia
*/
	public function thisConfig($params) {
		echo "<pre>";
		$co = kcl::package("config")->this;
		return $co;
	}
/*
	Obtener la configuracion dado un directorio
*/
	public function getConfigAsDir($params) {
		echo "<pre>";
		$path = kcl::router("this")."cfg/local/";
		$co = kcl::package("config")->load($path);
		return $co;
	}
/*
	Obtener la configuracion dado un nombre de fichero 
*/
	public function getConfigAsFileName($params) {
		echo "<pre>";
		$path = kcl::router("this")."cfg/local/";
		$co = kcl::package("config")->load($path, "mst");
		return $co;
	}
/*
	Obtener la configuracion dado un nombre de fichero, especificandose el formato
*/
	public function getConfigAsFileNameAndFormat($params) {
		echo "<pre>";
		$path = kcl::router("this")."cfg/local/";
		$co = kcl::package("config")->load($path, "mst", "xml");
		return $co;
	}
/*
	Obtener la configuracion dado un nombre de fichero 
*/
	public function getConfigAsFile($params) {
		echo "<pre>";
		$path = kcl::router("this")."cfg/local/mst.php";
		$co = kcl::package("config")->load($path);
		//print_r($co);
		return $co["sxx"]["interno"];
	}
/*
	Obtener la configuracion dado un nombre de fichero 
*/
	public function getConfigCustomised($params) {
		echo "<pre>";
		$path = kcl::router("this")."cfg/test/tesing.flow";
		$co = kcl::package("config")->load($path);
		print_r($co);
		//return $co["sxx"]["interno"];
	}
	
/*
	Obtener la configuracion dado un nombre de fichero como referencia al camino
*/
	public function getConfigAsFileRefPath($params) {
		echo "<pre>";
		$path = kcl::router("this")."cfg/local/mst.php";
		$co = kcl::package("config")->load($path, "inst" );
		return $co;
	}
	
/*
	Salvar la configuracion dado un dir
*/
	public function saveConfigAsDir($params) {
		$path = kcl::router("this")."cfg/config";
		$co = kcl::package("config")->load($path);
		return $co;
	}
/*
	Obtener la configuracion empleando la directiva import
*/
	public function importConfig($params) {
		$path = kcl::router("this")."cfg/import/";
		$kkkk = kcl::loader()->fileconf($path, "tt", "none");
		return $kkkk;
	}
/*      -------------------------------------------------- Request
	Acceder a las varables contenidas en el request sea: POST/GET/PUT
*/
	public function requestbyRouter($params) {
		$co = kcl::router()->request->all();
		return $co;
	}
/*
	Acceder a las varables contenidas en el request sea: POST/GET/PUT
*/
	public function request($params) {
		$co = kcl::request("name");
		return $co;
	}
/*
	Acceder a las varables contenidas en el request de tipo GET
*/
	public function requestGET($params) {
		$co = kcl::request("byMethod", 'GET');
		return $co;
	}
/*
	Acceder a las varables contenidas en el request de tipo Semantica
*/
	public function requestPretty($params) {
		$co = kcl::request("byMethod", 'PRETTY');
		return $co;
	}
/*
	Acceder a las varables contenidas en el request de tipo Semantica
*/
	public function requestPrettyAlias($params) {
		return $params;
	}
/*
	Acceder a las varables contenidas en el request de tipo REQUEST
*/
	public function getByrequest($params) {
		return 	kcl::request("r", "REQUEST");;
	}	
/*      -------------------------------------------------- Router 
	Obtener la ruta completa del core
*/
	public function pathCore($params) {
		$co = kcl::router("core");
		return $co;
	}
/*
	Obtener la ruta completa del modulo principal
*/
	public function pathMain($params) {
		$co = kcl::router("module", "Main");
		return $co;
	}
/*
	Obtener la ruta completa de este modulo
*/
	public function pathThisT($params) {
		$co = kcl::router("this");
		return $co;
	}
/*
	Obtener la ruta completa de este modulo
*/
	public function pathThis($params) {
		$co = kcl::router()->this;
		return $co;
	}
/*      -------------------------------------------------- Driver
	Acceder al driver de administracion de ficheros 
*/
	public function driverFile($params) {
		$u1 = kcl::driver("File", kcl::router("this")."server/common/tes.docs");
		return $u1->read(); 
	}
/*      -------------------------------------------------- Loader
	Suscribir un cargador local 
*/
	public function loader($params) {
		kcl::loader("supply", new TesLoader);
		//kcl::loader()->supply(new TesLoader);
		$feu = new \Estu\Feu();
		$cua = new \Work\Cuadro();
		return $cua; 
	}
/*      -------------------------------------------------- package Dir
	Escanear directorios
*/
	public function scanDir($params) {
		echo "<pre>";
		$path = kcl::router("this")."dirs/";
		$data = kcl::package("dir")->scan($path, "-r" ); // mode : [-i|-r]
		//$data = kcl::dir()->scan($path, "-r"); // mode : [-i|-r]
		print_r($data);
		//return $data; 
	}
	
	public function searchDir($params) {
		echo "<pre>";
		$path = kcl::router("this")."dirs/";
		$data = kcl::package("dir")->find("d", $path, "strict");  //type : [strict|sstrict|regular expresion]
		print_r($data);
		//return $data; 
	}

	public function onFind($lst, $path, $params, $item, $type)
	{
		//echo "$path$item <br>";
		//return array ("file"=> $lst["file"]) ;
		//return isset($lst["file"]) ? $path.$lst["file"][0] : "";
	}
	
	public function onFinish($lst, $path, $params, $item, $type)
	{
		echo "<pre>";
		//return array ("file"=> $lst["file"]) ;
		//return isset($lst["file"]) ? $path.$lst["file"][0] : "";
	}
/*      -------------------------------------------------- Assist 
*/
/*
	Obtener informacion de que clase hizo la llamada a esta funcion
*/
	public function whoCallme($params) {
		$co = kcl::whoCallme();
		return $co;
	}
/*
	Obtener informacion de que funcion hizo la llamada a esta funcion
*/
	public function whoFunctionCallme($params) {
		$co = kcl::whoCallme(2, "function");
		return $co;
		//param2: file|line|function|class|object|type|args|all
	}
/*
	Obtener informacion de que clase llamo a que clase que invoco a esta funcion a 
*/
	public function whoClassCallClasswhoCallme($params) {
		$co = kcl::whoCallme(3);
		return $co;
	}
/*
	Obtener los nombres de todas las funciones invocadas
*/
	public function allCallClasswhoCallme($params) {
		$co = kcl::whoCallme("all", "function");
		return $co;
	}
/*      -------------------------------------------------- Log
	Empleo de los mensajes de tipo Log
*/
	public function logsave($params) {
		kcl::package("log")->save("Esto es un ejemplo de log para la app");
		return "Logs oks";
	}
/* 
	Generar un log en este modulo 
*/
	public function logInModule($params) {
		//... se procede a definir el formato y contenido del log a generar, estalecido por la relacion clave-valor de un array asiciativo
		$datos = array(
			"msg" => "este es un log para el modulo",
			"type" => "local",
			"numeric" => 12345
		);
		$path = kcl::router("this")."log/";
		//... se imdica la generacion de un log en el directorio log/ del propio modulo en ejecusion, con el nombre de "local"
		kcl::package("log")->save($datos, "local", $path);
		return "Local Logs oks";
	}
/* 
	Modificar el formato del log
*/
	public function logInModuleMod($params) 
	{
		//...	genera un log con el nombre "trace.log" en el directorio app/log/	
		kcl::package("log")->option['format']['@<'] = '#';
		kcl::package("log")->option['format']['@>'] = '#';
		kcl::package("log")->option['format']['#<'] = ':# "';
		kcl::package("log")->option['format']['#>'] = '#';
		kcl::package("log")->option['format']['|'] 	= '| ';
		kcl::package("log")->option['format']['<'] 	= '<<';
		kcl::package("log")->option['format']['>'] 	= '>>,';
		kcl::package("log")->option["dateFormat"]  	= 'Y/m/d';
		
		kcl::package("log")->save("Esto es un ejemplo de log para la app1");
		kcl::package("log")->reset();
		//...	retoma la configuracion inicial y adiciona un log al archivo "trace.log" en el directorio app/log/	
		kcl::package("log")->save("Esto es un ejemplo de log para la app2");
		return "Local Logs oks";
	}
/* 
	Trabajar con distintos tipos de log
*/
	public function log2($params) 
	{
		//... genera un log en el directorio por defecto denominado app/log/, pero con el nombre "test1" y la estencion ".log"
		kcl::package("log")->save("Esto es un ejemplo de log para la app1", "test1");
		return "Local Logs oks";
	}
/* 
	Trabajar con el driver Twig
*/
	public function twigcall($params) 
	{
		$path = kcl::router()->this."server/tpl/tpl.twig";
		$tpl = kcl::driver("Twig");
		
		$out = $tpl->tplString2Doc(file_get_contents($path),  
			array(
				'BHTemplate'=>array(
					'Type'=>'Project',
					'Version'=>'1.0'
				),
				'content'=>"This is a template fired on Twig"
			)
		);
		return $out;
	}
}
