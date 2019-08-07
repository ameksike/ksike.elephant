<?php
use Ksike\ksl\filter\control\App;
use Ksike\ksl\base\helpers\Assist as kcl;
class Main extends App
{
	public function index($params)
	{
		$path = kcl::router("this");
		$file = $path."client/html/view.html";	
		return file_get_contents($file);
	}
	
	public function holaMundo($params)
	{
		return array(
			'action'=>'holaMundo',
			'result'=>'hola '.$params->name
		);
	}
}
