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
Kcl.Class( "Kcl.Error",
{
	patterns: ["Singleton", "Observed"],
	behavior: {
		construct: function(params){
			this._inf_.event = "onCatch";
		}
	}
});
