<?php 
/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: patterns
 * @version: 0.1

 * @description: Singleton es una libreria para la ... 
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 06/11/2010
 * @update-Date: 05/12/2010
 * @license: GPL v2
 *
 */
namespace Ksike\lib\base\src\common\php\patterns;
class Observed
{
	protected $event;
	protected $nevents;
	protected $catcher;

	public function __construct(){
		$this->catcher = false;
		$this->nevents = false;
		$this->event = "notify";
	}

	protected function trigger($params, $event=false)
	{
		$event = ($event) ? $event : $this->event;
		if($this->catcher) foreach($this->catcher as $i){
			if($this->nevents===true || isset($this->nevents[$event])) break;
			$params = is_array($params) ? $params : ($params) ? array($params) : array();
			call_user_func_array(array($i, $event), $params);
		}
		return $this;
	}

	public function supply($catcher, $key=false)
	{
		if(!$this->catcher) $this->catcher = array();
		if(!$key) $this->catcher[] = $catcher;
		else $this->catcher[$key] = $catcher;
		return $this;
	}

	public function remove($key=0)
	{
		unset($this->catcher[$key]);
		return $this;
	}

	protected function setStatusEvent($event, $status){
		if($event=="all") $this->events = $status;
		else{
			if(!$status) $this->events[$event] = true;
			else unset($this->events[$event]);
		}
	}

	public function interrupt($event="all"){
		$this->setStatusEvent($event, true);
	}

	public function enable($event="all"){
		$this->setStatusEvent($event, false);
	}
}
