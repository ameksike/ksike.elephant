std.include('plugins/ServerAdmin/client/js/common/splash.js');
std.include('plugins/ServerAdmin/client/css/app.css');
//-------------------------------------------------------------------------
Kcl.Class( 'ServerAdmin',
{
	extend: Kcl.Plugin,
	property:{
		'name': '',
		'age': ''
	},
	behavior: {
		construct:function(params)
		{
			params = params || {};
			this.name = params.name,
			this.age = params.age;
			alert('ServerAdmin');
		},
		serverResponse:function(objResponse)
		{			
		},
		buildGUI:function(params){
			var _this = ServerAdmin.prototype;
			//_this.parent.somefunction();
		}
	}
});
/*ServerAdmin.require = [
	std.Router.getModulePath()+'css/init.css',
	std.Router.getModulePath()+'js/common/MainMenuBar.js',
];*/
