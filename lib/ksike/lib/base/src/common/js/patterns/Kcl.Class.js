/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: patterns
 * @version: 0.1

 * @description: Class es una libreria para el trabajo con clases, pretende acercar el javascript a la POO
 * @authors: ing. Hermes Lazaro Herrera Martinez, ing. Antonio Membrides Espinosa
 * @making-Date: 08/12/2010
 * @update-Date: 17/01/2011
 * @license: GPL v2
 *
 */
Kcl.Class = function()
{
	if(typeof arguments[0] != "object") var _prototype = arguments[1];
	else var _prototype = arguments[0];
	var _class = false;
	var _this = Kcl.Class.prototype;
	_this.helper = _this.helper || new Kcl.Assist();	
	_this.clone = function(_in, _out, rex, typ){
		for(var i in _in) {
			if(typ){
				var type = typeof(_in[i]);
				var _typ = type.match(new RegExp(typ));
			} else var _typ = true;
			var _rex = rex ? i.match(new RegExp(rex)) : 0;
			if(_this.keyword[i]) _this.keyword[i](_in[i], _out);
			else if(!_rex && _typ) _out[i] = _in[i];
		}return _out;
	}
	_this.keyword = {
		"property" : _this.clone,
		"behavior" : _this.clone,
		"extend" : function(_in, _out, opt){
			if(_in){
				if(opt){
					var _construct = _in.prototype.construct; 
					if( _construct) _in.prototype.construct = 0;
					var _out = new _in();
					if( _construct) _in.prototype.construct = _construct;
					var _father = _out.parent ? {"parent":_out.parent} : {};
					for(var i in _out) if(typeof(_out[i])=="function"){
						_father[i] = function(){
							var _parent = this.parent;
							var _scope = _this.helper.whoCallme();
							this.parent = _scope.prototype._parent;
							_this.helper.$(_scope.prototype._ns).prototype[_scope.prototype._action].apply(this, arguments);	
							this.parent = _parent;
						}
						_father[i].prototype._action = i;
						_father[i].prototype._ns = _out._inf_.ns;
						_father[i].prototype._parent = _out.parent;
					}
					_out.parent = _father;
				}else if(_in.prototype._inf_) _out["_inf_"].parent = _in.prototype._inf_.ns;			
			}return _out;
		},
		"imitate" : function(_in, _out){
			_out._inf_.imitate = _in;
			_out.parent = _out.parent ||{};
			var _clone = function(_in, _out){
				_this.clone(_in.prototype, _out, "_inf_|parent|construct");	
				_this.clone(_in.prototype, _out.parent, "_inf_|parent|construct");		
			}
			if(typeof(_in) === "function") _clone(_in, _out);
			else if(_in instanceof Array)
				for(var i in _in) _clone(_in[i], _out);
		},
		"implements" : function(_in, _out){},
		"patterns" : function(_in, _class, _obj){
			if(_in){
				if(_obj){
					var _implement = function(key, _class, _obj){
						if(Kcl.DesignPatterns)
							if(Kcl.DesignPatterns[key]){
								if(Kcl.DesignPatterns[key].prototype.implement)
									return Kcl.DesignPatterns[key].prototype.implement(_class, _obj);
							}
						throw {msg: "Design patterns <<"+key+">> it not exist", type:"core", thrower:"KclClass"};			
					}
					var obj = false;
					if(_in instanceof Array){
						for(var i in _in)
							obj = _implement(_in[i], _class, _obj) || obj;
					}else obj = _implement(_in, _class, _obj);
					if(obj) return obj;
				} if(_class._inf_ ) _class._inf_.patterns = _in; 			
			}
		},
		"require" : function(_in, _out){
			if(_in instanceof Array){
				if(_out._inf_ ) _out._inf_.require = _in; 	
			}else _out["require"] = _in;
		},
	}
	_this.locate = function(_class, namespace){
			
		_class.prototype._inf_.ns = namespace;
		var ns = namespace.split('.');
		var _name = ns[ns.length-1];
		_class.prototype._inf_.name = _name;
		if(ns.length>1){
			delete ns[ns.length-1];
			ns = _this.helper.$(ns);
			ns[_name] = _class;	
		}else window[_name] = _class;
	}
	_this.build = function(arguments, _class){
		_class = function(){
			var obj = _this.keyword.patterns(this._inf_.patterns, _class, this);
			if(obj) return obj;
			if(this.construct) this.construct.apply(this, arguments);
		};
		_class.prototype.construct = function(){
			var _this = _class.prototype;
			if(_this.parent && _this.parent.construct) 
				_this.parent.construct.apply(_this, arguments);	
		}	
		var _body = _this.keyword.extend(_prototype.extend, {}, true);
		_body._inf_ = { type:"Kcl.Class" };
		_this.clone(_prototype, _body);
		_class.prototype = _body;
		if(typeof arguments[0] != "object") _this.locate(_class, arguments[0]);
		else _this.locate(_class, arguments[0].name);
	}(arguments, _class);
	return _class;
}