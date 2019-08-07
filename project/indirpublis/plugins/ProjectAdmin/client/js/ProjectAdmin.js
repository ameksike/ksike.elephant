
/**
 *
 * @framework: Merma
 * @package: Plugins
 * @subpackage: ProjectAdmin
 * @version: 0.1

 * @description: ProjectAdmin es una clase para ...
 * @authors: Nosinc
 * @created: 12-apr-2011 4:17:23
 * @license: GPL v3
 */ 
var load = function(){
	alert("asdsa");
}

var _IP = "localhost/";
var _ADDRESS = "ksike/project/";

Kcl.Class( "ProjectAdmin",
{
    extend: Kcl.Plugin,
    property:{
        projectWindow:null,
        projectExplorer:null,
        customPanel: null
    },
    behavior:{
        construct : function(){
            var _this = ProjectAdmin.prototype;
			
            // This is the parent's definition call
            _this.parent.construct.apply(this, []);
			
            //this.projectWindow = new CreateProjectWindow();			
        },
        buildGUI : function(params){
            var _this = ProjectAdmin.prototype;
            this.gui = params.gui;
			
            this.gui.menuBar.addItem({//--- Nuevo
                text:'Project',
                iconCls:'icon-new-project',
                handler:this.newProject
            }, "mnew");

            this.gui.menuBar.addItem({//--- Abrir
                text:'Project',
                iconCls:'icon-open-project',
                handler:function(){ 
                    var _this = ProjectAdmin.prototype;
                    _this.openProject();
                }
            }, "mopen");
                        
            this.gui.menuBar.addItem({//--- Abrir
                text:'Project',
                checked:true
            }, "mview-toolbars");

            this.gui.menuBar.addItem({//--- Menu Proyecto
                text:'Project',
                menu:[{
                    text:'Property'
                },{
                    text:'Make Module'
                },{
                    text:'Export Template',
                    disabled:true
                }]
            });
            ///////// Project Explorer Section
            _this.projectExplorer = new ProjectExplorer();
            this.gui.toolBar.addItem({
                text:'PE',
                tooltip:'Project Explorer',
                enableToogle:true,
                toogle:true,
                handler: function(){
                    _this.projectExplorer.show();
                }
            },"tbapp-starts-on");
            this.gui.east.addItem({
                layout:'border',
                frame:false,
                defaults:{
                    frame:false,
                    split:true
                },
                items:[_this.projectExplorer.obj,_this.projectExplorer.propertiesPanel.obj]
            });
            ///////// Project Explorer Section ends here
         
            
            //--- Barra de Proyecto
            this.gui.toolBar.insertItem({
                xtype:'buttongroup',
                items:[{
                    iconCls:'icon-new-project',
                    tooltip:'New Project',
                    handler:this.newProject
                },{
                    text:'OP',
                    xtype:'splitbutton',
                    tooltip:'Open Project',
                    handler:function(){ 
                        //var _this = ProjectAdmin.prototype;
                        _this.openProject();
                    },
                    menu:[{
                        text:'Recent 1'
                    },{
                        text:'Recent 2'
                    }]
					
                }]
            },0);			

        },
        newProject: function(){
            var _this = ProjectAdmin.prototype;
            this.projectWindow = new CreateProjectWindow();
            this.projectWindow.buildGUI();
            this.projectWindow.show();
        },
        openProject:function(path){		
            if(!path){
                var openFile = new OpenFileDialog({
                    initialDirectory: "/var/www/" + _ADDRESS,
                    title:'Open Project',
                    onlyFolder:true,
                    callback:function(path){
                        std.FrontController.send({
                            action: 'getProjectInfo',
                            controller: 'ProjectAdmin',
                            params:{
                                'path': path
                            }
                        });
                    }
                });
                openFile.show();
				
            }else{
                std.FrontController.send({
                    action: 'getProjectInfo',
                    controller: 'ProjectAdmin',
                    params:{
                        'path': path
                    }
                });
            }
        },
        serverResponse : function(objResponse){		
            var _this = ProjectAdmin.prototype;
            switch(objResponse._action)
            {
                case 'makeProject':					
                    var namepro = objResponse.name;
                    if(objResponse.success){
                        var pathPro = objResponse.pathPro;
                        this.openProject( pathPro+namepro+"/");
                    }
                    else
                    {
                        Ext.Msg.alert('Make Project: '+namepro, 'Error in project creation:<br/>'+objResponse.message);
                    }				
                    break;
                case 'getProjectInfo':
                    var data = objResponse.data;
                    //data.projectInfo['projectPath'] = data.projectPath;
                   // var namepro     = projectInfo.projectName;                    
                    this.projectExplorer.openProject(data);
                    var proj = data.proj;
		    			
                    //var name = data.projectInfo.vars.projectPath + data.projectInfo.vars.projectName; 
                    var iframe = document.getElementById("iframe_"+data.proj.serial);
                    if(iframe == null){
                    //--- update main gui
                    this.gui.center.addItem({
                        layout:'fit',
                        "title": "RUN-"+proj.name,//data.projectInfo.vars.projectName, 
                        "id": 'tab_'+proj.serial,                        
                        closable:true,
                        html:"<iframe style='width:100%; height:100%;' src = 'http://"+_IP+_ADDRESS+proj.name+"/index.php' id='"+"iframe_"+data.proj.serial+"' onload='load'}/>"
                    });
                    
                    // kk para arreglar 
                    std.mod.ErrorReporter.reporter.load(proj.path);	

                    	 
                    }else
                    {
                        iframe.src = "http://"+_IP+_ADDRESS+proj.name+"/index.php";//data.projectInfo.vars.projectName;
                    }
                    break;
                case 'getTplInfo':
                    this.projectWindow.customPanel.addCustomsInputs( objResponse.projectConfig.vars1 );
                    this.projectWindow.customPanel.addCustomsInputs( objResponse.appConfig.vars1 );
                    break;
                case 'getProjectTemplates':
                    alert(objResponse.data);
                    break;
                case 'getProjectPhysicContent':
                    var content = objResponse.data;
                    this.projectExplorer.loadProjectPhysicContent(content);
                    break;
            }
        }
    }
});

ProjectAdmin.require = [
    /*"plugins/ProjectAdmin/client/css/main.css",
    "plugins/ProjectAdmin/client/css/icons.css",
    
    "plugins/ProjectAdmin/client/js/common/Application.js",
    "plugins/ProjectAdmin/client/js/common/Project.js",
    
    "plugins/ProjectAdmin/client/js/views/TemplateSelectionPanel.js",
    "plugins/ProjectAdmin/client/js/controllers/TemplateSelectionPanel.class.js",
    
    "plugins/ProjectAdmin/client/js/views/DependenciesManagerPanel.js",
    "plugins/ProjectAdmin/client/js/controllers/DependenciesManagerPanel.class.js",
    
    "plugins/ProjectAdmin/client/js/views/ProjectVariablesManager.js",
    //"plugins/ProjectAdmin/client/js/controllers/ProjectVariablesManager.class.js",
    
    "plugins/ProjectAdmin/client/js/views/ProjectConstantsPanel.js",
    "plugins/ProjectAdmin/client/js/controllers/ProjectConstantsPanel.class.js",
    
    "plugins/ProjectAdmin/client/js/views/ProjectConfigurationPanel.js",
    "plugins/ProjectAdmin/client/js/controllers/ProjectConfigurationPanel.class.js",
    
    "plugins/ProjectAdmin/client/js/views/CreateProjectWindow.js",
    "plugins/ProjectAdmin/client/js/controllers/CreateProjectWindow.class.js",
    
    "plugins/ProjectAdmin/client/js/views/ProjectExplorer.js",
    "plugins/ProjectAdmin/client/js/controllers/ProjectExplorer.class.js",
    
    "plugins/ProjectAdmin/client/js/views/PropertiesViewer.js",
    "plugins/ProjectAdmin/client/js/controllers/PropertiesViewer.class.js",
    
    "plugins/ProjectAdmin/client/js/views/CustomDesignInput.js"*/
];
