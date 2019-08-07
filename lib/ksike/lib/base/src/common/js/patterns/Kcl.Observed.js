/**
 *
 * @framework: Ksike
 * @package: base
 * @subpackage: patterns
 * @version: 0.1

 * @description: Class es una libreria para el trabajo con clases, pretende acercar el javascript a la POO
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 20/01/2011
 * @update-Date: 20/01/2011
 * @license: GPL v2
 *
 */
Kcl.Class( "Kcl.DesignPatterns.Observed",
{
	implement:function(_class, _obj){
		if(!_class.prototype._inf_)  _class.prototype._inf_ = {};
		_class.prototype._inf_.subscribers = [];
		_class.prototype._inf_.event = "notify";
		_class.prototype.supply = function(obj, key)
		{
			key = key || false;
			if(!key) this._inf_.subscribers.push(obj);
			else this._inf_.subscribers[key] = obj;
			return this;
		}
		_class.prototype.trigger = function(data, event)
		{
				event = event || _class.prototype._inf_.event; 
				for(var i in _class.prototype._inf_.subscribers) {
					if(_class.prototype._inf_.subscribers[i][event])
						_class.prototype._inf_.subscribers[i][event](data);
				}
				return this;
		}	
		_class.prototype.remove = function (key)
		{
			key = key || false;
			delete _class.prototype._inf_.subscribers[key];
			return this;
		}
	}
});