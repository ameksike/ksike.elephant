/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: patterns
 * @version: 0.1

 * @description: POO es una libreria para el trabajo con
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 02/06/2010
 * @update-Date: 25/09/2010
 * @license: GPL v2
 *
 */
Kcl.OOP = function()
{
	var _this = Kcl.OOP.prototype;
	//...........................................................
	_this.initialice = function(obj, Class, params)
	{
		Class.apply(obj, params);
	}
	//...........................................................
	_this.extend = function(Child, Parent)
	{
		var _construct = Parent.prototype.construct; 
		if(_construct) Parent.prototype.construct = 0;
		Child.prototype = new Parent();
		if(_construct) Parent.prototype.construct = _construct;
		Child.prototype._inf = 0;
		Child.prototype.parent = Child.prototype;
	}
	//...........................................................
	_this.imitate = function(obj, parent, params)
	{
		if(obj && parent){
			if(!params) params = [[]];
			if(!obj.parent) obj.parent = new Object();
			_this.initialice(obj, parent, params);
			_this.initialice(obj.parent, parent, params);
		}
	}
	//...........................................................
	_this.implement = function() 
	{
	    if(arguments.length < 1) {
		throw new Error("Tiene" + arguments.length + " argumento, como minimo 1.");
	    }
	    if(this.prototype == {}){
		throw new Error("La Clase no implementa ningun metodo");
	    }
	    for(var i = 0, len = arguments.length; i < len; i++) {
		var iface = arguments[i];
		for(var j in iface.prototype) {
		    var method = null;
		    if(iface.prototype[j] instanceof Function)
		        method = j;
		    else
		        continue;
		    if(!this.prototype[method] || typeof this.prototype[method] !== 'function') {
		        throw new Error("La Clase "
		            + "no puede implementar la interfaz " + iface
		            + ". El metodo " + method + " no se encuentra.");
		    }
		}
	    }
	};
}
//------------------------------------------------------------------------------------------
