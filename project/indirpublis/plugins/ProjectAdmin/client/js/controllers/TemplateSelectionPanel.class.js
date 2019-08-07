TemplateSelectionPanel.prototype.getTarget = function(){
    var _that = TemplateSelectionPanel.prototype;
    var activeViewer = this.templatesViewer.getActiveItem();
    if(activeViewer.hasTarget() && this.form.getForm().isValid())
        return {
            'appName':     this.txt_appName.getValue(),
            'projectName': this.txt_projectName.getValue(),
            'projectPath': this.txt_projectPath.getValue(),
            'template':    activeViewer.getStore().getAt(activeViewer.selectedIndex()).data
        };
    return false;
}

TemplateSelectionPanel.prototype.on_click_btn_iconView = function(){
    var _that = TemplateSelectionPanel.prototype;
    this.templatesViewer.setActiveElement(0);
}

TemplateSelectionPanel.prototype.on_click_btn_detailView = function(){
    var _that = TemplateSelectionPanel.prototype;
    this.templatesViewer.setActiveElement(1);
}

TemplateSelectionPanel.prototype.on_select_cmb_sortSelect = function(cmb,record,index){
    var _that = TemplateSelectionPanel.prototype;
    var v = cmb.getValue();
    var active = _that.templatesViewer.getActiveItem();
    active.store.sort(v, v == 'name' ? 'asc' : 'desc');
    active.selectItem(0);
}

TemplateSelectionPanel.prototype.on_keyup_txt_filter = function(){
    this.filter();
}

TemplateSelectionPanel.prototype.filter = function(){
    var _that = TemplateSelectionPanel.prototype;
    var active = _that.templatesViewer.getActiveItem();
    active.store.filter('name',this.txt_filter.getValue());
    active.selectItem(0);
}

TemplateSelectionPanel.prototype.on_click_btn_browsePath = function(){
    var _that = TemplateSelectionPanel.prototype;
    var _this = this;
    var openFile = new OpenFileDialog({
        initialDirectory:'/var/www/'+_ADDRESS,
        title:'Select Path',
        onlyFolder:true,
        callback:function(path){
            _this.txt_projectPath.setValue(path)
        }
    });
    openFile.show();
}

TemplateSelectionPanel.prototype.on_keyup_txt_projectName = function(){
    this.txt_projectName.changeable = false;
}

TemplateSelectionPanel.prototype.on_keyup_txt_appName = function(comp,e){
    this.txt_appName.changeValue(comp.getValue());
}

TemplateSelectionPanel.prototype.changeValue_txt_appName = function(value){
    var _that = TemplateSelectionPanel.prototype;
    this.txt_appName.setValue(value);
    var proj = this.txt_projectName;
    if(proj.changeable)
        proj.setValue(this.txt_appName.getValue());
}

TemplateSelectionPanel.prototype.on_selectionchange_gridSelectionModel = function(sm){
    var _that = TemplateSelectionPanel.prototype;
    var selNode = sm.getSelected();
    
    var detailEl = _that.detailsPanel.body;
    if(selNode){
        var data = this.lookup[selNode.data.name];
        detailEl.hide();
        this.detailsTemplate.overwrite(detailEl, data);
        detailEl.slideIn('r', {
            stopFx:true,
            duration:.1
        });        
        this.txt_appName.changeValue(data.name);
        //this.getsTarget();
    }else{        
        detailEl.update();
        //this.losesTarget();
    }
}

TemplateSelectionPanel.prototype.on_selectionchange_dataView = function(dv,selects){
    var _that = TemplateSelectionPanel.prototype;
    var selNode = dv.getSelectedNodes();
    var detailEl = _that.detailsPanel.body;
    if(selNode && selNode.length > 0){
        selNode = selNode[0];
        //Ext.getCmp('btn_next').enable();
        var data = this.lookup[selNode.id];
        detailEl.hide();
        this.detailsTemplate.overwrite(detailEl, data);
        detailEl.slideIn('l', {
            stopFx:true,
            duration:.1
        });        
        this.txt_appName.changeValue(data.name);
        //this.getsTarget();
    }else{
        //Ext.getCmp('btn_next').disable();
        //this.txt_appName.changeValue("");
        detailEl.update();
        //this.losesTarget();
    }
}

TemplateSelectionPanel.prototype.on_beforeselect_dataView = function(view){
    return view.store.getRange().length > 0;
}

TemplateSelectionPanel.prototype.selectedItemId_dataView = function(){
    var selNode = this.getSelectedNodes();//[0].projectType;
    selNode = selNode[0];
    return selNode.id;
}

TemplateSelectionPanel.prototype.selectItem_dataView = function(item){
    this.select(item);
}

TemplateSelectionPanel.prototype.selectedIndex_dataView = function(){
    var selNode = this.getSelectedIndexes();//[0].projectType;
    return selNode[0];
}

TemplateSelectionPanel.prototype.hasTarget_dataView = function(){
    if(this.getSelectedNodes().lenght != 0)
        return true;
    return false;
}

TemplateSelectionPanel.prototype.selectedIndex_gridPanel = function(){
    var selected = this.getSelectionModel().getSelected();
    return this.getStore().indexOf(selected);
}

TemplateSelectionPanel.prototype.selectItem_gridPanel = function(item){
    this.getSelectionModel().selectRow(item);
}

TemplateSelectionPanel.prototype.selectedItemId_gridPanel = function(){
    var selNode = this.getSelectionModel().getSelected();
    return selNode.data.name;
}

TemplateSelectionPanel.prototype.hasTarget_gridPanel = function(){
    return this.getSelectionModel().hasSelection();
}

TemplateSelectionPanel.prototype.getActiveItem_templatesViewer = function(){
    var _that = TemplateSelectionPanel.prototype;
    var lay = this.templatesViewer.getLayout().activeItem//.id;
    //var res = Ext.getCmp(lay);
    return lay;//res;
}

TemplateSelectionPanel.prototype.setActiveElement_templatesViewer = function(item){
    var viewer = this.getActiveItem();
    var index = viewer.selectedIndex();
    var lay = this.getLayout();
    lay.setActiveItem(item);
    viewer = this.getActiveItem();
    viewer.selectItem(index);
}

TemplateSelectionPanel.prototype.on_rowselect_gridSelectionModel = function(val){
    return '<img class="list-thumb" src="'+val+'"/>';
}

TemplateSelectionPanel.prototype.renderer_gridColumn1 = function(val){
    return '<img class="list-thumb" src="'+val+'"/>';
}

TemplateSelectionPanel.prototype.on_load_store = function(){
    var _that = TemplateSelectionPanel.prototype;
    this.templatesViewer.getActiveItem().selectItem(0);
}

TemplateSelectionPanel.prototype.on_expandnode_tree = function(node){
    if(node.tplType == 'templates' && node.hasChildNodes() && node.isExpanded())
        node.firstChild.expand();
    else
        node.select();
}
                    
TemplateSelectionPanel.prototype.on_click_tree = function(node, e){
    var _that = TemplateSelectionPanel.prototype;
    if(node.isSelected() && node.isExpanded())
        _that.showNodeDetail(node);
    else
        node.expand();
}

TemplateSelectionPanel.prototype.on_beforeselect_defaultSelectionModel = function(sm,node){
    var _that = TemplateSelectionPanel.prototype;
    _that.store.load({
        params:{
            projTpl  : node.attributes.name,
            category : node.attributes.category
        }
    });	
}

TemplateSelectionPanel.prototype.on_beforeload_treeLoader = function(tl, node) {
    tl.baseParams = {
        type     : node.attributes.type,
        category    : node.attributes.category,
        typeOfNode  : node.attributes.typeOfNode
    };								
}

TemplateSelectionPanel.prototype.showNodeDetail = function(node){
    var selNode = node;
    var detailEl = this.detailsPanel.body;
    if(selNode){
        var data = { 
            description : selNode.attributes.description,
            type        : selNode.attributes.id,
            sizeString  : 12			
        };
        detailEl.hide();
        this.detailsTemplate.overwrite(detailEl,data);
        detailEl.slideIn('l', {
            stopFx:true,
            duration:.1
        });
    }else{
        Ext.getCmp('btn_next').disable();
        detailEl.update('');
    }
}

TemplateSelectionPanel.prototype.onLoadException = function(v,o){
    var _that = TemplateSelectionPanel.prototype;
    var active = _that.templatesViewer.getActiveItem();
    active.getEl().update('<div style="padding:10px;">Error loading templates.</div>');
}

String.prototype.ellipse = function(maxLength){
    if(this.length > maxLength){
        return this.substr(0, maxLength-3) + '...';
    }
    return this;
}