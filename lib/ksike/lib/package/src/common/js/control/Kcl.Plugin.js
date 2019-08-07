/**
 *
 * @framework: Ksike
 * @package: Core
 * @subpackage: js
 * @version: 0.1

 * @description: Plugin es una clase para la administracion de modulos o plugins
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 03/06/2010
 * @update-Date: 03/06/2010
 * @license: GPL v2
 *
 */
Kcl.Class( "Kcl.Plugin",
{
	extend: Kcl.Primal,
	behavior: {
		buildGUI:function(params){},
		construct:function(typeResponse){
			var _this = Kcl.Plugin.prototype;
			_this.parent.construct.apply(this, [typeResponse]);
		}
	}
});
//------------------------------------------------------------------------------------------
