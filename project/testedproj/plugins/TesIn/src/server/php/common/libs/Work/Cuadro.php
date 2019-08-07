<?php
	namespace Work;
	class Cuadro extends Trabajador
	{
		public $ini;
		public function __construct($name="Tas", $age=12, $sex="G")
		{
			parent::__construct($name, $age, $sex);
			$this->ini = $name."DD";
		}
	}

?>
