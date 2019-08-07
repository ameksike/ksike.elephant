/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: helpers
 * @version: 0.1

 * @description: Assist es una librería que encapsula los recursos nativos del framework Ksike
 * @authors: ing. Antonio Membrides Espinosa, ing. Hermes Lazaro Herrera Martinez
 * @making-Date: 01/06/2010
 * @update-Date: 22/12/2010
 * @license: GPL v2
 *
 */
var Kcl = {}
Kcl.Assist = function(uri)
{
	var _this = Kcl.Assist.prototype;
	var filesAdded = [];
	var isLoaded = function(file){
		var lst = document.getElementsByTagName("script");
		for(i in lst)
            if(lst[i].src == file) return true;
        return false;
	}

	var _is = function(path, type){
		type = type || "js";
		if(path.match(new RegExp('\.'+type+'\s*$'))) return true;
		else return false;	
	}

	var _ext = function(filename){
		var dta = filename.match(/(\.\w+)?\s*$/);	
		return dta[1] ? dta[1] : "";
	}

	var writeHead = function(path)
	{	//... less -> most dependency
		var file;
		switch(_ext(path))
		{
			case ".js": case "":
				file = document.createElement("script");
				file.type = "text/javascript";
				file.src  = path;
				file.id = "isT";
			break;
			
			case ".css": 	
				file = document.createElement("link");
				file.type = "text/css";
				file.rel  = "stylesheet";
				file.href  = path;
			break;
		}
		document.getElementsByTagName("head")[0].appendChild(file);
		return file;
	};

	var doit = function(callback, params){
		switch(typeof(callback)){
			case "function": callback(params); break;
			case "string": eval (callback+"(params);"); break;
		}
	}

	var requireAsyncrhonic = function(lst, callback, params){
		for(var i in lst) if(i !="remove")_this.include(lst[i], callback, params);
	}

	var requireSyncrhonic = function(params){
		if(params.i >= params.lst.length){ 
			if(params.onFinish) params.onFinish(params.params, params);
		}else{
			if(params.onLoad) params.onLoad(params.params, params);
			params.i++;
			if(params.lst[params.i-1]){
				if(_is(params.lst[params.i-1], "css")){
					_this.include(params.lst[params.i-1]);
					requireSyncrhonic(params);
				}else  _this.include(params.lst[params.i-1], requireSyncrhonic, params);
			}else if(params.onFinish) params.onFinish(params, params.params);
		}
	}

	_this.require = function(lst, option, params){
		if(option instanceof Function) option = { "onFinish": option, "params": params};
		option = option || {};
		option.i = 0;
		option.lst = lst;
		option.onFinish = option.onFinish || false;
		option.params = option.params || false;
		if(lst instanceof Array)
		{
			var type = type ? type : "syncrhonic";
			if(type == "syncrhonic") requireSyncrhonic(option);
			else requireAsyncrhonic(lst, option, params);
		}else _this.include(lst, option.onFinish, option.params);
	}

	_this.include = function(path, callback, params){
		if (!isLoaded(path)) 
	 	{
			filesAdded.push(path); 
	  		var fileref = writeHead(path);
			fileref.onload = function(elm){
				doit(callback, params);
			}
			fileref.onreadystatechange = function(elm){
				if (this.readyState == "loaded" || this.readyState == "complete")
					doit(callback, params);
			}
		} else doit(callback, params);
	};
	_this.$ = function(namespace, force){
		if(window[namespace]) return window[namespace];
		else if (window.Kcl[namespace]) return window.Kcl[namespace];
		if(typeof namespace == "object") var lst = namespace;
		else var lst = namespace.split('.');
		if(!window[lst[0]]) window[lst[0]] = {};
		var obj = window[lst[0]];
		for(var i=1; i<lst.length; i++)
		{
			if(lst[i]!==undefined)
			{
				if(!obj[lst[i]] ) {
					if(!force) obj[lst[i]]={}; 
					else return false;
				}
				obj=obj[lst[i]];
			} 
		}
		return obj;
	}
	_this.typeOf = function(source){
		var type = typeof(source); //number, undefined, string, object, function, array
		if(type == "object") type = (source instanceof Array) ? "array" : "object";
		return type;
	} 
	_this.whoCallme = function(deep, elm){
		deep = deep || 1;
		elm = elm || "function";
		var hand = arguments.callee;
		for(var i=0; i<deep; i++)
			hand = hand.caller;
		return (elm=="function") ? hand : hand.prototype["_"+elm];
	}
	_this._inf_ = {
		ns: "Kcl.Assist",
		name: "Assist"
	}
}