<?php
/**
 *
 * @framework: Ksike
 * @package: Lib
 * @subpackage: DataBase
 * @version: 0.1 

 * @description: Esta libreria esta diseñada para manejar Bases de Datos basado en el ORM Doctrine
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 07/01/2011
 * @update-Date: 07/01/2011
 * @license: GPL v3
 *
 */
require_once 'Doctrine/Core.php';
class Doctrine extends Doctrine_Core
{
	public  $user;         // Usuario para conectarme al servidor;
	public  $password;     // Contraseña para conectarme al servidor
	public  $host;         // Direcion IP del servidor en ocaciones puede ser : "localhost"
	public  $dbname;       // Nombre de la base de datos deseada;
	public  $port;         // Puerto de conexion al servidor
	public  $driver;       // Sistema gestor de bases de datos a utilizar
	public  $path;         // 
	private $connection;   // Contiene un objeto de tipo conexion

	public function __construct($dbname, $options=null, $inv="Main")
	{
		$this->dbname = $dbname;
		$this->path = isset($options['path']) ? $options['path'] : 'server/models';
		$this->host = isset($options['host']) ? $options['host'] : 'localhost';
		$this->port = isset($options['port']) ? $options['port'] : '5432';
		$this->user = isset($options['user']) ? $options['user'] : 'postgres';
		$this->password = isset($options['password']) ? $options['password'] : 'postgres';
		$this->driver = isset($options['driver']) ? $options['driver'] : 'pgsql';
		$this->connect();
		$this->loadClassModel($inv);
	}
	
	public function connect()
	{
		spl_autoload_register(array('Doctrine', 'autoload'));
		$this->connection = Doctrine_Manager::connection(
			"{$this->driver}://{$this->user}:{$this->password}@{$this->host}/{$this->dbname}", 
			'doctrine'
		);
		$this->connection->setCharset('utf8'); 
	}

	public function loadClassModel($class="Main")
	{
		$path = Router::getModulePath($class).$this->path;
		Doctrine_Core::loadModels($path);
	}
}
