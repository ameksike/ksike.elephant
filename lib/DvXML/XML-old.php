<?php
/**
 *
 * @framework: Ksike
 * @package: Lib
 * @subpackage: DvXML
 * @version: 0.1 

 * @description: Esta clase esta diseñada para manejar tipos de datos
 * @authors: ing. Antonio Membrides Espinosa
 * @making-Date: 11/05/2011
 * @update-Date: 12/05/2011
 *
 */
class XML
{
	public function __construct() {}
	
	/**
	* The main function for converting to an XML document.
	* Pass in a multi dimensional array and this recrusively loops through and builds up an XML document.
	*
	* @param array $data
	* @param string $rootNodeName - what you want the root node to be - defaultsto data.
	* @param SimpleXMLElement $xml - should only be used recursively
	* @return string XML
	*/
    	public static function Array2XML( $data, $rootNodeName='root', &$xml=null ) 
	{
		if(is_object($data)) $data = (array)$data;
		/*if($rootNodeName=='root') if(count($data)==1) foreach($data as $key=>$i){
			$rootNodeName = $key;
			$data = $i;
			continue;
		}*/
		// turn off compatibility mode as simple xml throws a wobbly if you don't.
		if ( ini_get('zend.ze1_compatibility_mode') == 1 ) ini_set ( 'zend.ze1_compatibility_mode', 0 );
		if ( is_null( $xml ) ) $xml = simplexml_load_string( "<?xml version='1.0' encoding='utf-8'?><$rootNodeName/>" );

		// loop through the data passed in.
		if(is_string($data)){
			$value = htmlentities( $data );
			$xml->addChild( "str", $data );
		}else foreach( $data as $key => $value ) {
		    // no numeric keys in our xml please!
		    if ( is_numeric( $key ) ) {
			$numeric = 1;
			$key = $rootNodeName;
		    }
		    // delete any char not allowed in XML element names
		    $key = preg_replace('/[^a-z0-9\-\_\.\:]/i', '', $key);
		    // if there is another array found recrusively call this function
		    if ( is_array( $value ) ) {
			$node = self::isAssoc( $value ) || $numeric ? $xml->addChild( $key ) : $xml;
			if ( $numeric ) $key = 'anon';
			self::Array2XML( $value, $key, $node );
		    } else {
			// add single node.
			$value = htmlentities( $value );
			$xml->addChild( $key, $value );
		    }
		}

		// pass back as XML
		return $xml->asXML();
	}
	/**
	* Determine if a variable is an associative array
	* @param array
	* @return bool
	*/
    	private static function isAssoc( $array ) {
       		return (is_array($array) && 0 !== count(array_diff_key($array, array_keys(array_keys($array)))));
    	}
	/**
	* getArrayFromXML($xml)
	* This is adds the contents of the return xml into the array for easier processing.
	* @access public
	* @param  string    $data this is the string of the xml data
	* @return Array
	*/
    	public static function XML2Array( $xml ) 
    	{
		if ( is_string( $xml ) ) $xml = new SimpleXMLElement( $xml );
		$children = $xml->children();
		if ( !$children ) return (string) $xml;
		$arr = array();
		foreach ( $children as $key => $node ) {
		    $node = self::XML2Array( $node );

		    // support for 'anon' non-associative arrays
		    if ( $key == 'anon' ) $key = count( $arr );

		    // if the node is already set, put it into an array
		    if ( isset( $arr[$key] ) ) {
		        if ( !is_array( $arr[$key] ) || $arr[$key][0] == null ) $arr[$key] = array( $arr[$key] );
		        $arr[$key][] = $node;
		    } else {
		        $arr[$key] = $node;
		    }
		}
		return $arr;
    	}

    	public static function save($data, $filePath="out.xml", $root="root" ) 
    	{
		if(is_array($data))
			$data = sel::Array2XML($data, $root);
		else if(is_file($data)) $data = file_get_contents($data);
		file_put_contents($filePath, $data);
	}
}
?>
