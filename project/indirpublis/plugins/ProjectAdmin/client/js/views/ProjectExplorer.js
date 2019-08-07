Kcl.Class('ProjectExplorer',
{
    extend: FloattingPanel,
    behavior:{
        construct:function(params){
            this.parent.construct(params);
            this.treeLoader = new Ext.tree.TreeLoader();            
            this.treeLoader.on('beforeload',this.on_beforeexpandnode_obj);
            this.buildGUI();			
        },
        buildGUI:function(){
            var _this = ProjectExplorer.prototype;

            _this.propertiesPanel = new PropertiesViewer();
            this.defaultSelectionModel = new Ext.tree.DefaultSelectionModel();
            this.tbItem1 = new Ext.Button();
            this.toolBar = new Ext.Toolbar();                
            this.menuItem1 = new Ext.menu.Item();
            this.menuItem2 = new Ext.menu.Item();
            this.menuItem3 = new Ext.menu.Item();
            this.menuItem4 = new Ext.menu.Item();
            this.contextMenu = new Ext.menu.Menu();
            this.rootNode = new Ext.tree.TreeNode();
            //
            //menuItem1
            //
            this.menuItem1.id = "rebuild-project";
            this.menuItem1.setText("Rebuild Project");
            
            this.menuItem4.id = "execute-project";
            this.menuItem4.setText("Execute Project");

            //this.menuItem1.on('click',_this.on_click_menuItem1);
            //
            //menuItem2
            //
            this.menuItem2.id = "delete-node";
            this.menuItem2.setText("Close Project");
            //
            //menuItem3
            //
            this.menuItem3.setText("Properties");
            //
            //contextMenu
            //
            this.contextMenu.addItem(this.menuItem1);
            this.contextMenu.addItem(this.menuItem2);
            this.contextMenu.addItem(this.menuItem3);
            this.contextMenu.addItem(this.menuItem3);
            this.contextMenu.addItem(this.menuItem4);
            
            this.contextMenu.on('itemclick',_this.on_itemclick_contextMenu);
            //
            // defaultSelectionModel
            //               
            this.defaultSelectionModel.on('beforeselect',_this.on_beforeselect_defaultSelectionModel);
            //
            //tbItem1
            //
            this.tbItem1.setText('Prop');
            this.tbItem1.setTooltip('Show Properties');
            this.tbItem1.on('click',_this.on_click_tbItem1);
            //
            //toolBar
            //
            this.toolBar.add(this.tbItem1);
            //
            //rootNode
            //
            this.rootNode.setText("BHike Projects");
            this.rootNode.typeOfNode = 'solution';
            this.rootNode.id = 'root-node';
            //
            //obj
            //
            _this.obj = new Ext.tree.TreePanel({tbar:this.toolBar});                
            this.obj.region = 'center';
            this.obj.setTitle("Project Explorer");
            this.obj.rootVisible = false;            
            this.obj.setHeight(300);
            this.obj.setWidth(250);
            this.obj.treeLoader = this.treeLoader;
            this.obj.autoShow = true;
            this.obj.autoScroll = true;
            this.obj.tools = this.parent.tools;
            //this.obj.getTopToolbar() = new Ext.Toolbar();
            this.obj.contextMenu = this.contextMenu;
            this.obj.selModel = this.defaultSelectionModel;
            this.obj.setRootNode(this.rootNode);
            this.obj.on("contextmenu",this.on_contextmenu_obj);
            this.obj.on('beforeexpandnode',this.on_beforeexpandnode_obj);
        }            
    }
});
