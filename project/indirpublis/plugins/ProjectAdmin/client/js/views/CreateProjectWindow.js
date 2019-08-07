Kcl.Class( 'CreateProjectWindow', 
{
    property:{},
    behavior:{
        construct: function(){
            this.lookup = {};
            var _this = CreateProjectWindow.prototype;
            			
            this.treeLoader = new Ext.tree.TreeLoader({
                dataUrl: std.FrontController.getRequest("treeHandler", "ProjectAdmin"),
                requestMethod: 'GET',
                listeners:{
                    "beforeload": /*this.onAppSelect*/ function(tl, node) {
                        tl.baseParams = {
                            tplType     : node.attributes.tplType,
                            projectType : node.attributes.projectType,
                            category    : node.attributes.category,
                            typeOfNode  : node.attributes.typeOfNode
                        };								
                    }
                }
            });            
        },
        buildGUI:function(){
            var _this = CreateProjectWindow.prototype;
            
	    this.templateSelectionPanel = new TemplateSelectionPanel();
            this.templateSelectionPanel.buildGUI();
            
            this.projectConfigurationPanel = new ProjectConfigurationPanel();
            this.projectConfigurationPanel.cardReady = _this.on_cardReady_projectConfigurationPanel.createDelegate(this);
            this.projectConfigurationPanel.buildGUI();
            
            this.projectVariablesManager = new ProjectVariablesManager();
            this.projectVariablesManager.buildGUI();
            
///////////////////////////////******************************************//////////////////
            var foldersConfig = new Ext.Panel({
                id: 'card-2',
                iconCls:'library',
                layout:'fit',	
                frame:false,					
                defaults:{
                    border:false
                },
                items:[]                
            });
	    //
            //cardManager
            //
            _this.cardManager = new CardManager({
                starts:_this.on_starts_cardManager
                //ends:
            });
            this.cardManager.buildGUI();
            this.cardManager.obj.border = false;
            this.cardManager.obj.activeItem = 0;
            this.cardManager.add(this.templateSelectionPanel);
            this.cardManager.add(this.projectConfigurationPanel);
            this.cardManager.add(this.projectVariablesManager);
            this.cardManager.ends = function(){
                alert("My Function");
            }           
            //
            //btn_back
            //
            _this.btn_back = new Ext.Button();
            this.btn_back.setText("Back");
            this.btn_back.on('click',_this.on_click_btn_back);//_this.cardManager.prevCard();
            //
            //btn_next
            //
            _this.btn_next = new Ext.Button();
            this.btn_next.setText("Next");
            this.btn_next.on('click',_this.on_click_btn_next);//_this.cardManager.prevCard();
            //
            //btn_finish
            //
            _this.btn_finish = new Ext.Button();
            this.btn_finish.setText("Finish");
            this.btn_finish.on('click',_this.on_click_btn_finish,this);//_this.cardManager.prevCard();
            //
            //btn_cancel
            //
            _this.btn_cancel = new Ext.Button();
            this.btn_cancel.setText("Cancel");
            this.btn_cancel.on('click',_this.on_click_btn_cancel);//_this.cardManager.prevCard();
            //
            //obj
            //
            _this.obj = new Ext.Window({
                title: 'New Project',
                keys: [{
                    key: 27, // Esc key
                    handler: function(){
                        this.obj.close();
                    },
                    scope: this
                },{
                    key: 13, // Enter key
                    //handler: _this.btn_finish_click,
                    scope: this
                }]
            });
            //this.obj.layout = 'box';
            this.obj.setWidth(650);
            this.obj.resizable = false;
            this.obj.modal = true;
            this.obj.constrain = true;
            this.obj.iconCls = 'icon-new-project';
            this.obj.add(this.cardManager.obj);
            this.obj.addButton(this.btn_back);
            this.obj.addButton(this.btn_next);
            this.obj.addButton(this.btn_finish);
            this.obj.addButton(this.btn_cancel);
            this.obj.on('resize',function(){this.doLayout(true,true);});
        }	
    }	
});
