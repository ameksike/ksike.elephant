<?php
/**
 *
 * @framework: Ksike
 * @package: Lib
 * @subpackage: DataBase
 * @version: 0.1 

 * @description: Esta clase esta diseñada para manejar Bases de Datos soportadas en PostgreSQL
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 23/03/2007
 * @update-Date: 12/04/2008
 * @license: GPL v3
 *
 */
class PgSQL
{
 //..........................Declaracion de Variables
 public  $user;                 // usuario para conectarme al servidor;
 public  $password;             // contraseña para conectarme al servidor
 public  $host;                 // direcion IP del servidor en ocaciones puede ser : "localhost"
 public  $dbname;               // nombre de la base de datos deseada;
 public  $port;                 // puerto de conexion al servidor
 private $connection;           // Contiene un objeto de tipo conexion
 //..........................Declaracion de Metodos
 public function __construct($dbname, $user='postgres', $password='postgres', $host='localhost', $port='5432')
 {
   $this->host = $host;
   $this->port   = $port;
   $this->dbname = $dbname;
   $this->user   = $user;
   $this->password  = $password;
 }
 //................................................
 public function executeSQL($syntaxSQL, $SELECT=0)
 {
   $this->startConnection();
   $count = pg_query($syntaxSQL);
   if($SELECT)
   {
     while( $value = pg_fetch_assoc($count) )
	$out[] = $value;
     $this->closeConnection();
     return $out;
   }
   $this->closeConnection();
 }
 //.................................................
 private function startConnection()
 {
   $strConnection = "host=$this->host port=$this->port dbname=$this->dbname user=$this->user password=$this->password";
   $this->connection = pg_pconnect($strConnection)
      or  die("ERROR: No se pudo establecer la coneccion con el servidor");
   if (pg_connection_busy($this->connection))
      die ("ERROR: La conexion esta ocupada");
 }
 //.................................................
 private function closeConnection()
 {
   pg_close($this->connection)
     or die ("ERROR: No se pudo cerrar la coneccion");
 }
 //................................................
};
?>
