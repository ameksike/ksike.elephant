/**
 * @Namespace:
 * @Class: Application
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

Kcl.Class('Application', 
{
    behavior:{
        construct: function(params){
            this.path = "app/";
            this.tpl = "../app/"+params.tpl+"/";
            this.optionalDirs = params.optionalDirs;            
        },
        getJson:function(){
            return {
                "path":this.path,
                "tpl":this.tpl,
                "optionalDirs":this.optionalDirs
            };
        }
    }
});

