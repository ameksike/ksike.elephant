<?php
/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: handlers
 * @version: 0.1

 * @description: Clase que se responsabilizar de la definicion de los procesos en el framework
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 09/07/2011
 * @update-Date: 23/11/2012
 * @license: GPL v3
 *
 */
 
 
namespace Ksike\base\common\handlers;
use Ksike\base\common\helpers\Assist;
class Engine
{
	public function on(){
		$this->initialize();
		$this->process();
		$this->respond();
	}
	public function initialize(){
		$this->requires();
		$this->configure();
		Assist::loader("onbase");
		Assist::package()->activate();
	}
	
	public function process($arguments=0){
		Assist::request()->process($arguments);
		
		Assist::package()->callthem("preDispatch");
		
		Assist::package("front")->build(
			Assist::request("option", 'outFormat'),
			Assist::request("option", 'outOption'),
			Assist::request("option", 'outInfo')
		);
		
		Assist::package("front")->dispatch(
			Assist::request("option", 'controller'),
			Assist::request("option", 'action'),
			Assist::request("option", 'params')
			$certificate
		);
		
		Assist::package()->callthem("posDispatch");
		return Assist::response;
	}
	
	public function respond(){
		$count = count(Assist::response);
		if($count > 0){
			if( Assist::respond()){
				Assist::respond()->option["cfg"]["format"] = Assist::request("option", 'outFormat'); 
				Assist::respond()->option["cfg"]["option"] = Assist::request("option", 'outOption');
				Assist::respond()->data = ($count == 1) ? Assist::response[0] : Assist::response;
				echo Assist::respond();
			}else foreach(Assist::response as $out) print_r($out);
		}
	}

	protected function requires(){
		include KCL.KCL_SRC.'ksl/base/common/patterns/Singleton'.KCL_EXT;	
		include KCL.KCL_SRC.'ksl/base/common/patterns/Factory'.KCL_EXT;	
		include KCL.KCL_SRC.'ksl/base/common/helpers/Assist'.KCL_EXT;
		include KCL.KCL_SRC.'ksl/base/common/helpers/Router'.KCL_EXT;
		include KCL.KCL_SRC.'ksl/base/common/helpers/Loader'.KCL_EXT;
		include KCL.KCL_SRC.'ksl/base/common/iom/Request'.KCL_EXT;
		include KCL.KCL_SRC.'ksl/base/common/messages/Debuger'.KCL_EXT;
	}

	protected function configure($path="core/cfg/", $file="config"){
		$data = Assist::loader()->cfg($path, $file, "base");
		Assist::debug("cfgBase", $data);
		Assist::package()->option = $data["loader"]["package"];
		Assist::router()->load($data["router"]);
		Assist::router()->load();
		Assist::loader()->option = $data["loader"];
		if(Assist::router()->proj() == DIRECTORY_SEPARATOR || Assist::router()->proj()== getcwd()."/"){
			$dir = getcwd().DIRECTORY_SEPARATOR."core".DIRECTORY_SEPARATOR."cfg".DIRECTORY_SEPARATOR;
			$cfg = Assist::loader()->cfg($dir, $file, "none");
			Assist::debug("cfgPublish", $cfg);			
			if(isset($cfg["router"])) Assist::router()->load($cfg["router"]);
		}
		$data = Assist::loader()->cfg($path, $file, "proj");
		Assist::debug("publishCFG", $data);
		if(isset($data["loader"])) 
			Assist::loader()->option = $data["loader"] + Assist::loader()->option;
		if(isset($data["loader"]["package"])) {
			Assist::package()->option = $data["loader"]["package"];	
			unset(Assist::package()->packages);
			Assist::package()->packages = array();
		}
		if(isset($data["router"])) {
			Assist::router()->load($data["router"]);
			Assist::router()->load();
		}
		unset($data);
	}
}
