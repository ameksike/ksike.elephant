/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
ProjectExplorer.prototype.on_contextmenu_obj = function(node, e) {
    //          Register the context node with the menu so 
    //			that a Menu Item's handler function can access		
    //          it via its parentMenu property.

    node.select();
    var c = node.getOwnerTree().contextMenu;
    c.contextNode = node;
    c.showAt(e.getXY());
}

ProjectExplorer.prototype.on_click_tbItem1 = function(){
    var _that = ProjectExplorer.prototype;
    if(!_that.propertiesPanel.obj.isVisible())
        _that.propertiesPanel.show();
    if(_that.obj.getSelectionModel().getSelectedNode()!= null)
        _that.propertiesPanel.showProperties(_that.obj.getSelectionModel().getSelectedNode().attributes.data.data);
}

ProjectExplorer.prototype.on_beforeselect_defaultSelectionModel = function(sm,node){
    var _that = ProjectExplorer.prototype;
    _that.propertiesPanel.showProperties(node.attributes.data);
}

ProjectExplorer.prototype.on_itemclick_contextMenu = function(item) {
    switch (item.id) {
    	case 'execute-project':
            var n = item.parentMenu.contextNode;
            if (n.parentNode) {
                var iframe = document.getElementById("iframe_"+n.attributes.data.serial);
            	iframe.src = iframe.src;
            }
            break;
        case 'delete-node':
            var n = item.parentMenu.contextNode;
            if (n.parentNode) {
                n.remove();
            }
            break;
        case 'rebuild-project':
            var node = item.parentMenu.contextNode;
            var project = node.attributes.data;
            var app  = node.findChild('typeOfNode','app').attributes.data;
            
            var vars = {};
            for(var i in project.data)
                vars[i]= project.data[i];
            for(var i in app.data)
                vars[i]= app.data[i];
            
            var ToolsAdmin = {
                "tpl":"defaultPlugin/",
                "tplPath":"templates/ksike/plugins/",
                "optionalDir":[
                "css",
                "img",
                "common",
                "config",
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
                "tplPath":"templates/ksike/plugins/",
                "optionalDir":[
                "css",
                "img",
                "common",
                "config"
                ],
                "data":{
                    "name":"ServerAdmin",
                    "news":"$this->data = \'Info\'; ",
                    "const":"alert(\'soy DevelopAdmin\'); var valido = function(){ return false; }"
                }
            }
            
            var newApp = new Application({
                "path":"app/",
                "tpl":"../app/ExtJS/",
                "optionalDirs": ["css", "img", "log", "common", "config", "include"]
            });
            
            var newProject = new Project({
                "name":project.projectName,
                "init":"app/config/", 
                "core":"../../",
                "path": project.projectPath,
                "proj":"project/"+project.projectName+"/",
                "plugins":[ToolsAdmin, ServerAdmin],
                "app":newApp,
                "tpl":project.tpl,
                "tplPath":project.tplPath,
                "optionalDirs": ["lib","tools","core","core/config","plugins"],
                "vars":vars             
            });
            newProject.makeProject();
            break;
    }
}

ProjectExplorer.prototype.openProject = function( data ){ 
    //dudoso 
    var existsProject = this.obj.root.findChild('id','node_'+data.proj.serial);
    if( existsProject == null){
        var proj = data.proj;
        //var app     = data.appInfo.vars;
        var dep = data.data.dep;
        
        var depNode = new Ext.tree.TreeNode({
            text: "References",
            projName:proj.name,
            typeOfNode:'dep',
            data:dep
        });
        for(var i = 0; i< dep.length;i++)
        {
            var nd = {
                'text':dep[i].name,
                'data':dep[i],
                'leaf':true
            };            
            depNode.appendChild(nd);
        }
        
        var projNode = new Ext.tree.TreeNode({
            text: proj.name,
            id: 'node_'+proj.serial,
            projName:proj.name,
            typeOfNode:'proj',
            icon:'plugins/OpenFileDialog/client/img/defaults/FileIcons/bhproj.png',
            //expanded: true,
            data:proj/*,
            children:[{
                text:"App",                
                typeOfNode:'app',
                data:app,
                children:[{
                    text:"Properties",
                    leaf:true,
                    typeOfNode:'prop',
                    data:app.data
                }]
            },{
                text:"Properties",
                leaf:true,
                typeOfNode:'prop',
                data:project.data
            },{
                text:"References",
                leaf:true,
                data:references
            }]*/
        });
        projNode.appendChild(depNode);
        this.obj.root.appendChild(projNode);
        projNode.expand();
        //this.obj.getSelectionModel().select(this.obj.root.findChild('id',project.projectPath+project.projectName));
    }
    else
        this.obj.getSelectionModel().select(existsProject);
    //fin dudoso

    /*if(!this.activeProject)
        this.setActiveProject(project.projectPath+project.projectName);*/
}

ProjectExplorer.prototype.setActiveProject = function( projName ){
    var _this = ProjectExplorer.prototype;
    var activeProjText = "";
    if(this.activeProject){
        activeProjText = this.obj.root.findChild( 'id', this.activeProject ).projectName;			
        this.obj.root.findChild( 'id', this.activeProject ).setText( activeProjText );
    }

    this.activeProject = projName;
    activeProjText = this.obj.root.findChild( 'id', projName ).text;
    this.obj.root.findChild( 'id', projName ).setText( '<b>'+activeProjText+'</b>' );
}

ProjectExplorer.prototype.getActiveProject = function(){
    return this.obj.root.findChild( 'id', this.activeProject);
}

ProjectExplorer.prototype.on_click_menuItem1 = function(){
    
}

ProjectExplorer.prototype.loadProjectPhysicContent = function(c){
    var children = c.children;
    var node = this.obj.root.findChild('id', c.guest);
    for(var i = 0; i < children.length;i++){
        var child = children[i];
        child.type = 'async';
        node.appendChild(child);
    }
}

ProjectExplorer.prototype.on_beforeload_treeLoader = function(tl,node,callbak){
    alert("Que vola");
}

ProjectExplorer.prototype.on_beforeexpandnode_obj = function(node, deep, anim){
    if(node.id != 'root-node'){
        std.FrontController.send({
            action: 'getProjectPhysicContent',
            controller: 'ProjectAdmin',
            params:{
                'path': node.attributes.data.path,
                'guest':node.attributes.id
            }
        });
    }
}
