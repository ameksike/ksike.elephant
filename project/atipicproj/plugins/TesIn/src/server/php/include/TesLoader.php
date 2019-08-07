<?php
	use Ksike\filter\iface\Loader;
	use Ksike\base\helpers\Assist;
	class TesLoader implements Loader
	{
		public function onLoad($name)
		{
			$path = Assist::router("module", "TesIn");
			@include $path."server/common/libs/".$name.KCL_EXT;
		}
	}

?>
