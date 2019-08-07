<?php
/**
 *
 * @framework: Ksike
 * @package: Lib
 * @subpackage: File
 * @version: 0.1 

 * @description: Esta clase esta diseñada para manejar ficheros de texto
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 23/03/2007
 * @update-Date: 12/04/2008
 *
 */
class File
{
	//------ Variables --------------------------------
	private $_File;
	private $_Modo;
	private $_FilePath;
	//------ Funciones --------------------------------
	public function __construct($FilePath)
	{
		$this->open($FilePath);
	}
	//----------------------------------- Escribe en el fichero una linea
	public function writeLine($valor)
	{
		fputs($this->_File, $valor."\r\n");
	}
	//----------------------------------- Retorna el contenido del F en una matriz
	public function read()
	{
		$datos = array();
		rewind($this->_File);
		while(!feof($this->_File))
		    $datos[] = fgets($this->_File);
		return $datos;
	}
	//----------------------------------- Lectura Binaria
	public function readbinary()
	{
		$datos = fread($this->_File, 1024);
		return $datos;
	}
	//----------------------------------- Lectura completa de un fichero
	public function readFull($FilePath)
	{
		$datos = readfile($FilePath);
		return $datos;
	}
	//----------------------------------- Retorna el contenido del F en una cadena
	public function readInStr($Separador)
	{
		$file  = file($this->_FilePath);
		$datos = implode($Separador,$file);
		return $datos;
	}
	//----------------------------------  Lectura del contenido
	public function readContents()
	{
		$datos = file_get_contents($this->_FilePath);
		return $datos;
	}
	//----------------------------------  Retorna el tamaño en byte del F
	public function size()
	{
		$datos = filesize($this->_FilePath);
		return $datos;
	}
	//----------------------------------  Retorna el tamaño en byte del F
	public function open($FilePath)
	{
		if($this->_File) fclose($this->_File); 
		if(file_exists($FilePath))
		{
			if(is_writable($FilePath)) $this->_Modo = "a+";
			else if(is_readable($FilePath)) $this->_Modo = "r";
			else die("Usted no tiene permisos de lectura sobre: ".$FilePath); 
			$this->_File = fopen($FilePath, $this->_Modo) 
			or die("Error al abrir el fichero: ".$FilePath); 
		}
		else die("El fichero '$FilePath' no existe"); 
		$this->_FilePath = $FilePath;
	}
	//----------------------------------
	public function __destruct()
	{
		if($this->_File) 
			fclose($this->_File); 
	}
}
//---------------------------------------------------------------------------------------
?>
