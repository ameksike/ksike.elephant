/**
 * @Namespace:
 * @Class:Project
 * @Description: 
 * @Authors: Nosinc
 * @Making Date: 22/12/2010
 * @Update Date: 22/12/2010
 *
 * @package: BHike
 * @subpackage: client
 * @version: 0.1 alpha
 *
 */

Kcl.Class('Project', 
{
    property:{
        name:null,
        init:null,
        core:null,
        path:null,
        tpl:null,
        apps:null,
        tplPath:null,
        optionalDirs:null
    },
    behavior:{
        construct: function(params){
            //this.data = params;
            this.name = params.name;
            this.init = params.init;
            this.core = params.core;
            this.path = params.path;
            this.proj = params.proj;
            this.plugins = params.plugins;
            this.app = params.app;
            this.tpl = params.tpl;
            this.tplPath = params.tplPath;
            this.optionalDirs = params.optionalDirs;
        //this.vars = params.vars;
        },
        makeProject:function(){
            std.FrontController.send({
                action: 'makeProject',
                controller: "ProjectAdmin",
                params: {
                    "proj":this.getJson(),
                    "app":this.app.getJson(),
                    "plugins":this.plugins
                }
            });
        }
    },
    loadInfo:function(path){
        var path = !path? this.path:path;
        if(path){
            std.FrontController.send({
                action: 'getProjectInfo',
                controller: 'ProjectAdmin',
                params:{
                    'path': path
                }
            });
        }
    },
    getJson:function(){        
        return {
            "name":this.name,
            "init":this.init, 
            "core":this.core,
            "path":this.path,
            "proj":this.proj,
            "plugins":this.proj,
            "app":this.proj,					
            "tpl":this.tpl,
            "tplPath":this.tplPath,
            "optionalDir": this.optionalDirs/*,
                        "vars":this.vars*/
        };
    }
});

