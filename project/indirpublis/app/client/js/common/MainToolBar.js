/**
 *
 * Description: MainToolBar es libria principal para la administracion de las interfaces
 * Authors: ing Antonio Membrides Espinosa
 * Making Date: 22/12/2010
 * Update Date: 22/12/2010
 *
 * @package: app
 * @subpackage: js
 * @version:
 *
 */
Kcl.Class("MainToolBar",{
    property:{
        obj:null
    },
    behavior:{
        construct:function(){
            this.buildGUI();
        },
        buildGUI:function(){
            this.obj = new Ext.Toolbar({
                defaults:{
                    scale:'small'
                },
                items:['->',{
                    id:'tbapp-starts-on',
                    xtype:'buttongroup',
                    items:[{
                        text:'SP',
                        tooltip:'Start Page',
                        handler:function(){}
                    }]
                },'-']
            });
        },
        addItem:function(toolObj,id){
            if(id){
                var com = Ext.getCmp(id);
                if(com) com.add(toolObj);
            }
            else {
                this.obj.add(toolObj);
                this.obj.doLayout();
            }
            this.obj.doLayout();
        },
        insertItem:function(obj,index){
            this.obj.insert(index,obj);
            this.obj.doLayout();
        }
    }
});
