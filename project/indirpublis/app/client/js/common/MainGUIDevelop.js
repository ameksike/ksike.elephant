/**
 *
 * Description: MainGUIDevelop es la libreria principal para la administracion de las interfaces
 * Authors: ing Antonio Membrides Espinosa, ...
 * Making Date: 22/12/2010
 * Update Date: 22/12/2010
 *
 * @package: app
 * @subpackage: js
 * @version:
 *
 */

Kcl.Class('MainGUIDevelop',
{
    property:{
        obj:null,
        north:null,
        center:null,
        east:null,
        west:null,
        south:null,
        toolBar:null,
        menuBar:null
    },
    behavior:{
        construct:function(){			
        //this.buildGUI();
        },
        buildGUI:function(){
            var _this = MainGUIDevelop.prototype;
            Ext.BLANK_IMAGE_URL = "../../lib/ext/images/default/s.gif";
            Ext.QuickTips.init();
			
            _this.toolBar = new MainToolBar();
            _this.menuBar = new MainMenuBar();
            
            _this.startPage = new StartPage();
            
            this.north = new Ext.Panel({
                id:'north',
                frame:false,
                padding:-5,
                height:100,
                region:'north',
                layout:'border',
                border:false,
                defaults:{
                    border:false
                },
                items:[
                new Ext.BoxComponent({
                    el:'header-div', 
                    region:'north'
                }),
                new Ext.Panel({
                    id:'north_contents',
                    region:'center',
                    border:false,
                    defaults:{
                        border:false
                    },
                    tbar: _this.menuBar.obj,
                    items: _this.toolBar.obj

                })
                ]
            });
			
            this.south = new Ext.TabPanel({
                title:'Algo',
                id:'south',
                height:50,
                region:'south',    
                activeTab:0,
                split:true,
                collapsible:true,
                collapseMode:'mini',
                collapsed:true,
                tabPosition:'bottom',
                items:[{
                    title:'Errors'
                }],
                addItem: function(obj){
                    this.add(obj);	
                    this.doLayout();
                }
            });
			
            this.west= new Ext.Panel({
                title:'West',
                id:'west',
                width:150,
                region:'west',
                collapsible:true,
                collapseMode:'mini',
                split:true,
                collapsed:true,
                addItem: function(obj){
                    this.add(obj);
                    this.expand(obj.expand ? obj.expand : true);
                },
                rem: function(obj){
                    _this.tab.remove(obj);
                }
            });
			
            this.east = new Ext.Panel({
                width:250,
                layout: 'fit',
                region:'east',
                hidden:true,
                //collapsible:true,
                collapsed:true,
                collapseMode:'mini',
                split:true,			
                addItem:function(obj){			
                    this.add(obj);
                    this.show();
                    this.doLayout();
                    this.expand();
                }
            });
			
            this.center = new Ext.TabPanel({
                id:'center',
                width:150,
                enableTabScroll:true,
                region:'center',				
                activeTab: 0,
                addItem: function(obj){
                    this.add(obj).show();
                }
            });
						
            this.obj = new Ext.Viewport({
                //renderTo:document.body,
                defaults:{
                    frame:false,
                    border:false,
                    margins:'0px'
                },
                layout: 'border',
                frame: false,
                items: [{
                    region:'center',
                    layout:'border',
                    items:[this.center,this.south]
                },
                this.north,
                this.west,
                this.east
                ],
                addItem: function(obj){
                    this.add(obj);
                    this.doLayout();
                }
            });
            
			
        }
    }    
});

/*std.require([
	std.Router.getModulePath()+'js/common/MainMenuBar.js',
	std.Router.getModulePath()+'js/common/MainToolBar.js'
]);*/
