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
 
/* $Id: php_libsexy.h,v 1.2 2008/02/29 19:05:53 andrei Exp $: */

#ifndef PHP_LIBSEXY_H
#define PHP_LIBSEXY_H

#include "php_gtk.h"

#if HAVE_LIBSEXY

#include <libsexy/sexy.h>

extern php_gtk_ext_entry libsexy_ext_entry;
#define php_gtk_ext_libsexy_ptr &libsexy_ext_entry

void phpg_sexy_register_classes(void);
void phpg_sexy_register_constants(const char *strip_prefix);

#else

#define php_gtk_ext_libsexy_ptr NULL

#endif	/* HAVE_LIBSEXY */

#endif	/* PHP_LIBSEXY_H */
