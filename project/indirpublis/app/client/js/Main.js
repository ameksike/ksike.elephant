Kcl.Class( "Kcl.Main",
{
    extend: Kcl.App,
    property:{
        gui:null
    },
    behavior: {
        construct : function(eve, loadType){
            var _this = Kcl.Main.prototype;
            this.parent.construct.apply(_this, [_this]);
			
           // _this.gui = new MainGUIDevelop();
           // _this.gui.buildGUI();
           // _this.gui.center.addItem(new StartPage().obj);
        },
        serverResponse:function(objResponse){
            var _this = Kcl.Main.prototype;
            _this.parent.serverResponse(objResponse, _this);
            switch(objResponse.action)
            {
                case '':
                    break;
            }
        },
        onLoadPlugins : function(params){
            var _this = Kcl.Main.prototype;
            _this.buildGUI({
                "gui": _this.gui
            });
        }
    }
});
//-------------------------------------------------------------------------
Kcl.Main.require = [

    'init.css',
    std.Router.lib()+'ext/css/ext-all.css',
    std.Router.lib()+'ext/css/misc/ux-all.css',
    std.Router.lib()+'ext/css/misc/fileuploadfield.css',
    std.Router.lib()+'ext/js/ext-base.js',
    std.Router.lib()+'ext/js/ext-all.js',
    std.Router.lib()+'ext/js/ext-all-debug.js',
    std.Router.lib()+'ext/js/misc/CheckColumn.js',
	
    std.Router.module()+'css/icons.css',
    std.Router.module()+'css/dataview.css',
    std.Router.module()+'css/init.css',
	
    std.Router.module()+'js/common/DataView.js',
	
    std.Router.module()+'js/common/StartPage.js',
    std.Router.module()+'js/common/MainMenuBar.js',
    std.Router.module()+'js/common/MainToolBar.js',
    std.Router.module()+'js/common/MainGUIDevelop.js',
    std.Router.module()+'js/common/CardManager.js',    
];/**/
