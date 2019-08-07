<?php
use Ksike\ksl\filter\control\App; 
use Ksike\ksl\base\bundles\Package; 
use Ksike\ksl\base\helpers\Assist as kcl;
class Main extends App 
{
	public function in($params)
	{
		//echo "<pre>"; print_r(get_included_files());
		return "<h3> in hola</h3>";

	}

	public function index($params)
	{
		$u1 = Package::this("ioc")->users;//->name;
		//$u2 = Package::this("ioc")->metas;
		//      Package::this("ioc")->metas->name = "musa";
		$u3 = Package::this("ioc")->agent;
		//$u4 = Package::this("ioc")->getim;
		$u5 = Package::this("ioc")->intim;
		$u6 = Package::this("ioc")->tusas;
		$u7 = Package::this("ioc")->mista;
		$u8 = Package::this("ioc")->intro;
 
		//print_r($u1); echo "<br>";
		//print_r($u2); echo "<br>";
		//print_r($u3::str($u2)); echo "<br>";
		//print_r($u4); echo "<br>";
		//print_r($u5); echo "<br>";
		//print_r($u7); echo "<br>";

		$co = Package::this("config")->Main;
		/*$co = Package::this("config")->load("Main");*/
		$co = Package::this("config")->load();
		$co = Package::this("config")->this;

		return $co;
	}

	public function out($params)
	{
		return "<h3> out hola</h3>";
		//print_r(get_included_files());
	}
}
