var config = {
	"ns" : "std",
	"router": {
		"mode": "none",  //... secure|none|partial
		"p2c": "../../", //... relative (../)| url (index.php/publisher/)
		"c2p": "project/visualExtJs/"
	},
	"loader": {
		"cfg": {
			"loadType": "syncrhonic"
		},
		"base": [
			'patterns/Kcl.Class',
			'patterns/Kcl.Singleton',
			'patterns/Kcl.Observed',
			'patterns/Kcl.Factory',
			'helpers/Kcl.Router',
			'helpers/Kcl.Loader',
			'handlers/Kcl.Engine'
		],
		"filter": [
			'resource/format/Kcl.Format',
			'resource/format/Kcl.Format.JSON',
			'resource/bridge/Kcl.Bridge',
			'resource/bridge/Kcl.Bridge.Ajax',
			'control/Kcl.Primal',
			'control/Kcl.Plugin',
			'control/Kcl.App'
		],
		"package": [
			'front/Kcl.FrontController',
			'error/Kcl.Error'
		],
		"other": [
			'Main'
		]
	}
}