/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: helpers
 * @version: 0.1

 * @description: Loader es una clase para la administracion de la carga dinamica de modulos o plugins
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 03/06/2010
 * @update-Date: 01/09/2010
 * @license: GPL v2
 *
 */
Kcl.Class( "Kcl.Loader",
{
	patterns: "Singleton",
	extend: Kcl.Assist,
	behavior: {
		construct: function(params)
		{
			params = params || {};
			var _this = Kcl.Loader.prototype;
			_this.factory = new Kcl.Factory(params);
			_this.router = new Kcl.Router(params);
		},
		build: function(elem, callback, params)
		{
			if(elem.i > 0 && elem.i <= elem.lst.length){
				Kcl.Loader.prototype.factory.build(elem.lst[elem.i-1], callback, params);
			}
		},
		onRequire: function(className, elm){
			Kcl.Loader.prototype.factory.build(className, 0);
		},
		onLoadLib: function(el, elem)
		{
			Kcl.Loader.prototype.build(elem, elem.item.callback, elem);
		},
		require: function(lst, cfg, params)
		{
			cfg = cfg || {};
			var option = {
				"onLoad": function(el, elem){
					Kcl.Loader.prototype.onLoad(el, elem);
					if(elem.item instanceof Function) elem.item(el, elem)
					else if(elem.item.onLoad) elem.item.onLoad(el, elem);
				}, 			
				"onFinish": function(el, elem){
					Kcl.Loader.prototype.onLoad(el, elem);
					if(elem.item instanceof Function) elem.item(el, elem);
					else if(elem.item.onFinish) cfg.onFinish(el, elem);
				},
				"params": (cfg.params) ? cfg.params : params,
				"item": cfg ? cfg : {}
			}
			Kcl.Loader.prototype.parent.require(lst, option, params);
		},
		onLoad: function(el, elem){
			if(elem.lst[elem.i]){
				var key = elem.params.key ? elem.params.key+"/" : "";
				var type = !elem.params.type ? (key!="") ? "core" : "module" : elem.params.type;
				if(type!="free") elem.lst[elem.i] = Kcl.Loader.prototype.router.urlTo(key+elem.lst[elem.i], type);			
			}
		} 
	}
});
