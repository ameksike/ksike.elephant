<?php
class TesCon 
{
	public function preAction($params, $action){
		return "--pre-- $action";
	}
	
	public function index($params){
		return "<< $params : Hooooo >>";
	}
	
	public function posAction($params, $action){
		return "@ $params @ $action";
	}
}
