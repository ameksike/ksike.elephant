CreateProjectWindow.prototype.on_click_btn_finish = function(){
    var _that = CreateProjectWindow.prototype;
    var data = this.templateSelectionPanel.getTarget();	
    var optionalDirs = this.projectConfigurationPanel.getOptionalDirs();
	
    //var customParams = _that.customPanel.getInputData();
	
    /*var data = {
        'name': Ext.getCmp('txt_projectName').getValue(),
        'tpl' : sel.projectType.split("/"),
        'optionalDir': optionalDirs,
        'vars': customParams,
        'projectPath': _that.projectPath.getValue()
    };*/
    //data.optionalDir = this.
    //alert(data.projectPath);   
    /*for(var i in optionalDirs){
        alert(optionalDirs[i]);
    }*/
    
    _that.buildProy(data);		
    _that.obj.close();
//return alert("Crear");
}

CreateProjectWindow.prototype.on_click_btn_back = function(){
    var _that = CreateProjectWindow.prototype;
    _that.cardManager.prevCard();  
    _that.btn_next.setDisabled(_that.cardManager.lastCardVisible());
    _that.btn_back.setDisabled(_that.cardManager.firstCardVisible());
}

CreateProjectWindow.prototype.on_click_btn_next = function(){
    var _that = CreateProjectWindow.prototype;
    _that.cardManager.nextCard();
    _that.btn_next.setDisabled(_that.cardManager.lastCardVisible());
    _that.btn_back.setDisabled(_that.cardManager.firstCardVisible());   
}

CreateProjectWindow.prototype.on_click_btn_cancel = function(){
    var _that = CreateProjectWindow.prototype;
    _that.obj.close();   
}

CreateProjectWindow.prototype.on_cardReady_projectConfigurationPanel = function(){
    var _that = CreateProjectWindow.prototype;
    var data = this.templateSelectionPanel.getTarget();
    this.projectConfigurationPanel.setData(data);
}

CreateProjectWindow.prototype.on_starts_cardManager = function(){
    var _that = CreateProjectWindow.prototype;
    _that.btn_back.setDisabled(true);
}

CreateProjectWindow.prototype.buildProy = function(params){
    //... plugins ......
    var ToolsAdmin = {
        "tpl":"defaultPlugin/",
        "tplPath":"templates/"+params.template.category+"/plugins/",
        "optionalDir":[
        "css",
        "img",
        "common",
        "cfg",
        "include",
        "controllers",
        "views"
        ],
        "data":{
            "name":"ToolsAdmin"
        } 
    }

    var ServerAdmin = {
        "tpl":"customPlugin/",
        "tplPath":"templates/"+params.template.category+"/plugins/",
        "optionalDir":[
        "css",
        "img",
        "common",
        "cfg"
        ],
        "data":{
            "name":"ServerAdmin",
            "news":"$this->data = \'Info\'; ",
            "const":"alert(\'soy DevelopAdmin\'); var valido = function(){ return false; }"
        }
    }
    
    var newApp = new Application({
        "path":"app/",
        "tpl":params.template.name,
        "optionalDirs": ["css", "img", "log", "common", "cfg", "include"]
    });
    
    var newProject = new Project({
        "name":params.appName,
        "init":"app/cfg/", 
        "core":"../../",
        "path": params.projectPath,
        "proj":"project/"+params.projectName+"/",
        "plugins":[ToolsAdmin, ServerAdmin],
        "app":newApp,					
        "tpl":params.template.proj+"/",
        "tplPath":"templates/"+params.template.category+"/project/",
        "optionalDirs": ["lib","tools","core","core/cfg","plugins"]//,//params.optionalDir, 
    //"vars":params.vars
    });
    newProject.makeProject();    
}

CreateProjectWindow.prototype.show = function(){
    this.obj.show();
}
