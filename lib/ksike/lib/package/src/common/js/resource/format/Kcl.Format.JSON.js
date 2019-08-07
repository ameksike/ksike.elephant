/**
 *
 * @framework: Ksike
 * @package: Core
 * @subpackage: js
 * @version: 0.1

 * @description: Format.JSON es una libreria para el trabajo con el formato JSON
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 01/05/2010
 * @update-Date: 10/05/2010
 * @license: GPL v2
 *
 */
Kcl.Class( "Kcl.Format.JSON",
{
	patterns: "Singleton",
	extend: Kcl.Format,
	behavior: {
		encode: function(value, comodin, extended)
		{
			var obj = {begin:"{", end:"}", key:true}; 
			switch(typeof(value))
			{
				case "object":
					if(value instanceof Array){obj.begin = "["; obj.end = "]"; obj.key = false;}
					var strJson = obj.begin; comodin = "";
					for(i in value)	if(i!="remove"){
						var key = "";
						if(obj.key) key = '\"' + i + '\"' + ":"; 
						strJson += comodin + key + this.encode(value[i], true, extended);
						comodin = ",";
					}
					return strJson + obj.end;
				break;
				case "string": 
					if(comodin) comodin = '\"'; else comodin = '';
					return comodin + value + comodin;
				break;
				case "function": 
					return (extended) ? value.toString() : null;
				break;
				default:
					return value; 
				break;
			}
		},
		decode: function(strJson)
		{	
			if(strJson){
				try{
					eval("var objJson ="+strJson+";");
					return objJson;
				}catch(error){this.failure(strJson, error);}
			}
		},
		failure: function(str, error)
		{
			throw {
				msg:"El json : \""+str+"\" provoca el siguiente error => "+error
			};
		}
	}
});