/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: handlers
 * @version: 0.1

 * @description: Engine es una libreria para gestionar las lirerias y los modulos del framework
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 02/06/2010
 * @update-Date: 25/09/2010
 * @license: GPL v2
 *
 */

Ksike.Class( "Ksike.js.base.client.handlers.Engine",
{
	extend: Kcl.Loader,
	property:{
		version: "Ksike 1.1 Elephant",
		mod: {}
	},
	behavior: {
		construct:function(){
			var _this = Kcl.Engine.prototype;
			arguments[0] = arguments[0] || {};
			arguments[0]["vendor"] = _this;
			arguments[0]["mods"] = _this.mod;
			_this.parent.construct.apply(_this, arguments);
		},
		load: function(lst){
			lst.key = "filter";
			this.require(lst["filter"], { "onFinish":this.onPackage, "params": lst });
		},
		onPackage: function(lst, elm){
			lst.key = "package";
			var _that = Kcl.Engine.prototype;
			_that.require(lst["package"], { "onFinish":_that.onResource, "params": lst, "onLoad": _that.onLoadLib });
		},
		onResource: function(lst, elm){
			var _that = Kcl.Engine.prototype;
			lst.key = false;
			_that.onLoadLib(lst, elm);
			_that.require(lst["other"], { "onFinish":_that.onLoadLib, "params": lst, "onLoad": _that.onLoadLib });
		}
	}
});
