<?php
use Ksike\ksl\filter\control\App;

class Main extends App
{
	public function holaMundo($params)
	{
		return array(
			'action'=>'holaMundo',
			'result'=>'hola '.$params->name
		);
	}
}
