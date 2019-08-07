/**
 * @Namespace:
 * @Class: Plugin
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

Kcl.Class('Plugin', 
{
    behavior:{
        construct: function(params){
            this.tpl = "defaultPlugin/";
            this.tplPath = "templates/"+params.tpl[0]+"/plugins/";
            this.optionalDirs = params.optionalDirs;
            this.name = ToolsAdmin;
        }
    }
});

