//... std.include(std.Router.getModulePath()+'css/style.css');
//-------------------------------------------------------------------------
Kcl.Class( 'Kcl.Main',
{
	extend: Kcl.App,
	behavior: {
		construct : function(eve, loadType){
			this.parent.construct.apply(this, [this]);
			this.form = new Ext.FormPanel({
				labelWidth: 75, // label settings here cascade unless overridden
				url:'save-form.php',
				frame:true,
				autoScroll:true,				
				bodyStyle:'padding:5px 5px 0',
				items: [{
				    xtype:'fieldset',
				    checkboxToggle:true,
				    title: 'User Information',
				    autoHeight:true,
				    defaults: {width: 210},
				    defaultType: 'textfield',
				    collapsed: true,
				    items :[{
					    fieldLabel: 'First Name',
					    name: 'first',
					    allowBlank:false
					},{
					    fieldLabel: 'Last Name',
					    name: 'last'
					},{
					    fieldLabel: 'Company',
					    name: 'company'
					}, {
					    fieldLabel: 'Email',
					    name: 'email',
					    vtype:'email'
					}
				    ]
				},{
				    xtype:'fieldset',
				    title: 'Phone Number',
				    collapsible: true,
				    autoHeight:true,
				    defaults: {width: 210},
				    defaultType: 'textfield',
				    items :[{
					    fieldLabel: 'Home',
					    name: 'home',
					    value: '(888) 555-1212'
					},{
					    fieldLabel: 'Business',
					    name: 'business'
					},{
					    fieldLabel: 'Mobile',
					    name: 'mobile'
					},{
					    fieldLabel: 'Fax',
					    name: 'fax'
					}
				    ]
				}],

				buttons: [{
				    text: 'Save'
				},{
				    text: 'Cancel'
				}]
			});
			var obj = new Ext.Window({
				x:0,
				y:0,
				constrain:true,
				layout:'fit',

				title:'WindowForm1',//'',
				height:300,//,
				width:550,
				items:this.form//
			});
			obj.show();
			this.assist.error.supply(new ErrorManager());
			throw {ms:"aaaaaa", ty:"tatatatat", te:3};
		},
		serverResponse:function(objResponse){
			this.parent.serverResponse(objResponse, this);
			switch(objResponse.action)
			{
				case 'holaMundo':
					Ext.Msg.alert(objResponse.result);
				break;
			}
		},
		onLoadPlugins : function(params){
			Ext.Msg.alert('','plugins loaded');
		},
		require : [
			std.router.lib()+'ext/css/ext-all.css',
			std.router.lib()+'ext/css/misc/ux-all.css',
			std.router.lib()+'ext/css/misc/fileuploadfield.css',
			std.router.lib()+'ext/js/ext-base.js',
			std.router.lib()+'ext/js/ext-all.js',
			std.router.lib()+'ext/js/ext-all-debug.js',
			std.router.lib()+'ext/js/misc/FileUploadField.js',
			std.router.module()+"js/ErrorManager.js"
		]
	}
});

