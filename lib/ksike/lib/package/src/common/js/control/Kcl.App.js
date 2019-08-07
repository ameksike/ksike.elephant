/**
 *
 * @framework: Ksike
 * @package: Core
 * @subpackage: js
 * @version: 0.1

 * @description: App es una clase para la administracion de modulos o plugins
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 03/06/2010
 * @update-Date: 09/09/2010
 * @license: GPL v2
 *
 */
Kcl.Class( "Kcl.App",
{
	extend: Kcl.Primal,
	property:{
		autoLoad: true,
		loadType: "syncrhonic"
	},
	behavior: {
		construct : function(eve, loadType, typeResponse){
			Kcl.App.prototype.parent.construct.apply(this, [typeResponse]);
			Kcl.App.prototype.eve = eve;
			this.loadType = loadType || "syncrhonic";
			if(this.autoLoad) if(this.assist.frontController)
				this.assist.frontController.send({action:'loadModules'});
		},
		serverResponse:function(objResponse){
			Kcl.App.prototype.loadModules(objResponse);
		},
		buildGUI:function(params){
			for (var i in this.assist.mod)
				if(i != 'remove' && i != 'Main')
					this.assist.mod[i].buildGUI(params);
		},
		loadModules:function(response)
		{
			var _this = Kcl.App.prototype;
			if(response.plugins instanceof Array){
				_this.assist.require(response.plugins, {
					"onFinish":_this.assist.onLoadLib,
					"onLoad": _this.assist.onLoadLib,
					"params":  response.plugins,
					"callback": _this.onModulesLoaded,
					"builded" : 0
				});
			}
		},
		onModulesLoaded: function(el, elm){
			elm.params.item.builded++;
			if(elm.params.item.builded >= elm.params.item.params.length)
				Kcl.App.prototype.eve.onLoadPlugins(el);
		}
	}
});