/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
Kcl.Class( 'PropertiesViewer', 
{
    extend: FloattingPanel,
    property:{
        //components fields
        grid:null,
        obj:null,
        store:null
    },
    behavior:{
        construct: function(params){
            this.parent.construct();           
            this.store = new Ext.data.JsonStore({
                //groupField: 'group',
                url: std.FrontController.getRequest("getFiles", "OpenFileDialog"),
                method:"GET"
            });
            
            this.buildGUI();
        },
        buildGUI:function(){
            this.comboBox1 = new Ext.form.ComboBox();
            this.gridView = new Ext.grid.GridView();
            this.panel1 = new Ext.Panel();
            this.tbItem1 = new Ext.Button();
            this.toolBar = new Ext.Toolbar();            
            //
            //gridView
            //
            this.gridView.autoFill = true;
            this.gridView.emptyText = '<div style="padding:10px; text-align:center; font-weight:bold;">No properties available</div>';
            //
            //grid
            //
            this.grid = new Ext.grid.PropertyGrid({store:this.store});
            this.grid.region = 'center';
            this.grid.view = this.gridView;
            //
            //comboBox1
            //
            this.comboBox1.region = 'north';
            //
            //panel1
            //            
            this.panel1.region = 'south';
            this.panel1.setHeight(70);
            this.panel1.frame = true;
            //
            //tbItem1
            //
            this.tbItem1.setText("P");
            //
            //tbItem1
            //
            this.toolBar.add(this.tbItem1);
            //
            //obj
            //
            this.obj = new Ext.Panel({tbar:this.toolBar});
            this.obj.tools = this.parent.tools;
            this.obj.setTitle("Properties");
            this.obj.setHeight(300);
            this.obj.region = 'south';
            this.obj.layout = 'border';
            this.obj.frame = false;
            this.obj.add(this.comboBox1);
            this.obj.add(this.grid);
            this.obj.add(this.panel1);            
        }
    }
});


