<?php
	namespace Base; 
	class Persona
	{
		public $name;
		public $age;
		public $sex;
		public function __construct($name="mist", $age="23", $sex="H")
		{
			$this->name = $name;
			$this->age = $age;
			$this->sex = $sex;
		}
	}

?>
