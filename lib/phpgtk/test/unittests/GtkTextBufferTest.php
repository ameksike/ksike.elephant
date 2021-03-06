<?php
// Call GtkTextBufferTest::main() if this source file is executed directly.
if (!defined("PHPUnit_MAIN_METHOD")) {
    define("PHPUnit_MAIN_METHOD", "GtkTextBufferTest::main");
}

require_once "PHPUnit/Framework/TestCase.php";
require_once "PHPUnit/Framework/TestSuite.php";

// You may remove the following line when all tests have been implemented.
require_once "PHPUnit/Framework/IncompleteTestError.php";

//

/**
 * Test class for GtkTextBuffer.
 * Generated by PHPUnit_Util_Skeleton on 2006-03-07 at 11:37:05.
 */
class GtkTextBufferTest extends PHPUnit_Framework_TestCase {
    /**
     * Runs the test methods of this class.
     *
     * @access public
     * @static
     */
    public static function main() {
        require_once "PHPUnit/TextUI/TestRunner.php";

        $suite  = new PHPUnit_Framework_TestSuite("GtkTextBufferTest");
        $result = PHPUnit_TextUI_TestRunner::run($suite);
    }

    /**
     * Sets up the fixture, for example, open a network connection.
     * This method is called before a test is executed.
     *
     * @access protected
     */
    protected function setUp() {
        $this->tb = new GtkTextBuffer();
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
     * @todo Implement testAdd_selection_clipboard().
     */
    public function testAdd_selection_clipboard() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testApply_tag().
     */
    public function testApply_tag() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testApply_tag_by_name().
     */
    public function testApply_tag_by_name() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testBackspace().
     */
    public function testBackspace() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testBegin_user_action().
     */
    public function testBegin_user_action() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testCopy_clipboard().
     */
    public function testCopy_clipboard() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testCreate_child_anchor().
     */
    public function testCreate_child_anchor() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testCreate_mark().
     */
    public function testCreate_mark() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testCut_clipboard().
     */
    public function testCut_clipboard() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testDelete().
     */
    public function testDelete() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testDelete_interactive().
     */
    public function testDelete_interactive() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testDelete_mark().
     */
    public function testDelete_mark() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testDelete_mark_by_name().
     */
    public function testDelete_mark_by_name() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testDelete_selection().
     */
    public function testDelete_selection() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testEnd_user_action().
     */
    public function testEnd_user_action() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     *  get_bounds should return an array with start and end iterator
     */
    public function testGet_bounds() {
        $this->tb->set_text('Hello world');
        $ar = $this->tb->get_bounds();
        $this->assertTrue(is_array($ar));
        $this->assertEquals(2, count($ar));
        $this->assertEquals('GtkTextIter', get_class($ar[0]));
        $this->assertEquals('GtkTextIter', get_class($ar[1]));
        $this->assertEquals('Hello world', $this->tb->get_text($ar[0], $ar[1]));
    }

    /**
     * @todo Implement testGet_char_count().
     */
    public function testGet_char_count() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testGet_end_iter().
     */
    public function testGet_end_iter() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testGet_insert().
     */
    public function testGet_insert() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testGet_iter_at_child_anchor().
     */
    public function testGet_iter_at_child_anchor() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testGet_iter_at_line().
     */
    public function testGet_iter_at_line() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testGet_iter_at_line_index().
     */
    public function testGet_iter_at_line_index() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testGet_iter_at_line_offset().
     */
    public function testGet_iter_at_line_offset() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testGet_iter_at_mark().
     */
    public function testGet_iter_at_mark() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testGet_iter_at_offset().
     */
    public function testGet_iter_at_offset() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testGet_line_count().
     */
    public function testGet_line_count() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testGet_mark().
     */
    public function testGet_mark() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testGet_modified().
     */
    public function testGet_modified() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testGet_selection_bound().
     */
    public function testGet_selection_bound() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * selection bounds with selection
     */
    public function testGet_selection_bounds() {
        //Something selected -> should return array
        $this->tb->set_text('Hello world');
        $this->tb->select_range($this->tb->get_start_iter(), $this->tb->get_end_iter());
        $ar = $this->tb->get_selection_bounds();
        $this->assertTrue(is_array($ar));
        $this->assertEquals(2, count($ar));
        $this->assertEquals('GtkTextIter', get_class($ar[0]));
        $this->assertEquals('GtkTextIter', get_class($ar[1]));
        $this->assertEquals('Hello world', $this->tb->get_text($ar[0], $ar[1]));
    }

    /**
     * selection bounds with no selection
     */
    public function testGet_selection_boundsNoSelection() {
        //Something selected -> should return array
        $this->tb->set_text('Hello world');
        $ar = $this->tb->get_selection_bounds();
        $this->assertFalse($ar);
    }

    /**
     * @todo Implement testGet_slice().
     */
    public function testGet_slice() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testGet_start_iter().
     */
    public function testGet_start_iter() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testGet_tag_table().
     */
    public function testGet_tag_table() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testGet_text().
     */
    public function testGet_text() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testInsert().
     */
    public function testInsert() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testInsert_at_cursor().
     */
    public function testInsert_at_cursor() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testInsert_child_anchor().
     */
    public function testInsert_child_anchor() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testInsert_interactive().
     */
    public function testInsert_interactive() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testInsert_interactive_at_cursor().
     */
    public function testInsert_interactive_at_cursor() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testInsert_pixbuf().
     */
    public function testInsert_pixbuf() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testInsert_range().
     */
    public function testInsert_range() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testInsert_range_interactive().
     */
    public function testInsert_range_interactive() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testMove_mark().
     */
    public function testMove_mark() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testMove_mark_by_name().
     */
    public function testMove_mark_by_name() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testPaste_clipboard().
     */
    public function testPaste_clipboard() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testPlace_cursor().
     */
    public function testPlace_cursor() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testRemove_all_tags().
     */
    public function testRemove_all_tags() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testRemove_selection_clipboard().
     */
    public function testRemove_selection_clipboard() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testRemove_tag().
     */
    public function testRemove_tag() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testRemove_tag_by_name().
     */
    public function testRemove_tag_by_name() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testSelect_range().
     */
    public function testSelect_range() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testSet_modified().
     */
    public function testSet_modified() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }

    /**
     * @todo Implement testSet_text().
     */
    public function testSet_text() {
        // Remove the following line when you implement this test.
        throw new PHPUnit_Framework_IncompleteTestError;
    }
}

// Call GtkTextBufferTest::main() if this source file is executed directly.
if (PHPUnit_MAIN_METHOD == "GtkTextBufferTest::main") {
    GtkTextBufferTest::main();
}
?>
