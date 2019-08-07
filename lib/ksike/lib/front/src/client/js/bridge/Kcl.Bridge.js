/**
 *
 * @framework: Ksike
 * @package: Core
 * @subpackage: js
 * @version: 0.1

 * @description: Bridge es una libreria para el trabajo con Ajax desde Javascript
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 01/06/2010
 * @update-Date: 01/06/2010
 * @license: GPL v2
 *
 */
Kcl.Class( "Kcl.Bridge",
{
	property:{
		method: 'POST',
		url: '',
		json: null
	},
	behavior:{
		construct: function(params)
		{
			params = params || {};
			var _this    = Kcl.Bridge.prototype;
			_this.json   = new Kcl.Format.JSON();
			_this.method = params.method ? params.method : 'POST';
			_this.url    = params.url ? params.url : '';
		},
		send: function (params){},
		failure: function(error){throw {msg:"Error: "+error};	}
	}
});
