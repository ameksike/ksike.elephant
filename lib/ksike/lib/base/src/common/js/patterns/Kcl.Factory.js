/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: patterns
 * @version: 0.1

 * @description: Factory es una libreria para el trabajo con
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 02/06/2010
 * @update-Date: 25/09/2012
 * @license: GPL v2
 *
 */
Kcl.Class( "Kcl.Factory",
{
	patterns: "Singleton",
	behavior: {
		construct:function(params)
		{
			this.reConfig(params);
		},
		reConfig:function(params)
		{
			params = params || {};
			this.objs = [];
			this.vendor = params.vendor;
			this.mods = params.mods;
		},
		getClass: function(_class)
		{
			return this.vendor.$(_class);
		},
		inject: function(_class)
		{
			if(!_class.prototype.assist) _class.prototype.assist = this.vendor;
			return _class;
		},
		make: function(opt)
		{
			if(opt.name){
				var _this = opt._this;
				opt._class = (!opt._class) ? _this.inject(_this.getClass(opt.name)) : _this.inject(opt._class);
				var obj = new opt._class(opt.params);
				if(window.Kcl.Primal){
					_this.inject(Kcl.Primal, _this);
					if(obj instanceof Kcl.Primal){
						_this.mods[opt.base] = obj;
						if(!obj._inf_ || obj._inf_.type != "Kcl.Class") obj.construct(opt.params);
					} else _this.vendor[opt.alias] = obj;
				}else _this.vendor[opt.alias] = obj;
				_this.objs.push(opt.name);
				if(opt.callback) opt.callback(obj, opt);
			}
		},
		build: function(opt, callback, params)
		{
			opt = (typeof(opt)=="string") ? this.parse(opt) : opt;
			if (this.objs.indexOf(opt.name) == -1) 
			{
				opt._class = this.getClass(opt.name);
				opt.callback = callback;
				opt.params = params;
				if(opt._class){
					opt._this = this;
					opt.type = "free";
					if(opt._class.prototype._inf_.require){
						this.vendor.require(opt._class.prototype._inf_.require, { "onFinish":Kcl.Factory.prototype.make, "params": opt} , opt);
					}else this.make(opt);
				}
			}else throw {"msg":"Warning: The instance of <<"+opt.name+">> it really exist", "type":"core", "thrower":"Kcl.Factory"};
		},
		parse: function(str)
		{
			var className = str.match(/((\w|\-|\.)+)?\s*$/);  
			className = className[1].match(/.+[^\.js]/);
			var alias = className[0].match(/((\w|\-|)+)$/);
			return {
				"name": className[0],
				"base": alias[0],
				"alias": this.lcfirst(alias[0])
			}
		},
		lcfirst: function  (str) {
			var f = str.charAt(0).toLowerCase();
			return f + str.substr(1);
		},
		ucfirst: function  (str) {
			var f = str.charAt(0).toUpperCase();
			return f + str.substr(1);
		}
	}
});