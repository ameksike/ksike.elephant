/*
 * @application: BHike
 * @version: 0.1
 * @package: alpha
 * 
 * @description: DependenciesManagerPanel is a class that implements...
 * @authors: Nosinc
 * @created: 09-oct-2011 9:52:25
 * @license: GPL v3
 **/

Kcl.Class( 'DependenciesManagerPanel', 
{
    extend:CardPanel,
    property:{
        obj:null,
        data:null
    },
    behavior:{
        construct: function(params){
            var _this = DependenciesManagerPanel.prototype;
            this.lookup = {};
            _this.store = new Ext.data.JsonStore({
                url: std.FrontController.getRequest("getDependencies", "ProjectAdmin"),
                root:'info',
                fields: ['state','icon','name','url','category','description','version'],
                sortInfo:{field: 'category', direction: "ASC"}
            });
            this.store.on('load',_this.on_load_store.createDelegate(this));
            _this.backup_store = new Ext.data.GroupingStore({
                reader: new Ext.data.ArrayReader({}, ['state','icon','name','url','category','description','version']),
                sortInfo:{field: 'category', direction: "ASC"},
                groupField:'category'                
            });
        },
        buildGUI:function(){
            var _this = DependenciesManagerPanel.prototype;
            
            this.gridSelectionModel = new Ext.grid.RowSelectionModel();
            this.gridView = new Ext.grid.GroupingView();
            var sm = new Ext.grid.CheckboxSelectionModel();
            //
            //btn_addPlugin
            //
            this.btn_addPlugin = new Ext.Button();
            this.btn_addPlugin.setText("Add New");
            /*this.btn_addPlugin.on('click',function(){
                var op = new OpenFileDialog({
                    title:'Add New Plugin',
                    initialDirectory: "/var/www/work/Nosinc/Developing/ksike/plugins",
                    callback:function(path){
                        
                    }
                });
                op.show();                
            });*/
            //
            //btn_removePlugin
            //
            this.btn_removePlugin = new Ext.Button();
            this.btn_removePlugin.setText("Remove");
            //
            //btn_changeState
            //
            this.btn_changeState = new Ext.Button();
            this.btn_changeState.setText("Activate/Deactivate");
            //
            //btn_modifyPath
            //
            this.btn_modifyPath = new Ext.Button();
            this.btn_modifyPath.setText("Modify Path");            
            //
            //btn_getOnline
            //
            this.btn_getOnline = new Ext.Button();
            this.btn_getOnline.setText("Extensions Online");
            //
            //toolBar
            //
            this.toolBar = new Ext.Toolbar();
            this.toolBar.add(this.btn_addPlugin);
            this.toolBar.add(this.btn_removePlugin);
            this.toolBar.add(this.btn_changeState);
            this.toolBar.add(this.btn_modifyPath);
            this.toolBar.add(this.btn_getOnline);
            
            this.cmbStore = new Ext.data.ArrayStore({
                fields:[{type:'string',name:'version'}]
            });
            
            this.cmb_editor =   new Ext.form.ComboBox();
            this.cmb_editor.store = this.cmbStore;
            this.cmb_editor.editable = false;
            //this.cmb_editor.typeAhead = true;
            this.cmb_editor.triggerAction = 'all';
            this.cmb_editor.lazyRender = true;
            this.cmb_editor.mode = 'local';
            this.cmb_editor.displayField = 'version';
            this.cmb_editor.valueField = 'version';
            this.cmb_editor.on('beforequery',_this.on_beforequery_cmb_editor);
            this.cmb_editor.on('beforerender',_this.on_beforerender_cmb_editor);
            //
            //gridColumnModel
            //
            this.gridColumnModel = new Ext.grid.ColumnModel([{
                id:'icon', 
                header:'Icon', 
                width:100,
                hidden:true,
                dataIndex:'icon'
            },{
                id:'name', 
                header:'Name', 
                width:50, 
                dataIndex:'name'
            },{
                id:'version', 
                header:'Ver.', 
                width:30, 
                dataIndex:'version',
                editor: this.cmb_editor
            },{
                id:'category', 
                header:'Category', 
                width:100, 
                dataIndex:'category',
                hidden:true
            },{
                id:'url', 
                header:'Path', 
                width:100, 
                dataIndex:'url'
            },{
                id:'state',                
                xtype:'checkcolumn',
                header:'Active',
                width:40, 
                dataIndex:'state'
            }]);
            //
            //gridSelectionModel
            //
            this.gridSelectionModel.singleSelect = true;
            this.gridSelectionModel.on('rowselect',_this.on_rowselect_gridSelectionModel.createDelegate(this));
            //
            //gridView
            //
            this.gridView.emptyText = '<div style="padding:10px; text-align:center; font-weight:bold;">No dependencies available</div>';
            this.gridView.forceFit = true;
            this.gridView.groupTextTpl = '{text}({[values.rs.length]} {[values.rs.length > 1 ? "Items" : "Item"]})';
            //
            //gridPanel
            //
            _this.gridPanel = new Ext.grid.EditorGridPanel({
                tbar:this.toolBar,
                margins:'2 2 2 2'
            });
            this.gridPanel.clicksToEdit = 1;
            this.gridPanel.region = 'center';
            this.gridPanel.store = this.backup_store;
            this.gridPanel.colModel = this.gridColumnModel;
            this.gridPanel.selModel = this.gridSelectionModel;
            this.gridPanel.autoExpandColumn = 'url';
            this.gridPanel.autoScroll = true;
            this.gridPanel.columnLines = true;
            this.gridPanel.enableHdMenu = false;
            this.gridPanel.border = true;
            this.gridPanel.enableKeyEvents = true,
            this.gridPanel.view = this.gridView;
            this.gridPanel.selectedIndex = _this.selectedIndex_gridPanel;
            this.gridPanel.selectItem = _this.selectItem_gridPanel;
            this.gridPanel.selectedItemId = _this.selectedItemId_gridPanel;
            //this.gridPanel.hasTarget = _this.hasTarget_gridPanel;
            this.gridPanel.on('afteredit',_this.on_afteredit_gridPanel.createDelegate(this));        
            //
            //template
            //
            this.template = new Ext.XTemplate(
                '<div class="config-details">',
                '<tpl for="."><div class="config-details-info">',
                '<b>Version:</b>',
                '<span>{version}</span>',
                '<b>Description:</b>',
                '<span>{description}</span></div>',
                '</tpl>',
                '</div>'
            );
            this.template.compile();
            //
            //detailsPanel
            //
            this.detailsPanel = new Ext.Panel({
                title:'Details',
                margins:'2 2 2 0'
            });
            this.detailsPanel.tpl = this.template;
            this.detailsPanel.region = 'east';
            this.detailsPanel.setWidth(250);
            //
            //obj
            //
            this.obj = new Ext.Panel({
                title:"Dependencies",                
                padding:'2'
            });
            this.obj.iconCls = 'icon-library';
            this.obj.layout = 'border';
            //this.obj.frame = true;
            this.obj.border = false;
            this.obj.add(this.gridPanel);
            this.obj.add(this.detailsPanel);
            this.obj.on('activate',_this.on_afterrender_obj);
            
            
            
        }	
    }	
});
