OpenFileDialog.prototype.renderer_gridColumn2 = function(val,a,store){
    var empty = '';
    if(store.data.empty)
        empty = " [Empty folder]"
    return '<div class="filedata"><img class="list-thumb" src="'+store.data.icon+'"/><div class="filename">'+val+empty+'</div></div>';
}

OpenFileDialog.prototype.on_keypress_obj = function(e){
    var _that = OpenFileDialog.prototype;
    if(e.getKey()==e.BACKSPACE)
        this.stepBack();
}
    
OpenFileDialog.prototype.on_render_searchFilter = function(){
    var _that = OpenFileDialog.prototype;
//_that.searchFilter.getEl().on('keyup', _that.filter)
}

OpenFileDialog.prototype.on_click_tbItem4 = function(){
    var _that = OpenFileDialog.prototype;
    this.tree.getLoader().load(this.tree.root)
}

OpenFileDialog.prototype.on_keypress_addressBar = function(cmb,e){
    switch(e.getKey()){
        case e.ENTER:
        this.loadData(this.addressBar.getValue());
        break;        
    }
}

OpenFileDialog.prototype.on_load_store1 = function(){
    var _that = OpenFileDialog.prototype;
    /*_that.store.load({
        params:{
            'path'		: _that.addressBar.getValue(),
            'extension' : _that.extensionBox.getValue().split('.')[1]
        }
    });*/
}

OpenFileDialog.prototype.on_beforeload_store1 = function(sts,obj){
    var _that = OpenFileDialog.prototype;
    params = {
        path	:_that.addressBar.getValue()
    }
}

OpenFileDialog.prototype.on_dbclick_tree = function(tree,event){
    
    }

OpenFileDialog.prototype.on_click_tree = function(node,event){
    var _that = OpenFileDialog.prototype;
    this.addressBar.setValue(node.attributes.path);
    /*this.store.load({
        params:{
            'path'		: this.addressBar.getValue(),
            'extension' : this.extensionBox.getValue().split('.')[1]
        }
    });*/
    this.loadData(node.attributes.path);
    node.expand();
    this.tree.getSelectionModel().select(node);
}

OpenFileDialog.prototype.on_beforeselect_defaultSelectionModel = function(sm,node){
    //_that.loadData(node.attributes.path);
    //sm.select(node);
    }

OpenFileDialog.prototype.on_afterrender_gridpanel = function(){
    var _that = OpenFileDialog.prototype;
    this.appViewer.getActiveItem().focus();
    this.loadData(this.initialDirectory);
}

OpenFileDialog.prototype.on_rowclick_gridpanel = function(gd,rIndex,e){
    gd.getSelectionModel().selectRow(rIndex);
}

OpenFileDialog.prototype.on_keydown_gridpanel = function(e){
    var _that = OpenFileDialog.prototype;
    e.stopEvent();
    var smodel = this.gridpanel.getSelectionModel();
    switch(e.getKey()){
        case e.ENTER:
            if(this.getSelectionModel().getSelections().length > 0)
                if(smodel.getSelections().length == 1)
                {	
                    var record = smodel.getSelected();
                    if(record.data.fileType=='Folder')
                        this.loadData(record.data.path);
                    else
                        this.getPath();
                }
            break;
        case e.BACKSPACE:			
            _that.stepBack();
            break;
        case e.DELETE:
            if(smodel.getSelections().length > 0)
                _that.deleteFiles(smodel.getSelections());
            break;
        case e.ARROWUP:										
            smodel.selectPrevious();
            break;	
        case e.ARROWDOWN:										
            smodel.selectNext();
            break;
        case e.F2:
            alert("Rename");
            break;
    }
}

OpenFileDialog.prototype.on_rowdblclick_gridpanel = function(grid,rowIndex,e){
    var _that = OpenFileDialog.prototype;
    var res = grid.getStore().getAt(rowIndex);
    //alert(res.data.fileType);
    if(res.data.fileType=='Folder'&& !(res.data.target))//||res.data.empty
        this.loadData(res.data.path);
    else{// Here is necessary to implement the extensions use.
        this.getPath();
    }
}

OpenFileDialog.prototype.on_rowselect_gridSelectionModel = function(sm,rowIndex,record){
    var _that = OpenFileDialog.prototype;
    if(record.data.fileType == 'File')
        this.dialogBox.setValue(record.data.name);
}

OpenFileDialog.prototype.on_select_extensionBox = function(){
   this.loadData(this.addressBar.getValue());
}

OpenFileDialog.prototype.on_beforeload_treeLoader = function(tl, node) {
    tl.baseParams = {
        path    : node.attributes.path,
        typeOfNode  : node.attributes.typeOfNode
    };								
}

OpenFileDialog.prototype.on_load_store = function(str,rLoaded){
    var _that = OpenFileDialog.prototype;
    this.store.sort([{
        field:'fileType',
        direction:'DESC'
    },{
        field:'name',
        direction:'ASC'
    }]);
    this.dialogBox.setValue('');
    this.appViewer.getActiveItem().selectItem(0);
}
    
OpenFileDialog.prototype.show = function(){
    var _that = OpenFileDialog.prototype;
    _that.obj.show();        
}

OpenFileDialog.prototype.loadData = function(path){
    var _that = OpenFileDialog.prototype;
    this.addressBar.setValue(path);
    this.store.load({
        params:{
            'path'	: this.addressBar.getValue(),
            'extension' : this.extensionBox.getValue().split('.')[1],
            'onlyFolder' : this.onlyFolder
        }
    });        
}

OpenFileDialog.prototype.getPath = function(){
    var _that = OpenFileDialog.prototype;
    var path = this.addressBar.getValue();
    
    if(!this.onlyFolder){
        if(this.dialogBox.isValid()){
            path += this.dialogBox.getValue();
            if(this.callback)
                this.callback(path);
        }
    }
    else{
        if(this.callback)
            this.callback(this.gridpanel.getSelectionModel().getSelected().data.path);
    }   

    _that.obj.close();    		
}

OpenFileDialog.prototype.stepBack = function(){
    var _that = OpenFileDialog.prototype;
    var path = this.addressBar.getValue();
    var i = path.length-1;
    var count = 0;
    for(i;i>0;i--){
        if(path[i]=='/')
            count++;
        if(count==2)    
            break;
    }
    var substr = path.substring(0, i+1);
    this.loadData(substr!=''?substr:'/');
}

OpenFileDialog.prototype.deleteFiles = function(files){
    var errase;
    switch(files.length){
        case 0:
            break;
        case 1:
            if(files[0].data.fileType == 'Folder')
                errase = Ext.Msg.confirm("BHike","Do you really want to delete " + files[0].data.name+" and all its contents?",deleteDesition);
            else
                errase = Ext.Msg.confirm("BHike","Do you really want to delete " + files[0].data.name+" ?",deleteDesition);
            break;
        default:
            errase = Ext.Msg.confirm("BHike","Do you really want to delete all these files?",deleteDesition);
    }

    function deleteDesition(btn){
        switch(btn){
            case 'yes':

                break;
        }
    }
}

OpenFileDialog.prototype.filter = function(){
    var _that = OpenFileDialog.prototype;
    var active = _that.appViewer.getActiveItem();
    active.store.filter('name',this.getValue());
    active.selectItem(0);
}

OpenFileDialog.prototype.selectedIndex_gridpanel = function(){
    var selected = this.getSelectionModel().getSelected();
    return this.getStore().indexOf(selected);
}

OpenFileDialog.prototype.selectItem_gridpanel = function(item){
    this.getSelectionModel().selectRow(item);
}

OpenFileDialog.prototype.selectedItemId_gridpanel = function(){
    var selNode = this.getSelectionModel().getSelected();
    return selNode.data.path; //return selNode.data.name; this is the original Value
}

OpenFileDialog.prototype.getActiveItem_appViewer = function(){
    var lay = this.getLayout().activeItem.id;
    return Ext.getCmp(lay);
}

OpenFileDialog.prototype.setActiveElement_appViewer = function(item){
    var viewer = this.getActiveItem();
    var index = viewer.selectedIndex();
    this.getLayout().setActiveItem(item);
    viewer = this.getActiveItem();
    viewer.selectItem(index);
}

OpenFileDialog.prototype.on_click_btnGrid = function(){
    var _that = OpenFileDialog.prototype;
    _that.appViewer.setActiveElement(0);
}

OpenFileDialog.prototype.on_click_btnDataview = function(){
    var _that = OpenFileDialog.prototype;
    _that.appViewer.setActiveElement(1);
}

OpenFileDialog.prototype.on_click_btnCancel = function(){
    var _that = OpenFileDialog.prototype;
    _that.obj.close();
}

OpenFileDialog.prototype.on_afterrender_obj = function(){
    var _that = OpenFileDialog.prototype;
}