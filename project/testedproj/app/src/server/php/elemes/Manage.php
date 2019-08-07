<?php
	class Manage
	{
		private static $id = "M2So";

		public static function str($e){
			return self::$id." : ".$e->str();
		}
	}
?>
