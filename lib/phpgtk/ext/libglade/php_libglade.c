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
 
/* $Id: php_libglade.c,v 1.13 2008/02/29 19:05:53 andrei Exp $: */

#include "php_libglade.h"

#if HAVE_LIBGLADE

#ifdef PHP_GTK_COMPILE_DL_LIBGLADE
PHP_GTK_GET_EXTENSION(libglade);
#endif

PHP_GTK_XINIT_FUNCTION(libglade)
{
	phpg_glade_register_classes();
	phpg_glade_register_constants("GLADE_");

	return SUCCESS;
}

php_gtk_ext_entry libglade_ext_entry = {
	"libglade",
	PHP_GTK_XINIT(libglade),
	NULL
};

#endif /* HAVE_LIBGLADE */
