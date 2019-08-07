//... std.include(std.Router.getModulePath()+'css/style.css');
//-------------------------------------------------------------------------
Kcl.Class( 'Kcl.Main',
{
	extend: Kcl.App,
	behavior: {
		construct : function(eve, loadType){
			var _this = Kcl.Main.prototype;
			_this.parent.construct.apply(_this, [_this]);

			std.FrontController.send({
				action: 'holaMundo',
				params: {
					'name':'eje',
					'age': 23
				}
		
			});
		},
		serverResponse:function(objResponse){
			var _this = Kcl.Main.prototype;
			_this.parent.serverResponse(objResponse, _this);
			switch(objResponse.action)
			{
				case 'holaMundo':
					alert(objResponse.result);
				break;
			}
		},

		onLoadPlugins : function(params){
			alert('plugins loaded');
		}
	}
});

/*Kcl.Main.require = [
	std.Router.getModulePath()+'css/init.css',
	std.Router.getModulePath()+'js/common/MainMenuBar.js',
];*/
