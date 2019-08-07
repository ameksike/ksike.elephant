<?php
/**
 *
 * @framework: Ksike
 * @package: package
 * @subpackage: out
 * @version: 0.1

 * @description: OutManager es una libreria para el trabajo con los formatos de exportacion de datos del controldor frontal...
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 16/06/2010
 * @update-Date: 24/08/2011
 * @license: GPL v2
 *
 */
namespace Ksike\ksl\package\han\proxy;
use Ksike\ksl\base\helpers\Assist as kcl;
class Han
{
	public function __construct($option=false) {
		print_r("Han:construct <br>");
		//print_r(kcl::request());
	}

	public function preDispatch()
	{
		print_r("Han:preDispatch <br>");

	}

	public function posDispatch()
	{
		print_r("Han:posDispatch <br>");
		print_r(get_included_files());

	}
}
