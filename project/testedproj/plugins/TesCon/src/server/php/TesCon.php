<?php
use Ksike\ksl\filter\control\Plugin; 
use Ksike\ksl\base\bundles\Package; 
use Ksike\ksl\base\helpers\Assist as kcl;
class TesCon extends Plugin 
{
	public function index(){
		$co = kcl::package("config")->Main;
		return $co;
	}

	public function getMain($params) {
		$co = Package::this("config")->Main;
		return $co;
	}

	public function getAsTrThis($params) {
		$co = Package::this("config")->load("TesCon");
		return $co;
	}

	public function getByLoad($params) {
		$co = Package::this("config")->load();
		return $co;
	}

	public function getByThis($params) {
		$co = Package::this("config")->this;
		return $co;
	}


	public function getmods($params) {
		$co = Package::this("config")->this;
		$co = $co["mods"];
		return $co;
	}
}
