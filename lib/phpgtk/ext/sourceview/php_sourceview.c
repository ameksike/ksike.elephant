/*
 * PHP-GTK - The PHP language bindings for GTK+
 *
 * Copyright (C) 2001-2008 Andrei Zmievski <andrei@php.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 
/* $Id: php_sourceview.c,v 1.5 2008/02/29 19:05:53 andrei Exp $ */

#include "php_sourceview.h"

#if HAVE_SOURCEVIEW

#ifdef PHP_GTK_COMPILE_DL_SOURCEVIEW
PHP_GTK_GET_EXTENSION(sourceview)
#endif

PHP_GTK_XINIT_FUNCTION(sourceview)
{
	phpg_gtksourceview_register_classes();
    phpg_gtksourceview_register_constants("SOURCEVIEW_");

	return SUCCESS;
}

php_gtk_ext_entry sourceview_ext_entry = {
	"sourceview",
	PHP_GTK_XINIT(sourceview),
	NULL,
};

#endif	/* HAVE_SOURCEVIEW */
