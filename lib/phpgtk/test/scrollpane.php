<?php
/* $Id: scrollpane.php,v 1.3 2002/12/04 17:31:50 fmk Exp $ */

	if (!extension_loaded('gtk')) {
		dl( 'php_gtk.' . PHP_SHLIB_SUFFIX);
	}

    $w = &new GtkWindow;
    $w->set_title('Testing GtkScrollPane');
    $w->set_border_width(10);
    $w->connect('destroy', create_function('','Gtk::main_quit();'));

	$x = &new GtkAdjustment(1.0, 0.0, 10.0, 0.1, 0.1, 2.0);

	$y = &new GtkAdjustment(1.0, 0.0, 10.0, 0.1, 0.1, 2.0);
	
	$sp = &new GtkScrollPane($x, $y, 0);
	$w->add($sp);

    $w->show_all();

    Gtk::main();
?>
