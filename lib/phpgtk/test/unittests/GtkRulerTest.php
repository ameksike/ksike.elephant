<?php
// Call GtkRulerTest::main() if this source file is executed directly.
if (!defined("PHPUnit_MAIN_METHOD")) {
    define("PHPUnit_MAIN_METHOD", "GtkRulerTest::main");
}

require_once "PHPUnit/Framework/TestCase.php";
require_once "PHPUnit/Framework/TestSuite.php";

// You may remove the following line when all tests have been implemented.
require_once "PHPUnit/Framework/IncompleteTestError.php";



/**
 * Test class for GtkRuler.
 * Generated by PHPUnit_Util_Skeleton on 2006-03-07 at 13:26:41.
 */
class GtkRulerTest extends PHPUnit_Framework_TestCase {
    /**
     * Runs the test methods of this class.
     *
     * @access public
     * @static
     */
    public static function main() {
        require_once "PHPUnit/TextUI/TestRunner.php";

        $suite  = new PHPUnit_Framework_TestSuite("GtkRulerTest");
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
     * @todo Implement testDraw_pos().
     */
    public function testDraw_pos() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testDraw_ticks().
     */
    public function testDraw_ticks() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testGet_metric().
     */
    public function testGet_metric() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testGet_range().
     */
    public function testGet_range() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testSet_metric().
     */
    public function testSet_metric() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testSet_range().
     */
    public function testSet_range() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }
}

// Call GtkRulerTest::main() if this source file is executed directly.
if (PHPUnit_MAIN_METHOD == "GtkRulerTest::main") {
    GtkRulerTest::main();
}
?>
