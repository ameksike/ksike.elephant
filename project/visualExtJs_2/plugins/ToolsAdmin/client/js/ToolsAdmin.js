//... std.include('plugins/ToolsAdmin/client/');
//-------------------------------------------------------------------------
Kcl.Class( 'ToolsAdmin',
{
	extend: Kcl.Plugin,
	property:{

	},
	behavior: {
		construct:function(params){
			//alert('ToolsAdmin');
		},
		serverResponse:function(objResponse)
		{			
		},
		buildGUI:function(params){
			var _this = ToolsAdmin.prototype;
			//_this.parent.somefunction();
		}
	}
});
/*ToolsAdmin.require = [
	std.Router.getModulePath()+'css/init.css',
	std.Router.getModulePath()+'js/common/MainMenuBar.js',
];*/
