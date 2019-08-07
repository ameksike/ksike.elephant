<?php
/**
 *
 * @framework: Ksike
 * @package: log
 * @subpackage: proxy
 * @version: 0.1

 * @description: Log es una libreria para el trabajo con registros de log
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 01/06/2010
 * @update-Date: 06/08/2011 
 * @license: GPL v3
 *
 */
namespace Ksike\ksl\package\log\proxy;
use Ksike\ksl\base\helpers\Assist;
class Metadata 
{
	public $option = false;
	private $cfg = false;

	public function __construct($option=false){
		$this->reset();
		if(is_array($option)) $this->option = $option + $this->option;
		$this->cfg = $this->option;
	}

	public function save($struct, $name="trace", $path=false)
	{
		$path =  $path ? $path : Assist::router("app").KCL_LOG;
		if(!file_exists($path)) mkdir($path, 0777, true);
		error_log($this->getMessage($struct)." \n", 3, $path.$name.$this->option["ext"]);
	}

	public function reed($struct, $name="trace", $path=false)
	{
		//... falta
	}

	protected function getMessage($struct)
	{
		$mess = $this->option["format"]['@<'].'Date'.$this->option["format"]['@>'].$this->option["format"]['#<'].date($this->option["dateFormat"]).$this->option["format"]['#>'];
		if(is_string($struct)) 
			$mess .= $this->option["format"]['|'].$this->option["format"]['@<']."Message".$this->option["format"]['@>'].$this->option["format"]['#<'] .$struct.$this->option["format"]['#>'];
		else foreach($struct as $key=>$value)
			$mess .= $this->option["format"]['|'].$this->option["format"]['@<'].$key.$this->option["format"]['@>'].$this->option["format"]['#<'] .$value.$this->option["format"]['#>'];
		return $this->option["format"]['<'].$mess.$this->option["format"]['>'];
	}

	public function reset($force=false)
	{
		if(!$this->cfg || $force)
			$this->option = array(
				"format" => array( '#<'=>': <<', '#>'=>'>>', '|'=>', ', '@<'=>'', '@>'=>'', '<'=>'', '>'=>'' ),
				"dateFormat" => 'Y/m/d H:i:s',
				"ext" => '.log'
			);
		else $this->option = $this->cfg;
	}
}
