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
Kcl.Class( "Kcl.DesignPatterns.Singleton",
{
	implement: function(_class, _obj){
		if(!_class.prototype._inf_)  _class.prototype._inf_ = {};
		if(_class.prototype._inf_.instance) return _class.prototype._inf_.instance;
		else _class.prototype._inf_.instance = _obj;
	}
});
