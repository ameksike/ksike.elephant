/**
 *
 * @framework: Ksike
 * @package: Core
 * @subpackage: js
 * @version: 0.1

 * @description: 
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 15/03/2011
 * @update-Date: 21/05/2011
 * @license: GPL v2
 *
 */
Kcl.Class( "Kcl.Bridge.HtmlRPC",
{
	extend: Kcl.Bridge,
	property:{
		iframe: null,
		form: null,
		id: "Kcl_iframeRPC"
	},
	behavior: {
		construct: function(params)
		{	
			params = params || {};
			var _this = Kcl.Bridge.HtmlRPC.prototype;
			_this.parent.construct.apply(this, arguments);
			this.buildIframe(params);
			this.buildForm(params);	
		},
		//........................................................................
		buildIframe:  function()
		{
			this.iframe = document.getElementById(this.id);
			if(!this.iframe){
				this.iframe = document.createElement('iframe');  
				this.iframe.src = this.url;
				this.iframe.width = 0;
				this.iframe.height = 0;
				this.iframe.id = this.id;
				this.iframe.name = this.id;
				this.iframe.style.border = '0px';
				document.body.appendChild(this.iframe);
			}
		},
		//........................................................................
		buildForm:  function(params)
		{
			this.form = document.getElementById(this.id+'_F');
			if(!this.form){
				this.form = document.createElement('form');  
				this.form.action = this.url;
				this.form.method = this.method;
				this.form.target = this.id;
				this.form.id = this.id+'_F';
				document.body.appendChild(this.form);
			}
		},
		//........................................................................
		addData: function (lst)
		{
			this.form.innerHTML = '';
			for(var i in lst)
			{
				var tmp = document.createElement('input');  
				tmp.name = i;
				tmp.type = "hidden";
				tmp.value = this.json ? this.json.encode(lst[i]) : lst[i];
				this.form.appendChild(tmp);	
			}
		},
		//........................................................................
		send: function (list, callback)
		{
			this.iframe.onload = function(){
				var _this = Kcl.Bridge.HtmlRPC.prototype;
				iframe = document.getElementById(_this.id);
				var str = iframe.contentDocument.body.firstChild.data;
				if(callback) callback(_this.json.decode(str));
			}
			this.addData(list);
			this.form.submit();
			this.form.innerHTML = '';
		}
	}
});
//---------------------------------------------------------------------------------
