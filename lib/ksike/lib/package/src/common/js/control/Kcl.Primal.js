/**
 *
 * @framework: Ksike
 * @package: Core
 * @subpackage: js
 * @version: 0.1

 * @description: Primal es una clase para la administracion de modulos o plugins
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 03/06/2010
 * @update-Date: 03/06/2010
 * @license: GPL v2
 *
 */
Kcl.Class( "Kcl.Primal",
{
	property:{
		typeResponse: "",
	},
	behavior: {
		construct : function(typeResponse){
			this.typeResponse = "center";
		},
		serverResponse:function(objResponse){}
	}
});
