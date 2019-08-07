/**
 *
 * @framework: Ksike
 * @package: Core
 * @subpackage: js
 * @version: 0.1

 * @description: Ajax es una libreria para el trabajo con Ajax desde Javascript
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 01/06/2010
 * @update-Date: 01/06/2010
 * @license: GPL v2
 *
 */
Kcl.Class( "Kcl.Bridge.Ajax",
{
	extend: Kcl.Bridge,
	behavior: {
		construct: function(params)
		{	
			params = params || {};
			var _this = Kcl.Bridge.Ajax.prototype;
			_this.parent.construct.apply(this, arguments);		
			this.type = params.type ? params.type : 'TXT';

			if (window.XMLHttpRequest)  /* Para IE7+, Firefox, Chrome, Opera, Safari */
				this.objAjax = new XMLHttpRequest(); 
			else if (window.ActiveXObject)
			{
				try
				{       /* Para IE6, IE5 */
					this.objAjax = new ActiveXObject("Microsoft.XMLHTTP"); 
				}
				catch(error)
				{
					try
					{	/* Restantes versiones de IE */
						this.objAjax = new ActiveXObject("Msxml2.XMLHTTP"); 
					}
					catch(error2) {	this.failure(error2); }
				}
			}	
		},
		//........................................................................
		config:  function(method, url, type)
		{
			this.method = method;
			this.url = url;
			this.type = type;
		},
		//........................................................................
		sendData: function (params)
		{		
			if(this.objAjax)
			{
				if(!params.method || params.method =="") params.method = 'POST';
				if (params.method == 'GET')
				{
					params.url += '?'+params.data;
					params.data = null;
				}
				this.objAjax.open(params.method, params.url, true);
				if (params.method == 'POST')				
					this.objAjax.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');

				this.objAjax.send(params.data);
				this.objAjax.onreadystatechange = function()
				{
					var _this = Kcl.Bridge.Ajax.prototype;
					if(this.readyState == 4)
						if(this.status == 200) 
						{
							var string = ""; 
							if(params.type == "XML") string = this.responseXML;
							else string = this.responseText;
							params.callback(_this.json.decode(string));
						}
				}
			}
		},
		//........................................................................
		send: function (list, callback)
		{
			var data = '';
			for(var i in  list)
			{
				var info = list[i];
				var json = this.json ? this.json.encode(info) : info;
				data += i +"="+ json +"&";
			}	
			this.sendData({"method":this.method, "url":this.url, "data":data, "type":this.type, "callback":callback});
		}
	}
});
