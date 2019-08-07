var config = {
	"ns" : "std",
	"router": {
		"mode": "public",
		"psh": "../../core/src/js/kcl/",
		"uri": "../../",
		"proj": "project/VisualExtJs/",
	},
	"loader": {
		"cfg": {
			"loadType": "syncrhonic",
			"mode": "secure"
		},
		"base": [
			'base/patterns/Kcl.Singleton.js',
			'base/handlers/Kcl.Class.js',
			'base/handlers/Kcl.Factory.js',
			'base/helpers/Kcl.Router.js',
			'base/helpers/Kcl.Loader.js',
			'base/handlers/Kcl.Engine.js'
		],
		"resource": [
			'filter/resource/format/Kcl.Format.js',
			'filter/resource/format/Kcl.Format.JSON.js',
			'filter/resource/bridge/Kcl.Bridge.js',
			'filter/resource/bridge/Kcl.Bridge.Ajax.js',
		],
		"package": [
			'package/front/Kcl.FrontController.js'
		],
		"control": [
			'filter/control/Kcl.Primal.js',
			'filter/control/Kcl.Plugin.js',
			'filter/control/Kcl.App.js'
		],
		"mod": [
			'Main.js'
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
				'Class.js',
				'Factory.js',
				'Engine.js',
			],
			"helpers":[
				'Router.js',
				'Loader.js',
			],
			"patterns":[
				'Singleton.js',
			]
		},front
		"filter": {
			"resource": [
				'Format.js',
				'Format.JSON.js.js',
				'Bridge.js',
				'Bridge.Ajax'
			],
			"control": [
				'Primal.js',
				'Plugin.js',
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
