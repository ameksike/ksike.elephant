var config = {
	"ns" : "std",
	"router": {
		"mode": "secure",
		"psh": "index.php/publisher/",
		"uri": "../../",
		"url": "index.php",
		"proj": "project/indirpublis/",
	},
	"loader": {
		"cfg": {
			"loadType": "syncrhonic",
			"mode": "secure"
		},
		"base": [
			'patterns/Kcl.Singleton',
			'patterns/Kcl.Class',
			'patterns/Kcl.Factory',
			'helpers/Kcl.Router',
			'helpers/Kcl.Loader',
			'handlers/Kcl.Engine',
		],
		"filter": [
			'resource/format/Kcl.Format',
			'resource/format/Kcl.Format.JSON.js',
			'resource/bridge/Kcl.Bridge',
			'resource/bridge/Kcl.Bridge.Ajax',
			'control/Kcl.Primal',
			'control/Kcl.Plugin',
			'control/Kcl.App'
		],
		"package": [
			'front/Kcl.FrontController'
		]
	}
}

/*
	"loader": {
		"cfg": {
			"loadType": "syncrhonic",
			"mode": "secure"
		},
		"base": {
			"handlers": [
				'Class',
				'Factory',
				'Engine',
			],
			"helpers":[
				'Router',
				'Loader',
			],
			"patterns":[
				'Singleton',
			]
		},
		"filter": {
			"resource": [
				'Format',
				'Format.JSON.js',
				'Bridge',
				'Bridge.Ajax'
			],
			"control": [
				'Primal',
				'Plugin',
				'App'
			],
		},
		"package": {
			"front":[
				'FrontController'
			]
		},
		"mod": [
			'Main'
		]
	}
*/
