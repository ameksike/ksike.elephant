<?php
use Ksike\ksl\filter\control\Plugin; 
use Ksike\ksl\base\bundles\Driver;
use Ksike\ksl\base\helpers\Assist;
class TesDriv extends Plugin 
{
	public function getFile($params) {
		$fi = Assist::router()->this."cfg/config.json";
		$u1 = Driver::this("File", $fi);
		return $u1; 
	}

	public function getFileByHelper($params) {
		$fi = Assist::router()->this."cfg/config.json";
		$u1 = Assist::driver("File", $fi);
		return $params; 
	}
}
