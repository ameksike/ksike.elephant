<?php
use Ksike\ksl\filter\control\Plugin; 
use Ksike\ksl\base\bundles\Package; 
class TesIOC extends Plugin 
{
	public function getObject($params) {
		$u1 = Package::this("ioc")->users;
		$u1->in = (isset($params->in)) ? $params->in : "none";
		return $u1; 
	}

	public function getClass($params) {
		$ob = Package::this("ioc")->users;
		$u1 = Package::this("ioc")->agent;
		$st = $u1::str($ob);
		return $st; 
	}

	public function getClassAction($params) {
		$u2 = Package::this("ioc")->metas;
		return $u2; 
	}

	public function getConfigRelative($params) {
		$u4 = Package::this("ioc")->tusas;
		return $u4; 
	}

	public function getConfigStatic($params) {
		$u4 = Package::this("ioc")->getim;
		return $u4; 
	}

	public function getDriver($params) {
		$u4 = Package::this("ioc")->mista;
		return $u4; 
	}

	public function getPackage($params) {
		$u4 = Package::this("ioc")->intro;
		return $u4; 
	}


	public function getModule($params) {
		$u4 = Package::this("ioc")->modss;
		return $u4; 
	}
	
	public function getModuleAcct($params) {
		$u4 = Package::this("ioc")->modAc;
		return $u4; 
	}
}
