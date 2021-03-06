<?php
/* $Id: list.php,v 1.11 2003/10/10 03:41:45 andrei Exp $ */

if (!extension_loaded('php-gtk')) {
	dl( 'php_gtk.' . PHP_SHLIB_SUFFIX);
}

/*
 * Called when delete-event happens. Returns false to indicate that the event
 * should proceed.
 */
function delete_event()
{
	return false;
}


/*
 * Create a new top-level window and connect the signals to the appropriate
 * functions. Note that all constructors must be assigned by reference.
 */
$window = new GtkWindow();
$window->connect_object('destroy', array('gtk', 'main_quit'));
$window->connect('delete-event', 'delete_event');

/*
 * Create a button and connect its 'clicked' signal to destroy() function.
 */
$button = new GtkButton('Close');
$button->connect_object('clicked', array('gtk', 'main_quit'));

/*
 * Create a vertical layout box.
 */
$box = new GtkVBox(false, 10);
$box->set_border_width(10);

/*
 * Create a list widget and populate it with month names.
 */
$list = new GtkList();
$list->set_selection_mode(GTK_SELECTION_BROWSE);
foreach (range(1, 12) as $month_num)
	$items[] = new GtkListItem(strftime('%B', mktime(0, 0, 0, $month_num)));
$list->append_items($items);

/*
 * Create a scrolled window and add the list widget to it - this provides
 * automatic scrollbars.
 */
$scrolled_window = new GtkScrolledWindow();
$scrolled_window->set_policy(GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
$scrolled_window->add_with_viewport($list);

/*
 * Add scrolled window and button to the vertical layout box.
 */
$box->pack_start($scrolled_window);
$box->pack_start($button, false);

/*
 * Add layout box to the window, set window attributes and show everything.
 */
$window->add($box);
$window->set_title('PHP Rules!');
$window->set_name('MainWindow');
$window->set_usize(150, 200);
$window->show_all();

/* Run the main loop. */
Gtk::main();

?>
