/**
 *
 * Description: MainMenuBar es libria principal para la administracion de las interfaces
 * Authors: ing Antonio Membrides Espinosa
 * Making Date: 22/12/2010
 * Update Date: 22/12/2010
 *
 * @package: app
 * @subpackage: js
 * @version:
 *
 */
 
Kcl.Class("MainMenuBar",{
    property:{
        obj:null
    },
    behavior:{
        construct:function(){
            this.buildGUI();
        },
        buildGUI:function(){
            this.obj = new Ext.Toolbar({
                id:'mainToolBar',
                items: ['-',{
                    text:'<u>F</u>ile',
                    id: "mfile",
                    menu:[{
                        text:'<u>N</u>ew',
                        id: "mnew",
                        menu:[]
                    },{
                        text:'<u>O</u>pen',
                        id: "mopen",
                        menu:[]
                    },'-',{
                        text:'<u>A</u>dd',
                        id: "madd",
                        disabled:true,
                        menu:[]
                    },'-',{
                        text:'<u>C</u>lose',
                        id: "mclose",
                        menu:[]
                    },{
                        text:'<u>Cl</u>ose All',
                        id: "mcloseall",
                        menu:[]
                    },'-',{
                        text:'<u>S</u>ave',
                        id: "msave",
                        disabled:true,
                        menu:[]
                    },{
                        text:'<u>S</u>ave All',
                        id: "msaveall",
                        disabled:true,
                        menu:[]			
                    },'-',{
                        text:'<u>R</u>ecent Project',
                        disabled:true
                    },'-',{
                        text:'Salir'
                    }]
                },{
                    text:'<u>V</u>iew',
                    id:'mview',
                    menu:[{
                        id:'tooltip_btn_dbexplorer',
                        text:'DB Explorer',
                        iconAlign:'right',
                        checked:false
                    },{
                        id:'tooltip_btn_sqlassistant',
                        text:'SQL Assistant',
                        iconAlign:'right',
                        checked:false
                    },{
                        text:'<u>T</u>oolbars',
                        id:'mview-toolbars',
                        menu:[]
                    }]
                },{
                    text:'<u>T</u>ools',
                    id: "mtools",
                    menu:[]          
                }]
            });
        },
        addItem:function(menuObj, id)
        {
            if(id){
                var com = Ext.getCmp(id);
                if(com) com.menu.add(menuObj);
            }
            else {
                this.obj.add(menuObj);
                this.obj.doLayout();
            }
        }
    }
});
