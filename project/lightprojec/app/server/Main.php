<?php
use Ksike\ksl\filter\control\App;
class Main extends App 
{
	public function in($params)
	{
		//echo "<pre>"; print_r(get_included_files());
		return " <h3> in slightly  </h3>";
	}

	public function index($params)
	{
		return "
			<h1> slightly hallow your self </h1>
			<h2> is joke </h2>
		";
	}

	public function out($params)
	{
		return " <h3> out slightly  </h3>";
	}

}
