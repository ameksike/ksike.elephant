/**
 *
 * @framework: Ksike
 * @package: Core
 * @subpackage: php
 * @version: 0.1

 * @description: Script que implementa el controlador frontal del framework Ksike
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 01/06/2010
 * @update-Date: 01/06/2010
 * @license: GPL v3
 *
 */
 window.onerror = function(msg, file, line){
	if (window[config.ns].error) window[config.ns].error.trigger({ "msg": msg, "file":file, "line": line});
 }
try {
	config = config || {};
	config.ns = config.ns || "std";
	window[config.ns] = new Kcl.Assist();
	window[config.ns].require(config.loader.base, {
		"onLoad": function(el, elem){
			if(elem.params.mode == "secure") 
				elem.lst[elem.i] = config.router.p2c+"open/js/?fl="+elem.lst[elem.i];	
			else elem.lst[elem.i] = config.router.p2c+"core/src/js/kcl/base/"+elem.lst[elem.i]+".js";	
		},
		"onFinish":function(el, elm){
			window[config.ns] = new Kcl.Engine(config.router);
			window[config.ns].load(config.loader);
		},"params" : config.router
	});
	delete config;
}catch(error){ 
	window.onerror(error);
}