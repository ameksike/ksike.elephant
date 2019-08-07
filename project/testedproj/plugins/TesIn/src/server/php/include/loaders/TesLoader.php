<?php
use Ksike\ksl\filter\iface\Loader;
use Ksike\ksl\base\helpers\Assist;
class TesLoader implements Loader
{
	public function onLoad($name)
	{
		$path = Assist::router("module", "TesIn");
		@include $path."server/common/libs/".$name.KCL_EXT;
	}
}
