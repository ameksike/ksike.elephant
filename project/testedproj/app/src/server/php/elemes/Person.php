<?php
	class Person
	{
		public $name;
		public $age;
		public $sex;

		public function __construct($name="Kuco", $age=23, $sex="M"){
			$this->name = $name;
			$this->age = $age;
			$this->sex = $sex;
		}

		public function getName($e){
			return $this->name." >> $e";
		}

		public function str(){
			return $this->name." >> ".$this->age." >> ".$this->sex." >> ";
		}

		public static function this($ask=false, $params=false)
		{
			return "ola";
		}

		/*protected static $__this = false;
		public static function this($ask=false, $params=false)
		{
			if(!self::$__this){
				if(is_array($ask)){
					$option = $ask;
					$ask = false;
				}else $option=false;
				self::$__this = new self($option);
			}
			if($ask){
				$out = self::$__this->__this($ask, $params);
				if($out) return $out;
			} 
			return self::$__this;
		}
		protected function __this($ask, $params=false){
			return $this->$ask;
		}*/
	}
?>
