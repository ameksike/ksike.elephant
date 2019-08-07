/**
 *
 * @framework: Ksike
 * @package: Core
 * @subpackage: js
 * @version: 0.1

 * @description: FrontController es una libreria para el trabajo con Ajax, funciona como controlador frontal del ladodel cliente
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 01/06/2010
 * @update-Date: 01/09/2010
 * @license: GPL v2
 *
 */
Kcl.Class( "Main",
{
	namespace: "Ksike.lib.front.src.client.js",
	patterns: "Singleton",
	property:{
		url: "index.php",
		driver: "Ajax",
		method: 'POST'
	},
	behavior: {
		construct:function(params)
		{
			params = params || {};
			this.callFunctions = new Array();
			this.base = params;
			if(params.driver) this.driver = params.driver;
			if(params.method ) this.method = params.method;
			if(params.url ) this.url = params.url;	
		},
		buildObj: function()
		{
			try {
				if(Kcl.Bridge[this.driver]){
					this.url  = this.assist.router.url ? this.assist.router.url : this.url;
					this.obj = new Kcl.Bridge[this.driver]({'method':this.method, 'url':this.url});
				}
			}catch(error){
				throw {"msg":error, "type":"core", "thrower":"Kcl.FrontController"};
			}
		},
		send: function (params)
		{
			if(!params.controller) params.controller = "Main";
			if(this.assist.router.c2p) params.proj = "&proj="+ this.assist.router.c2p;
			params.outInfo = params.outInfo || "embebed";
			params.outFormat = params.outFormat || "json";
			this.buildObj();
			this.obj.send(params, this.serverResponse);
		},
		serverResponse: function(response)
		{
			var _this = Kcl.FrontController.prototype;
			if(response){
				if(response instanceof Array)for(var i in response){
					if(i != "remove") _this.setResponse(_this.assist.mod[response[i]._plugin], response[i]);
				}else _this.setResponse(_this.assist.mod[response._plugin], response);
			}
		},
		getRequest: function(action, controller, params){
			params = params || {};
			this.buildObj();
			var controller = controller ? controller : "Main";
			var request = this.url;
			request += "?action="+action;
			request += "&outInfo=false";
			request += "&controller="+controller;
			request += "&outFormat=";
			request +=  params.outFormat || "json";
			request += (this.assist.router.c2p) ? "&proj="+ this.assist.router.c2p : "";
			if(params)request += "&params="+this.obj.json.encode(params);
			return request;
		},
		addCallFunctions: function(action){
			this.callFunctions.push(action);
		},
		dellCallFunctions: function(action){},
		failure: function(reason){},
		setResponse: function(mod, response)
		{
			if(mod)
			{
				if(mod.typeResponse == "center")
					mod.serverResponse(response);
				else if(mod[response._action]) mod[response._action](response);
			}
		}
	}
});
