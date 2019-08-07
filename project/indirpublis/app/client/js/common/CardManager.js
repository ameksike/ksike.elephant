/*
 * @application: BHike
 * @version: 0.1
 * @package: alpha
 * 
 * @description: CardManager is a class that implements...
 * @authors: Nosinc
 * @created: 09-oct-2011 10:26:31
 * @license: GPL v3
 **/

Kcl.Class( 'CardManager', 
{
    property:{
        obj:null,
        collection:null,
        ends:null,
        starts:null
    },
    behavior:{
        construct: function(params){
            var _this = CardManager.prototype;
            this.collection = [];
            /////////////////////////////////////////////////////////////
            _this.starts = !params || !params.starts ? null: params.starts;
            _this.ends   = !params || !params.ends   ? null: params.ends
        },
        buildGUI:function(params){
            var _this = CardManager.prototype;
            _this.obj = new Ext.Panel();
            this.obj.layout = 'card';
            this.obj.autoHeight = true;
            this.obj.autoWidth = true;
            this.obj.on('afterrender',_this.on_afterrender_obj);
        }	
    },
    add:function(elem){
        this.obj.add(elem.obj); 
        var key = 'card-'+(this.obj.items.length-1);
        this.collection[this.obj.items.length-1] = [key,elem];               
    },
    getActiveItem:function(){
        var lay = this.obj.getLayout().activeItem.id;
        return Ext.getCmp(lay);
    },
    getActiveCard:function(){
        var acItm = this.obj.getLayout().activeItem;
        for(var i in this.collection){
            if(this.collection[i][1].obj.id == acItm.id)
                return this.collection[i][0];
        }
        return false;
    },
    setActiveItem:function(item){
        this.obj.getLayout().setActiveItem(item);
    },
    cardNav: function(incr){
        var l = this.obj.getLayout();
        var i = this.getActiveCard().split('card-')[1];
        //alert(i);
        var next = parseInt(i,10) + incr;        
        if(next==this.obj.items.length){
            this.ends();
        }
        else{
            var item = this.collection[next][1];
            this.setActiveItem(item.obj);
            item.cardReady();
        }
        if((parseInt(i,10) + incr)== 0 && this.starts!=null)
            this.starts();
    },
    nextCard:function(){
        this.cardNav(1);
    },
    prevCard:function(){
        this.cardNav(-1);
    },
    on_afterrender_obj:function(){
        var _this = CardManager.prototype;
        
        if(_this.starts != null)
            _this.starts();
    },
    firstCardVisible:function(){
        return this.getActiveCard() == 'card-0';
    },
    lastCardVisible:function(){
        var _this = CardManager.prototype;
        var val = this.getActiveCard();
        return val == 'card-'+(this.obj.items.length-1);
    }
});


/*
 * @application: BHike
 * @version: 0.1
 * @package: alpha
 * 
 * @description: CardPanel is a class that implements...
 * @authors: Nosinc
 * @created: 09-oct-2011 10:26:31
 * @license: GPL v3
 **/

Kcl.Class( 'CardPanel', 
{
    property:{
        obj:null
    },
    behavior:{
        construct: function(params){
            var _this = CardPanel.prototype;
        },
        buildGUI:function(){
            var _this = CardPanel.prototype;
        }	
    },
    cardReady:function(){ }
});