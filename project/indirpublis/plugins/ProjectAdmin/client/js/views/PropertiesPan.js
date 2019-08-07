Kcl.Class( 'ProjectProperties', 
{
    property:{
        //components fields
        obj:null
    },
    behavior:{
        construct: function(params){
            var _this = ProjectProperties.prototype;            

        },
        buildGUI:function(){
            var _this = ProjectProperties.prototype;			
            this.obj = new Ext.Panel({
                width:'100%',
                height:'100%',
                title:'Project Name'
            });		
        }
    }
});
