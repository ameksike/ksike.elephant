/**
 *
 * @framework: Ksike
 * @package: Core
 * @subpackage: js
 * @version: 0.1

 * @description: Router es una vendorreria para el trabajo con
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 02/06/2010
 * @update-Date: 25/09/2010
 * @license: GPL v2
 *
 */
Kcl.Class( "Kcl.Router",
{
	patterns: "Singleton",
	property:{
		c2p: "",
		p2c: "",
		vendor:{}
	},
	behavior: {
		construct:function(params)
		{
			this.reConfig(params);
		},
		reConfig:function(params)
		{
			params = params || {};
			if(params["lib"]){
				 params["vendor"] = params["lib"]; 
				 delete params["lib"]; 
			}
			for(var i in params) this[i] = params[i];
			if(typeof(this.vendor)=="string") this.vendor = {"0":this.vendor};
			this.vendor["core"] = this.p2c+"lib/";
			//var uri = document.location.pathname.split("/");
			//this.c2p += uri[uri.length-2] + "/";
		},
		module: function(vendorName, parent)
		{
			var _c2p = parent ? parent : this.c2p;
			var _mod = vendorName ? vendorName : "Main";
			if(_mod != "Main") var path = _c2p+"plugins/"+_mod+"/client/";
			else var path = _c2p+"app/client/";
			return path;
		},
		core: function(parent)
		{
			var _p2c = parent ? parent : this.p2c;
			return _p2c+"core/src/js/kcl/";
		},
		lib: function(key)
		{
			key = key || "core";
			return this.vendor[key];
		},
		path: function(vendorName, type)
		{
			return (this[type]) ? this[type](vendorName) : "";
		},
		urlTo: function(path, type)
		{
			var sl = (type=="module") ? "js/" : "";
			var value = (type=="core") ? "" : path;
			if(this.mode == "secure")  return "open/js/?fl="+path;	
			else return this.path(value, type)+sl+path+".js";	
		}
		
	}
});