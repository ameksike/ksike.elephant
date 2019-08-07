/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
Kcl.Class( 'StartPage', 
{
    property:{
        //components fields
        obj:null
    },
    behavior:{
        construct: function(params){
            var _this = StartPage.prototype;            
            this.buildGUI();
        },
        buildGUI:function(){
            var _this = StartPage.prototype;			
            this.obj = new Ext.Panel({
                title:'Start Page',
                closable:true,
                html:"<center><b>Ksike rules. We make the magic!!!</b></center>"
            });		
        }
    }
});
