<?php
// Call AtkRelationTest::main() if this source file is executed directly.
if (!defined("PHPUnit_MAIN_METHOD")) {
    define("PHPUnit_MAIN_METHOD", "AtkRelationTest::main");
}

require_once "PHPUnit/Framework/TestCase.php";
require_once "PHPUnit/Framework/TestSuite.php";

// You may remove the following line when all tests have been implemented.
require_once "PHPUnit/Framework/IncompleteTestError.php";



/**
 * Test class for AtkRelation.
 * Generated by PHPUnit_Util_Skeleton on 2006-03-07 at 13:26:40.
 */
class AtkRelationTest extends PHPUnit_Framework_TestCase {
    /**
     * Runs the test methods of this class.
     *
     * @access public
     * @static
     */
    public static function main() {
        require_once "PHPUnit/TextUI/TestRunner.php";

        $suite  = new PHPUnit_Framework_TestSuite("AtkRelationTest");
        $result = PHPUnit_TextUI_TestRunner::run($suite);
    }

    /**
     * Sets up the fixture, for example, open a network connection.
     * This method is called before a test is executed.
     *
     * @access protected
     */
    protected function setUp() {
    }

    /**
     * Tears down the fixture, for example, close a network connection.
     * This method is called after a test is executed.
     *
     * @access protected
     */
    protected function tearDown() {
    }

    /**
     * @todo Implement testGet_relation_type().
     */
    public function testGet_relation_type() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }
}

// Call AtkRelationTest::main() if this source file is executed directly.
if (PHPUnit_MAIN_METHOD == "AtkRelationTest::main") {
    AtkRelationTest::main();
}
?>
