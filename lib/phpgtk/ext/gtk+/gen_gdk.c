#include "php_gtk.h"

#if HAVE_PHP_GTK
#include <gdk-pixbuf/gdk-pixbuf.h>

#if defined(GDK_WINDOWING_X11)
#include <gdk/gdkx.h>
#elif defined(GDK_WINDOWING_WIN32)
#include <gdk/gdkwin32.h>
#endif

/* make GDK_DISPLAY() the case macro */
#undef GDK_DISPLAY
#define GDK_DISPLAY(object) (GDK_DISPLAY_OBJECT(object))

#define MAX_INTENSITY 65535

/* Forward declaration, since gen_gtk.h is generated later. */
extern PHP_GTK_EXPORT_CE(gtkwidget_ce);

#include "gen_pango.h"

static inline int clamp_int(int value, int low, int high)
{
    return (value < low ? low : (value > high ? high : value));
}

static ZEND_METHOD(GdkColormap, alloc_color);

/* {{{ ignores */

PHP_GTK_EXPORT_CE(gdkcolormap_ce);
PHP_GTK_EXPORT_CE(gdkdevice_ce);
PHP_GTK_EXPORT_CE(gdkdisplay_ce);
PHP_GTK_EXPORT_CE(gdkdisplaymanager_ce);
PHP_GTK_EXPORT_CE(gdkdragcontext_ce);
PHP_GTK_EXPORT_CE(gdkdrawable_ce);
PHP_GTK_EXPORT_CE(gdkwindow_ce);
PHP_GTK_EXPORT_CE(gdkpixmap_ce);
PHP_GTK_EXPORT_CE(gdkgc_ce);
PHP_GTK_EXPORT_CE(gdkimage_ce);
PHP_GTK_EXPORT_CE(gdkkeymap_ce);
PHP_GTK_EXPORT_CE(gdkpixbuf_ce);
PHP_GTK_EXPORT_CE(gdkpixbufanimation_ce);
PHP_GTK_EXPORT_CE(gdkpixbufanimationiter_ce);
PHP_GTK_EXPORT_CE(gdkpixbufloader_ce);
PHP_GTK_EXPORT_CE(gdkscreen_ce);
PHP_GTK_EXPORT_CE(gdkvisual_ce);
PHP_GTK_EXPORT_CE(gdkevent_ce);
PHP_GTK_EXPORT_CE(gdkfont_ce);
PHP_GTK_EXPORT_CE(gdkcolor_ce);
PHP_GTK_EXPORT_CE(gdkcursor_ce);
PHP_GTK_EXPORT_CE(gdkrectangle_ce);
PHP_GTK_EXPORT_CE(gdk_ce);
#line 3061 "ext/gtk+/gdk.overrides"
static PHP_METHOD(Gdk, atom_intern)
{
    char *atom_name;
	zend_bool free_atom_name, only_if_exists = FALSE;
	GdkAtom php_atom;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u|b", &atom_name, &free_atom_name, &only_if_exists))
		return;

    php_atom = gdk_atom_intern(atom_name, (gboolean)only_if_exists);
	if (free_atom_name) g_free(atom_name);
    if (php_atom == GDK_NONE) {
        RETURN_NULL();
    }
    phpg_gdkatom_new(&return_value, php_atom TSRMLS_CC);
}

#line 74 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(Gdk, beep)
{

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_beep();

}


static PHP_METHOD(Gdk, bitmap_create_from_data)
{
	GdkDrawable *drawable = NULL;
	zval *php_drawable;
	char *data;
	zend_bool free_data = FALSE;
	long width, height;
	GdkBitmap* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Nuii", &php_drawable, gdkdrawable_ce, &data, &free_data, &width, &height))
		return;
    if (Z_TYPE_P(php_drawable) != IS_NULL)
        drawable = GDK_DRAWABLE(PHPG_GOBJECT(php_drawable));

    php_retval = gdk_bitmap_create_from_data(drawable, data, (gint)width, (gint)height);
	if (free_data) g_free(data);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(Gdk, colormap_get_system_size)
{
	long php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

	phpg_warn_deprecated(NULL TSRMLS_CC);

    php_retval = gdk_colormap_get_system_size();
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(Gdk, draw_layout_with_colors)
{
	zval *drawable, *gc, *layout, *php_foreground, *php_background;
	long x, y;
	GdkColor *foreground = NULL, *background = NULL;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OOiiOOO", &drawable, gdkdrawable_ce, &gc, gdkgc_ce, &x, &y, &layout, pangolayout_ce, &php_foreground, gboxed_ce, &php_background, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_foreground, GDK_TYPE_COLOR, FALSE TSRMLS_CC)) {
        foreground = (GdkColor *) PHPG_GBOXED(php_foreground);
    } else {
        php_error(E_WARNING, "%s::%s() expects foreground argument to be a valid GdkColor object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    if (phpg_gboxed_check(php_background, GDK_TYPE_COLOR, FALSE TSRMLS_CC)) {
        background = (GdkColor *) PHPG_GBOXED(php_background);
    } else {
        php_error(E_WARNING, "%s::%s() expects background argument to be a valid GdkColor object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

	phpg_warn_deprecated("use GdkDrawable::draw_layout() instead" TSRMLS_CC);

    gdk_draw_layout_with_colors(GDK_DRAWABLE(PHPG_GOBJECT(drawable)), GDK_GC(PHPG_GOBJECT(gc)), (gint)x, (gint)y, PANGO_LAYOUT(PHPG_GOBJECT(layout)), foreground, background);

}


static PHP_METHOD(Gdk, event_get)
{
	GdkEvent *php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_event_get();
	phpg_gboxed_new(&return_value, GDK_TYPE_EVENT, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(Gdk, event_get_graphics_expose)
{
	zval *window;
	GdkEvent *php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &window, gdkwindow_ce))
		return;

    php_retval = gdk_event_get_graphics_expose(GDK_WINDOW(PHPG_GOBJECT(window)));
	phpg_gboxed_new(&return_value, GDK_TYPE_EVENT, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(Gdk, event_peek)
{
	GdkEvent *php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_event_peek();
	phpg_gboxed_new(&return_value, GDK_TYPE_EVENT, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(Gdk, events_pending)
{
	gboolean php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_events_pending();
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(Gdk, flush)
{

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_flush();

}


static PHP_METHOD(Gdk, font_from_description)
{
	PangoFontDescription *font_desc = NULL;
	zval *php_font_desc;
	GdkFont *php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_font_desc, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_font_desc, PANGO_TYPE_FONT_DESCRIPTION, FALSE TSRMLS_CC)) {
        font_desc = (PangoFontDescription *) PHPG_GBOXED(php_font_desc);
    } else {
        php_error(E_WARNING, "%s::%s() expects font_desc argument to be a valid PangoFontDescription object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    php_retval = gdk_font_from_description(font_desc);
	phpg_gboxed_new(&return_value, GDK_TYPE_FONT, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(Gdk, font_from_description_for_display)
{
	zval *display, *php_font_desc;
	PangoFontDescription *font_desc = NULL;
	GdkFont *php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OO", &display, gdkdisplay_ce, &php_font_desc, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_font_desc, PANGO_TYPE_FONT_DESCRIPTION, FALSE TSRMLS_CC)) {
        font_desc = (PangoFontDescription *) PHPG_GBOXED(php_font_desc);
    } else {
        php_error(E_WARNING, "%s::%s() expects font_desc argument to be a valid PangoFontDescription object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    php_retval = gdk_font_from_description_for_display(GDK_DISPLAY(PHPG_GOBJECT(display)), font_desc);
	phpg_gboxed_new(&return_value, GDK_TYPE_FONT, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(Gdk, font_load_for_display)
{
	zval *display;
	char *font_name;
	zend_bool free_font_name = FALSE;
	GdkFont *php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Ou", &display, gdkdisplay_ce, &font_name, &free_font_name))
		return;

    php_retval = gdk_font_load_for_display(GDK_DISPLAY(PHPG_GOBJECT(display)), font_name);
	if (free_font_name) g_free(font_name);
	phpg_gboxed_new(&return_value, GDK_TYPE_FONT, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(Gdk, fontset_load)
{
	char *fontset_name;
	zend_bool free_fontset_name = FALSE;
	GdkFont *php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &fontset_name, &free_fontset_name))
		return;

    php_retval = gdk_fontset_load(fontset_name);
	if (free_fontset_name) g_free(fontset_name);
	phpg_gboxed_new(&return_value, GDK_TYPE_FONT, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(Gdk, fontset_load_for_display)
{
	zval *display;
	char *fontset_name;
	zend_bool free_fontset_name = FALSE;
	GdkFont *php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Ou", &display, gdkdisplay_ce, &fontset_name, &free_fontset_name))
		return;

    php_retval = gdk_fontset_load_for_display(GDK_DISPLAY(PHPG_GOBJECT(display)), fontset_name);
	if (free_fontset_name) g_free(fontset_name);
	phpg_gboxed_new(&return_value, GDK_TYPE_FONT, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(Gdk, get_default_root_window)
{
	GdkWindow* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_get_default_root_window();
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(Gdk, get_show_events)
{
	gboolean php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_get_show_events();
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(Gdk, keyboard_grab)
{
	zval *window;
	zend_bool owner_events = FALSE;
	long time = GDK_CURRENT_TIME, php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O|bi", &window, gdkwindow_ce, &owner_events, &time))
		return;

    php_retval = gdk_keyboard_grab(GDK_WINDOW(PHPG_GOBJECT(window)), (gboolean)owner_events, (guint32)time);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(Gdk, keyboard_ungrab)
{
	long time = GDK_CURRENT_TIME;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "|i", &time))
		return;

    gdk_keyboard_ungrab((guint32)time);

}

#line 66 "ext/gtk+/gdk.overrides"
static PHP_METHOD(Gdk, keyval_convert_case)
{
    guint symbol, upper, lower = 0;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &symbol))
        return;

    gdk_keyval_convert_case(symbol, &lower, &upper);
    php_gtk_build_value(&return_value, "(ii)", lower, upper);
}

#line 375 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(Gdk, keyval_from_name)
{
	char *keyval_name;
	zend_bool free_keyval_name = FALSE;
	long php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &keyval_name, &free_keyval_name))
		return;

    php_retval = gdk_keyval_from_name(keyval_name);
	if (free_keyval_name) g_free(keyval_name);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(Gdk, keyval_is_lower)
{
	long keyval;
	gboolean php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &keyval))
		return;

    php_retval = gdk_keyval_is_lower((guint)keyval);
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(Gdk, keyval_is_upper)
{
	long keyval;
	gboolean php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &keyval))
		return;

    php_retval = gdk_keyval_is_upper((guint)keyval);
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(Gdk, keyval_name)
{
	long keyval;
	gchar *php_retval, *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &keyval))
		return;

    php_retval = gdk_keyval_name((guint)keyval);
    if (php_retval) {
        cp_ret = phpg_from_utf8(php_retval, strlen(php_retval), &cp_len, &free_result TSRMLS_CC);
        if (cp_ret) {
            RETVAL_STRINGL((char *)cp_ret, cp_len, 1);
        } else {
            php_error(E_WARNING, "%s::%s(): could not convert return value from UTF-8", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        }
        g_free(php_retval);
        if (free_result)
            g_free(cp_ret);
    } else
        RETVAL_NULL();
}


static PHP_METHOD(Gdk, keyval_to_lower)
{
	long keyval, php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &keyval))
		return;

    php_retval = gdk_keyval_to_lower((guint)keyval);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(Gdk, keyval_to_unicode)
{
	long keyval, php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &keyval))
		return;

    php_retval = gdk_keyval_to_unicode((guint)keyval);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(Gdk, keyval_to_upper)
{
	long keyval, php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &keyval))
		return;

    php_retval = gdk_keyval_to_upper((guint)keyval);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(Gdk, pixbuf_loader_new)
{
	GdkPixbufLoader* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

	phpg_warn_deprecated("use GdkPixbufLoader() constructor instead" TSRMLS_CC);

    php_retval = gdk_pixbuf_loader_new();
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(Gdk, pixbuf_loader_new_with_mime_type)
{
	char *mime_type;
	zend_bool free_mime_type = FALSE;
	GError *error = NULL;
	GdkPixbufLoader* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &mime_type, &free_mime_type))
		return;

    php_retval = gdk_pixbuf_loader_new_with_mime_type(mime_type, &error);
	if (free_mime_type) g_free(mime_type);
    if (phpg_handle_gerror(&error TSRMLS_CC)) {
        return;
    }
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(Gdk, pixmap_create_from_data)
{
	GdkDrawable *drawable = NULL;
	zval *php_drawable, *php_fg, *php_bg;
	char *data;
	zend_bool free_data = FALSE;
	long width, height, depth;
	GdkColor *fg = NULL, *bg = NULL;
	GdkPixmap* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "NuiiiOO", &php_drawable, gdkdrawable_ce, &data, &free_data, &width, &height, &depth, &php_fg, gboxed_ce, &php_bg, gboxed_ce))
		return;
    if (Z_TYPE_P(php_drawable) != IS_NULL)
        drawable = GDK_DRAWABLE(PHPG_GOBJECT(php_drawable));

    if (phpg_gboxed_check(php_fg, GDK_TYPE_COLOR, FALSE TSRMLS_CC)) {
        fg = (GdkColor *) PHPG_GBOXED(php_fg);
    } else {
        php_error(E_WARNING, "%s::%s() expects fg argument to be a valid GdkColor object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    if (phpg_gboxed_check(php_bg, GDK_TYPE_COLOR, FALSE TSRMLS_CC)) {
        bg = (GdkColor *) PHPG_GBOXED(php_bg);
    } else {
        php_error(E_WARNING, "%s::%s() expects bg argument to be a valid GdkColor object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    php_retval = gdk_pixmap_create_from_data(drawable, data, (gint)width, (gint)height, (gint)depth, fg, bg);
	if (free_data) g_free(data);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(Gdk, pixmap_foreign_new)
{
	long anid;
	GdkPixmap* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &anid))
		return;

    php_retval = gdk_pixmap_foreign_new((GdkNativeWindow)anid);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
    if (php_retval != NULL) {
        g_object_unref(php_retval);
    }
}


static PHP_METHOD(Gdk, pixmap_foreign_new_for_display)
{
	zval *display;
	long anid;
	GdkPixmap* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Oi", &display, gdkdisplay_ce, &anid))
		return;

    php_retval = gdk_pixmap_foreign_new_for_display(GDK_DISPLAY(PHPG_GOBJECT(display)), (GdkNativeWindow)anid);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
    if (php_retval != NULL) {
        g_object_unref(php_retval);
    }
}


static PHP_METHOD(Gdk, pixmap_lookup)
{
	long anid;
	GdkPixmap* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &anid))
		return;

    php_retval = gdk_pixmap_lookup((GdkNativeWindow)anid);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(Gdk, pixmap_lookup_for_display)
{
	zval *display;
	long anid;
	GdkPixmap* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Oi", &display, gdkdisplay_ce, &anid))
		return;

    php_retval = gdk_pixmap_lookup_for_display(GDK_DISPLAY(PHPG_GOBJECT(display)), (GdkNativeWindow)anid);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(Gdk, pointer_grab)
{
	zval *window, *php_event_mask = NULL, *php_confine_to = NULL, *php_cursor = NULL;
	zend_bool owner_events = FALSE;
	GdkEventMask event_mask;
	GdkWindow *confine_to = NULL;
	GdkCursor *cursor = NULL;
	long time = GDK_CURRENT_TIME, php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O|bVNNi", &window, gdkwindow_ce, &owner_events, &php_event_mask, &php_confine_to, gdkwindow_ce, &php_cursor, gboxed_ce, &time))
		return;

	if (php_event_mask && phpg_gvalue_get_flags(GDK_TYPE_EVENT_MASK, php_event_mask, (gint *)&event_mask) == FAILURE) {
		return;
	}
    if (php_confine_to) {
        if (Z_TYPE_P(php_confine_to) == IS_NULL)
            confine_to = NULL;
        else
            confine_to = GDK_WINDOW(PHPG_GOBJECT(php_confine_to));
    }

    if (php_cursor) {
        if (Z_TYPE_P(php_cursor) == IS_NULL) {
            cursor = NULL;
        } else {
            if (phpg_gboxed_check(php_cursor, GDK_TYPE_CURSOR, FALSE TSRMLS_CC)) {
                cursor = (GdkCursor *) PHPG_GBOXED(php_cursor);
            } else {
                php_error(E_WARNING, "%s::%s() expects cursor argument to be a valid GdkCursor object or null", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
                return;
            }
        }
    }

    php_retval = gdk_pointer_grab(GDK_WINDOW(PHPG_GOBJECT(window)), (gboolean)owner_events, event_mask, confine_to, cursor, (guint32)time);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(Gdk, pointer_is_grabbed)
{
	gboolean php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pointer_is_grabbed();
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(Gdk, pointer_ungrab)
{
	long time = GDK_CURRENT_TIME;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "|i", &time))
		return;

    gdk_pointer_ungrab((guint32)time);

}

#line 118 "ext/gtk+/gdk.overrides"
static PHP_METHOD(Gdk, query_depths)
{
    gint *depths, count, i;

    gdk_query_depths(&depths, &count);

    array_init(return_value);
    for (i = 0; i < count; i++) {
        add_next_index_long(return_value, depths[i]);
    }
}

#line 688 "ext/gtk+/gen_gdk.c"


#line 132 "ext/gtk+/gdk.overrides"
static PHP_METHOD(Gdk, query_visual_types)
{
    GdkVisualType *visual_types;
    gint count, i;

    gdk_query_visual_types(&visual_types, &count);

    array_init(return_value);
    for (i = 0; i < count; i++) {
        add_next_index_long(return_value, visual_types[i]);
    }
}

#line 705 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(Gdk, rgb_ditherable)
{
	gboolean php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_rgb_ditherable();
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(Gdk, rgb_gc_set_background)
{
	zval *gc;
	long rgb;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Oi", &gc, gdkgc_ce, &rgb))
		return;

    gdk_rgb_gc_set_background(GDK_GC(PHPG_GOBJECT(gc)), (guint32)rgb);

}


static PHP_METHOD(Gdk, rgb_gc_set_foreground)
{
	zval *gc;
	long rgb;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Oi", &gc, gdkgc_ce, &rgb))
		return;

    gdk_rgb_gc_set_foreground(GDK_GC(PHPG_GOBJECT(gc)), (guint32)rgb);

}


static PHP_METHOD(Gdk, rgb_get_cmap)
{
	GdkColormap* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

	phpg_warn_deprecated("use gdk::rgb_get_colormap() instead" TSRMLS_CC);

    php_retval = gdk_rgb_get_cmap();
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(Gdk, rgb_get_colormap)
{
	GdkColormap* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_rgb_get_colormap();
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(Gdk, rgb_get_visual)
{
	GdkVisual* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_rgb_get_visual();
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(Gdk, rgb_set_install)
{
	zend_bool install;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &install))
		return;

    gdk_rgb_set_install((gboolean)install);

}


static PHP_METHOD(Gdk, rgb_set_min_colors)
{
	long min_colors;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &min_colors))
		return;

    gdk_rgb_set_min_colors((gint)min_colors);

}


static PHP_METHOD(Gdk, rgb_set_verbose)
{
	zend_bool verbose;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &verbose))
		return;

    gdk_rgb_set_verbose((gboolean)verbose);

}


static PHP_METHOD(Gdk, rgb_xpixel_from_rgb)
{
	long rgb, php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &rgb))
		return;

    php_retval = gdk_rgb_xpixel_from_rgb((guint32)rgb);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(Gdk, selection_owner_get)
{
	GdkAtom selection;
	zval *php_selection = NULL;
	GdkWindow* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_selection))
		return;

    selection = phpg_gdkatom_from_zval(php_selection TSRMLS_CC);
    if (selection == NULL) {
        php_error(E_WARNING, "%s::%s() expects selection argument to be a valid GdkAtom object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    php_retval = gdk_selection_owner_get(selection);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(Gdk, selection_owner_get_for_display)
{
	zval *display, *php_selection = NULL;
	GdkAtom selection;
	GdkWindow* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OV", &display, gdkdisplay_ce, &php_selection))
		return;

    selection = phpg_gdkatom_from_zval(php_selection TSRMLS_CC);
    if (selection == NULL) {
        php_error(E_WARNING, "%s::%s() expects selection argument to be a valid GdkAtom object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    php_retval = gdk_selection_owner_get_for_display(GDK_DISPLAY(PHPG_GOBJECT(display)), selection);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(Gdk, selection_owner_set)
{
	zval *owner, *php_selection = NULL;
	GdkAtom selection;
	long time;
	zend_bool send_event;
	gboolean php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OVib", &owner, gdkwindow_ce, &php_selection, &time, &send_event))
		return;

    selection = phpg_gdkatom_from_zval(php_selection TSRMLS_CC);
    if (selection == NULL) {
        php_error(E_WARNING, "%s::%s() expects selection argument to be a valid GdkAtom object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    php_retval = gdk_selection_owner_set(GDK_WINDOW(PHPG_GOBJECT(owner)), selection, (guint32)time, (gboolean)send_event);
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(Gdk, selection_owner_set_for_display)
{
	zval *display, *owner, *php_selection = NULL;
	GdkAtom selection;
	long time;
	zend_bool send_event;
	gboolean php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OOVib", &display, gdkdisplay_ce, &owner, gdkwindow_ce, &php_selection, &time, &send_event))
		return;

    selection = phpg_gdkatom_from_zval(php_selection TSRMLS_CC);
    if (selection == NULL) {
        php_error(E_WARNING, "%s::%s() expects selection argument to be a valid GdkAtom object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    php_retval = gdk_selection_owner_set_for_display(GDK_DISPLAY(PHPG_GOBJECT(display)), GDK_WINDOW(PHPG_GOBJECT(owner)), selection, (guint32)time, (gboolean)send_event);
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(Gdk, selection_send_notify)
{
	long requestor, time;
	GdkAtom selection, target, property;
	zval *php_selection = NULL, *php_target = NULL, *php_property = NULL;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iVVVi", &requestor, &php_selection, &php_target, &php_property, &time))
		return;

    selection = phpg_gdkatom_from_zval(php_selection TSRMLS_CC);
    if (selection == NULL) {
        php_error(E_WARNING, "%s::%s() expects selection argument to be a valid GdkAtom object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    target = phpg_gdkatom_from_zval(php_target TSRMLS_CC);
    if (target == NULL) {
        php_error(E_WARNING, "%s::%s() expects target argument to be a valid GdkAtom object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    property = phpg_gdkatom_from_zval(php_property TSRMLS_CC);
    if (property == NULL) {
        php_error(E_WARNING, "%s::%s() expects property argument to be a valid GdkAtom object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    gdk_selection_send_notify((guint32)requestor, selection, target, property, (guint32)time);

}


static PHP_METHOD(Gdk, selection_send_notify_for_display)
{
	zval *display, *php_selection = NULL, *php_target = NULL, *php_property = NULL;
	long requestor, time;
	GdkAtom selection, target, property;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OiVVVi", &display, gdkdisplay_ce, &requestor, &php_selection, &php_target, &php_property, &time))
		return;

    selection = phpg_gdkatom_from_zval(php_selection TSRMLS_CC);
    if (selection == NULL) {
        php_error(E_WARNING, "%s::%s() expects selection argument to be a valid GdkAtom object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    target = phpg_gdkatom_from_zval(php_target TSRMLS_CC);
    if (target == NULL) {
        php_error(E_WARNING, "%s::%s() expects target argument to be a valid GdkAtom object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    property = phpg_gdkatom_from_zval(php_property TSRMLS_CC);
    if (property == NULL) {
        php_error(E_WARNING, "%s::%s() expects property argument to be a valid GdkAtom object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    gdk_selection_send_notify_for_display(GDK_DISPLAY(PHPG_GOBJECT(display)), (guint32)requestor, selection, target, property, (guint32)time);

}


static PHP_METHOD(Gdk, set_double_click_time)
{
	long msec;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &msec))
		return;

    gdk_set_double_click_time((guint)msec);

}


static PHP_METHOD(Gdk, set_show_events)
{
	zend_bool show_events;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &show_events))
		return;

    gdk_set_show_events((gboolean)show_events);

}


static PHP_METHOD(Gdk, set_sm_client_id)
{
	char *sm_client_id;
	zend_bool free_sm_client_id = FALSE;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &sm_client_id, &free_sm_client_id))
		return;

    gdk_set_sm_client_id(sm_client_id);
	if (free_sm_client_id) g_free(sm_client_id);

}


static PHP_METHOD(Gdk, threads_enter)
{

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_threads_enter();

}


static PHP_METHOD(Gdk, threads_init)
{

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_threads_init();

}


static PHP_METHOD(Gdk, threads_leave)
{

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_threads_leave();

}


static PHP_METHOD(Gdk, unicode_to_keyval)
{
	long wc, php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &wc))
		return;

    php_retval = gdk_unicode_to_keyval((guint32)wc);
	RETVAL_LONG(php_retval);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_bitmap_create_from_data, 0)
    ZEND_ARG_OBJ_INFO(0, drawable, GdkDrawable, 1)
    ZEND_ARG_INFO(0, data)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_gdk_draw_layout_with_colors, 0)
    ZEND_ARG_OBJ_INFO(0, drawable, GdkDrawable, 1)
    ZEND_ARG_OBJ_INFO(0, gc, GdkGC, 1)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_OBJ_INFO(0, layout, PangoLayout, 1)
    ZEND_ARG_OBJ_INFO(0, foreground, GdkColor, 1)
    ZEND_ARG_OBJ_INFO(0, background, GdkColor, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_event_get_graphics_expose, 0)
    ZEND_ARG_OBJ_INFO(0, window, GdkWindow, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_font_from_description, 0)
    ZEND_ARG_OBJ_INFO(0, font_desc, PangoFontDescription, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_font_from_description_for_display, 0)
    ZEND_ARG_OBJ_INFO(0, display, GdkDisplay, 1)
    ZEND_ARG_OBJ_INFO(0, font_desc, PangoFontDescription, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_font_load_for_display, 0)
    ZEND_ARG_OBJ_INFO(0, display, GdkDisplay, 1)
    ZEND_ARG_INFO(0, font_name)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_fontset_load, 0)
    ZEND_ARG_INFO(0, fontset_name)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_fontset_load_for_display, 0)
    ZEND_ARG_OBJ_INFO(0, display, GdkDisplay, 1)
    ZEND_ARG_INFO(0, fontset_name)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdk_keyboard_grab, 0, 0, 1)
    ZEND_ARG_OBJ_INFO(0, window, GdkWindow, 1)
    ZEND_ARG_INFO(0, owner_events)
    ZEND_ARG_INFO(0, time)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdk_keyboard_ungrab, 0, 0, 0)
    ZEND_ARG_INFO(0, time)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_keyval_from_name, 0)
    ZEND_ARG_INFO(0, keyval_name)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_keyval_is_lower, 0)
    ZEND_ARG_INFO(0, keyval)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_keyval_is_upper, 0)
    ZEND_ARG_INFO(0, keyval)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_keyval_name, 0)
    ZEND_ARG_INFO(0, keyval)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_keyval_to_lower, 0)
    ZEND_ARG_INFO(0, keyval)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_keyval_to_unicode, 0)
    ZEND_ARG_INFO(0, keyval)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_keyval_to_upper, 0)
    ZEND_ARG_INFO(0, keyval)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_pixbuf_loader_new_with_mime_type, 0)
    ZEND_ARG_INFO(0, mime_type)
    ZEND_ARG_INFO(0, error)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_pixmap_create_from_data, 0)
    ZEND_ARG_OBJ_INFO(0, drawable, GdkDrawable, 1)
    ZEND_ARG_INFO(0, data)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, depth)
    ZEND_ARG_OBJ_INFO(0, fg, GdkColor, 1)
    ZEND_ARG_OBJ_INFO(0, bg, GdkColor, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_pixmap_foreign_new, 0)
    ZEND_ARG_INFO(0, anid)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_pixmap_foreign_new_for_display, 0)
    ZEND_ARG_OBJ_INFO(0, display, GdkDisplay, 1)
    ZEND_ARG_INFO(0, anid)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_pixmap_lookup, 0)
    ZEND_ARG_INFO(0, anid)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_pixmap_lookup_for_display, 0)
    ZEND_ARG_OBJ_INFO(0, display, GdkDisplay, 1)
    ZEND_ARG_INFO(0, anid)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdk_pointer_grab, 0, 0, 2)
    ZEND_ARG_OBJ_INFO(0, window, GdkWindow, 1)
    ZEND_ARG_INFO(0, owner_events)
    ZEND_ARG_INFO(0, event_mask)
    ZEND_ARG_OBJ_INFO(0, confine_to, GdkWindow, 1)
    ZEND_ARG_OBJ_INFO(0, cursor, GdkCursor, 1)
    ZEND_ARG_INFO(0, time)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdk_pointer_ungrab, 0, 0, 0)
    ZEND_ARG_INFO(0, time)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_rgb_gc_set_background, 0)
    ZEND_ARG_OBJ_INFO(0, gc, GdkGC, 1)
    ZEND_ARG_INFO(0, rgb)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_rgb_gc_set_foreground, 0)
    ZEND_ARG_OBJ_INFO(0, gc, GdkGC, 1)
    ZEND_ARG_INFO(0, rgb)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_rgb_set_install, 0)
    ZEND_ARG_INFO(0, install)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_rgb_set_min_colors, 0)
    ZEND_ARG_INFO(0, min_colors)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_rgb_set_verbose, 0)
    ZEND_ARG_INFO(0, verbose)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_rgb_xpixel_from_rgb, 0)
    ZEND_ARG_INFO(0, rgb)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_selection_owner_get, 0)
    ZEND_ARG_INFO(0, selection)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_selection_owner_get_for_display, 0)
    ZEND_ARG_OBJ_INFO(0, display, GdkDisplay, 1)
    ZEND_ARG_INFO(0, selection)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_selection_owner_set, 0)
    ZEND_ARG_OBJ_INFO(0, owner, GdkWindow, 1)
    ZEND_ARG_INFO(0, selection)
    ZEND_ARG_INFO(0, time)
    ZEND_ARG_INFO(0, send_event)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_selection_owner_set_for_display, 0)
    ZEND_ARG_OBJ_INFO(0, display, GdkDisplay, 1)
    ZEND_ARG_OBJ_INFO(0, owner, GdkWindow, 1)
    ZEND_ARG_INFO(0, selection)
    ZEND_ARG_INFO(0, time)
    ZEND_ARG_INFO(0, send_event)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_selection_send_notify, 0)
    ZEND_ARG_INFO(0, requestor)
    ZEND_ARG_INFO(0, selection)
    ZEND_ARG_INFO(0, target)
    ZEND_ARG_INFO(0, property)
    ZEND_ARG_INFO(0, time)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_selection_send_notify_for_display, 0)
    ZEND_ARG_OBJ_INFO(0, display, GdkDisplay, 1)
    ZEND_ARG_INFO(0, requestor)
    ZEND_ARG_INFO(0, selection)
    ZEND_ARG_INFO(0, target)
    ZEND_ARG_INFO(0, property)
    ZEND_ARG_INFO(0, time)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_set_double_click_time, 0)
    ZEND_ARG_INFO(0, msec)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_set_show_events, 0)
    ZEND_ARG_INFO(0, show_events)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_set_sm_client_id, 0)
    ZEND_ARG_INFO(0, sm_client_id)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdk_unicode_to_keyval, 0)
    ZEND_ARG_INFO(0, wc)
ZEND_END_ARG_INFO();

static function_entry gdk_methods[] = {
	PHP_ME(Gdk, atom_intern,          NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, beep,                 NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, bitmap_create_from_data, arginfo_gdk_gdk_bitmap_create_from_data, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, colormap_get_system_size, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, draw_layout_with_colors, arginfo_gdk_gdk_gdk_draw_layout_with_colors, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, event_get,            NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, event_get_graphics_expose, arginfo_gdk_gdk_event_get_graphics_expose, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, event_peek,           NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, events_pending,       NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, flush,                NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, font_from_description, arginfo_gdk_gdk_font_from_description, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, font_from_description_for_display, arginfo_gdk_gdk_font_from_description_for_display, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, font_load_for_display, arginfo_gdk_gdk_font_load_for_display, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, fontset_load,         arginfo_gdk_gdk_fontset_load, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, fontset_load_for_display, arginfo_gdk_gdk_fontset_load_for_display, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, get_default_root_window, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, get_show_events,      NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, keyboard_grab,        arginfo_gdk_gdk_keyboard_grab, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, keyboard_ungrab,      arginfo_gdk_gdk_keyboard_ungrab, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, keyval_convert_case,  NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, keyval_from_name,     arginfo_gdk_gdk_keyval_from_name, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, keyval_is_lower,      arginfo_gdk_gdk_keyval_is_lower, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, keyval_is_upper,      arginfo_gdk_gdk_keyval_is_upper, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, keyval_name,          arginfo_gdk_gdk_keyval_name, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, keyval_to_lower,      arginfo_gdk_gdk_keyval_to_lower, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, keyval_to_unicode,    arginfo_gdk_gdk_keyval_to_unicode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, keyval_to_upper,      arginfo_gdk_gdk_keyval_to_upper, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, pixbuf_loader_new, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, pixbuf_loader_new_with_mime_type, arginfo_gdk_gdk_pixbuf_loader_new_with_mime_type, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, pixmap_create_from_data, arginfo_gdk_gdk_pixmap_create_from_data, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, pixmap_foreign_new,   arginfo_gdk_gdk_pixmap_foreign_new, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, pixmap_foreign_new_for_display, arginfo_gdk_gdk_pixmap_foreign_new_for_display, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, pixmap_lookup,        arginfo_gdk_gdk_pixmap_lookup, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, pixmap_lookup_for_display, arginfo_gdk_gdk_pixmap_lookup_for_display, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, pointer_grab,         arginfo_gdk_gdk_pointer_grab, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, pointer_is_grabbed,   NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, pointer_ungrab,       arginfo_gdk_gdk_pointer_ungrab, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, query_depths,         NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, query_visual_types,   NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, rgb_ditherable,       NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, rgb_gc_set_background, arginfo_gdk_gdk_rgb_gc_set_background, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, rgb_gc_set_foreground, arginfo_gdk_gdk_rgb_gc_set_foreground, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, rgb_get_cmap,         NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, rgb_get_colormap,     NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, rgb_get_visual,       NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, rgb_set_install,      arginfo_gdk_gdk_rgb_set_install, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, rgb_set_min_colors,   arginfo_gdk_gdk_rgb_set_min_colors, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, rgb_set_verbose,      arginfo_gdk_gdk_rgb_set_verbose, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, rgb_xpixel_from_rgb,  arginfo_gdk_gdk_rgb_xpixel_from_rgb, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, selection_owner_get,  arginfo_gdk_gdk_selection_owner_get, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, selection_owner_get_for_display, arginfo_gdk_gdk_selection_owner_get_for_display, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, selection_owner_set,  arginfo_gdk_gdk_selection_owner_set, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, selection_owner_set_for_display, arginfo_gdk_gdk_selection_owner_set_for_display, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, selection_send_notify, arginfo_gdk_gdk_selection_send_notify, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, selection_send_notify_for_display, arginfo_gdk_gdk_selection_send_notify_for_display, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, set_double_click_time, arginfo_gdk_gdk_set_double_click_time, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, set_show_events,      arginfo_gdk_gdk_set_show_events, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, set_sm_client_id,     arginfo_gdk_gdk_set_sm_client_id, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, threads_enter,        NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, threads_init,         NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, threads_leave,        NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Gdk, unicode_to_keyval,    arginfo_gdk_gdk_unicode_to_keyval, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(GdkColormap, __construct)
{
	zval *visual;
	zend_bool allocate;
	GObject *wrapped_obj;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Ob", &visual, gdkvisual_ce, &allocate)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkColormap);
	}

	wrapped_obj = (GObject *) gdk_colormap_new(GDK_VISUAL(PHPG_GOBJECT(visual)), (gboolean)allocate);

	if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkColormap);
	}

    phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}

#line 298 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkColormap, alloc)
{
	phpg_warn_deprecated("use GdkColormap::alloc_color()" TSRMLS_CC);
#if ZEND_EXTENSION_API_NO > 220051025
    PHP_MN(GdkColormap_alloc_color)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
#else
    PHP_FN(GdkColormap_alloc_color)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
#endif
}
#line 1421 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkColormap, black)
{
	GdkColor *color = NULL;
	zval *php_color;
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_color, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_color, GDK_TYPE_COLOR, FALSE TSRMLS_CC)) {
        color = (GdkColor *) PHPG_GBOXED(php_color);
    } else {
        php_error(E_WARNING, "%s::%s() expects color argument to be a valid GdkColor object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    php_retval = gdk_color_black(GDK_COLORMAP(PHPG_GOBJECT(this_ptr)), color);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkColormap, change)
{
	GdkColor *color = NULL;
	zval *php_color;
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_color, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_color, GDK_TYPE_COLOR, FALSE TSRMLS_CC)) {
        color = (GdkColor *) PHPG_GBOXED(php_color);
    } else {
        php_error(E_WARNING, "%s::%s() expects color argument to be a valid GdkColor object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    php_retval = gdk_color_change(GDK_COLORMAP(PHPG_GOBJECT(this_ptr)), color);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkColormap, white)
{
	GdkColor *color = NULL;
	zval *php_color;
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_color, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_color, GDK_TYPE_COLOR, FALSE TSRMLS_CC)) {
        color = (GdkColor *) PHPG_GBOXED(php_color);
    } else {
        php_error(E_WARNING, "%s::%s() expects color argument to be a valid GdkColor object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    php_retval = gdk_color_white(GDK_COLORMAP(PHPG_GOBJECT(this_ptr)), color);
	RETVAL_LONG(php_retval);
}

#line 322 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkColormap, alloc_color)
{
    GdkColor color = { 0, 0, 0, 0 };
    guint red = 0, green = 0, blue = 0;
    zend_bool writeable = FALSE;
    zend_bool best_match = TRUE;
    zval *php_color;
	gchar *color_spec;

    NOT_STATIC_METHOD();

    if (php_gtk_parse_args_quiet(ZEND_NUM_ARGS(), "iii|bb", &red, &green, &blue, &writeable, &best_match)) {
        color.red = clamp_int(red, 0, MAX_INTENSITY);
        color.green = clamp_int(green, 0, MAX_INTENSITY);
        color.blue = clamp_int(blue, 0, MAX_INTENSITY);
    } else if (php_gtk_parse_args_quiet(ZEND_NUM_ARGS(), "O|bb",
                                        &php_color, gdkcolor_ce, &writeable, &best_match)) {
        color = *(GdkColor*)PHPG_GBOXED(php_color);
    } else if (php_gtk_parse_args_quiet(ZEND_NUM_ARGS(), "s|bb", &color_spec, &writeable, &best_match)) {
        if (!gdk_color_parse(color_spec, &color)) {
            php_error(E_WARNING, "%s::%s() could not parse color spec '%s'",
                      get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C), color_spec);
            RETURN_FALSE;
        }
    } else {
            php_error(E_WARNING, "%s::%s() requires color to be specified as an RGB triplet, GdkColor, or a string", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
    }

	if (!gdk_colormap_alloc_color(GDK_COLORMAP(PHPG_GOBJECT(this_ptr)), &color, writeable, best_match)) {
        php_error(E_WARNING, "%s::%s() could not allocate color", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        RETURN_FALSE;
	}

    phpg_gboxed_new(&return_value, GDK_TYPE_COLOR, &color, TRUE, TRUE TSRMLS_CC);
}

#line 1533 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkColormap, get_screen)
{
	GdkScreen* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_colormap_get_screen(GDK_COLORMAP(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkColormap, get_system)
{
	GdkColormap* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_colormap_get_system();
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkColormap, get_visual)
{
	GdkVisual* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_colormap_get_visual(GDK_COLORMAP(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}

#line 367 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkColormap, query_color)
{
    GdkColor color = { 0 , 0 , 0 , 0 };
    guint pixel;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &pixel))
        return;
    gdk_colormap_query_color(GDK_COLORMAP(PHPG_GOBJECT(this_ptr)), pixel, &color);
    phpg_gboxed_new(&return_value, GDK_TYPE_COLOR, &color, TRUE, TRUE TSRMLS_CC);
}

#line 1590 "ext/gtk+/gen_gdk.c"



static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkcolormap_gdk_colormap_new, 0)
    ZEND_ARG_OBJ_INFO(0, visual, GdkVisual, 1)
    ZEND_ARG_INFO(0, allocate)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkcolormap_black, 0)
    ZEND_ARG_OBJ_INFO(0, color, GdkColor, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkcolormap_change, 0)
    ZEND_ARG_OBJ_INFO(0, color, GdkColor, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkcolormap_white, 0)
    ZEND_ARG_OBJ_INFO(0, color, GdkColor, 1)
ZEND_END_ARG_INFO();
static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkcolormap_alloc_color, 0, 0, 0)
    ZEND_ARG_INFO(0, color OR red)
    ZEND_ARG_INFO(0, blue)
    ZEND_ARG_INFO(0, green)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkcolormap_query_color, 0)
    ZEND_ARG_INFO(0, allocated)
ZEND_END_ARG_INFO();


static function_entry gdkcolormap_methods[] = {
	PHP_ME(GdkColormap, __construct,          arginfo_gdk_gdkcolormap_gdk_colormap_new, ZEND_ACC_PUBLIC)
	PHP_ME(GdkColormap, alloc,                NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkColormap, alloc_color,          arginfo_gdk_gdkcolormap_alloc_color, ZEND_ACC_PUBLIC)
	PHP_ME(GdkColormap, black,                arginfo_gdk_gdkcolormap_black, ZEND_ACC_PUBLIC)
	PHP_ME(GdkColormap, change,               arginfo_gdk_gdkcolormap_change, ZEND_ACC_PUBLIC)
	PHP_ME(GdkColormap, get_screen,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkColormap, get_system,           NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkColormap, get_visual,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkColormap, query_color,          arginfo_gdk_gdkcolormap_query_color, ZEND_ACC_PUBLIC)
	PHP_ME(GdkColormap, white,                arginfo_gdk_gdkcolormap_white, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

PHPG_PROP_READER(GdkDevice, name)
{
	const gchar *php_retval;
	gchar *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    php_retval = GDK_DEVICE(((phpg_gobject_t *)object)->obj)->name;
    if (php_retval) {
        cp_ret = phpg_from_utf8(php_retval, strlen(php_retval), &cp_len, &free_result TSRMLS_CC);
        if (cp_ret) {
            RETVAL_STRINGL((char *)cp_ret, cp_len, 1);
        } else {
            php_error(E_WARNING, "%s::%s(): could not convert return value from UTF-8", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        }
        if (free_result)
            g_free(cp_ret);
    } else {
        RETVAL_NULL();
    }
    return SUCCESS;
}


PHPG_PROP_READER(GdkDevice, source)
{
	long php_retval;

    php_retval = GDK_DEVICE(((phpg_gobject_t *)object)->obj)->source;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkDevice, mode)
{
	long php_retval;

    php_retval = GDK_DEVICE(((phpg_gobject_t *)object)->obj)->mode;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkDevice, has_cursor)
{
	gboolean php_retval;

    php_retval = GDK_DEVICE(((phpg_gobject_t *)object)->obj)->has_cursor;
	RETVAL_BOOL(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkDevice, num_axes)
{
	long php_retval;

    php_retval = GDK_DEVICE(((phpg_gobject_t *)object)->obj)->num_axes;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}

#line 386 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkDevice, axes)
{
    GdkDevice *device;
    zval *value;
    int i;

    device = GDK_DEVICE(((phpg_gobject_t *)object)->obj);

    array_init(return_value);
    for (i = 0; i < device->num_axes; i++) {
        MAKE_STD_ZVAL(value);
        php_gtk_build_value(&value, "(idd)", device->axes[i].use, device->axes[i].min, device->axes[i].max);
        add_next_index_zval(return_value, value);
    }

    return SUCCESS;
}

#line 1723 "ext/gtk+/gen_gdk.c"



PHPG_PROP_READER(GdkDevice, num_keys)
{
	long php_retval;

    php_retval = GDK_DEVICE(((phpg_gobject_t *)object)->obj)->num_keys;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}

#line 406 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkDevice, keys)
{
    GdkDevice *device;
    zval *value;
    int i;

    device = GDK_DEVICE(((phpg_gobject_t *)object)->obj);

    array_init(return_value);
    for (i = 0; i < device->num_keys; i++) {
        MAKE_STD_ZVAL(value);
        php_gtk_build_value(&value, "(ii)", device->keys[i].keyval, device->keys[i].modifiers);
        add_next_index_zval(return_value, value);
    }

    return SUCCESS;
}

#line 1755 "ext/gtk+/gen_gdk.c"



static prop_info_t gdkdevice_prop_info[] = {
	{ "name", PHPG_PROP_READ_FN(GdkDevice, name), NULL },
	{ "source", PHPG_PROP_READ_FN(GdkDevice, source), NULL },
	{ "mode", PHPG_PROP_READ_FN(GdkDevice, mode), NULL },
	{ "has_cursor", PHPG_PROP_READ_FN(GdkDevice, has_cursor), NULL },
	{ "num_axes", PHPG_PROP_READ_FN(GdkDevice, num_axes), NULL },
	{ "axes", PHPG_PROP_READ_FN(GdkDevice, axes), NULL },
	{ "num_keys", PHPG_PROP_READ_FN(GdkDevice, num_keys), NULL },
	{ "keys", PHPG_PROP_READ_FN(GdkDevice, keys), NULL },
	{ NULL, NULL, NULL },
};

#line 434 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkDevice, get_axis)
{
    zval *php_axes, *php_axis_to_use = NULL;
    GdkDevice *device;
    GdkAxisUse axis_to_use;
    gdouble *axes, value;
    int arr_count, i;
    zval **php_item;
    gboolean ret;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "aV", &php_axes, &php_axis_to_use))
        return;

    if (php_axis_to_use && phpg_gvalue_get_enum(GDK_TYPE_AXIS_USE, php_axis_to_use, (gint *)&axis_to_use) == FAILURE) {
        return;
    }

    device = GDK_DEVICE(PHPG_GOBJECT(this_ptr));

    arr_count = zend_hash_num_elements(Z_ARRVAL_P(php_axes));
    axes = g_new(gdouble, arr_count);

    for (i=0, zend_hash_internal_pointer_reset(Z_ARRVAL_P(php_axes));
         zend_hash_get_current_data(Z_ARRVAL_P(php_axes), (void **)&php_item) == SUCCESS;
         zend_hash_move_forward(Z_ARRVAL_P(php_axes))) {

        axes[i++] = Z_DVAL_PP(php_item);
    }

    ret = gdk_device_get_axis(device, axes, axis_to_use, &value);
    g_free(axes);

    if (ret) {
        RETURN_DOUBLE(value);
    } else {
        RETURN_NULL();
    }
}

#line 1813 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkDevice, get_core_pointer)
{
	GdkDevice* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_device_get_core_pointer();
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}

#line 486 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkDevice, get_history)
{
    zval *php_window;
    guint start, stop;
    GdkDevice *device;
    GdkTimeCoord **events;
    gint n_events, j;
    int i;
    zval *php_axes = NULL, *value, *php_event;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Nii", &php_window, gdkwindow_ce, &start, &stop))
        return;

    device = GDK_DEVICE(PHPG_GOBJECT(this_ptr));

    gdk_device_get_history(device, GDK_WINDOW(PHPG_GOBJECT(php_window)),
                           start, stop, &events, &n_events);

    array_init(return_value);
    for (i = 0; i < n_events; i++) {
        MAKE_STD_ZVAL(php_axes);
        array_init(php_axes);
        for (j = 0; j < device->num_axes; j++) {
            MAKE_STD_ZVAL(value);
            ZVAL_DOUBLE(value, events[i]->axes[j]);
            add_next_index_zval(php_axes, value);
        }

        MAKE_STD_ZVAL(php_event);
        php_gtk_build_value(&php_event, "(iN)", events[i]->time, php_axes);

        add_next_index_zval(return_value, php_event);
    }
    gdk_device_free_history(events, n_events);
}

#line 1867 "ext/gtk+/gen_gdk.c"


#line 533 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkDevice, get_state)
{
    zval *php_window;
    GdkDevice *device;
    gdouble *axes;
    GdkModifierType mask;
    zval *php_axes = NULL, *value;
    int i;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "N", &php_window, gdkwindow_ce))
        return;

    device = GDK_DEVICE(PHPG_GOBJECT(this_ptr));

    axes = g_new0(gdouble, device->num_axes);

    gdk_device_get_state(
            device,
            GDK_WINDOW(PHPG_GOBJECT(php_window)),
            axes, &mask);

    MAKE_STD_ZVAL(php_axes);
    array_init(php_axes);
    for (i = 0; i < device->num_axes; i++) {
        MAKE_STD_ZVAL(value);
        ZVAL_DOUBLE(value, axes[i]);
        add_next_index_zval(php_axes, value);
    }
    g_free(axes);

    php_gtk_build_value(&return_value, "(Ni)", php_axes, (int)mask);
}

#line 1906 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkDevice, set_axis_use)
{
	long index;
	GdkAxisUse use;
	zval *php_use = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iV", &index, &php_use))
		return;

	if (php_use && phpg_gvalue_get_enum(GDK_TYPE_AXIS_USE, php_use, (gint *)&use) == FAILURE) {
		return;
	}

    gdk_device_set_axis_use(GDK_DEVICE(PHPG_GOBJECT(this_ptr)), (guint)index, use);

}


static PHP_METHOD(GdkDevice, set_key)
{
	long index, keyval;
	GdkModifierType modifiers;
	zval *php_modifiers = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iiV", &index, &keyval, &php_modifiers))
		return;

	if (php_modifiers && phpg_gvalue_get_flags(GDK_TYPE_MODIFIER_TYPE, php_modifiers, (gint *)&modifiers) == FAILURE) {
		return;
	}

    gdk_device_set_key(GDK_DEVICE(PHPG_GOBJECT(this_ptr)), (guint)index, (guint)keyval, modifiers);

}


static PHP_METHOD(GdkDevice, set_mode)
{
	GdkInputMode mode;
	zval *php_mode = NULL;
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_mode))
		return;

	if (php_mode && phpg_gvalue_get_enum(GDK_TYPE_INPUT_MODE, php_mode, (gint *)&mode) == FAILURE) {
		return;
	}

    php_retval = gdk_device_set_mode(GDK_DEVICE(PHPG_GOBJECT(this_ptr)), mode);
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(GdkDevice, set_source)
{
	GdkInputSource source;
	zval *php_source = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_source))
		return;

	if (php_source && phpg_gvalue_get_enum(GDK_TYPE_INPUT_SOURCE, php_source, (gint *)&source) == FAILURE) {
		return;
	}

    gdk_device_set_source(GDK_DEVICE(PHPG_GOBJECT(this_ptr)), source);

}

#line 79 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkDevice, list_devices)
{
    GList *list, *item;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    list = gdk_devices_list();

    array_init(return_value);
    for (item = list; item; item = item->next) {
        zval *php_item = NULL;
        phpg_gobject_new(&php_item, G_OBJECT(item->data) TSRMLS_CC);
        add_next_index_zval(return_value, php_item);
    }

    g_list_free(list);
}

#line 2008 "ext/gtk+/gen_gdk.c"


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdevice_get_history, 0)
    ZEND_ARG_OBJ_INFO(0, window, GdkWindow, 0)
    ZEND_ARG_INFO(0, start)
    ZEND_ARG_INFO(0, stop)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdevice_get_state, 0)
    ZEND_ARG_OBJ_INFO(0, window, GdkWindow, 0)
ZEND_END_ARG_INFO();


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdevice_set_axis_use, 0)
    ZEND_ARG_INFO(0, index)
    ZEND_ARG_INFO(0, use)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdevice_set_key, 0)
    ZEND_ARG_INFO(0, index)
    ZEND_ARG_INFO(0, keyval)
    ZEND_ARG_INFO(0, modifiers)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdevice_set_mode, 0)
    ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdevice_set_source, 0)
    ZEND_ARG_INFO(0, source)
ZEND_END_ARG_INFO();

static function_entry gdkdevice_methods[] = {
	PHP_ME(GdkDevice, get_axis,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDevice, get_core_pointer,     NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkDevice, get_history,          arginfo_gdk_gdkdevice_get_history, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDevice, get_state,            arginfo_gdk_gdkdevice_get_state, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDevice, list_devices,         NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkDevice, set_axis_use,         arginfo_gdk_gdkdevice_set_axis_use, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDevice, set_key,              arginfo_gdk_gdkdevice_set_key, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDevice, set_mode,             arginfo_gdk_gdkdevice_set_mode, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDevice, set_source,           arginfo_gdk_gdkdevice_set_source, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(GdkDisplay, __construct)
{
	char *display_name;
	zend_bool free_display_name = FALSE;
	GObject *wrapped_obj;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &display_name, &free_display_name)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkDisplay);
	}

	wrapped_obj = (GObject *) gdk_display_open(display_name);
	if (free_display_name) g_free(display_name);

	if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkDisplay);
	}

    phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}


static PHP_METHOD(GdkDisplay, beep)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_display_beep(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkDisplay, close)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_display_close(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkDisplay, flush)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_display_flush(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkDisplay, get_core_pointer)
{
	GdkDevice* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_display_get_core_pointer(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkDisplay, get_default)
{
	GdkDisplay* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_display_get_default();
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkDisplay, get_default_cursor_size)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_display_get_default_cursor_size(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkDisplay, get_default_group)
{
	GdkWindow* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_display_get_default_group(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkDisplay, get_default_screen)
{
	GdkScreen* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_display_get_default_screen(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkDisplay, get_event)
{
	GdkEvent *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_display_get_event(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));
	phpg_gboxed_new(&return_value, GDK_TYPE_EVENT, php_retval, TRUE, TRUE TSRMLS_CC);

}

#line 574 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkDisplay, get_maximal_cursor_size)
{
    gint width, height;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    gdk_display_get_maximal_cursor_size(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)), &width, &height);
    php_gtk_build_value(&return_value, "(ii)", width, height);
}

#line 2216 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkDisplay, get_n_screens)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_display_get_n_screens(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkDisplay, get_name)
{
	const gchar *php_retval;
	gchar *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_display_get_name(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));
    if (php_retval) {
        cp_ret = phpg_from_utf8(php_retval, strlen(php_retval), &cp_len, &free_result TSRMLS_CC);
        if (cp_ret) {
            RETVAL_STRINGL((char *)cp_ret, cp_len, 1);
        } else {
            php_error(E_WARNING, "%s::%s(): could not convert return value from UTF-8", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        }
        if (free_result)
            g_free(cp_ret);
    } else {
        RETVAL_NULL();
    }
}


static PHP_METHOD(GdkDisplay, get_screen)
{
	long screen_num;
	GdkScreen* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &screen_num))
		return;

    php_retval = gdk_display_get_screen(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)), (gint)screen_num);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}

#line 589 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkDisplay, get_window_at_pointer)
{
    gint x, y;
    GdkWindow *window;
    zval *php_window = NULL;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    window = gdk_display_get_window_at_pointer(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)), &x, &y);

    if (window != NULL) {
        phpg_gboxed_new(&php_window, GDK_TYPE_WINDOW, &window, TRUE, TRUE TSRMLS_CC);
        php_gtk_build_value(&return_value, "(Nii)", php_window, x, y);
    } else {
        RETURN_FALSE;
    }
}

#line 2298 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkDisplay, keyboard_ungrab)
{
	long time_ = GDK_CURRENT_TIME;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "|i", &time_))
		return;

    gdk_display_keyboard_ungrab(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)), (guint32)time_);

}

#line 612 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkDisplay, list_devices)
{
    GList *list, *item;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    list = gdk_display_list_devices(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));

    array_init(return_value);
    for (item = list; item; item = item->next) {
        zval *php_item = NULL;
        phpg_gobject_new(&php_item, G_OBJECT(item->data) TSRMLS_CC);
        add_next_index_zval(return_value, php_item);
    }
}

#line 2335 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkDisplay, open_default_libgtk_only)
{
	GdkDisplay* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_display_open_default_libgtk_only();
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkDisplay, peek_event)
{
	GdkEvent *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_display_peek_event(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));
	phpg_gboxed_new(&return_value, GDK_TYPE_EVENT, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(GdkDisplay, pointer_is_grabbed)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_display_pointer_is_grabbed(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(GdkDisplay, pointer_ungrab)
{
	long time_ = GDK_CURRENT_TIME;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "|i", &time_))
		return;

    gdk_display_pointer_ungrab(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)), (guint32)time_);

}


static PHP_METHOD(GdkDisplay, put_event)
{
	GdkEvent *event = NULL;
	zval *php_event;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_event, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_event, GDK_TYPE_EVENT, FALSE TSRMLS_CC)) {
        event = (GdkEvent *) PHPG_GBOXED(php_event);
    } else {
        php_error(E_WARNING, "%s::%s() expects event argument to be a valid GdkEvent object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    gdk_display_put_event(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)), event);

}


static PHP_METHOD(GdkDisplay, request_selection_notification)
{
	GdkAtom selection;
	zval *php_selection = NULL;
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_selection))
		return;

    selection = phpg_gdkatom_from_zval(php_selection TSRMLS_CC);
    if (selection == NULL) {
        php_error(E_WARNING, "%s::%s() expects selection argument to be a valid GdkAtom object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    php_retval = gdk_display_request_selection_notification(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)), selection);
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(GdkDisplay, set_double_click_distance)
{
	long distance;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &distance))
		return;

    gdk_display_set_double_click_distance(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)), (guint)distance);

}


static PHP_METHOD(GdkDisplay, set_double_click_time)
{
	long msec;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &msec))
		return;

    gdk_display_set_double_click_time(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)), (guint)msec);

}


static PHP_METHOD(GdkDisplay, supports_clipboard_persistence)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_display_supports_clipboard_persistence(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(GdkDisplay, supports_cursor_alpha)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_display_supports_cursor_alpha(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(GdkDisplay, supports_cursor_color)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_display_supports_cursor_color(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(GdkDisplay, supports_selection_notification)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_display_supports_selection_notification(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(GdkDisplay, sync)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_display_sync(GDK_DISPLAY(PHPG_GOBJECT(this_ptr)));

}


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdisplay_gdk_display_open, 0)
    ZEND_ARG_INFO(0, display_name)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdisplay_get_screen, 0)
    ZEND_ARG_INFO(0, screen_num)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkdisplay_keyboard_ungrab, 0, 0, 0)
    ZEND_ARG_INFO(0, time_)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkdisplay_pointer_ungrab, 0, 0, 0)
    ZEND_ARG_INFO(0, time_)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdisplay_put_event, 0)
    ZEND_ARG_OBJ_INFO(0, event, GdkEvent, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdisplay_request_selection_notification, 0)
    ZEND_ARG_INFO(0, selection)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdisplay_set_double_click_distance, 0)
    ZEND_ARG_INFO(0, distance)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdisplay_set_double_click_time, 0)
    ZEND_ARG_INFO(0, msec)
ZEND_END_ARG_INFO();

static function_entry gdkdisplay_methods[] = {
	PHP_ME(GdkDisplay, __construct,          arginfo_gdk_gdkdisplay_gdk_display_open, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, beep,                 NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, close,                NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, flush,                NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, get_core_pointer,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, get_default,          NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkDisplay, get_default_cursor_size, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, get_default_group,    NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, get_default_screen,   NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, get_event,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, get_maximal_cursor_size, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, get_n_screens,        NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, get_name,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, get_screen,           arginfo_gdk_gdkdisplay_get_screen, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, get_window_at_pointer, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, keyboard_ungrab,      arginfo_gdk_gdkdisplay_keyboard_ungrab, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, list_devices,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, open_default_libgtk_only, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkDisplay, peek_event,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, pointer_is_grabbed,   NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, pointer_ungrab,       arginfo_gdk_gdkdisplay_pointer_ungrab, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, put_event,            arginfo_gdk_gdkdisplay_put_event, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, request_selection_notification, arginfo_gdk_gdkdisplay_request_selection_notification, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, set_double_click_distance, arginfo_gdk_gdkdisplay_set_double_click_distance, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, set_double_click_time, arginfo_gdk_gdkdisplay_set_double_click_time, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, supports_clipboard_persistence, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, supports_cursor_alpha, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, supports_cursor_color, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, supports_selection_notification, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplay, sync,                 NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(GdkDisplayManager, get)
{
	GdkDisplayManager* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_display_manager_get();
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkDisplayManager, get_default_display)
{
	GdkDisplay* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_display_manager_get_default_display(GDK_DISPLAY_MANAGER(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}

#line 637 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkDisplayManager, list_displays)
{
    GSList *list, *tmp;

    list = gdk_display_manager_list_displays(GDK_DISPLAY_MANAGER(PHPG_GOBJECT(this_ptr)));
    array_init(return_value);
    for (tmp = list; tmp != NULL; tmp = tmp->next) {
        zval *php_item = NULL;
        phpg_gobject_new(&php_item, G_OBJECT(tmp->data) TSRMLS_CC);
        add_next_index_zval(return_value, php_item);
    }
    g_slist_free(list);
}

#line 2651 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkDisplayManager, set_default_display)
{
	zval *display;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &display, gdkdisplay_ce))
		return;

    gdk_display_manager_set_default_display(GDK_DISPLAY_MANAGER(PHPG_GOBJECT(this_ptr)), GDK_DISPLAY(PHPG_GOBJECT(display)));

}


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdisplaymanager_set_default_display, 0)
    ZEND_ARG_OBJ_INFO(0, display, GdkDisplay, 1)
ZEND_END_ARG_INFO();

static function_entry gdkdisplaymanager_methods[] = {
	PHP_ME(GdkDisplayManager, get,                  NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkDisplayManager, get_default_display,  NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplayManager, list_displays,        NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDisplayManager, set_default_display,  arginfo_gdk_gdkdisplaymanager_set_default_display, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(GdkDragContext, __construct)
{
    GObject *wrapped_obj;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "")) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkDragContext);
    }


    wrapped_obj = (GObject *) g_object_newv(phpg_gtype_from_zval(this_ptr), 0, NULL);

    if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkDragContext);
    }

    phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}


PHPG_PROP_READER(GdkDragContext, protocol)
{
	long php_retval;

    php_retval = GDK_DRAG_CONTEXT(((phpg_gobject_t *)object)->obj)->protocol;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkDragContext, is_source)
{
	gboolean php_retval;

    php_retval = GDK_DRAG_CONTEXT(((phpg_gobject_t *)object)->obj)->is_source;
	RETVAL_BOOL(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkDragContext, source_window)
{
	GdkWindow* php_retval;

    php_retval = GDK_DRAG_CONTEXT(((phpg_gobject_t *)object)->obj)->source_window;
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
    return SUCCESS;
}


PHPG_PROP_READER(GdkDragContext, dest_window)
{
	GdkWindow* php_retval;

    php_retval = GDK_DRAG_CONTEXT(((phpg_gobject_t *)object)->obj)->dest_window;
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
    return SUCCESS;
}


PHPG_PROP_READER(GdkDragContext, actions)
{
	long php_retval;

    php_retval = GDK_DRAG_CONTEXT(((phpg_gobject_t *)object)->obj)->actions;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkDragContext, suggested_action)
{
	long php_retval;

    php_retval = GDK_DRAG_CONTEXT(((phpg_gobject_t *)object)->obj)->suggested_action;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkDragContext, action)
{
	long php_retval;

    php_retval = GDK_DRAG_CONTEXT(((phpg_gobject_t *)object)->obj)->action;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkDragContext, start_time)
{
	long php_retval;

    php_retval = GDK_DRAG_CONTEXT(((phpg_gobject_t *)object)->obj)->start_time;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


static prop_info_t gdkdragcontext_prop_info[] = {
	{ "protocol", PHPG_PROP_READ_FN(GdkDragContext, protocol), NULL },
	{ "is_source", PHPG_PROP_READ_FN(GdkDragContext, is_source), NULL },
	{ "source_window", PHPG_PROP_READ_FN(GdkDragContext, source_window), NULL },
	{ "dest_window", PHPG_PROP_READ_FN(GdkDragContext, dest_window), NULL },
	{ "actions", PHPG_PROP_READ_FN(GdkDragContext, actions), NULL },
	{ "suggested_action", PHPG_PROP_READ_FN(GdkDragContext, suggested_action), NULL },
	{ "action", PHPG_PROP_READ_FN(GdkDragContext, action), NULL },
	{ "start_time", PHPG_PROP_READ_FN(GdkDragContext, start_time), NULL },
	{ NULL, NULL, NULL },
};


static PHP_METHOD(GdkDragContext, drag_abort)
{
	long time;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &time))
		return;

    gdk_drag_abort(GDK_DRAG_CONTEXT(PHPG_GOBJECT(this_ptr)), (guint32)time);

}


static PHP_METHOD(GdkDragContext, ref)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_drag_context_ref(GDK_DRAG_CONTEXT(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkDragContext, unref)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_drag_context_unref(GDK_DRAG_CONTEXT(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkDragContext, drag_drop)
{
	long time;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &time))
		return;

    gdk_drag_drop(GDK_DRAG_CONTEXT(PHPG_GOBJECT(this_ptr)), (guint32)time);

}


static PHP_METHOD(GdkDragContext, drag_drop_succeeded)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_drag_drop_succeeded(GDK_DRAG_CONTEXT(PHPG_GOBJECT(this_ptr)));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(GdkDragContext, drag_get_selection)
{
	GdkAtom php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_drag_get_selection(GDK_DRAG_CONTEXT(PHPG_GOBJECT(this_ptr)));
	phpg_gdkatom_new(&return_value, php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkDragContext, drag_motion)
{
	zval *dest_window, *php_protocol = NULL, *php_suggested_action = NULL, *php_possible_actions = NULL;
	GdkDragProtocol protocol;
	long x_root, y_root, time;
	GdkDragAction suggested_action, possible_actions;
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OViiVVi", &dest_window, gdkwindow_ce, &php_protocol, &x_root, &y_root, &php_suggested_action, &php_possible_actions, &time))
		return;

	if (php_protocol && phpg_gvalue_get_enum(GDK_TYPE_DRAG_PROTOCOL, php_protocol, (gint *)&protocol) == FAILURE) {
		return;
	}

	if (php_suggested_action && phpg_gvalue_get_flags(GDK_TYPE_DRAG_ACTION, php_suggested_action, (gint *)&suggested_action) == FAILURE) {
		return;
	}

	if (php_possible_actions && phpg_gvalue_get_flags(GDK_TYPE_DRAG_ACTION, php_possible_actions, (gint *)&possible_actions) == FAILURE) {
		return;
	}

    php_retval = gdk_drag_motion(GDK_DRAG_CONTEXT(PHPG_GOBJECT(this_ptr)), GDK_WINDOW(PHPG_GOBJECT(dest_window)), protocol, (gint)x_root, (gint)y_root, suggested_action, possible_actions, (guint32)time);
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(GdkDragContext, drag_status)
{
	GdkDragAction action;
	zval *php_action = NULL;
	long time = GDK_CURRENT_TIME;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V|i", &php_action, &time))
		return;

	if (php_action && phpg_gvalue_get_flags(GDK_TYPE_DRAG_ACTION, php_action, (gint *)&action) == FAILURE) {
		return;
	}

    gdk_drag_status(GDK_DRAG_CONTEXT(PHPG_GOBJECT(this_ptr)), action, (guint32)time);

}


static PHP_METHOD(GdkDragContext, drop_finish)
{
	zend_bool success;
	long time = GDK_CURRENT_TIME;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b|i", &success, &time))
		return;

    gdk_drop_finish(GDK_DRAG_CONTEXT(PHPG_GOBJECT(this_ptr)), (gboolean)success, (guint32)time);

}


static PHP_METHOD(GdkDragContext, drop_reply)
{
	zend_bool ok;
	long time = GDK_CURRENT_TIME;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b|i", &ok, &time))
		return;

    gdk_drop_reply(GDK_DRAG_CONTEXT(PHPG_GOBJECT(this_ptr)), (gboolean)ok, (guint32)time);

}


static PHP_METHOD(GdkDragContext, finish)
{
	zend_bool success, del;
	long time = GDK_CURRENT_TIME;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "bb|i", &success, &del, &time))
		return;

    gtk_drag_finish(GDK_DRAG_CONTEXT(PHPG_GOBJECT(this_ptr)), (gboolean)success, (gboolean)del, (guint32)time);

}


static PHP_METHOD(GdkDragContext, get_source_widget)
{
	GtkWidget* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gtk_drag_get_source_widget(GDK_DRAG_CONTEXT(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkDragContext, set_icon_default)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gtk_drag_set_icon_default(GDK_DRAG_CONTEXT(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkDragContext, set_icon_pixbuf)
{
	zval *pixbuf;
	long hot_x, hot_y;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Oii", &pixbuf, gdkpixbuf_ce, &hot_x, &hot_y))
		return;

    gtk_drag_set_icon_pixbuf(GDK_DRAG_CONTEXT(PHPG_GOBJECT(this_ptr)), GDK_PIXBUF(PHPG_GOBJECT(pixbuf)), (gint)hot_x, (gint)hot_y);

}


static PHP_METHOD(GdkDragContext, set_icon_pixmap)
{
	zval *colormap, *pixmap, *mask;
	long hot_x, hot_y;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OOOii", &colormap, gdkcolormap_ce, &pixmap, gdkpixmap_ce, &mask, gdkpixmap_ce, &hot_x, &hot_y))
		return;

    gtk_drag_set_icon_pixmap(GDK_DRAG_CONTEXT(PHPG_GOBJECT(this_ptr)), GDK_COLORMAP(PHPG_GOBJECT(colormap)), GDK_PIXMAP(PHPG_GOBJECT(pixmap)), GDK_PIXMAP(PHPG_GOBJECT(mask)), (gint)hot_x, (gint)hot_y);

}


static PHP_METHOD(GdkDragContext, set_icon_stock)
{
	char *stock_id;
	zend_bool free_stock_id = FALSE;
	long hot_x, hot_y;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "uii", &stock_id, &free_stock_id, &hot_x, &hot_y))
		return;

    gtk_drag_set_icon_stock(GDK_DRAG_CONTEXT(PHPG_GOBJECT(this_ptr)), stock_id, (gint)hot_x, (gint)hot_y);
	if (free_stock_id) g_free(stock_id);

}


static PHP_METHOD(GdkDragContext, set_icon_widget)
{
	zval *widget;
	long hot_x, hot_y;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Oii", &widget, gtkwidget_ce, &hot_x, &hot_y))
		return;

    gtk_drag_set_icon_widget(GDK_DRAG_CONTEXT(PHPG_GOBJECT(this_ptr)), GTK_WIDGET(PHPG_GOBJECT(widget)), (gint)hot_x, (gint)hot_y);

}


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdragcontext_drag_abort, 0)
    ZEND_ARG_INFO(0, time)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdragcontext_drag_drop, 0)
    ZEND_ARG_INFO(0, time)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdragcontext_drag_motion, 0)
    ZEND_ARG_OBJ_INFO(0, dest_window, GdkWindow, 1)
    ZEND_ARG_INFO(0, protocol)
    ZEND_ARG_INFO(0, x_root)
    ZEND_ARG_INFO(0, y_root)
    ZEND_ARG_INFO(0, suggested_action)
    ZEND_ARG_INFO(0, possible_actions)
    ZEND_ARG_INFO(0, time)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkdragcontext_drag_status, 0, 0, 1)
    ZEND_ARG_INFO(0, action)
    ZEND_ARG_INFO(0, time)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkdragcontext_drop_finish, 0, 0, 1)
    ZEND_ARG_INFO(0, success)
    ZEND_ARG_INFO(0, time)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkdragcontext_drop_reply, 0, 0, 1)
    ZEND_ARG_INFO(0, ok)
    ZEND_ARG_INFO(0, time)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkdragcontext_finish, 0, 0, 2)
    ZEND_ARG_INFO(0, success)
    ZEND_ARG_INFO(0, del)
    ZEND_ARG_INFO(0, time)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdragcontext_set_icon_pixbuf, 0)
    ZEND_ARG_OBJ_INFO(0, pixbuf, GdkPixbuf, 1)
    ZEND_ARG_INFO(0, hot_x)
    ZEND_ARG_INFO(0, hot_y)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdragcontext_set_icon_pixmap, 0)
    ZEND_ARG_OBJ_INFO(0, colormap, GdkColormap, 1)
    ZEND_ARG_OBJ_INFO(0, pixmap, GdkPixmap, 1)
    ZEND_ARG_INFO(0, mask)
    ZEND_ARG_INFO(0, hot_x)
    ZEND_ARG_INFO(0, hot_y)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdragcontext_set_icon_stock, 0)
    ZEND_ARG_INFO(0, stock_id)
    ZEND_ARG_INFO(0, hot_x)
    ZEND_ARG_INFO(0, hot_y)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdragcontext_set_icon_widget, 0)
    ZEND_ARG_OBJ_INFO(0, widget, GtkWidget, 1)
    ZEND_ARG_INFO(0, hot_x)
    ZEND_ARG_INFO(0, hot_y)
ZEND_END_ARG_INFO();

static function_entry gdkdragcontext_methods[] = {
	PHP_ME(GdkDragContext, __construct,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDragContext, drag_abort,           arginfo_gdk_gdkdragcontext_drag_abort, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDragContext, drag_drop,            arginfo_gdk_gdkdragcontext_drag_drop, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDragContext, drag_drop_succeeded,  NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDragContext, drag_get_selection,   NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDragContext, drag_motion,          arginfo_gdk_gdkdragcontext_drag_motion, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDragContext, drag_status,          arginfo_gdk_gdkdragcontext_drag_status, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDragContext, drop_finish,          arginfo_gdk_gdkdragcontext_drop_finish, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDragContext, drop_reply,           arginfo_gdk_gdkdragcontext_drop_reply, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDragContext, finish,               arginfo_gdk_gdkdragcontext_finish, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDragContext, get_source_widget,    NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDragContext, ref,                  NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDragContext, set_icon_default,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDragContext, set_icon_pixbuf,      arginfo_gdk_gdkdragcontext_set_icon_pixbuf, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDragContext, set_icon_pixmap,      arginfo_gdk_gdkdragcontext_set_icon_pixmap, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDragContext, set_icon_stock,       arginfo_gdk_gdkdragcontext_set_icon_stock, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDragContext, set_icon_widget,      arginfo_gdk_gdkdragcontext_set_icon_widget, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDragContext, unref,                NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
#line 657 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkDrawable, xid)
{
#if defined(GDK_WINDOWING_X11)
	RETVAL_LONG(GDK_DRAWABLE_XID(((GdkDrawable *)((phpg_gobject_t *)object)->obj)));
#else
    RETVAL_LONG((long) GDK_WINDOW_HWND((GdkDrawable *)((phpg_gobject_t *)object)->obj));
#endif
    return SUCCESS;
}

#line 3168 "ext/gtk+/gen_gdk.c"



static prop_info_t gdkdrawable_prop_info[] = {
	{ "xid", PHPG_PROP_READ_FN(GdkDrawable, xid), NULL },
	{ NULL, NULL, NULL },
};


static PHP_METHOD(GdkDrawable, draw_arc)
{
	zval *gc;
	zend_bool filled;
	long x, y, width, height, angle1, angle2;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Obiiiiii", &gc, gdkgc_ce, &filled, &x, &y, &width, &height, &angle1, &angle2))
		return;

    gdk_draw_arc(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), GDK_GC(PHPG_GOBJECT(gc)), (gboolean)filled, (gint)x, (gint)y, (gint)width, (gint)height, (gint)angle1, (gint)angle2);

}


static PHP_METHOD(GdkDrawable, draw_drawable)
{
	zval *gc, *src;
	long xsrc, ysrc, xdest, ydest, width, height;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OOiiiiii", &gc, gdkgc_ce, &src, gdkdrawable_ce, &xsrc, &ysrc, &xdest, &ydest, &width, &height))
		return;

    gdk_draw_drawable(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), GDK_GC(PHPG_GOBJECT(gc)), GDK_DRAWABLE(PHPG_GOBJECT(src)), (gint)xsrc, (gint)ysrc, (gint)xdest, (gint)ydest, (gint)width, (gint)height);

}


static PHP_METHOD(GdkDrawable, draw_glyphs)
{
	zval *gc, *font, *php_glyphs;
	long x, y;
	PangoGlyphString *glyphs = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OOiiO", &gc, gdkgc_ce, &font, pangofont_ce, &x, &y, &php_glyphs, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_glyphs, PANGO_TYPE_GLYPH_STRING, FALSE TSRMLS_CC)) {
        glyphs = (PangoGlyphString *) PHPG_GBOXED(php_glyphs);
    } else {
        php_error(E_WARNING, "%s::%s() expects glyphs argument to be a valid PangoGlyphString object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    gdk_draw_glyphs(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), GDK_GC(PHPG_GOBJECT(gc)), PANGO_FONT(PHPG_GOBJECT(font)), (gint)x, (gint)y, glyphs);

}


static PHP_METHOD(GdkDrawable, draw_gray_image)
{
	zval *gc, *php_dith = NULL;
	long x, y, width, height, rowstride;
	GdkRgbDither dith;
	char *buf;
	zend_bool free_buf = FALSE;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OiiiiVui", &gc, gdkgc_ce, &x, &y, &width, &height, &php_dith, &buf, &free_buf, &rowstride))
		return;

	if (php_dith && phpg_gvalue_get_enum(GDK_TYPE_RGB_DITHER, php_dith, (gint *)&dith) == FAILURE) {
		return;
	}

    gdk_draw_gray_image(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), GDK_GC(PHPG_GOBJECT(gc)), (gint)x, (gint)y, (gint)width, (gint)height, dith, buf, (gint)rowstride);
	if (free_buf) g_free(buf);

}


static PHP_METHOD(GdkDrawable, draw_image)
{
	zval *gc, *image;
	long xsrc, ysrc, xdest, ydest, width, height;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OOiiiiii", &gc, gdkgc_ce, &image, gdkimage_ce, &xsrc, &ysrc, &xdest, &ydest, &width, &height))
		return;

    gdk_draw_image(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), GDK_GC(PHPG_GOBJECT(gc)), GDK_IMAGE(PHPG_GOBJECT(image)), (gint)xsrc, (gint)ysrc, (gint)xdest, (gint)ydest, (gint)width, (gint)height);

}


static PHP_METHOD(GdkDrawable, draw_layout)
{
	zval *gc, *layout;
	long x, y;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OiiO", &gc, gdkgc_ce, &x, &y, &layout, pangolayout_ce))
		return;

    gdk_draw_layout(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), GDK_GC(PHPG_GOBJECT(gc)), (gint)x, (gint)y, PANGO_LAYOUT(PHPG_GOBJECT(layout)));

}


static PHP_METHOD(GdkDrawable, draw_line)
{
	zval *gc;
	long x1, y1, x2, y2;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Oiiii", &gc, gdkgc_ce, &x1, &y1, &x2, &y2))
		return;

    gdk_draw_line(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), GDK_GC(PHPG_GOBJECT(gc)), (gint)x1, (gint)y1, (gint)x2, (gint)y2);

}


static PHP_METHOD(GdkDrawable, draw_pixbuf)
{
	GdkGC *gc = NULL;
	zval *php_gc, *php_pixbuf, *php_dither = NULL;
	GdkPixbuf *pixbuf = NULL;
	long src_x, src_y, dest_x, dest_y, width = -1, height = -1, x_dither = GDK_RGB_DITHER_NORMAL, y_dither = GDK_RGB_DITHER_NORMAL;
	GdkRgbDither dither = GDK_RGB_DITHER_NORMAL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "NNiiii|iiVii", &php_gc, gdkgc_ce, &php_pixbuf, gdkpixbuf_ce, &src_x, &src_y, &dest_x, &dest_y, &width, &height, &php_dither, &x_dither, &y_dither))
		return;
    if (Z_TYPE_P(php_gc) != IS_NULL)
        gc = GDK_GC(PHPG_GOBJECT(php_gc));
    if (Z_TYPE_P(php_pixbuf) != IS_NULL)
        pixbuf = GDK_PIXBUF(PHPG_GOBJECT(php_pixbuf));

	if (php_dither && phpg_gvalue_get_enum(GDK_TYPE_RGB_DITHER, php_dither, (gint *)&dither) == FAILURE) {
		return;
	}

    gdk_draw_pixbuf(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), gc, pixbuf, (gint)src_x, (gint)src_y, (gint)dest_x, (gint)dest_y, (gint)width, (gint)height, dither, (gint)x_dither, (gint)y_dither);

}


static PHP_METHOD(GdkDrawable, draw_point)
{
	zval *gc;
	long x, y;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Oii", &gc, gdkgc_ce, &x, &y))
		return;

    gdk_draw_point(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), GDK_GC(PHPG_GOBJECT(gc)), (gint)x, (gint)y);

}


static PHP_METHOD(GdkDrawable, draw_rectangle)
{
	zval *gc;
	zend_bool filled;
	long x, y, width, height;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Obiiii", &gc, gdkgc_ce, &filled, &x, &y, &width, &height))
		return;

    gdk_draw_rectangle(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), GDK_GC(PHPG_GOBJECT(gc)), (gboolean)filled, (gint)x, (gint)y, (gint)width, (gint)height);

}

#line 719 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkDrawable, draw_rgb_32_image)
{
	zval *gc, *php_dith = NULL;
	long x, y, width, height, rowstride = -1, xdith = 0, ydith = 0;
	GdkRgbDither dith;
	guchar *rgb_buf;
    int rgb_buf_len;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OiiiiVs#|iii", &gc, gdkgc_ce, &x, &y, &width, &height, &php_dith, &rgb_buf, &rgb_buf_len, &rowstride, &xdith, &ydith))
		return;

	if (php_dith && phpg_gvalue_get_enum(GDK_TYPE_RGB_DITHER, php_dith, (gint *)&dith) == FAILURE) {
		return;
	}

    if (width <= 0 || height <= 0) {
        php_error(E_WARNING, "width and height must be greater than 0");
        return;
    }

    if (rowstride == -1) {
        rowstride = width << 2;
    }
    if (rgb_buf_len < rowstride * (height-1) + (width << 2)) {
        php_error(E_WARNING, "RGB buffer is not large enough");
        return;
    }

    gdk_draw_rgb_32_image_dithalign(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), GDK_GC(PHPG_GOBJECT(gc)), (gint)x, (gint)y, (gint)width, (gint)height, dith, rgb_buf, (gint)rowstride, (gint)xdith, (gint)ydith);
}

#line 3391 "ext/gtk+/gen_gdk.c"


#line 684 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkDrawable, draw_rgb_image)
{
	zval *gc, *php_dith = NULL;
	long x, y, width, height, rowstride = -1, xdith = 0, ydith = 0;
	GdkRgbDither dith;
	guchar *rgb_buf;
    int rgb_buf_len;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OiiiiVs#|iii", &gc, gdkgc_ce, &x, &y, &width, &height, &php_dith, &rgb_buf, &rgb_buf_len, &rowstride, &xdith, &ydith))
		return;

	if (php_dith && phpg_gvalue_get_enum(GDK_TYPE_RGB_DITHER, php_dith, (gint *)&dith) == FAILURE) {
		return;
	}

    if (width <= 0 || height <= 0) {
        php_error(E_WARNING, "width and height must be greater than 0");
        return;
    }

    if (rowstride == -1) {
        rowstride = width * 3;
    }
    if (rgb_buf_len < rowstride * (height-1) + width * 3) {
        php_error(E_WARNING, "RGB buffer is not large enough");
        return;
    }

    gdk_draw_rgb_image_dithalign(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), GDK_GC(PHPG_GOBJECT(gc)), (gint)x, (gint)y, (gint)width, (gint)height, dith, rgb_buf, (gint)rowstride, (gint)xdith, (gint)ydith);
}

#line 3428 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkDrawable, draw_string)
{
	GdkFont *font = NULL;
	zval *php_font, *gc;
	long x, y;
	char *string;
	zend_bool free_string = FALSE;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OOiiu", &php_font, gboxed_ce, &gc, gdkgc_ce, &x, &y, &string, &free_string))
		return;

    if (phpg_gboxed_check(php_font, GDK_TYPE_FONT, FALSE TSRMLS_CC)) {
        font = (GdkFont *) PHPG_GBOXED(php_font);
    } else {
        php_error(E_WARNING, "%s::%s() expects font argument to be a valid GdkFont object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

	phpg_warn_deprecated("use GdkDrawable::draw_layout()" TSRMLS_CC);

    gdk_draw_string(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), font, GDK_GC(PHPG_GOBJECT(gc)), (gint)x, (gint)y, string);
	if (free_string) g_free(string);

}


static PHP_METHOD(GdkDrawable, draw_text)
{
	GdkFont *font = NULL;
	zval *php_font, *gc;
	long x, y, text_length;
	char *text;
	zend_bool free_text = FALSE;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OOiiui", &php_font, gboxed_ce, &gc, gdkgc_ce, &x, &y, &text, &free_text, &text_length))
		return;

    if (phpg_gboxed_check(php_font, GDK_TYPE_FONT, FALSE TSRMLS_CC)) {
        font = (GdkFont *) PHPG_GBOXED(php_font);
    } else {
        php_error(E_WARNING, "%s::%s() expects font argument to be a valid GdkFont object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

	phpg_warn_deprecated("use GdkDrawable::draw_layout()" TSRMLS_CC);

    gdk_draw_text(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), font, GDK_GC(PHPG_GOBJECT(gc)), (gint)x, (gint)y, text, (gint)text_length);
	if (free_text) g_free(text);

}


static PHP_METHOD(GdkDrawable, get_colormap)
{
	GdkColormap* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_drawable_get_colormap(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkDrawable, get_depth)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_drawable_get_depth(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkDrawable, get_display)
{
	GdkDisplay* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_drawable_get_display(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkDrawable, get_image)
{
	long x, y, width, height;
	GdkImage* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iiii", &x, &y, &width, &height))
		return;

    php_retval = gdk_drawable_get_image(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), (gint)x, (gint)y, (gint)width, (gint)height);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
    if (php_retval != NULL) {
        g_object_unref(php_retval);
    }
}


static PHP_METHOD(GdkDrawable, get_screen)
{
	GdkScreen* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_drawable_get_screen(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}

#line 669 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkDrawable, get_size)
{
    gint width, height;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    gdk_drawable_get_size(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), &width, &height);
    php_gtk_build_value(&return_value, "(ii)", width, height);
}

#line 3577 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkDrawable, get_visual)
{
	GdkVisual* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_drawable_get_visual(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkDrawable, ref)
{
	GdkDrawable* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_drawable_ref(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkDrawable, set_colormap)
{
	zval *colormap;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &colormap, gdkcolormap_ce))
		return;

    gdk_drawable_set_colormap(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), GDK_COLORMAP(PHPG_GOBJECT(colormap)));

}


static PHP_METHOD(GdkDrawable, unref)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_drawable_unref(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkDrawable, image_get)
{
	long x, y, width, height;
	GdkImage* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iiii", &x, &y, &width, &height))
		return;

	phpg_warn_deprecated("use GdkDrawable::get_image()" TSRMLS_CC);

    php_retval = gdk_image_get(GDK_DRAWABLE(PHPG_GOBJECT(this_ptr)), (gint)x, (gint)y, (gint)width, (gint)height);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdrawable_draw_arc, 0)
    ZEND_ARG_OBJ_INFO(0, gc, GdkGC, 1)
    ZEND_ARG_INFO(0, filled)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, angle1)
    ZEND_ARG_INFO(0, angle2)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdrawable_draw_drawable, 0)
    ZEND_ARG_OBJ_INFO(0, gc, GdkGC, 1)
    ZEND_ARG_OBJ_INFO(0, src, GdkDrawable, 1)
    ZEND_ARG_INFO(0, xsrc)
    ZEND_ARG_INFO(0, ysrc)
    ZEND_ARG_INFO(0, xdest)
    ZEND_ARG_INFO(0, ydest)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdrawable_draw_glyphs, 0)
    ZEND_ARG_OBJ_INFO(0, gc, GdkGC, 1)
    ZEND_ARG_OBJ_INFO(0, font, PangoFont, 1)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_OBJ_INFO(0, glyphs, PangoGlyphString, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdrawable_draw_gray_image, 0)
    ZEND_ARG_OBJ_INFO(0, gc, GdkGC, 1)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, dith)
    ZEND_ARG_INFO(0, buf)
    ZEND_ARG_INFO(0, rowstride)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdrawable_draw_image, 0)
    ZEND_ARG_OBJ_INFO(0, gc, GdkGC, 1)
    ZEND_ARG_OBJ_INFO(0, image, GdkImage, 1)
    ZEND_ARG_INFO(0, xsrc)
    ZEND_ARG_INFO(0, ysrc)
    ZEND_ARG_INFO(0, xdest)
    ZEND_ARG_INFO(0, ydest)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdrawable_draw_layout, 0)
    ZEND_ARG_OBJ_INFO(0, gc, GdkGC, 1)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_OBJ_INFO(0, layout, PangoLayout, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdrawable_draw_line, 0)
    ZEND_ARG_OBJ_INFO(0, gc, GdkGC, 1)
    ZEND_ARG_INFO(0, x1)
    ZEND_ARG_INFO(0, y1)
    ZEND_ARG_INFO(0, x2)
    ZEND_ARG_INFO(0, y2)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkdrawable_draw_pixbuf, 0, 0, 6)
    ZEND_ARG_OBJ_INFO(0, gc, GdkGC, 1)
    ZEND_ARG_OBJ_INFO(0, pixbuf, GdkPixbuf, 1)
    ZEND_ARG_INFO(0, src_x)
    ZEND_ARG_INFO(0, src_y)
    ZEND_ARG_INFO(0, dest_x)
    ZEND_ARG_INFO(0, dest_y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, dither)
    ZEND_ARG_INFO(0, x_dither)
    ZEND_ARG_INFO(0, y_dither)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdrawable_draw_point, 0)
    ZEND_ARG_OBJ_INFO(0, gc, GdkGC, 1)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdrawable_draw_rectangle, 0)
    ZEND_ARG_OBJ_INFO(0, gc, GdkGC, 1)
    ZEND_ARG_INFO(0, filled)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdrawable_draw_string, 0)
    ZEND_ARG_OBJ_INFO(0, font, GdkFont, 1)
    ZEND_ARG_OBJ_INFO(0, gc, GdkGC, 1)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdrawable_draw_text, 0)
    ZEND_ARG_OBJ_INFO(0, font, GdkFont, 1)
    ZEND_ARG_OBJ_INFO(0, gc, GdkGC, 1)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, text_length)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdrawable_get_image, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdrawable_set_colormap, 0)
    ZEND_ARG_OBJ_INFO(0, colormap, GdkColormap, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkdrawable_image_get, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();

static function_entry gdkdrawable_methods[] = {
	PHP_ME(GdkDrawable, draw_arc,             arginfo_gdk_gdkdrawable_draw_arc, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, draw_drawable,        arginfo_gdk_gdkdrawable_draw_drawable, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, draw_glyphs,          arginfo_gdk_gdkdrawable_draw_glyphs, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, draw_gray_image,      arginfo_gdk_gdkdrawable_draw_gray_image, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, draw_image,           arginfo_gdk_gdkdrawable_draw_image, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, draw_layout,          arginfo_gdk_gdkdrawable_draw_layout, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, draw_line,            arginfo_gdk_gdkdrawable_draw_line, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, draw_pixbuf,          arginfo_gdk_gdkdrawable_draw_pixbuf, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, draw_point,           arginfo_gdk_gdkdrawable_draw_point, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, draw_rectangle,       arginfo_gdk_gdkdrawable_draw_rectangle, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, draw_rgb_32_image,    NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, draw_rgb_image,       NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, draw_string,          arginfo_gdk_gdkdrawable_draw_string, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, draw_text,            arginfo_gdk_gdkdrawable_draw_text, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, get_colormap,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, get_depth,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, get_display,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, get_image,            arginfo_gdk_gdkdrawable_get_image, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, get_screen,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, get_size,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, get_visual,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, image_get,            arginfo_gdk_gdkdrawable_image_get, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, ref,                  NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, set_colormap,         arginfo_gdk_gdkdrawable_set_colormap, ZEND_ACC_PUBLIC)
	PHP_ME(GdkDrawable, unref,                NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(GdkWindow, input_set_extension_events)
{
	long mask;
	GdkExtensionMode mode;
	zval *php_mode = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iV", &mask, &php_mode))
		return;

	if (php_mode && phpg_gvalue_get_enum(GDK_TYPE_EXTENSION_MODE, php_mode, (gint *)&mode) == FAILURE) {
		return;
	}

    gdk_input_set_extension_events(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gint)mask, mode);

}


static PHP_METHOD(GdkWindow, property_change)
{
	GdkAtom property, type;
	zval *php_property = NULL, *php_type = NULL, *php_mode = NULL;
	long format, nelements;
	GdkPropMode mode;
	char *data;
	zend_bool free_data = FALSE;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "VViVui", &php_property, &php_type, &format, &php_mode, &data, &free_data, &nelements))
		return;

    property = phpg_gdkatom_from_zval(php_property TSRMLS_CC);
    if (property == NULL) {
        php_error(E_WARNING, "%s::%s() expects property argument to be a valid GdkAtom object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    type = phpg_gdkatom_from_zval(php_type TSRMLS_CC);
    if (type == NULL) {
        php_error(E_WARNING, "%s::%s() expects type argument to be a valid GdkAtom object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

	if (php_mode && phpg_gvalue_get_enum(GDK_TYPE_PROP_MODE, php_mode, (gint *)&mode) == FAILURE) {
		return;
	}

    gdk_property_change(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), property, type, (gint)format, mode, data, (gint)nelements);
	if (free_data) g_free(data);

}


static PHP_METHOD(GdkWindow, property_delete)
{
	GdkAtom property;
	zval *php_property = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_property))
		return;

    property = phpg_gdkatom_from_zval(php_property TSRMLS_CC);
    if (property == NULL) {
        php_error(E_WARNING, "%s::%s() expects property argument to be a valid GdkAtom object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    gdk_property_delete(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), property);

}


static PHP_METHOD(GdkWindow, selection_convert)
{
	GdkAtom selection, target;
	zval *php_selection = NULL, *php_target = NULL;
	long time;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "VVi", &php_selection, &php_target, &time))
		return;

    selection = phpg_gdkatom_from_zval(php_selection TSRMLS_CC);
    if (selection == NULL) {
        php_error(E_WARNING, "%s::%s() expects selection argument to be a valid GdkAtom object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    target = phpg_gdkatom_from_zval(php_target TSRMLS_CC);
    if (target == NULL) {
        php_error(E_WARNING, "%s::%s() expects target argument to be a valid GdkAtom object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    gdk_selection_convert(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), selection, target, (guint32)time);

}

#line 2835 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkWindow, at_pointer)
{
    gint x, y;
    GdkWindow *window;
    zval *php_window = NULL;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    window = gdk_window_at_pointer(&x, &y);

    if (window != NULL) {
        phpg_gboxed_new(&php_window, GDK_TYPE_WINDOW, &window, TRUE, TRUE TSRMLS_CC);
        php_gtk_build_value(&return_value, "(Nii)", php_window, x, y);
    } else {
        RETURN_FALSE;
    }
}


#line 3958 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkWindow, begin_move_drag)
{
	long button, root_x, root_y, timestamp;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iiii", &button, &root_x, &root_y, &timestamp))
		return;

    gdk_window_begin_move_drag(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gint)button, (gint)root_x, (gint)root_y, (guint32)timestamp);

}


static PHP_METHOD(GdkWindow, begin_paint_rect)
{
	GdkRectangle rectangle = { 0, 0, 0, 0 };
	zval *php_rectangle;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_rectangle))
		return;

    if (phpg_rectangle_from_zval(php_rectangle, (GdkRectangle*)&rectangle TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects rectangle argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    gdk_window_begin_paint_rect(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), &rectangle);

}


static PHP_METHOD(GdkWindow, begin_resize_drag)
{
	GdkWindowEdge edge;
	zval *php_edge = NULL;
	long button, root_x, root_y, timestamp;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Viiii", &php_edge, &button, &root_x, &root_y, &timestamp))
		return;

	if (php_edge && phpg_gvalue_get_enum(GDK_TYPE_WINDOW_EDGE, php_edge, (gint *)&edge) == FAILURE) {
		return;
	}

    gdk_window_begin_resize_drag(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), edge, (gint)button, (gint)root_x, (gint)root_y, (guint32)timestamp);

}


static PHP_METHOD(GdkWindow, clear)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_clear(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, clear_area)
{
	long x, y, width, height;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iiii", &x, &y, &width, &height))
		return;

    gdk_window_clear_area(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gint)x, (gint)y, (gint)width, (gint)height);

}


static PHP_METHOD(GdkWindow, clear_area_e)
{
	long x, y, width, height;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iiii", &x, &y, &width, &height))
		return;

    gdk_window_clear_area_e(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gint)x, (gint)y, (gint)width, (gint)height);

}


static PHP_METHOD(GdkWindow, configure_finished)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_configure_finished(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, deiconify)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_deiconify(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, destroy)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_destroy(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, enable_synchronized_configure)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_enable_synchronized_configure(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, end_paint)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_end_paint(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, focus)
{
	long timestamp = GDK_CURRENT_TIME;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "|i", &timestamp))
		return;

    gdk_window_focus(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (guint32)timestamp);

}


static PHP_METHOD(GdkWindow, foreign_new)
{
	long anid;
	GdkWindow* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &anid))
		return;

    php_retval = gdk_window_foreign_new((GdkNativeWindow)anid);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
    if (php_retval != NULL) {
        g_object_unref(php_retval);
    }
}


static PHP_METHOD(GdkWindow, foreign_new_for_display)
{
	zval *display;
	long anid;
	GdkWindow* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Oi", &display, gdkdisplay_ce, &anid))
		return;

    php_retval = gdk_window_foreign_new_for_display(GDK_DISPLAY(PHPG_GOBJECT(display)), (GdkNativeWindow)anid);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
    if (php_retval != NULL) {
        g_object_unref(php_retval);
    }
}


static PHP_METHOD(GdkWindow, freeze_updates)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_freeze_updates(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, fullscreen)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_fullscreen(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}

#line 2857 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkWindow, get_children)
{
    GList *list, *item;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    list = gdk_window_get_children(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

    array_init(return_value);
    for (item = list; item; item = item->next) {
        zval *php_item = NULL;
        phpg_gobject_new(&php_item, G_OBJECT(item->data) TSRMLS_CC);
        add_next_index_zval(return_value, php_item);
    }

    g_list_free(list);
}


#line 4216 "ext/gtk+/gen_gdk.c"


#line 2881 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkWindow, get_deskrelative_origin)
{
    gint x, y;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    gdk_window_get_deskrelative_origin(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), &x, &y);
    phpg_warn_deprecated(NULL TSRMLS_CC);
    php_gtk_build_value(&return_value, "(ii)", x, y);
}

#line 4234 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkWindow, get_events)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_window_get_events(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}

#line 2897 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkWindow, get_frame_extents)
{
    GdkRectangle rect;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    gdk_window_get_frame_extents(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), &rect);
    phpg_gboxed_new(&return_value, GDK_TYPE_RECTANGLE, &rect, TRUE, TRUE TSRMLS_CC);
}


#line 4266 "ext/gtk+/gen_gdk.c"


#line 2913 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkWindow, get_geometry)
{
    gint x, y, width, height, depth;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    gdk_window_get_geometry(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), &x, &y, &width, &height, &depth);
    php_gtk_build_value(&return_value, "(iiiii)", x, y, width, height, depth);
}


#line 4284 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkWindow, get_group)
{
	GdkWindow* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_window_get_group(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}

#line 2929 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkWindow, get_origin)
{
    gint x, y;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    gdk_window_get_origin(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), &x, &y);
    php_gtk_build_value(&return_value, "(ii)", x, y);
}


#line 4316 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkWindow, get_parent)
{
	GdkWindow* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_window_get_parent(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}

#line 2945 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkWindow, get_pointer)
{
    int x, y = 0;
    GdkModifierType mask = 0;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    gdk_window_get_pointer(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), &x, &y, &mask);
    php_gtk_build_value(&return_value, "(iii)", x, y, mask);
}


#line 4349 "ext/gtk+/gen_gdk.c"


#line 2962 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkWindow, get_position)
{
    gint x, y;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    gdk_window_get_position(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), &x, &y);
    php_gtk_build_value(&return_value, "(ii)", x, y);
}


#line 4367 "ext/gtk+/gen_gdk.c"


#line 2978 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkWindow, get_root_origin)
{
    gint x, y;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    gdk_window_get_root_origin(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), &x, &y);
    php_gtk_build_value(&return_value, "(ii)", x, y);
}


#line 4385 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkWindow, get_state)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_window_get_state(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkWindow, get_toplevel)
{
	GdkWindow* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_window_get_toplevel(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}

#line 2994 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkWindow, get_toplevels)
{
    GList *list, *item;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    list = gdk_window_get_toplevels();

    array_init(return_value);
    for (item = list; item; item = item->next) {
        zval *php_item = NULL;
        phpg_gobject_new(&php_item, G_OBJECT(item->data) TSRMLS_CC);
        add_next_index_zval(return_value, php_item);
    }

    g_list_free(list);
}

#line 4436 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkWindow, get_window_type)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_window_get_window_type(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkWindow, hide)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_hide(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, iconify)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_iconify(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, invalidate_rect)
{
	GdkRectangle rect_arg = { 0, 0, 0, 0 }, *rect;
	zval *php_rect = NULL;
	zend_bool invalidate_children;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Vb", &php_rect, &invalidate_children))
		return;

    if (Z_TYPE_P(php_rect) == IS_NULL) {
        rect = NULL;
    } else if (phpg_rectangle_from_zval(php_rect, (GdkRectangle*)&rect_arg TSRMLS_CC) == SUCCESS) {
        rect = &rect_arg;
    } else {
        php_error(E_WARNING, "%s::%s() expects rect argument to be a 4-element array, a GdkRectangle object, or null", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    gdk_window_invalidate_rect(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), rect, (gboolean)invalidate_children);

}


static PHP_METHOD(GdkWindow, is_viewable)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_window_is_viewable(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(GdkWindow, is_visible)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_window_is_visible(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(GdkWindow, lookup)
{
	long anid;
	GdkWindow* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &anid))
		return;

    php_retval = gdk_window_lookup((GdkNativeWindow)anid);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkWindow, lookup_for_display)
{
	zval *display;
	long anid;
	GdkWindow* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Oi", &display, gdkdisplay_ce, &anid))
		return;

    php_retval = gdk_window_lookup_for_display(GDK_DISPLAY(PHPG_GOBJECT(display)), (GdkNativeWindow)anid);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkWindow, lower)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_lower(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, maximize)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_maximize(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, merge_child_shapes)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_merge_child_shapes(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, move)
{
	long x, y;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "ii", &x, &y))
		return;

    gdk_window_move(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gint)x, (gint)y);

}


static PHP_METHOD(GdkWindow, move_resize)
{
	long x, y, width, height;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iiii", &x, &y, &width, &height))
		return;

    gdk_window_move_resize(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gint)x, (gint)y, (gint)width, (gint)height);

}


static PHP_METHOD(GdkWindow, process_all_updates)
{

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_process_all_updates();

}


static PHP_METHOD(GdkWindow, process_updates)
{
	zend_bool update_children;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &update_children))
		return;

    gdk_window_process_updates(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gboolean)update_children);

}


static PHP_METHOD(GdkWindow, raise)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_raise(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, register_dnd)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_register_dnd(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, reparent)
{
	zval *new_parent;
	long x, y;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Oii", &new_parent, gdkwindow_ce, &x, &y))
		return;

    gdk_window_reparent(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), GDK_WINDOW(PHPG_GOBJECT(new_parent)), (gint)x, (gint)y);

}


static PHP_METHOD(GdkWindow, resize)
{
	long width, height;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "ii", &width, &height))
		return;

    gdk_window_resize(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gint)width, (gint)height);

}


static PHP_METHOD(GdkWindow, scroll)
{
	long dx, dy;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "ii", &dx, &dy))
		return;

    gdk_window_scroll(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gint)dx, (gint)dy);

}


static PHP_METHOD(GdkWindow, set_accept_focus)
{
	zend_bool accept_focus;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &accept_focus))
		return;

    gdk_window_set_accept_focus(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gboolean)accept_focus);

}


static PHP_METHOD(GdkWindow, set_back_pixmap)
{
	GdkPixmap *pixmap = NULL;
	zval *php_pixmap;
	zend_bool parent_relative;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Nb", &php_pixmap, gdkpixmap_ce, &parent_relative))
		return;
    if (Z_TYPE_P(php_pixmap) != IS_NULL)
        pixmap = GDK_PIXMAP(PHPG_GOBJECT(php_pixmap));

    gdk_window_set_back_pixmap(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), pixmap, (gboolean)parent_relative);

}


static PHP_METHOD(GdkWindow, set_background)
{
	GdkColor *color = NULL;
	zval *php_color;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_color, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_color, GDK_TYPE_COLOR, FALSE TSRMLS_CC)) {
        color = (GdkColor *) PHPG_GBOXED(php_color);
    } else {
        php_error(E_WARNING, "%s::%s() expects color argument to be a valid GdkColor object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    gdk_window_set_background(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), color);

}


static PHP_METHOD(GdkWindow, set_child_shapes)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_set_child_shapes(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, set_cursor)
{
	GdkCursor *cursor = NULL;
	zval *php_cursor;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "N", &php_cursor, gboxed_ce))
		return;

    if (Z_TYPE_P(php_cursor) != IS_NULL) {
        if (phpg_gboxed_check(php_cursor, GDK_TYPE_CURSOR, FALSE TSRMLS_CC)) {
            cursor = (GdkCursor *) PHPG_GBOXED(php_cursor);
        } else {
            php_error(E_WARNING, "%s::%s() expects cursor argument to be a valid GdkCursor object or null", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
            return;
        }
    }

    gdk_window_set_cursor(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), cursor);

}


static PHP_METHOD(GdkWindow, set_debug_updates)
{
	zend_bool setting;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &setting))
		return;

    gdk_window_set_debug_updates((gboolean)setting);

}


static PHP_METHOD(GdkWindow, set_decorations)
{
	GdkWMDecoration decorations;
	zval *php_decorations = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_decorations))
		return;

	if (php_decorations && phpg_gvalue_get_flags(GDK_TYPE_WM_DECORATION, php_decorations, (gint *)&decorations) == FAILURE) {
		return;
	}

    gdk_window_set_decorations(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), decorations);

}


static PHP_METHOD(GdkWindow, set_events)
{
	GdkEventMask event_mask;
	zval *php_event_mask = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_event_mask))
		return;

	if (php_event_mask && phpg_gvalue_get_flags(GDK_TYPE_EVENT_MASK, php_event_mask, (gint *)&event_mask) == FAILURE) {
		return;
	}

    gdk_window_set_events(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), event_mask);

}


static PHP_METHOD(GdkWindow, set_focus_on_map)
{
	zend_bool focus_on_map;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &focus_on_map))
		return;

    gdk_window_set_focus_on_map(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gboolean)focus_on_map);

}


static PHP_METHOD(GdkWindow, set_functions)
{
	GdkWMFunction functions;
	zval *php_functions = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_functions))
		return;

	if (php_functions && phpg_gvalue_get_flags(GDK_TYPE_WM_FUNCTION, php_functions, (gint *)&functions) == FAILURE) {
		return;
	}

    gdk_window_set_functions(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), functions);

}


static PHP_METHOD(GdkWindow, set_group)
{
	zval *leader;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &leader, gdkwindow_ce))
		return;

    gdk_window_set_group(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), GDK_WINDOW(PHPG_GOBJECT(leader)));

}


static PHP_METHOD(GdkWindow, set_hints)
{
	long x, y, min_width, min_height, max_width, max_height, flags;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iiiiiii", &x, &y, &min_width, &min_height, &max_width, &max_height, &flags))
		return;

    gdk_window_set_hints(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gint)x, (gint)y, (gint)min_width, (gint)min_height, (gint)max_width, (gint)max_height, (gint)flags);

}


static PHP_METHOD(GdkWindow, set_icon)
{
	zval *icon_window, *pixmap, *mask;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OOO", &icon_window, gdkwindow_ce, &pixmap, gdkpixmap_ce, &mask, gdkpixmap_ce))
		return;

    gdk_window_set_icon(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), GDK_WINDOW(PHPG_GOBJECT(icon_window)), GDK_PIXMAP(PHPG_GOBJECT(pixmap)), GDK_PIXMAP(PHPG_GOBJECT(mask)));

}

#line 3015 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkWindow, set_icon_list)
{
    zval *php_pixbufs = NULL, **php_pixbuf;
    GList *pixbufs = 0;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "a", &php_pixbufs))
        return;

    zend_hash_internal_pointer_reset(Z_ARRVAL_P(php_pixbufs));
    while (zend_hash_get_current_data(Z_ARRVAL_P(php_pixbufs), (void **)&php_pixbuf) == SUCCESS) {
        if (php_gtk_check_class(*php_pixbuf, gdkpixbuf_ce)) {
            GdkPixbuf *pixbuf = GDK_PIXBUF(PHPG_GOBJECT(*php_pixbuf));
            pixbufs = g_list_prepend(pixbufs, pixbuf);
        } else {
            php_error(E_WARNING, "%s::%s() requires the array elements to be objects of class GdkPixbuf", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        }
    }

    pixbufs = g_list_reverse(pixbufs);
    gdk_window_set_icon_list(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), pixbufs);

    g_list_free(pixbufs);
}

#line 4963 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkWindow, set_icon_name)
{
	char *name;
	zend_bool free_name = FALSE;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &name, &free_name))
		return;

    gdk_window_set_icon_name(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), name);
	if (free_name) g_free(name);

}


static PHP_METHOD(GdkWindow, set_keep_above)
{
	zend_bool setting;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &setting))
		return;

    gdk_window_set_keep_above(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gboolean)setting);

}


static PHP_METHOD(GdkWindow, set_keep_below)
{
	zend_bool setting;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &setting))
		return;

    gdk_window_set_keep_below(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gboolean)setting);

}


static PHP_METHOD(GdkWindow, set_modal_hint)
{
	zend_bool modal;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &modal))
		return;

    gdk_window_set_modal_hint(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gboolean)modal);

}


static PHP_METHOD(GdkWindow, set_override_redirect)
{
	zend_bool override_redirect;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &override_redirect))
		return;

    gdk_window_set_override_redirect(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gboolean)override_redirect);

}


static PHP_METHOD(GdkWindow, set_role)
{
	char *role;
	zend_bool free_role = FALSE;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &role, &free_role))
		return;

    gdk_window_set_role(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), role);
	if (free_role) g_free(role);

}


static PHP_METHOD(GdkWindow, set_skip_pager_hint)
{
	zend_bool modal;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &modal))
		return;

    gdk_window_set_skip_pager_hint(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gboolean)modal);

}


static PHP_METHOD(GdkWindow, set_skip_taskbar_hint)
{
	zend_bool modal;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &modal))
		return;

    gdk_window_set_skip_taskbar_hint(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gboolean)modal);

}


static PHP_METHOD(GdkWindow, set_static_gravities)
{
	zend_bool use_static;
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &use_static))
		return;

    php_retval = gdk_window_set_static_gravities(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), (gboolean)use_static);
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(GdkWindow, set_title)
{
	char *title;
	zend_bool free_title = FALSE;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &title, &free_title))
		return;

    gdk_window_set_title(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), title);
	if (free_title) g_free(title);

}


static PHP_METHOD(GdkWindow, set_transient_for)
{
	zval *leader;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &leader, gdkwindow_ce))
		return;

    gdk_window_set_transient_for(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), GDK_WINDOW(PHPG_GOBJECT(leader)));

}


static PHP_METHOD(GdkWindow, set_type_hint)
{
	GdkWindowTypeHint hint;
	zval *php_hint = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_hint))
		return;

	if (php_hint && phpg_gvalue_get_enum(GDK_TYPE_WINDOW_TYPE_HINT, php_hint, (gint *)&hint) == FAILURE) {
		return;
	}

    gdk_window_set_type_hint(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), hint);

}


static PHP_METHOD(GdkWindow, shape_combine_mask)
{
	GdkPixmap *shape_mask = NULL;
	zval *php_shape_mask;
	long offset_x, offset_y;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Nii", &php_shape_mask, gdkpixmap_ce, &offset_x, &offset_y))
		return;
    if (Z_TYPE_P(php_shape_mask) != IS_NULL)
        shape_mask = GDK_PIXMAP(PHPG_GOBJECT(php_shape_mask));

    gdk_window_shape_combine_mask(GDK_WINDOW(PHPG_GOBJECT(this_ptr)), shape_mask, (gint)offset_x, (gint)offset_y);

}


static PHP_METHOD(GdkWindow, show)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_show(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, stick)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_stick(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, thaw_updates)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_thaw_updates(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, unfullscreen)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_unfullscreen(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, unmaximize)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_unmaximize(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, unstick)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_unstick(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(GdkWindow, withdraw)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_window_withdraw(GDK_WINDOW(PHPG_GOBJECT(this_ptr)));

}


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_input_set_extension_events, 0)
    ZEND_ARG_INFO(0, mask)
    ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_property_change, 0)
    ZEND_ARG_INFO(0, property)
    ZEND_ARG_INFO(0, type)
    ZEND_ARG_INFO(0, format)
    ZEND_ARG_INFO(0, mode)
    ZEND_ARG_INFO(0, data)
    ZEND_ARG_INFO(0, nelements)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_property_delete, 0)
    ZEND_ARG_INFO(0, property)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_selection_convert, 0)
    ZEND_ARG_INFO(0, selection)
    ZEND_ARG_INFO(0, target)
    ZEND_ARG_INFO(0, time)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_begin_move_drag, 0)
    ZEND_ARG_INFO(0, button)
    ZEND_ARG_INFO(0, root_x)
    ZEND_ARG_INFO(0, root_y)
    ZEND_ARG_INFO(0, timestamp)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_begin_paint_rect, 0)
    ZEND_ARG_OBJ_INFO(0, rectangle, GdkRectangle, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_begin_resize_drag, 0)
    ZEND_ARG_INFO(0, edge)
    ZEND_ARG_INFO(0, button)
    ZEND_ARG_INFO(0, root_x)
    ZEND_ARG_INFO(0, root_y)
    ZEND_ARG_INFO(0, timestamp)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_clear_area, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_clear_area_e, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkwindow_focus, 0, 0, 0)
    ZEND_ARG_INFO(0, timestamp)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_foreign_new, 0)
    ZEND_ARG_INFO(0, anid)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_foreign_new_for_display, 0)
    ZEND_ARG_OBJ_INFO(0, display, GdkDisplay, 1)
    ZEND_ARG_INFO(0, anid)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_invalidate_rect, 0)
    ZEND_ARG_OBJ_INFO(0, rect, GdkRectangle, 1)
    ZEND_ARG_INFO(0, invalidate_children)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_lookup, 0)
    ZEND_ARG_INFO(0, anid)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_lookup_for_display, 0)
    ZEND_ARG_OBJ_INFO(0, display, GdkDisplay, 1)
    ZEND_ARG_INFO(0, anid)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_move, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_move_resize, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_process_updates, 0)
    ZEND_ARG_INFO(0, update_children)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_reparent, 0)
    ZEND_ARG_OBJ_INFO(0, new_parent, GdkWindow, 1)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_resize, 0)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_scroll, 0)
    ZEND_ARG_INFO(0, dx)
    ZEND_ARG_INFO(0, dy)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_accept_focus, 0)
    ZEND_ARG_INFO(0, accept_focus)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_back_pixmap, 0)
    ZEND_ARG_OBJ_INFO(0, pixmap, GdkPixmap, 1)
    ZEND_ARG_INFO(0, parent_relative)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_background, 0)
    ZEND_ARG_OBJ_INFO(0, color, GdkColor, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_cursor, 0)
    ZEND_ARG_OBJ_INFO(0, cursor, GdkCursor, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_debug_updates, 0)
    ZEND_ARG_INFO(0, setting)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_decorations, 0)
    ZEND_ARG_INFO(0, decorations)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_events, 0)
    ZEND_ARG_INFO(0, event_mask)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_focus_on_map, 0)
    ZEND_ARG_INFO(0, focus_on_map)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_functions, 0)
    ZEND_ARG_INFO(0, functions)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_group, 0)
    ZEND_ARG_OBJ_INFO(0, leader, GdkWindow, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_hints, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, min_width)
    ZEND_ARG_INFO(0, min_height)
    ZEND_ARG_INFO(0, max_width)
    ZEND_ARG_INFO(0, max_height)
    ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_icon, 0)
    ZEND_ARG_OBJ_INFO(0, icon_window, GdkWindow, 1)
    ZEND_ARG_OBJ_INFO(0, pixmap, GdkPixmap, 1)
    ZEND_ARG_INFO(0, mask)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_icon_name, 0)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_keep_above, 0)
    ZEND_ARG_INFO(0, setting)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_keep_below, 0)
    ZEND_ARG_INFO(0, setting)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_modal_hint, 0)
    ZEND_ARG_INFO(0, modal)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_override_redirect, 0)
    ZEND_ARG_INFO(0, override_redirect)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_role, 0)
    ZEND_ARG_INFO(0, role)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_skip_pager_hint, 0)
    ZEND_ARG_INFO(0, modal)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_skip_taskbar_hint, 0)
    ZEND_ARG_INFO(0, modal)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_static_gravities, 0)
    ZEND_ARG_INFO(0, use_static)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_title, 0)
    ZEND_ARG_INFO(0, title)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_transient_for, 0)
    ZEND_ARG_OBJ_INFO(0, leader, GdkWindow, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_set_type_hint, 0)
    ZEND_ARG_INFO(0, hint)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkwindow_shape_combine_mask, 0)
    ZEND_ARG_INFO(0, shape_mask)
    ZEND_ARG_INFO(0, offset_x)
    ZEND_ARG_INFO(0, offset_y)
ZEND_END_ARG_INFO();

static function_entry gdkwindow_methods[] = {
#if ZEND_EXTENSION_API_NO > 220051025
	PHP_ME_MAPPING(__construct, no_direct_constructor, NULL, 0)
#else
	PHP_ME_MAPPING(__construct, no_direct_constructor, NULL)
#endif
	PHP_ME(GdkWindow, at_pointer,           NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkWindow, begin_move_drag,      arginfo_gdk_gdkwindow_begin_move_drag, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, begin_paint_rect,     arginfo_gdk_gdkwindow_begin_paint_rect, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, begin_resize_drag,    arginfo_gdk_gdkwindow_begin_resize_drag, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, clear,                NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, clear_area,           arginfo_gdk_gdkwindow_clear_area, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, clear_area_e,         arginfo_gdk_gdkwindow_clear_area_e, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, configure_finished,   NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, deiconify,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, destroy,              NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, enable_synchronized_configure, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, end_paint,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, focus,                arginfo_gdk_gdkwindow_focus, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, foreign_new,          arginfo_gdk_gdkwindow_foreign_new, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkWindow, foreign_new_for_display, arginfo_gdk_gdkwindow_foreign_new_for_display, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkWindow, freeze_updates,       NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, fullscreen,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, get_children,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, get_deskrelative_origin, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, get_events,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, get_frame_extents,    NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, get_geometry,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, get_group,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, get_origin,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, get_parent,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, get_pointer,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, get_position,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, get_root_origin,      NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, get_state,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, get_toplevel,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, get_toplevels,        NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkWindow, get_window_type,      NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, hide,                 NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, iconify,              NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, input_set_extension_events, arginfo_gdk_gdkwindow_input_set_extension_events, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, invalidate_rect,      arginfo_gdk_gdkwindow_invalidate_rect, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, is_viewable,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, is_visible,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, lookup,               arginfo_gdk_gdkwindow_lookup, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkWindow, lookup_for_display,   arginfo_gdk_gdkwindow_lookup_for_display, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkWindow, lower,                NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, maximize,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, merge_child_shapes,   NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, move,                 arginfo_gdk_gdkwindow_move, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, move_resize,          arginfo_gdk_gdkwindow_move_resize, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, process_all_updates,  NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkWindow, process_updates,      arginfo_gdk_gdkwindow_process_updates, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, property_change,      arginfo_gdk_gdkwindow_property_change, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, property_delete,      arginfo_gdk_gdkwindow_property_delete, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, raise,                NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, register_dnd,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, reparent,             arginfo_gdk_gdkwindow_reparent, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, resize,               arginfo_gdk_gdkwindow_resize, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, scroll,               arginfo_gdk_gdkwindow_scroll, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, selection_convert,    arginfo_gdk_gdkwindow_selection_convert, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_accept_focus,     arginfo_gdk_gdkwindow_set_accept_focus, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_back_pixmap,      arginfo_gdk_gdkwindow_set_back_pixmap, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_background,       arginfo_gdk_gdkwindow_set_background, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_child_shapes,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_cursor,           arginfo_gdk_gdkwindow_set_cursor, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_debug_updates,    arginfo_gdk_gdkwindow_set_debug_updates, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkWindow, set_decorations,      arginfo_gdk_gdkwindow_set_decorations, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_events,           arginfo_gdk_gdkwindow_set_events, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_focus_on_map,     arginfo_gdk_gdkwindow_set_focus_on_map, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_functions,        arginfo_gdk_gdkwindow_set_functions, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_group,            arginfo_gdk_gdkwindow_set_group, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_hints,            arginfo_gdk_gdkwindow_set_hints, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_icon,             arginfo_gdk_gdkwindow_set_icon, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_icon_list,        NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_icon_name,        arginfo_gdk_gdkwindow_set_icon_name, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_keep_above,       arginfo_gdk_gdkwindow_set_keep_above, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_keep_below,       arginfo_gdk_gdkwindow_set_keep_below, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_modal_hint,       arginfo_gdk_gdkwindow_set_modal_hint, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_override_redirect, arginfo_gdk_gdkwindow_set_override_redirect, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_role,             arginfo_gdk_gdkwindow_set_role, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_skip_pager_hint,  arginfo_gdk_gdkwindow_set_skip_pager_hint, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_skip_taskbar_hint, arginfo_gdk_gdkwindow_set_skip_taskbar_hint, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_static_gravities, arginfo_gdk_gdkwindow_set_static_gravities, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_title,            arginfo_gdk_gdkwindow_set_title, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_transient_for,    arginfo_gdk_gdkwindow_set_transient_for, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, set_type_hint,        arginfo_gdk_gdkwindow_set_type_hint, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, shape_combine_mask,   arginfo_gdk_gdkwindow_shape_combine_mask, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, show,                 NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, stick,                NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, thaw_updates,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, unfullscreen,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, unmaximize,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, unstick,              NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkWindow, withdraw,             NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(GdkPixmap, __construct)
{
	GdkDrawable *drawable = NULL;
	zval *php_drawable;
	long width, height, depth = -1;
	GObject *wrapped_obj;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Nii|i", &php_drawable, gdkdrawable_ce, &width, &height, &depth)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixmap);
	}
    if (Z_TYPE_P(php_drawable) != IS_NULL)
        drawable = GDK_DRAWABLE(PHPG_GOBJECT(php_drawable));

	wrapped_obj = (GObject *) gdk_pixmap_new(drawable, (gint)width, (gint)height, (gint)depth);

	if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixmap);
	}

    phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}

#line 2585 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkPixmap, create_from_xpm)
{
	zval *php_drawable, *php_trans_color, *php_colormap = NULL;
	zval *ret_pixmap = NULL, *ret_mask = NULL;
	gchar *filename;
	zend_bool free_filename = FALSE;
	GdkDrawable *drawable = NULL;
	GdkColor *trans_color = NULL;
	GdkColormap *colormap = NULL;
	GdkPixmap *pixmap = NULL;
	GdkBitmap *mask;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OOu|O", &php_drawable, gdkdrawable_ce,
													&php_trans_color, gdkcolor_ce,
													&filename, &free_filename,
													&php_colormap, gdkcolormap_ce)) {
		PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixmap);
	}

	drawable = GDK_DRAWABLE(PHPG_GOBJECT(php_drawable));
	trans_color = (GdkColor *) PHPG_GBOXED(php_trans_color);

	if (php_colormap) {
		colormap = GDK_COLORMAP(PHPG_GOBJECT(php_colormap));
		pixmap = gdk_pixmap_colormap_create_from_xpm(drawable, colormap, &mask, trans_color, filename);
	} else {
		pixmap = gdk_pixmap_create_from_xpm(drawable, &mask, trans_color, filename);
	}

	if (free_filename) g_free(filename);

	if (!pixmap) {
		php_error(E_WARNING, "%s() cannot load pixmap", get_active_function_name(TSRMLS_C));
		PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixmap);
	}

	phpg_gobject_new(&ret_pixmap, (GObject*)pixmap TSRMLS_CC);
	gdk_pixmap_unref(pixmap);

	phpg_gobject_new(&ret_mask, (GObject *)mask TSRMLS_CC);
	gdk_bitmap_unref(mask);

	php_gtk_build_value(&return_value, "(NN)", ret_pixmap, ret_mask);
}

#line 5695 "ext/gtk+/gen_gdk.c"


#line 2632 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkPixmap, create_from_xpm_data)
{
	zval *php_drawable, *php_trans_color, *php_data, *php_colormap = NULL;
	zval *ret_pixmap = NULL, *ret_mask = NULL;
	zval **line;
	GdkDrawable *drawable = NULL;
	GdkColor *trans_color = NULL;
	GdkColormap *colormap = NULL;
	GdkPixmap *pixmap = NULL;
	GdkBitmap *mask;
	char **data;
	int len, i = 0;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OOa|O", &php_drawable, gdkdrawable_ce,
													&php_trans_color, gdkcolor_ce,
													&php_data,
													&php_colormap, gdkcolormap_ce)) {
		PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixmap);
	}

	drawable = GDK_DRAWABLE(PHPG_GOBJECT(php_drawable));
	trans_color = (GdkColor *) PHPG_GBOXED(php_trans_color);

	len = zend_hash_num_elements(Z_ARRVAL_P(php_data));
	data = safe_emalloc(len, sizeof(char *), 0);

	for (zend_hash_internal_pointer_reset(Z_ARRVAL_P(php_data));
		 zend_hash_get_current_data(Z_ARRVAL_P(php_data), (void **)&line) == SUCCESS;
		 zend_hash_move_forward(Z_ARRVAL_P(php_data))) {
		convert_to_string_ex(line);
		data[i++] = Z_STRVAL_PP(line);
	}

	if (php_colormap) {
		colormap = GDK_COLORMAP(PHPG_GOBJECT(php_colormap));
		pixmap = gdk_pixmap_colormap_create_from_xpm_d(drawable, colormap, &mask, trans_color, data);
	} else {
		pixmap = gdk_pixmap_create_from_xpm_d(drawable, &mask, trans_color, data);
	}

	efree(data);

	if (!pixmap) {
		php_error(E_WARNING, "%s() cannot load pixmap", get_active_function_name(TSRMLS_C));
		PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixmap);
	}

	phpg_gobject_new(&ret_pixmap, (GObject*)pixmap TSRMLS_CC);
	gdk_pixmap_unref(pixmap);

	phpg_gobject_new(&ret_mask, (GObject *)mask TSRMLS_CC);
	gdk_bitmap_unref(mask);

	php_gtk_build_value(&return_value, "(NN)", ret_pixmap, ret_mask);
}

#line 5755 "ext/gtk+/gen_gdk.c"



static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkpixmap_gdk_pixmap_new, 0, 0, 3)
    ZEND_ARG_OBJ_INFO(0, drawable, GdkDrawable, 1)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, depth)
ZEND_END_ARG_INFO();

static function_entry gdkpixmap_methods[] = {
	PHP_ME(GdkPixmap, __construct,          arginfo_gdk_gdkpixmap_gdk_pixmap_new, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixmap, create_from_xpm,      NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkPixmap, create_from_xpm_data, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(GdkGC, __construct)
{
	zval *drawable;
	GObject *wrapped_obj;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &drawable, gdkdrawable_ce)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkGC);
	}

	wrapped_obj = (GObject *) gdk_gc_new(GDK_DRAWABLE(PHPG_GOBJECT(drawable)));

	if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkGC);
	}

    phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}

#line 1376 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, foreground)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    phpg_gboxed_new(&return_value, GDK_TYPE_COLOR, &(gc.foreground), TRUE, TRUE TSRMLS_CC);
    return SUCCESS;
}

#line 5801 "ext/gtk+/gen_gdk.c"


#line 1386 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, background)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    phpg_gboxed_new(&return_value, GDK_TYPE_COLOR, &(gc.background), TRUE, TRUE TSRMLS_CC);
    return SUCCESS;
}

#line 5813 "ext/gtk+/gen_gdk.c"


#line 1396 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, font)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    phpg_gboxed_new(&return_value, GDK_TYPE_FONT, gc.font, TRUE, TRUE TSRMLS_CC);
    return SUCCESS;
}

#line 5825 "ext/gtk+/gen_gdk.c"


#line 1406 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, function)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    RETVAL_LONG(gc.function);
    return SUCCESS;
}

#line 5837 "ext/gtk+/gen_gdk.c"


#line 1416 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, fill)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    RETVAL_LONG(gc.fill);
    return SUCCESS;
}

#line 5849 "ext/gtk+/gen_gdk.c"


#line 1426 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, tile)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    phpg_gobject_new(&return_value, (GObject *)gc.tile TSRMLS_CC);
    return SUCCESS;
}

#line 5861 "ext/gtk+/gen_gdk.c"


#line 1436 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, stipple)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    phpg_gobject_new(&return_value, (GObject *)gc.stipple TSRMLS_CC);
    return SUCCESS;
}

#line 5873 "ext/gtk+/gen_gdk.c"


#line 1446 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, clip_mask)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    phpg_gobject_new(&return_value, (GObject *)gc.clip_mask TSRMLS_CC);
    return SUCCESS;
}

#line 5885 "ext/gtk+/gen_gdk.c"


#line 1456 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, subwindow_mode)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    RETVAL_LONG(gc.subwindow_mode);
    return SUCCESS;
}

#line 5897 "ext/gtk+/gen_gdk.c"


#line 1466 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, ts_x_origin)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    RETVAL_LONG(gc.ts_x_origin);
    return SUCCESS;
}

#line 5909 "ext/gtk+/gen_gdk.c"


#line 1476 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, ts_y_origin)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    RETVAL_LONG(gc.ts_y_origin);
    return SUCCESS;
}

#line 5921 "ext/gtk+/gen_gdk.c"


#line 1486 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, clip_x_origin)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    RETVAL_LONG(gc.clip_x_origin);
    return SUCCESS;
}

#line 5933 "ext/gtk+/gen_gdk.c"


#line 1496 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, clip_y_origin)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    RETVAL_LONG(gc.clip_y_origin);
    return SUCCESS;
}

#line 5945 "ext/gtk+/gen_gdk.c"


#line 1506 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, graphics_exposures)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    RETVAL_LONG(gc.graphics_exposures);
    return SUCCESS;
}

#line 5957 "ext/gtk+/gen_gdk.c"


#line 1516 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, line_width)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    RETVAL_LONG(gc.line_width);
    return SUCCESS;
}

#line 5969 "ext/gtk+/gen_gdk.c"


#line 1526 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, line_style)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    RETVAL_LONG(gc.line_style);
    return SUCCESS;
}

#line 5981 "ext/gtk+/gen_gdk.c"


#line 1536 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, cap_style)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    RETVAL_LONG(gc.cap_style);
    return SUCCESS;
}

#line 5993 "ext/gtk+/gen_gdk.c"


#line 1546 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkGC, join_style)
{
    GdkGCValues gc;
    gdk_gc_get_values(GDK_GC(((phpg_gobject_t *)object)->obj), &gc);
    RETVAL_LONG(gc.join_style);
    return SUCCESS;
}

#line 6005 "ext/gtk+/gen_gdk.c"



static prop_info_t gdkgc_prop_info[] = {
	{ "foreground", PHPG_PROP_READ_FN(GdkGC, foreground), NULL },
	{ "background", PHPG_PROP_READ_FN(GdkGC, background), NULL },
	{ "font", PHPG_PROP_READ_FN(GdkGC, font), NULL },
	{ "function", PHPG_PROP_READ_FN(GdkGC, function), NULL },
	{ "fill", PHPG_PROP_READ_FN(GdkGC, fill), NULL },
	{ "tile", PHPG_PROP_READ_FN(GdkGC, tile), NULL },
	{ "stipple", PHPG_PROP_READ_FN(GdkGC, stipple), NULL },
	{ "clip_mask", PHPG_PROP_READ_FN(GdkGC, clip_mask), NULL },
	{ "subwindow_mode", PHPG_PROP_READ_FN(GdkGC, subwindow_mode), NULL },
	{ "ts_x_origin", PHPG_PROP_READ_FN(GdkGC, ts_x_origin), NULL },
	{ "ts_y_origin", PHPG_PROP_READ_FN(GdkGC, ts_y_origin), NULL },
	{ "clip_x_origin", PHPG_PROP_READ_FN(GdkGC, clip_x_origin), NULL },
	{ "clip_y_origin", PHPG_PROP_READ_FN(GdkGC, clip_y_origin), NULL },
	{ "graphics_exposures", PHPG_PROP_READ_FN(GdkGC, graphics_exposures), NULL },
	{ "line_width", PHPG_PROP_READ_FN(GdkGC, line_width), NULL },
	{ "line_style", PHPG_PROP_READ_FN(GdkGC, line_style), NULL },
	{ "cap_style", PHPG_PROP_READ_FN(GdkGC, cap_style), NULL },
	{ "join_style", PHPG_PROP_READ_FN(GdkGC, join_style), NULL },
	{ NULL, NULL, NULL },
};


static PHP_METHOD(GdkGC, copy)
{
	zval *src_gc;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &src_gc, gdkgc_ce))
		return;

    gdk_gc_copy(GDK_GC(PHPG_GOBJECT(this_ptr)), GDK_GC(PHPG_GOBJECT(src_gc)));

}


static PHP_METHOD(GdkGC, get_colormap)
{
	GdkColormap* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_gc_get_colormap(GDK_GC(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkGC, get_screen)
{
	GdkScreen* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_gc_get_screen(GDK_GC(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkGC, offset)
{
	long x_offset, y_offset;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "ii", &x_offset, &y_offset))
		return;

    gdk_gc_offset(GDK_GC(PHPG_GOBJECT(this_ptr)), (gint)x_offset, (gint)y_offset);

}


static PHP_METHOD(GdkGC, set_background)
{
	GdkColor *color = NULL;
	zval *php_color;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_color, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_color, GDK_TYPE_COLOR, FALSE TSRMLS_CC)) {
        color = (GdkColor *) PHPG_GBOXED(php_color);
    } else {
        php_error(E_WARNING, "%s::%s() expects color argument to be a valid GdkColor object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    gdk_gc_set_background(GDK_GC(PHPG_GOBJECT(this_ptr)), color);

}


static PHP_METHOD(GdkGC, set_clip_mask)
{
	zval *mask;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &mask, gdkpixmap_ce))
		return;

    gdk_gc_set_clip_mask(GDK_GC(PHPG_GOBJECT(this_ptr)), GDK_PIXMAP(PHPG_GOBJECT(mask)));

}


static PHP_METHOD(GdkGC, set_clip_origin)
{
	long x, y;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "ii", &x, &y))
		return;

    gdk_gc_set_clip_origin(GDK_GC(PHPG_GOBJECT(this_ptr)), (gint)x, (gint)y);

}


static PHP_METHOD(GdkGC, set_clip_rectangle)
{
	GdkRectangle rectangle = { 0, 0, 0, 0 };
	zval *php_rectangle;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_rectangle))
		return;

    if (phpg_rectangle_from_zval(php_rectangle, (GdkRectangle*)&rectangle TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects rectangle argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    gdk_gc_set_clip_rectangle(GDK_GC(PHPG_GOBJECT(this_ptr)), &rectangle);

}


static PHP_METHOD(GdkGC, set_colormap)
{
	zval *colormap;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &colormap, gdkcolormap_ce))
		return;

    gdk_gc_set_colormap(GDK_GC(PHPG_GOBJECT(this_ptr)), GDK_COLORMAP(PHPG_GOBJECT(colormap)));

}

#line 1556 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkGC, set_dashes)
{
    int dash_offset, n, i;
    zval *dash_array, **item;
    gint8 *dash_list;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "ia", &dash_offset, &dash_array)) {
        return;
    }

    n = zend_hash_num_elements(Z_ARRVAL_P(dash_array));
    dash_list = emalloc(n * sizeof(char));
    for (i = 0, zend_hash_internal_pointer_reset(Z_ARRVAL_P(dash_array));
         zend_hash_get_current_data(Z_ARRVAL_P(dash_array), (void **) &item) == SUCCESS;
         zend_hash_move_forward(Z_ARRVAL_P(dash_array)), i++) {

        if (Z_TYPE_PP(item) != IS_LONG) {
            php_error(E_WARNING, "%s::%s(): dash list elements have to be integers",
                      get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
            efree(dash_list);
            return;
        }
        dash_list[i] = (guchar)clamp_int(Z_LVAL_PP(item), 0, 255);
        if (dash_list[i] == 0) {
            php_error(E_WARNING, "%s::%s(): dash list element cannot be 0",
                      get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
            efree(dash_list);
            return;
        }
    }

    gdk_gc_set_dashes(GDK_GC(PHPG_GOBJECT(this_ptr)), dash_offset, dash_list, n);
    efree(dash_list);
}

#line 6209 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkGC, set_exposures)
{
	zend_bool exposures;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &exposures))
		return;

    gdk_gc_set_exposures(GDK_GC(PHPG_GOBJECT(this_ptr)), (gboolean)exposures);

}


static PHP_METHOD(GdkGC, set_fill)
{
	GdkFill fill;
	zval *php_fill = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_fill))
		return;

	if (php_fill && phpg_gvalue_get_enum(GDK_TYPE_FILL, php_fill, (gint *)&fill) == FAILURE) {
		return;
	}

    gdk_gc_set_fill(GDK_GC(PHPG_GOBJECT(this_ptr)), fill);

}


static PHP_METHOD(GdkGC, set_font)
{
	GdkFont *font = NULL;
	zval *php_font;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_font, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_font, GDK_TYPE_FONT, FALSE TSRMLS_CC)) {
        font = (GdkFont *) PHPG_GBOXED(php_font);
    } else {
        php_error(E_WARNING, "%s::%s() expects font argument to be a valid GdkFont object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    gdk_gc_set_font(GDK_GC(PHPG_GOBJECT(this_ptr)), font);

}


static PHP_METHOD(GdkGC, set_foreground)
{
	GdkColor *color = NULL;
	zval *php_color;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_color, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_color, GDK_TYPE_COLOR, FALSE TSRMLS_CC)) {
        color = (GdkColor *) PHPG_GBOXED(php_color);
    } else {
        php_error(E_WARNING, "%s::%s() expects color argument to be a valid GdkColor object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    gdk_gc_set_foreground(GDK_GC(PHPG_GOBJECT(this_ptr)), color);

}


static PHP_METHOD(GdkGC, set_function)
{
	GdkFunction function;
	zval *php_function = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_function))
		return;

	if (php_function && phpg_gvalue_get_enum(GDK_TYPE_FUNCTION, php_function, (gint *)&function) == FAILURE) {
		return;
	}

    gdk_gc_set_function(GDK_GC(PHPG_GOBJECT(this_ptr)), function);

}


static PHP_METHOD(GdkGC, set_line_attributes)
{
	long line_width;
	GdkLineStyle line_style;
	zval *php_line_style = NULL, *php_cap_style = NULL, *php_join_style = NULL;
	GdkCapStyle cap_style;
	GdkJoinStyle join_style;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iVVV", &line_width, &php_line_style, &php_cap_style, &php_join_style))
		return;

	if (php_line_style && phpg_gvalue_get_enum(GDK_TYPE_LINE_STYLE, php_line_style, (gint *)&line_style) == FAILURE) {
		return;
	}

	if (php_cap_style && phpg_gvalue_get_enum(GDK_TYPE_CAP_STYLE, php_cap_style, (gint *)&cap_style) == FAILURE) {
		return;
	}

	if (php_join_style && phpg_gvalue_get_enum(GDK_TYPE_JOIN_STYLE, php_join_style, (gint *)&join_style) == FAILURE) {
		return;
	}

    gdk_gc_set_line_attributes(GDK_GC(PHPG_GOBJECT(this_ptr)), (gint)line_width, line_style, cap_style, join_style);

}


static PHP_METHOD(GdkGC, set_rgb_bg_color)
{
	GdkColor *color = NULL;
	zval *php_color;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_color, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_color, GDK_TYPE_COLOR, FALSE TSRMLS_CC)) {
        color = (GdkColor *) PHPG_GBOXED(php_color);
    } else {
        php_error(E_WARNING, "%s::%s() expects color argument to be a valid GdkColor object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    gdk_gc_set_rgb_bg_color(GDK_GC(PHPG_GOBJECT(this_ptr)), color);

}


static PHP_METHOD(GdkGC, set_rgb_fg_color)
{
	GdkColor *color = NULL;
	zval *php_color;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_color, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_color, GDK_TYPE_COLOR, FALSE TSRMLS_CC)) {
        color = (GdkColor *) PHPG_GBOXED(php_color);
    } else {
        php_error(E_WARNING, "%s::%s() expects color argument to be a valid GdkColor object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    gdk_gc_set_rgb_fg_color(GDK_GC(PHPG_GOBJECT(this_ptr)), color);

}


static PHP_METHOD(GdkGC, set_stipple)
{
	zval *stipple;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &stipple, gdkpixmap_ce))
		return;

    gdk_gc_set_stipple(GDK_GC(PHPG_GOBJECT(this_ptr)), GDK_PIXMAP(PHPG_GOBJECT(stipple)));

}


static PHP_METHOD(GdkGC, set_subwindow)
{
	GdkSubwindowMode mode;
	zval *php_mode = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_mode))
		return;

	if (php_mode && phpg_gvalue_get_enum(GDK_TYPE_SUBWINDOW_MODE, php_mode, (gint *)&mode) == FAILURE) {
		return;
	}

    gdk_gc_set_subwindow(GDK_GC(PHPG_GOBJECT(this_ptr)), mode);

}


static PHP_METHOD(GdkGC, set_tile)
{
	zval *tile;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &tile, gdkpixmap_ce))
		return;

    gdk_gc_set_tile(GDK_GC(PHPG_GOBJECT(this_ptr)), GDK_PIXMAP(PHPG_GOBJECT(tile)));

}


static PHP_METHOD(GdkGC, set_ts_origin)
{
	long x, y;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "ii", &x, &y))
		return;

    gdk_gc_set_ts_origin(GDK_GC(PHPG_GOBJECT(this_ptr)), (gint)x, (gint)y);

}

#line 1595 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkGC, set_values)
{
    zval *php_values, **value;
	char *key;
	uint key_len;
	ulong num_key;
	HashTable *hash;
	GdkGCValues values;
	GdkGCValuesMask mask = 0;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "a", &php_values)) {
		return;
    }

    hash = HASH_OF(php_values);
    zend_hash_internal_pointer_reset(hash);
    while (zend_hash_get_current_data(hash, (void**)&value) == SUCCESS) {
        if (zend_hash_get_current_key_ex(hash, &key, &key_len, &num_key, 0, NULL) == HASH_KEY_IS_STRING) {
            if (!strcmp(key, "foreground")) {
                GdkColor *c;

                if (!phpg_object_isa(*value, gdkcolor_ce TSRMLS_CC)) {
                    php_error(E_WARNING, "foreground value has to be a GdkColor");
                    return;
                }
                c = (GdkColor *) PHPG_GBOXED(*value);
                mask |= GDK_GC_FOREGROUND;
                values.foreground.red 	= c->red;
                values.foreground.green = c->green;
                values.foreground.blue 	= c->blue;
                values.foreground.pixel = c->pixel;
            } else if (!strcmp(key, "background")) {
                GdkColor *c;

                if (!phpg_object_isa(*value, gdkcolor_ce TSRMLS_CC)) {
                    php_error(E_WARNING, "background value has to be a GdkColor");
                    return;
                }
                c = (GdkColor *) PHPG_GBOXED(*value);
                mask |= GDK_GC_BACKGROUND;
                values.background.red 	= c->red;
                values.background.green = c->green;
                values.background.blue 	= c->blue;
                values.background.pixel = c->pixel;
            } else if (!strcmp(key, "font")) {
                if (!phpg_object_isa(*value, gdkfont_ce TSRMLS_CC)) {
                    php_error(E_WARNING, "font value has to be a GdkFont");
                    return;
                }
                mask |= GDK_GC_FONT;
                values.font = (GdkFont *) PHPG_GBOXED(*value);
            } else if (!strcmp(key, "function")) {
                if (Z_TYPE_PP(value) != IS_LONG) {
                    php_error(E_WARNING, "function value has to be an integer");
                    return;
                }
                mask |= GDK_GC_FUNCTION;
                values.function = Z_LVAL_PP(value);
            } else if (!strcmp(key, "fill")) {
                if (Z_TYPE_PP(value) != IS_LONG) {
                    php_error(E_WARNING, "fill value has to be an integer");
                    return;
                }
                mask |= GDK_GC_FILL;
                values.fill = Z_LVAL_PP(value);
            } else if (!strcmp(key, "tile")) {
                if (!phpg_object_isa(*value, gdkpixmap_ce TSRMLS_CC)) {
                    php_error(E_WARNING, "tile value has to be a GdkPixmap");
                    return;
                }
                mask |= GDK_GC_TILE;
                values.tile = GDK_PIXMAP(PHPG_GOBJECT(*value));
            } else if (!strcmp(key, "stipple")) {
                if (!phpg_object_isa(*value, gdkpixmap_ce TSRMLS_CC)) {
                    php_error(E_WARNING, "stipple value has to be a GdkPixmap");
                    return;
                }
                mask |= GDK_GC_STIPPLE;
                values.stipple = GDK_PIXMAP(PHPG_GOBJECT(*value));
            } else if (!strcmp(key, "clip_mask")) {
                if (!phpg_object_isa(*value, gdkpixmap_ce TSRMLS_CC)) {
                    php_error(E_WARNING, "clip_mask value has to be a GdkPixmap");
                    return;
                }
                mask |= GDK_GC_CLIP_MASK;
                values.clip_mask = GDK_PIXMAP(PHPG_GOBJECT(*value));
            } else if (!strcmp(key, "subwindow_mode")) {
                if (Z_TYPE_PP(value) != IS_LONG) {
                    php_error(E_WARNING, "subwindow_mode value has to be an integer");
                    return;
                }
                mask |= GDK_GC_SUBWINDOW;
                values.subwindow_mode = Z_LVAL_PP(value);
            } else if (!strcmp(key, "ts_x_origin")) {
                if (Z_TYPE_PP(value) != IS_LONG) {
                    php_error(E_WARNING, "ts_x_origin value has to be an integer");
                    return;
                }
                mask |= GDK_GC_TS_X_ORIGIN;
                values.ts_x_origin = Z_LVAL_PP(value);
            } else if (!strcmp(key, "ts_y_origin")) {
                if (Z_TYPE_PP(value) != IS_LONG) {
                    php_error(E_WARNING, "ts_y_origin value has to be an integer");
                    return;
                }
                mask |= GDK_GC_TS_Y_ORIGIN;
                values.ts_y_origin = Z_LVAL_PP(value);
            } else if (!strcmp(key, "clip_x_origin")) {
                if (Z_TYPE_PP(value) != IS_LONG) {
                    php_error(E_WARNING, "clip_x_origin value has to be an integer");
                    return;
                }
                mask |= GDK_GC_CLIP_X_ORIGIN;
                values.clip_x_origin = Z_LVAL_PP(value);
            } else if (!strcmp(key, "clip_y_origin")) {
                if (Z_TYPE_PP(value) != IS_LONG) {
                    php_error(E_WARNING, "clip_y_origin value has to be an integer");
                    return;
                }
                mask |= GDK_GC_CLIP_Y_ORIGIN;
                values.clip_y_origin = Z_LVAL_PP(value);
            } else if (!strcmp(key, "graphics_exposures")) {
                if (Z_TYPE_PP(value) != IS_LONG) {
                    php_error(E_WARNING, "graphics_exposures value has to be an integer");
                    return;
                }
                mask |= GDK_GC_EXPOSURES;
                values.graphics_exposures = Z_LVAL_PP(value);
            } else if (!strcmp(key, "line_width")) {
                if (Z_TYPE_PP(value) != IS_LONG) {
                    php_error(E_WARNING, "line_width value has to be an integer");
                    return;
                }
                mask |= GDK_GC_LINE_WIDTH;
                values.line_width = Z_LVAL_PP(value);
            } else if (!strcmp(key, "line_style")) {
                if (Z_TYPE_PP(value) != IS_LONG) {
                    php_error(E_WARNING, "line_style value has to be an integer");
                    return;
                }
                mask |= GDK_GC_LINE_STYLE;
                values.line_style = Z_LVAL_PP(value);
            } else if (!strcmp(key, "cap_style")) {
                if (Z_TYPE_PP(value) != IS_LONG) {
                    php_error(E_WARNING, "cap_style value has to be an integer");
                    return;
                }
                mask |= GDK_GC_CAP_STYLE;
                values.cap_style = Z_LVAL_PP(value);
            } else if (!strcmp(key, "join_style")) {
                if (Z_TYPE_PP(value) != IS_LONG) {
                    php_error(E_WARNING, "join_style value has to be an integer");
                    return;
                }
                mask |= GDK_GC_JOIN_STYLE;
                values.join_style = Z_LVAL_PP(value);
            }
        }
        zend_hash_move_forward(hash);
    }

    gdk_gc_set_values(GDK_GC(PHPG_GOBJECT(this_ptr)), &values, mask);
    RETURN_TRUE;
}

#line 6615 "ext/gtk+/gen_gdk.c"



static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_gc_new, 0)
    ZEND_ARG_OBJ_INFO(0, drawable, GdkDrawable, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_copy, 0)
    ZEND_ARG_OBJ_INFO(0, src_gc, GdkGC, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_offset, 0)
    ZEND_ARG_INFO(0, x_offset)
    ZEND_ARG_INFO(0, y_offset)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_set_background, 0)
    ZEND_ARG_OBJ_INFO(0, color, GdkColor, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_set_clip_mask, 0)
    ZEND_ARG_INFO(0, mask)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_set_clip_origin, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_set_clip_rectangle, 0)
    ZEND_ARG_OBJ_INFO(0, rectangle, GdkRectangle, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_set_colormap, 0)
    ZEND_ARG_OBJ_INFO(0, colormap, GdkColormap, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_set_exposures, 0)
    ZEND_ARG_INFO(0, exposures)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_set_fill, 0)
    ZEND_ARG_INFO(0, fill)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_set_font, 0)
    ZEND_ARG_OBJ_INFO(0, font, GdkFont, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_set_foreground, 0)
    ZEND_ARG_OBJ_INFO(0, color, GdkColor, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_set_function, 0)
    ZEND_ARG_INFO(0, function)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_set_line_attributes, 0)
    ZEND_ARG_INFO(0, line_width)
    ZEND_ARG_INFO(0, line_style)
    ZEND_ARG_INFO(0, cap_style)
    ZEND_ARG_INFO(0, join_style)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_set_rgb_bg_color, 0)
    ZEND_ARG_OBJ_INFO(0, color, GdkColor, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_set_rgb_fg_color, 0)
    ZEND_ARG_OBJ_INFO(0, color, GdkColor, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_set_stipple, 0)
    ZEND_ARG_OBJ_INFO(0, stipple, GdkPixmap, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_set_subwindow, 0)
    ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_set_tile, 0)
    ZEND_ARG_OBJ_INFO(0, tile, GdkPixmap, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkgc_set_ts_origin, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO();

static function_entry gdkgc_methods[] = {
	PHP_ME(GdkGC, __construct,          arginfo_gdk_gdkgc_gc_new, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, copy,                 arginfo_gdk_gdkgc_copy, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, get_colormap,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, get_screen,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, offset,               arginfo_gdk_gdkgc_offset, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_background,       arginfo_gdk_gdkgc_set_background, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_clip_mask,        arginfo_gdk_gdkgc_set_clip_mask, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_clip_origin,      arginfo_gdk_gdkgc_set_clip_origin, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_clip_rectangle,   arginfo_gdk_gdkgc_set_clip_rectangle, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_colormap,         arginfo_gdk_gdkgc_set_colormap, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_dashes,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_exposures,        arginfo_gdk_gdkgc_set_exposures, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_fill,             arginfo_gdk_gdkgc_set_fill, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_font,             arginfo_gdk_gdkgc_set_font, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_foreground,       arginfo_gdk_gdkgc_set_foreground, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_function,         arginfo_gdk_gdkgc_set_function, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_line_attributes,  arginfo_gdk_gdkgc_set_line_attributes, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_rgb_bg_color,     arginfo_gdk_gdkgc_set_rgb_bg_color, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_rgb_fg_color,     arginfo_gdk_gdkgc_set_rgb_fg_color, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_stipple,          arginfo_gdk_gdkgc_set_stipple, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_subwindow,        arginfo_gdk_gdkgc_set_subwindow, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_tile,             arginfo_gdk_gdkgc_set_tile, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_ts_origin,        arginfo_gdk_gdkgc_set_ts_origin, ZEND_ACC_PUBLIC)
	PHP_ME(GdkGC, set_values,           NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(GdkImage, __construct)
{
	GdkImageType type;
	zval *php_type = NULL, *visual;
	long width, height;
	GObject *wrapped_obj;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "VOii", &php_type, &visual, gdkvisual_ce, &width, &height)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkImage);
	}

	if (php_type && phpg_gvalue_get_enum(GDK_TYPE_IMAGE_TYPE, php_type, (gint *)&type) == FAILURE) {
		PHPG_THROW_CONSTRUCT_EXCEPTION(GdkImage);
	}

	wrapped_obj = (GObject *) gdk_image_new(type, GDK_VISUAL(PHPG_GOBJECT(visual)), (gint)width, (gint)height);

	if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkImage);
	}

    phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}


static PHP_METHOD(GdkImage, get_colormap)
{
	GdkColormap* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_image_get_colormap(GDK_IMAGE(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkImage, get_pixel)
{
	long x, y, php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "ii", &x, &y))
		return;

    php_retval = gdk_image_get_pixel(GDK_IMAGE(PHPG_GOBJECT(this_ptr)), (gint)x, (gint)y);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkImage, put_pixel)
{
	long x, y, pixel;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iii", &x, &y, &pixel))
		return;

    gdk_image_put_pixel(GDK_IMAGE(PHPG_GOBJECT(this_ptr)), (gint)x, (gint)y, (guint32)pixel);

}


static PHP_METHOD(GdkImage, set_colormap)
{
	zval *colormap;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &colormap, gdkcolormap_ce))
		return;

    gdk_image_set_colormap(GDK_IMAGE(PHPG_GOBJECT(this_ptr)), GDK_COLORMAP(PHPG_GOBJECT(colormap)));

}


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkimage_gdk_image_new, 0)
    ZEND_ARG_INFO(0, type)
    ZEND_ARG_OBJ_INFO(0, visual, GdkVisual, 1)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkimage_get_pixel, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkimage_put_pixel, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, pixel)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkimage_set_colormap, 0)
    ZEND_ARG_OBJ_INFO(0, colormap, GdkColormap, 1)
ZEND_END_ARG_INFO();

static function_entry gdkimage_methods[] = {
	PHP_ME(GdkImage, __construct,          arginfo_gdk_gdkimage_gdk_image_new, ZEND_ACC_PUBLIC)
	PHP_ME(GdkImage, get_colormap,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkImage, get_pixel,            arginfo_gdk_gdkimage_get_pixel, ZEND_ACC_PUBLIC)
	PHP_ME(GdkImage, put_pixel,            arginfo_gdk_gdkimage_put_pixel, ZEND_ACC_PUBLIC)
	PHP_ME(GdkImage, set_colormap,         arginfo_gdk_gdkimage_set_colormap, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(GdkKeymap, get_default)
{
	GdkKeymap* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_keymap_get_default();
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkKeymap, get_direction)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_keymap_get_direction(GDK_KEYMAP(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkKeymap, get_for_display)
{
	zval *display;
	GdkKeymap* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &display, gdkdisplay_ce))
		return;

    php_retval = gdk_keymap_get_for_display(GDK_DISPLAY(PHPG_GOBJECT(display)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkkeymap_get_for_display, 0)
    ZEND_ARG_OBJ_INFO(0, display, GdkDisplay, 1)
ZEND_END_ARG_INFO();

static function_entry gdkkeymap_methods[] = {
	PHP_ME(GdkKeymap, get_default,          NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkKeymap, get_direction,        NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkKeymap, get_for_display,      arginfo_gdk_gdkkeymap_get_for_display, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{ NULL, NULL, NULL }
};
#line 1778 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkPixbuf, __construct)
{
    zend_bool has_alpha;
    long bits_per_sample, width, height;
    GObject *wrapped_obj;
    zval *php_colorspace;
    GdkColorspace colorspace;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "ibiii", &php_colorspace, &has_alpha, &bits_per_sample, &width, &height)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixbuf);
    }

    if (phpg_gvalue_get_enum(GDK_TYPE_COLORSPACE, php_colorspace, (gint *) &colorspace) == FAILURE)
        return;

    wrapped_obj = (GObject *) gdk_pixbuf_new(colorspace, (gboolean)has_alpha, (int)bits_per_sample, (int)width, (int)height);

    if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixbuf);
    }
    phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}

#line 6943 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkPixbuf, new_from_file)
{
	char *filename;
	zend_bool free_filename = FALSE;
	GError *error = NULL;
	GObject *wrapped_obj;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &filename, &free_filename)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixbuf);
	}

	wrapped_obj = (GObject *) gdk_pixbuf_new_from_file(filename, &error);
	if (free_filename) g_free(filename);
    if (phpg_handle_gerror(&error TSRMLS_CC)) {
        return;
    }

	if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixbuf);
	}
    phpg_gobject_new(&return_value, wrapped_obj TSRMLS_CC);
    g_object_unref(wrapped_obj); /* phpg_gobject_new() increments reference count */
}


static PHP_METHOD(GdkPixbuf, new_from_file_at_size)
{
	char *filename;
	zend_bool free_filename = FALSE;
	long width, height;
	GError *error = NULL;
	GObject *wrapped_obj;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "uii", &filename, &free_filename, &width, &height)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixbuf);
	}

	wrapped_obj = (GObject *) gdk_pixbuf_new_from_file_at_size(filename, (int)width, (int)height, &error);
	if (free_filename) g_free(filename);
    if (phpg_handle_gerror(&error TSRMLS_CC)) {
        return;
    }

	if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixbuf);
	}
    phpg_gobject_new(&return_value, wrapped_obj TSRMLS_CC);
    g_object_unref(wrapped_obj); /* phpg_gobject_new() increments reference count */
}

#line 1810 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkPixbuf, new_from_xpm_data)
{
    zval *php_data;
    int size, i;
    gchar **data;
    zval **line;
    GdkPixbuf *pixbuf;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "a/", &php_data)) {
        return;
    }

    size = zend_hash_num_elements(Z_ARRVAL_P(php_data));
    data = safe_emalloc(size, sizeof(gchar *), 0);

	for (i = 0, zend_hash_internal_pointer_reset(Z_ARRVAL_P(php_data));
		 zend_hash_get_current_data(Z_ARRVAL_P(php_data), (void **)&line) == SUCCESS;
		 zend_hash_move_forward(Z_ARRVAL_P(php_data))) {

		convert_to_string_ex(line);
		data[i++] = Z_STRVAL_PP(line);
	}

    pixbuf = gdk_pixbuf_new_from_xpm_data((const char **)data);
    efree(data);

    if (pixbuf == NULL) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixbuf);
    }

    phpg_gobject_new(&return_value, (GObject *)pixbuf TSRMLS_CC);
    g_object_unref(pixbuf); /* phpg_gobject_new() increments reference count */
}

#line 7032 "ext/gtk+/gen_gdk.c"


#line 2097 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkPixbuf, add_alpha)
{
	int red, blue, green;
	guchar r = 255, g = 255, b = 255;
	GdkPixbuf* pixbuf;

	NOT_STATIC_METHOD();

	if (ZEND_NUM_ARGS() > 0) {
		if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iii", &red, &green, &blue))
			return;
		r = (guchar)red;
		g = (guchar)green;
		b = (guchar)blue;
		pixbuf = gdk_pixbuf_add_alpha(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), 1, r, g, b);
	} else {
		if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
			return;
		pixbuf = gdk_pixbuf_add_alpha(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), 0, r, g, b);
	}

	if (pixbuf) {
		phpg_gobject_new(&return_value, (GObject *)pixbuf TSRMLS_CC);
		g_object_unref(pixbuf);
	}
}

#line 7063 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkPixbuf, composite)
{
	zval *dest, *php_interp_type = NULL;
	long dest_x, dest_y, dest_width, dest_height, overall_alpha;
	double offset_x, offset_y, scale_x, scale_y;
	GdkInterpType interp_type;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OiiiiddddVi", &dest, gdkpixbuf_ce, &dest_x, &dest_y, &dest_width, &dest_height, &offset_x, &offset_y, &scale_x, &scale_y, &php_interp_type, &overall_alpha))
		return;

	if (php_interp_type && phpg_gvalue_get_enum(GDK_TYPE_INTERP_TYPE, php_interp_type, (gint *)&interp_type) == FAILURE) {
		return;
	}

    gdk_pixbuf_composite(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), GDK_PIXBUF(PHPG_GOBJECT(dest)), (int)dest_x, (int)dest_y, (int)dest_width, (int)dest_height, offset_x, offset_y, scale_x, scale_y, interp_type, (int)overall_alpha);

}


static PHP_METHOD(GdkPixbuf, composite_color)
{
	zval *dest, *php_interp_type = NULL;
	long dest_x, dest_y, dest_width, dest_height, overall_alpha, check_x, check_y, check_size, color1, color2;
	double offset_x, offset_y, scale_x, scale_y;
	GdkInterpType interp_type;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OiiiiddddViiiiii", &dest, gdkpixbuf_ce, &dest_x, &dest_y, &dest_width, &dest_height, &offset_x, &offset_y, &scale_x, &scale_y, &php_interp_type, &overall_alpha, &check_x, &check_y, &check_size, &color1, &color2))
		return;

	if (php_interp_type && phpg_gvalue_get_enum(GDK_TYPE_INTERP_TYPE, php_interp_type, (gint *)&interp_type) == FAILURE) {
		return;
	}

    gdk_pixbuf_composite_color(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), GDK_PIXBUF(PHPG_GOBJECT(dest)), (int)dest_x, (int)dest_y, (int)dest_width, (int)dest_height, offset_x, offset_y, scale_x, scale_y, interp_type, (int)overall_alpha, (int)check_x, (int)check_y, (int)check_size, (guint32)color1, (guint32)color2);

}


static PHP_METHOD(GdkPixbuf, composite_color_simple)
{
	long dest_width, dest_height, overall_alpha, check_size, color1, color2;
	GdkInterpType interp_type;
	zval *php_interp_type = NULL;
	GdkPixbuf* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iiViiii", &dest_width, &dest_height, &php_interp_type, &overall_alpha, &check_size, &color1, &color2))
		return;

	if (php_interp_type && phpg_gvalue_get_enum(GDK_TYPE_INTERP_TYPE, php_interp_type, (gint *)&interp_type) == FAILURE) {
		return;
	}

    php_retval = gdk_pixbuf_composite_color_simple(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), (int)dest_width, (int)dest_height, interp_type, (int)overall_alpha, (int)check_size, (guint32)color1, (guint32)color2);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
    if (php_retval != NULL) {
        g_object_unref(php_retval);
    }
}


static PHP_METHOD(GdkPixbuf, copy)
{
	GdkPixbuf* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_copy(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
    if (php_retval != NULL) {
        g_object_unref(php_retval);
    }
}


static PHP_METHOD(GdkPixbuf, copy_area)
{
	long src_x, src_y, width, height, dest_x, dest_y;
	zval *dest_pixbuf;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iiiiOii", &src_x, &src_y, &width, &height, &dest_pixbuf, gdkpixbuf_ce, &dest_x, &dest_y))
		return;

    gdk_pixbuf_copy_area(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), (int)src_x, (int)src_y, (int)width, (int)height, GDK_PIXBUF(PHPG_GOBJECT(dest_pixbuf)), (int)dest_x, (int)dest_y);

}

#line 2363 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkPixbuf, fill)
{
    long pixel, r, g, b, a;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i|iii", &r, &g, &b, &a)) {
        return;
    }

    if (ZEND_NUM_ARGS() == 4) {
        pixel = 0;
        pixel += r << 24;
        pixel += g << 16;
        pixel += b << 8;
        pixel += a;
    } else {
        pixel = r;
    }

    gdk_pixbuf_fill(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), (guint32)pixel);
}

#line 7188 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkPixbuf, get_bits_per_sample)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_get_bits_per_sample(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkPixbuf, get_colorspace)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_get_colorspace(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}

#line 2301 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkPixbuf, get_formats)
{
    GSList *list, *tmp;
    zval *item, *mimes;
    gchar *sval, **aval;
    gint i;
    GdkPixbufFormat *format;

    list = gdk_pixbuf_get_formats();
    array_init(return_value);
    for (tmp = list; tmp != NULL; tmp = tmp->next) {
        format = tmp->data;

        MAKE_STD_ZVAL(item);
        array_init(item);

        sval = gdk_pixbuf_format_get_name(format);
        add_assoc_string(item, "name", sval, 1);
        g_free(sval);

        sval = gdk_pixbuf_format_get_description(format);
        add_assoc_string(item, "description", sval, 1);
        g_free(sval);

        aval = gdk_pixbuf_format_get_mime_types(format);
        MAKE_STD_ZVAL(mimes);
        array_init(mimes);
        for (i = 0; aval[i] != NULL; i++) {
            add_next_index_string(mimes, aval[i], 1);
        }
        add_assoc_zval(item, "description", mimes);
        g_strfreev(aval);

        aval = gdk_pixbuf_format_get_extensions(format);
        MAKE_STD_ZVAL(mimes);
        array_init(mimes);
        for (i = 0; aval[i] != NULL; i++) {
            add_next_index_string(mimes, aval[i], 1);
        }
        add_assoc_zval(item, "extensions", mimes);
        g_strfreev(aval);

        add_assoc_long(item, "is_writable", gdk_pixbuf_format_is_writable(format));
        add_assoc_long(item, "is_scalable", gdk_pixbuf_format_is_scalable(format));

        add_next_index_zval(return_value, item);
    }
    g_slist_free(list);
}

#line 7270 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkPixbuf, get_from_drawable)
{
	zval *src, *cmap;
	long src_x, src_y, dest_x, dest_y, width, height;
	GdkPixbuf* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OOiiiiii", &src, gdkdrawable_ce, &cmap, gdkcolormap_ce, &src_x, &src_y, &dest_x, &dest_y, &width, &height))
		return;

    php_retval = gdk_pixbuf_get_from_drawable(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), GDK_DRAWABLE(PHPG_GOBJECT(src)), GDK_COLORMAP(PHPG_GOBJECT(cmap)), (int)src_x, (int)src_y, (int)dest_x, (int)dest_y, (int)width, (int)height);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkPixbuf, get_from_image)
{
	zval *src, *cmap;
	long src_x, src_y, dest_x, dest_y, width, height;
	GdkPixbuf* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OOiiiiii", &src, gdkimage_ce, &cmap, gdkcolormap_ce, &src_x, &src_y, &dest_x, &dest_y, &width, &height))
		return;

    php_retval = gdk_pixbuf_get_from_image(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), GDK_IMAGE(PHPG_GOBJECT(src)), GDK_COLORMAP(PHPG_GOBJECT(cmap)), (int)src_x, (int)src_y, (int)dest_x, (int)dest_y, (int)width, (int)height);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkPixbuf, get_has_alpha)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_get_has_alpha(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(GdkPixbuf, get_height)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_get_height(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkPixbuf, get_n_channels)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_get_n_channels(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkPixbuf, get_option)
{
	char *key;
	zend_bool free_key = FALSE, free_result;
	const gchar *php_retval;
	gchar *cp_ret;
	gsize cp_len;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &key, &free_key))
		return;

    php_retval = gdk_pixbuf_get_option(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), key);
	if (free_key) g_free(key);
    if (php_retval) {
        cp_ret = phpg_from_utf8(php_retval, strlen(php_retval), &cp_len, &free_result TSRMLS_CC);
        if (cp_ret) {
            RETVAL_STRINGL((char *)cp_ret, cp_len, 1);
        } else {
            php_error(E_WARNING, "%s::%s(): could not convert return value from UTF-8", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        }
        if (free_result)
            g_free(cp_ret);
    } else {
        RETVAL_NULL();
    }
}

#line 2126 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkPixbuf, get_pixels)
{
    GdkPixbuf *pixbuf;
    guchar *pixels;
    gint rowstride, height;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "")) {
        return;
    }

    pixbuf = GDK_PIXBUF(PHPG_GOBJECT(this_ptr));
    pixels = gdk_pixbuf_get_pixels(pixbuf);
    rowstride = gdk_pixbuf_get_rowstride(pixbuf);
    height = gdk_pixbuf_get_height(pixbuf);

    if (pixels == NULL) {
        php_error(E_WARNING, "Could not get pixel data");
        return;
    }

    RETURN_STRINGL(pixels, rowstride*height, 1);
}

#line 7403 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkPixbuf, get_rowstride)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_get_rowstride(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkPixbuf, get_width)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_get_width(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkPixbuf, subpixbuf)
{
	long src_x, src_y, width, height;
	GdkPixbuf* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iiii", &src_x, &src_y, &width, &height))
		return;

    php_retval = gdk_pixbuf_new_subpixbuf(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), (int)src_x, (int)src_y, (int)width, (int)height);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
    if (php_retval != NULL) {
        g_object_unref(php_retval);
    }
}

#line 2056 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkPixbuf, render_pixmap_and_mask)
{
    int alpha_threshold = 127;
    GdkPixmap *pixmap;
    GdkBitmap *mask;
    zval *php_pixmap = NULL;
    zval *php_mask = NULL;

    NOT_STATIC_METHOD();
    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "|i", &alpha_threshold))
        return;

    gdk_pixbuf_render_pixmap_and_mask(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), &pixmap, &mask, alpha_threshold);
    if (pixmap) {
        phpg_gobject_new(&php_pixmap, (GObject*)pixmap TSRMLS_CC);
        gdk_pixmap_unref(pixmap);
    } else {
        MAKE_STD_ZVAL(php_pixmap);
    }

    if (mask) {
        phpg_gobject_new(&php_mask, (GObject *)mask TSRMLS_CC);
        gdk_bitmap_unref(mask);
    } else {
        MAKE_STD_ZVAL(php_mask);
    }

    php_gtk_build_value(&return_value, "(NN)", php_pixmap, php_mask);
}

#line 7483 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkPixbuf, render_to_drawable)
{
	zval *drawable, *gc, *php_dither = NULL;
	long src_x, src_y, dest_x, dest_y, width, height, x_dither = GDK_RGB_DITHER_NORMAL, y_dither = GDK_RGB_DITHER_NORMAL;
	GdkRgbDither dither = GDK_RGB_DITHER_NORMAL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OOiiiiii|Vii", &drawable, gdkdrawable_ce, &gc, gdkgc_ce, &src_x, &src_y, &dest_x, &dest_y, &width, &height, &php_dither, &x_dither, &y_dither))
		return;

	if (php_dither && phpg_gvalue_get_enum(GDK_TYPE_RGB_DITHER, php_dither, (gint *)&dither) == FAILURE) {
		return;
	}

	phpg_warn_deprecated("use GdkDrawable::draw_pixbuf() instead" TSRMLS_CC);

    gdk_pixbuf_render_to_drawable(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), GDK_DRAWABLE(PHPG_GOBJECT(drawable)), GDK_GC(PHPG_GOBJECT(gc)), (int)src_x, (int)src_y, (int)dest_x, (int)dest_y, (int)width, (int)height, dither, (gint)x_dither, (gint)y_dither);

}


static PHP_METHOD(GdkPixbuf, render_to_drawable_alpha)
{
	zval *drawable, *php_alpha_mode = NULL, *php_dither = NULL;
	long src_x, src_y, dest_x, dest_y, width, height, alpha_threshold, x_dither = GDK_RGB_DITHER_NORMAL, y_dither = GDK_RGB_DITHER_NORMAL;
	GdkPixbufAlphaMode alpha_mode;
	GdkRgbDither dither = GDK_RGB_DITHER_NORMAL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OiiiiiiVi|Vii", &drawable, gdkdrawable_ce, &src_x, &src_y, &dest_x, &dest_y, &width, &height, &php_alpha_mode, &alpha_threshold, &php_dither, &x_dither, &y_dither))
		return;

	if (php_alpha_mode && phpg_gvalue_get_enum(GDK_TYPE_PIXBUF_ALPHA_MODE, php_alpha_mode, (gint *)&alpha_mode) == FAILURE) {
		return;
	}

	if (php_dither && phpg_gvalue_get_enum(GDK_TYPE_RGB_DITHER, php_dither, (gint *)&dither) == FAILURE) {
		return;
	}

	phpg_warn_deprecated("use GdkDrawable::draw_pixbuf() and GdkPixbuf::render_threshold_alpha()instead" TSRMLS_CC);

    gdk_pixbuf_render_to_drawable_alpha(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), GDK_DRAWABLE(PHPG_GOBJECT(drawable)), (int)src_x, (int)src_y, (int)dest_x, (int)dest_y, (int)width, (int)height, alpha_mode, (int)alpha_threshold, dither, (gint)x_dither, (gint)y_dither);

}


static PHP_METHOD(GdkPixbuf, saturate_and_pixelate)
{
	zval *dest;
	double saturation;
	zend_bool pixelate;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Odb", &dest, gdkpixbuf_ce, &saturation, &pixelate))
		return;

    gdk_pixbuf_saturate_and_pixelate(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), GDK_PIXBUF(PHPG_GOBJECT(dest)), (float)saturation, (gboolean)pixelate);

}

#line 2520 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkPixbuf, save)
{
    char *filename;
    char *type;
    char **option_keys   = NULL;
    char **option_values = NULL;
    zval *php_options = NULL;
    GError *error = NULL;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "ss|a", &filename, &type, &php_options)) {
        return;
    }

    if (php_options) {
        zval **item;
        char *key;
        ulong index;
        int i = 0, n;

        n = zend_hash_num_elements(Z_ARRVAL_P(php_options));
        option_keys   = safe_emalloc(n + 1, sizeof(char*), 0);
        option_values = safe_emalloc(n + 1, sizeof(char*), 0);

        for (zend_hash_internal_pointer_reset(Z_ARRVAL_P(php_options));
             zend_hash_get_current_data(Z_ARRVAL_P(php_options), (void**)&item) == SUCCESS;
             zend_hash_move_forward(Z_ARRVAL_P(php_options))) {

            if (zend_hash_get_current_key(Z_ARRVAL_P(php_options), &key, &index, 0) == HASH_KEY_IS_STRING) {
                convert_to_string_ex(item);
                option_keys[i]   = key;
                option_values[i] = Z_STRVAL_PP(item);
                i++;
            } else {
                php_error(E_WARNING, "%s::%s(): option array keys have to be strings", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
                efree(option_keys);
                efree(option_values);
                return;
            }
        }

        option_keys[i]   = NULL;
        option_values[i] = NULL;
    }

    gdk_pixbuf_savev(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), filename,
                     type, option_keys, option_values, &error);

    if (option_keys) {
        efree(option_keys);
        efree(option_values);
    }

    if (phpg_handle_gerror(&error TSRMLS_CC)) {
        return;
    }
}

#line 7611 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkPixbuf, scale)
{
	zval *dest, *php_interp_type = NULL;
	long dest_x, dest_y, dest_width, dest_height;
	double offset_x, offset_y, scale_x, scale_y;
	GdkInterpType interp_type;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OiiiiddddV", &dest, gdkpixbuf_ce, &dest_x, &dest_y, &dest_width, &dest_height, &offset_x, &offset_y, &scale_x, &scale_y, &php_interp_type))
		return;

	if (php_interp_type && phpg_gvalue_get_enum(GDK_TYPE_INTERP_TYPE, php_interp_type, (gint *)&interp_type) == FAILURE) {
		return;
	}

    gdk_pixbuf_scale(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), GDK_PIXBUF(PHPG_GOBJECT(dest)), (int)dest_x, (int)dest_y, (int)dest_width, (int)dest_height, offset_x, offset_y, scale_x, scale_y, interp_type);

}


static PHP_METHOD(GdkPixbuf, scale_simple)
{
	long dest_width, dest_height;
	GdkInterpType interp_type;
	zval *php_interp_type = NULL;
	GdkPixbuf* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iiV", &dest_width, &dest_height, &php_interp_type))
		return;

	if (php_interp_type && phpg_gvalue_get_enum(GDK_TYPE_INTERP_TYPE, php_interp_type, (gint *)&interp_type) == FAILURE) {
		return;
	}

    php_retval = gdk_pixbuf_scale_simple(GDK_PIXBUF(PHPG_GOBJECT(this_ptr)), (int)dest_width, (int)dest_height, interp_type);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
    if (php_retval != NULL) {
        g_object_unref(php_retval);
    }
}

#line 1853 "ext/gtk+/gdk.overrides"

/* Avoid needing gd headers when building */

#define gdMaxColors 256
#define gdTrueColorGetAlpha(c) (((c) & 0x7F000000) >> 24)
#define gdTrueColorGetRed(c) (((c) & 0xFF0000) >> 16)
#define gdTrueColorGetGreen(c) (((c) & 0x00FF00) >> 8)
#define gdTrueColorGetBlue(c) ((c) & 0x0000FF)
typedef struct gdImageStruct {
	unsigned char ** pixels;
	int sx;
	int sy;
	int colorsTotal;
	int red[gdMaxColors];
	int green[gdMaxColors];
	int blue[gdMaxColors];
	int open[gdMaxColors];
	int transparent;
	int *polyInts;
	int polyAllocated;
	struct gdImageStruct *brush;
	struct gdImageStruct *tile;
	int brushColorMap[gdMaxColors];
	int tileColorMap[gdMaxColors];
	int styleLength;
	int stylePos;
	int *style;
	int interlace;
	int thick;
	int alpha[gdMaxColors];
	int trueColor;
	int ** tpixels;
	int alphaBlendingFlag;
	int antialias;
	int saveAlphaFlag;
	int AA;
	int AA_color;
	int AA_dont_blend;
	unsigned char **AA_opacity;
	int AA_polygon;
	int AAL_x1;
	int AAL_y1;
	int AAL_x2;
	int AAL_y2;
	int AAL_Bx_Ax;
	int AAL_By_Ay;
	int AAL_LAB_2;
	float AAL_LAB;
	int cx1;
	int cy1;
	int cx2;
	int cy2;
} gdImage;

typedef gdImage * gdImagePtr;

void phpg_free_pixbuf_data(guchar *pixels, gpointer data)
{
    efree(pixels);
}

static PHP_METHOD(GdkPixbuf, new_from_gd)
{
    zval *php_gd;
    gdImagePtr gd;
    guint *data;
    guint pixel;
    GdkPixbuf *pixbuf;
    int x, y, c, alpha;
    struct _zend_module_entry *module;
    
#ifdef WIN32
	int (__stdcall *phpi_get_le_gd)(void);
	BOOL (__stdcall *EnumProcessModules)(HANDLE hProcess, HMODULE* lphModule, DWORD cb, LPDWORD lpcbNeeded);
#else
	int (*phpi_get_le_gd)(void);
#endif

	if (zend_hash_find(&module_registry, "gd", sizeof("gd"), (void **)&module) == FAILURE) {
        php_error(E_ERROR, "The php gd extension must be loaded to use this method");
        return;
    }

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "r", &php_gd)) {
        return;
    }

#ifdef WIN32
	if (module->handle == NULL)
	{
		/* Decidedly evil hack to be able to GetProcAddress with NULL handle properly */
		HANDLE cur_proc;
		HMODULE *modules;
		DWORD needed, i;

		HMODULE psapi = LoadLibrary("psapi.dll");

		if (!psapi)
		{
			php_error(E_ERROR, "Could not load gd functions");
			return;
		}
		EnumProcessModules = (GetProcAddress(psapi, "EnumProcessModules"), NULL, 0, 0);
		if (!EnumProcessModules)
		{
			php_error(E_ERROR, "Could not load gd functions");
			return;
		}
		cur_proc = GetCurrentProcess();
		EnumProcessModules(cur_proc, NULL, 0, &needed);
		modules = (HMODULE*)alloca(needed);
		EnumProcessModules(cur_proc, modules, needed, &needed);
		for (i=0; i < needed/sizeof(HMODULE); i++)
		{
			if ((phpi_get_le_gd = (void*)GetProcAddress(modules[i], "phpi_get_le_gd")))
			break;
		}
		free(modules);
	}
	else
	{
		phpi_get_le_gd = (void*)GetProcAddress(module->handle, "phpi_get_le_gd");
	}
#else
	phpi_get_le_gd = DL_FETCH_SYMBOL(module->handle, "phpi_get_le_gd");
#endif

	if (!phpi_get_le_gd)
	{
		php_error(E_ERROR, "Could not load gd functions");
		return;
	}

    ZEND_FETCH_RESOURCE(gd, gdImagePtr, &php_gd, -1, "Image", phpi_get_le_gd());

    data = safe_emalloc(gd->sx * gd->sy, sizeof(guint), 0);
    c = 0;

    if (gd->trueColor) {
        for (y = 0; y < gd->sy; y++) {
            for (x = 0; x < gd->sx; x++) {
                pixel = gd->tpixels[y][x];
                if (pixel == (uint)gd->transparent) {
                    alpha = 0;
                } else {
                    alpha = 127 - gdTrueColorGetAlpha(pixel);
                }
#ifdef WORDS_BIGENDIAN
                data[c++] = (pixel << 8) | ((alpha << 1) + (alpha >> 6));
#else
                data[c++] = (((alpha << 1) + (alpha >> 6)) << 24) |
                            (gdTrueColorGetBlue(pixel)     << 16) |
                            (gdTrueColorGetGreen(pixel)    << 8)  |
                            (gdTrueColorGetRed(pixel));
#endif
            }
        }
    } else {
        for (y = 0; y < gd->sy; y++) {
            for (x = 0; x < gd->sx; x++) {
                pixel = gd->pixels[y][x];
                if (pixel == (uint)gd->transparent) {
                    alpha = 0;
                } else {
                    alpha = 127 - gd->alpha[pixel];
                }
#ifdef WORDS_BIGENDIAN
                data[c++] = (gd->red[pixel]   << 24) |
                            (gd->blue[pixel]  << 16) |
                            (gd->green[pixel] << 8)  |
                            ((alpha << 1) + (alpha >> 6));
#else
                data[c++] = (((alpha << 1) + (alpha >> 6)) << 24) |
                            (gd->blue[pixel]               << 16) |
                            (gd->green[pixel]              << 8)  |
                            (gd->red[pixel]);
#endif
            }
        }
    }

    pixbuf = gdk_pixbuf_new_from_data((const guchar*)data, GDK_COLORSPACE_RGB, 1, 8,
                                      gd->sx, gd->sy, gd->sx * sizeof(guint),
                                      (GdkPixbufDestroyNotify)phpg_free_pixbuf_data, NULL);

    if (pixbuf == NULL) {
        efree(data);
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixbuf);
    }

    phpg_gobject_new(&return_value, (GObject *)pixbuf TSRMLS_CC);
    g_object_unref(pixbuf); /* phpg_gobject_new() increments reference count */
}

#line 7854 "ext/gtk+/gen_gdk.c"


#line 2161 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkPixbuf, get_pixel)
{
    gint x, y;
    long pixel;
    GdkPixbuf *pixbuf;

    guchar *pixels;
    guint r = 0, g = 0, b = 0, a = 0;
    gint w, h;
    int n_channels, rowstride;


    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "ii", &x, &y))
        return;

    pixbuf = GDK_PIXBUF(PHPG_GOBJECT(this_ptr));

    if ((w = gdk_pixbuf_get_width(pixbuf)) == 0 || (h = gdk_pixbuf_get_height(pixbuf)) == 0) {
        php_error(E_WARNING, "%s::%s() empty GdkPixbuf",
                  get_active_class_name(NULL TSRMLS_CC),
                  get_active_function_name(TSRMLS_C));
        return;
    }

    if (x < 0 || y < 0 || x >= w || y >= h) {
        php_error(E_WARNING, "%s::%s() x or y coordinates (%d, %d) out of range (0 - %d, 0 - %d)",
                  get_active_class_name(NULL TSRMLS_CC),
                  get_active_function_name(TSRMLS_C), x, y, w, h);
        return;
    }

    pixels     = gdk_pixbuf_get_pixels(pixbuf);
    n_channels = gdk_pixbuf_get_n_channels(pixbuf);
    rowstride  = gdk_pixbuf_get_rowstride(pixbuf);

    pixels += rowstride * y;
    if (n_channels == 3) {
        pixels += 3 * x;
        r = pixels[0];
        g = pixels[1];
        b = pixels[2];
    } else if (n_channels == 4) {
        pixels += 4 * x;
        r = pixels[0];
        g = pixels[1];
        b = pixels[2];
        a = pixels[3];
    }

    pixel = 0;
    pixel += r << 24;
    pixel += g << 16;
    pixel += b << 8;
    pixel += a;

    RETVAL_LONG(pixel);
}

#line 7918 "ext/gtk+/gen_gdk.c"


#line 2235 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkPixbuf, put_pixel)
{
    gint x, y;
    long pixel;
    GdkPixbuf *pixbuf;

    guchar *pixels;
    guint r, g, b, a;
    gint w, h;
    int n_channels, rowstride;


    NOT_STATIC_METHOD();

    if (ZEND_NUM_ARGS() == 6) {
        if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iiiiii", &x, &y, &r, &g, &b, &a))
            return;
    } else {
        if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iii", &x, &y, &pixel))
            return;
    }

    pixbuf = GDK_PIXBUF(PHPG_GOBJECT(this_ptr));

    if ((w = gdk_pixbuf_get_width(pixbuf)) == 0 || (h = gdk_pixbuf_get_height(pixbuf)) == 0) {
        php_error(E_WARNING, "%s::%s() empty GdkPixbuf",
                  get_active_class_name(NULL TSRMLS_CC),
                  get_active_function_name(TSRMLS_C));
        return;
    }

    if (x < 0 || y < 0 || x >= w || y >= h) {
        php_error(E_WARNING, "%s::%s() x or y coordinates (%d, %d) out of range (0 - %d, 0 - %d)",
                  get_active_class_name(NULL TSRMLS_CC),
                  get_active_function_name(TSRMLS_C), x, y, w, h);
        return;
    }

    pixels     = gdk_pixbuf_get_pixels(pixbuf);
    n_channels = gdk_pixbuf_get_n_channels(pixbuf);
    rowstride  = gdk_pixbuf_get_rowstride(pixbuf);

    if (ZEND_NUM_ARGS() != 6) {
        r = (pixel & 0xff000000) >> 24;
        g = (pixel & 0x00ff0000) >> 16;
        b = (pixel & 0x0000ff00) >> 8;
        a = (pixel & 0x000000ff);
    }

    pixels += rowstride * y;
    if (n_channels == 3) {
        pixels += 3 * x;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
    } else if (n_channels == 4) {
        pixels += 4 * x;
        pixels[0] = r;
        pixels[1] = g;
        pixels[2] = b;
        pixels[3] = a;
    }
}

#line 7986 "ext/gtk+/gen_gdk.c"


#line 2402 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkPixbuf, fill_area)
{
    gint x, y, width, height;
    long pixel;
    GdkPixbuf *pixbuf;

    guchar *pixels;
    guint r, g, b, a;
    guchar *p;
    gint w, h;
    gint ix;
    int n_channels, rowstride;


    NOT_STATIC_METHOD();

    if (ZEND_NUM_ARGS() == 8) {
        if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iiiiiiii", &x, &y,
                                &width, &height, &r, &g, &b, &a))
            return;
    }
    else {
        if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iiiii", &x, &y,
                                &width, &height, &pixel))
            return;
    }

    pixbuf = GDK_PIXBUF(PHPG_GOBJECT(this_ptr));

    /* TODO
     * not sure whether this is correct or not. Christian?
     */
    if (x < 0) {
        width = width - x;
        x = 0;
    }
    if (y < 0) {
        height = height - y;
        y = 0;
    }


    if ((w = gdk_pixbuf_get_width(pixbuf)) == 0 || (h = gdk_pixbuf_get_height(pixbuf)) == 0) {
        php_error(E_WARNING, "%s::%s() empty GdkPixbuf",
                  get_active_class_name(NULL TSRMLS_CC),
                  get_active_function_name(TSRMLS_C));
        return;
    }

    if (width < 0 || height < 0) {
        php_error(E_WARNING, "%s::%s() supplied width or height are < 0",
                  get_active_class_name(NULL TSRMLS_CC),
                  get_active_function_name(TSRMLS_C));
        return;
    }

    if (x >= w || y >= h) {
        php_error(E_WARNING, "%s::%s() x or y coordinates exceed GdkPixbuf width / height",
                  get_active_class_name(NULL TSRMLS_CC),
                  get_active_function_name(TSRMLS_C));
        return;
    }

    pixels     = gdk_pixbuf_get_pixels(pixbuf);
    n_channels = gdk_pixbuf_get_n_channels(pixbuf);
    rowstride  = gdk_pixbuf_get_rowstride(pixbuf);

    if (ZEND_NUM_ARGS() != 8) {
        r = (pixel & 0xff000000) >> 24;
        g = (pixel & 0x00ff0000) >> 16;
        b = (pixel & 0x0000ff00) >> 8;
        a = (pixel & 0x000000ff);
    }

    /* TODO
     * check this too
     */
    if (x + width < w)
        w = x + width;
    if (y + height < h)
        h = y + height;

    pixels += rowstride * y;
    for ( ; y < h; y++) {
        p = pixels;
        if (n_channels == 3) {
            p += 3 * x;
            for (ix = x; ix < w; ix++) {
                p[0] = r;
                p[1] = g;
                p[2] = b;
                p += 3;
            }
        } else if (n_channels == 4) {
            p += 4 * x;
            for(ix = x; ix < w; ix++) {
                p[0] = r;
                p[1] = g;
                p[2] = b;
                p[3] = a;
                p += 4;
            }
        }
        pixels += rowstride;
    }
}

#line 8097 "ext/gtk+/gen_gdk.c"


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbuf_gdk_pixbuf_new, 0)
    ZEND_ARG_INFO(0, colorspace)
    ZEND_ARG_INFO(0, has_alpha)
    ZEND_ARG_INFO(0, bits_per_sample)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbuf_pixbuf_new_from_file, 0)
    ZEND_ARG_INFO(0, filename)
    ZEND_ARG_INFO(0, error)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbuf_pixbuf_new_from_file_at_size, 0)
    ZEND_ARG_INFO(0, filename)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, error)
ZEND_END_ARG_INFO();
static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbuf_pixbuf_new_from_xpm_data, 0)
    ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkpixbuf_add_alpha, 0, 0, 0)
    ZEND_ARG_INFO(0, red)
    ZEND_ARG_INFO(0, green)
    ZEND_ARG_INFO(0, blue)
ZEND_END_ARG_INFO();


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbuf_composite, 0)
    ZEND_ARG_OBJ_INFO(0, dest, GdkPixbuf, 1)
    ZEND_ARG_INFO(0, dest_x)
    ZEND_ARG_INFO(0, dest_y)
    ZEND_ARG_INFO(0, dest_width)
    ZEND_ARG_INFO(0, dest_height)
    ZEND_ARG_INFO(0, offset_x)
    ZEND_ARG_INFO(0, offset_y)
    ZEND_ARG_INFO(0, scale_x)
    ZEND_ARG_INFO(0, scale_y)
    ZEND_ARG_INFO(0, interp_type)
    ZEND_ARG_INFO(0, overall_alpha)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbuf_composite_color, 0)
    ZEND_ARG_OBJ_INFO(0, dest, GdkPixbuf, 1)
    ZEND_ARG_INFO(0, dest_x)
    ZEND_ARG_INFO(0, dest_y)
    ZEND_ARG_INFO(0, dest_width)
    ZEND_ARG_INFO(0, dest_height)
    ZEND_ARG_INFO(0, offset_x)
    ZEND_ARG_INFO(0, offset_y)
    ZEND_ARG_INFO(0, scale_x)
    ZEND_ARG_INFO(0, scale_y)
    ZEND_ARG_INFO(0, interp_type)
    ZEND_ARG_INFO(0, overall_alpha)
    ZEND_ARG_INFO(0, check_x)
    ZEND_ARG_INFO(0, check_y)
    ZEND_ARG_INFO(0, check_size)
    ZEND_ARG_INFO(0, color1)
    ZEND_ARG_INFO(0, color2)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbuf_composite_color_simple, 0)
    ZEND_ARG_INFO(0, dest_width)
    ZEND_ARG_INFO(0, dest_height)
    ZEND_ARG_INFO(0, interp_type)
    ZEND_ARG_INFO(0, overall_alpha)
    ZEND_ARG_INFO(0, check_size)
    ZEND_ARG_INFO(0, color1)
    ZEND_ARG_INFO(0, color2)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbuf_copy_area, 0)
    ZEND_ARG_INFO(0, src_x)
    ZEND_ARG_INFO(0, src_y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_OBJ_INFO(0, dest_pixbuf, GdkPixbuf, 1)
    ZEND_ARG_INFO(0, dest_x)
    ZEND_ARG_INFO(0, dest_y)
ZEND_END_ARG_INFO();
static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkpixbuf_fill, 0, 0, 1)
    ZEND_ARG_INFO(0, pixel_or_red)
    ZEND_ARG_INFO(0, green)
    ZEND_ARG_INFO(0, blue)
    ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO();


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbuf_get_from_drawable, 0)
    ZEND_ARG_OBJ_INFO(0, src, GdkDrawable, 1)
    ZEND_ARG_OBJ_INFO(0, cmap, GdkColormap, 1)
    ZEND_ARG_INFO(0, src_x)
    ZEND_ARG_INFO(0, src_y)
    ZEND_ARG_INFO(0, dest_x)
    ZEND_ARG_INFO(0, dest_y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbuf_get_from_image, 0)
    ZEND_ARG_OBJ_INFO(0, src, GdkImage, 1)
    ZEND_ARG_OBJ_INFO(0, cmap, GdkColormap, 1)
    ZEND_ARG_INFO(0, src_x)
    ZEND_ARG_INFO(0, src_y)
    ZEND_ARG_INFO(0, dest_x)
    ZEND_ARG_INFO(0, dest_y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbuf_get_option, 0)
    ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbuf_subpixbuf, 0)
    ZEND_ARG_INFO(0, src_x)
    ZEND_ARG_INFO(0, src_y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();
static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkpixbuf_render_pixmap_and_mask, 0, 0, 0)
    ZEND_ARG_INFO(0, alpha_threshold)
ZEND_END_ARG_INFO();


static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkpixbuf_render_to_drawable, 0, 0, 8)
    ZEND_ARG_OBJ_INFO(0, drawable, GdkDrawable, 1)
    ZEND_ARG_OBJ_INFO(0, gc, GdkGC, 1)
    ZEND_ARG_INFO(0, src_x)
    ZEND_ARG_INFO(0, src_y)
    ZEND_ARG_INFO(0, dest_x)
    ZEND_ARG_INFO(0, dest_y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, dither)
    ZEND_ARG_INFO(0, x_dither)
    ZEND_ARG_INFO(0, y_dither)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkpixbuf_render_to_drawable_alpha, 0, 0, 9)
    ZEND_ARG_OBJ_INFO(0, drawable, GdkDrawable, 1)
    ZEND_ARG_INFO(0, src_x)
    ZEND_ARG_INFO(0, src_y)
    ZEND_ARG_INFO(0, dest_x)
    ZEND_ARG_INFO(0, dest_y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, alpha_mode)
    ZEND_ARG_INFO(0, alpha_threshold)
    ZEND_ARG_INFO(0, dither)
    ZEND_ARG_INFO(0, x_dither)
    ZEND_ARG_INFO(0, y_dither)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbuf_saturate_and_pixelate, 0)
    ZEND_ARG_OBJ_INFO(0, dest, GdkPixbuf, 1)
    ZEND_ARG_INFO(0, saturation)
    ZEND_ARG_INFO(0, pixelate)
ZEND_END_ARG_INFO();
static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkpixbuf_save, 0, 0, 2)
    ZEND_ARG_INFO(0, filename)
    ZEND_ARG_INFO(0, type)
    ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO();


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbuf_scale, 0)
    ZEND_ARG_OBJ_INFO(0, dest, GdkPixbuf, 1)
    ZEND_ARG_INFO(0, dest_x)
    ZEND_ARG_INFO(0, dest_y)
    ZEND_ARG_INFO(0, dest_width)
    ZEND_ARG_INFO(0, dest_height)
    ZEND_ARG_INFO(0, offset_x)
    ZEND_ARG_INFO(0, offset_y)
    ZEND_ARG_INFO(0, scale_x)
    ZEND_ARG_INFO(0, scale_y)
    ZEND_ARG_INFO(0, interp_type)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbuf_scale_simple, 0)
    ZEND_ARG_INFO(0, dest_width)
    ZEND_ARG_INFO(0, dest_height)
    ZEND_ARG_INFO(0, interp_type)
ZEND_END_ARG_INFO();
static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbuf_new_from_gd, 0)
    ZEND_ARG_INFO(0, gd)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbuf_get_pixel, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkpixbuf_put_pixel, 0, 0, 3)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, pixel_or_red)
    ZEND_ARG_INFO(0, green)
    ZEND_ARG_INFO(0, blue)
    ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkpixbuf_fill_area, 0, 0, 5)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, pixel_or_red)
    ZEND_ARG_INFO(0, green)
    ZEND_ARG_INFO(0, blue)
    ZEND_ARG_INFO(0, alpha)
ZEND_END_ARG_INFO();


static function_entry gdkpixbuf_methods[] = {
	PHP_ME(GdkPixbuf, __construct,          arginfo_gdk_gdkpixbuf_gdk_pixbuf_new, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, new_from_file,        arginfo_gdk_gdkpixbuf_pixbuf_new_from_file, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkPixbuf, new_from_file_at_size, arginfo_gdk_gdkpixbuf_pixbuf_new_from_file_at_size, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkPixbuf, new_from_xpm_data,    arginfo_gdk_gdkpixbuf_pixbuf_new_from_xpm_data, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkPixbuf, add_alpha,            arginfo_gdk_gdkpixbuf_add_alpha, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, composite,            arginfo_gdk_gdkpixbuf_composite, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, composite_color,      arginfo_gdk_gdkpixbuf_composite_color, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, composite_color_simple, arginfo_gdk_gdkpixbuf_composite_color_simple, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, copy,                 NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, copy_area,            arginfo_gdk_gdkpixbuf_copy_area, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, fill,                 arginfo_gdk_gdkpixbuf_fill, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, fill_area,            arginfo_gdk_gdkpixbuf_fill_area, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, get_bits_per_sample,  NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, get_colorspace,       NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, get_formats,          NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkPixbuf, get_from_drawable,    arginfo_gdk_gdkpixbuf_get_from_drawable, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, get_from_image,       arginfo_gdk_gdkpixbuf_get_from_image, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, get_has_alpha,        NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, get_height,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, get_n_channels,       NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, get_option,           arginfo_gdk_gdkpixbuf_get_option, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, get_pixel,            arginfo_gdk_gdkpixbuf_get_pixel, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, get_pixels,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, get_rowstride,        NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, get_width,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, new_from_gd,          arginfo_gdk_gdkpixbuf_new_from_gd, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkPixbuf, put_pixel,            arginfo_gdk_gdkpixbuf_put_pixel, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, render_pixmap_and_mask, arginfo_gdk_gdkpixbuf_render_pixmap_and_mask, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, render_to_drawable,   arginfo_gdk_gdkpixbuf_render_to_drawable, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, render_to_drawable_alpha, arginfo_gdk_gdkpixbuf_render_to_drawable_alpha, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, saturate_and_pixelate, arginfo_gdk_gdkpixbuf_saturate_and_pixelate, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, save,                 arginfo_gdk_gdkpixbuf_save, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, scale,                arginfo_gdk_gdkpixbuf_scale, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, scale_simple,         arginfo_gdk_gdkpixbuf_scale_simple, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbuf, subpixbuf,            arginfo_gdk_gdkpixbuf_subpixbuf, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(GdkPixbufAnimation, __construct)
{
	char *filename;
	zend_bool free_filename = FALSE;
	GError *error = NULL;
	GObject *wrapped_obj;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &filename, &free_filename)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixbufAnimation);
	}

	wrapped_obj = (GObject *) gdk_pixbuf_animation_new_from_file(filename, &error);
	if (free_filename) g_free(filename);
    if (phpg_handle_gerror(&error TSRMLS_CC)) {
        return;
    }

	if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixbufAnimation);
	}

    phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}


static PHP_METHOD(GdkPixbufAnimation, get_height)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_animation_get_height(GDK_PIXBUF_ANIMATION(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkPixbufAnimation, get_static_image)
{
	GdkPixbuf* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_animation_get_static_image(GDK_PIXBUF_ANIMATION(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkPixbufAnimation, get_width)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_animation_get_width(GDK_PIXBUF_ANIMATION(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkPixbufAnimation, is_static_image)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_animation_is_static_image(GDK_PIXBUF_ANIMATION(PHPG_GOBJECT(this_ptr)));
	RETVAL_BOOL(php_retval);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbufanimation_gdk_pixbuf_animation_new_from_file, 0)
    ZEND_ARG_INFO(0, filename)
    ZEND_ARG_INFO(0, error)
ZEND_END_ARG_INFO();

static function_entry gdkpixbufanimation_methods[] = {
	PHP_ME(GdkPixbufAnimation, __construct,          arginfo_gdk_gdkpixbufanimation_gdk_pixbuf_animation_new_from_file, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbufAnimation, get_height,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbufAnimation, get_static_image,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbufAnimation, get_width,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbufAnimation, is_static_image,      NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(GdkPixbufAnimationIter, get_delay_time)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_animation_iter_get_delay_time(GDK_PIXBUF_ANIMATION_ITER(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkPixbufAnimationIter, get_pixbuf)
{
	GdkPixbuf* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_animation_iter_get_pixbuf(GDK_PIXBUF_ANIMATION_ITER(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkPixbufAnimationIter, on_currently_loading_frame)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_animation_iter_on_currently_loading_frame(GDK_PIXBUF_ANIMATION_ITER(PHPG_GOBJECT(this_ptr)));
	RETVAL_BOOL(php_retval);
}


static function_entry gdkpixbufanimationiter_methods[] = {
	PHP_ME(GdkPixbufAnimationIter, get_delay_time,       NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbufAnimationIter, get_pixbuf,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbufAnimationIter, on_currently_loading_frame, NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(GdkPixbufLoader, __construct)
{
	char *image_type;
	zend_bool free_image_type = FALSE;
	GError *error = NULL;
	GObject *wrapped_obj;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &image_type, &free_image_type)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixbufLoader);
	}

	wrapped_obj = (GObject *) gdk_pixbuf_loader_new_with_type(image_type, &error);
	if (free_image_type) g_free(image_type);
    if (phpg_handle_gerror(&error TSRMLS_CC)) {
        return;
    }

	if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkPixbufLoader);
	}

    phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}


static PHP_METHOD(GdkPixbufLoader, close)
{
	GError *error = NULL;
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_loader_close(GDK_PIXBUF_LOADER(PHPG_GOBJECT(this_ptr)), &error);
    if (phpg_handle_gerror(&error TSRMLS_CC)) {
        return;
    }
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(GdkPixbufLoader, get_animation)
{
	GdkPixbufAnimation* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_loader_get_animation(GDK_PIXBUF_LOADER(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkPixbufLoader, get_pixbuf)
{
	GdkPixbuf* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_pixbuf_loader_get_pixbuf(GDK_PIXBUF_LOADER(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkPixbufLoader, set_size)
{
	long width, height;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "ii", &width, &height))
		return;

    gdk_pixbuf_loader_set_size(GDK_PIXBUF_LOADER(PHPG_GOBJECT(this_ptr)), (int)width, (int)height);

}


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbufloader_gdk_pixbuf_loader_new_with_type, 0)
    ZEND_ARG_INFO(0, image_type)
    ZEND_ARG_INFO(0, error)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbufloader_close, 0)
    ZEND_ARG_INFO(0, error)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkpixbufloader_set_size, 0)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();

static function_entry gdkpixbufloader_methods[] = {
	PHP_ME(GdkPixbufLoader, __construct,          arginfo_gdk_gdkpixbufloader_gdk_pixbuf_loader_new_with_type, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbufLoader, close,                arginfo_gdk_gdkpixbufloader_close, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbufLoader, get_animation,        NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbufLoader, get_pixbuf,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkPixbufLoader, set_size,             arginfo_gdk_gdkpixbufloader_set_size, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(GdkScreen, broadcast_client_message)
{
	GdkEvent *event = NULL;
	zval *php_event;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_event, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_event, GDK_TYPE_EVENT, FALSE TSRMLS_CC)) {
        event = (GdkEvent *) PHPG_GBOXED(php_event);
    } else {
        php_error(E_WARNING, "%s::%s() expects event argument to be a valid GdkEvent object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    gdk_screen_broadcast_client_message(GDK_SCREEN(PHPG_GOBJECT(this_ptr)), event);

}


static PHP_METHOD(GdkScreen, get_default)
{
	GdkScreen* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_get_default();
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkScreen, get_default_colormap)
{
	GdkColormap* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_get_default_colormap(GDK_SCREEN(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkScreen, get_display)
{
	GdkDisplay* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_get_display(GDK_SCREEN(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkScreen, get_height)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_get_height(GDK_SCREEN(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkScreen, get_height_mm)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_get_height_mm(GDK_SCREEN(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkScreen, get_monitor_at_point)
{
	long x, y, php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "ii", &x, &y))
		return;

    php_retval = gdk_screen_get_monitor_at_point(GDK_SCREEN(PHPG_GOBJECT(this_ptr)), (gint)x, (gint)y);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkScreen, get_monitor_at_window)
{
	zval *window;
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &window, gdkwindow_ce))
		return;

    php_retval = gdk_screen_get_monitor_at_window(GDK_SCREEN(PHPG_GOBJECT(this_ptr)), GDK_WINDOW(PHPG_GOBJECT(window)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkScreen, get_monitor_geometry)
{
	long monitor_num;
	GdkRectangle dest = { 0, 0, 0, 0 };
	zval *php_dest;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iV", &monitor_num, &php_dest))
		return;

    if (phpg_rectangle_from_zval(php_dest, (GdkRectangle*)&dest TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects dest argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    gdk_screen_get_monitor_geometry(GDK_SCREEN(PHPG_GOBJECT(this_ptr)), (gint)monitor_num, &dest);

}


static PHP_METHOD(GdkScreen, get_n_monitors)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_get_n_monitors(GDK_SCREEN(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkScreen, get_number)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_get_number(GDK_SCREEN(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkScreen, get_rgb_colormap)
{
	GdkColormap* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_get_rgb_colormap(GDK_SCREEN(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkScreen, get_rgb_visual)
{
	GdkVisual* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_get_rgb_visual(GDK_SCREEN(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkScreen, get_root_window)
{
	GdkWindow* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_get_root_window(GDK_SCREEN(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkScreen, get_system_colormap)
{
	GdkColormap* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_get_system_colormap(GDK_SCREEN(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkScreen, get_system_visual)
{
	GdkVisual* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_get_system_visual(GDK_SCREEN(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}

#line 2785 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkScreen, get_toplevel_windows)
{
    GList *list, *item;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    list = gdk_screen_get_toplevel_windows(GDK_SCREEN(PHPG_GOBJECT(this_ptr)));

    array_init(return_value);
    for (item = list; item; item = item->next) {
        zval *php_item = NULL;
        phpg_gobject_new(&php_item, G_OBJECT(item->data) TSRMLS_CC);
        add_next_index_zval(return_value, php_item);
    }

    g_list_free(list);
}

#line 8896 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkScreen, get_width)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_get_width(GDK_SCREEN(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkScreen, get_width_mm)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_get_width_mm(GDK_SCREEN(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkScreen, height)
{
	long php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_height();
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkScreen, height_mm)
{
	long php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_height_mm();
	RETVAL_LONG(php_retval);
}

#line 2808 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkScreen, list_visuals)
{
    GList *list, *item;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    list = gdk_screen_list_visuals(GDK_SCREEN(PHPG_GOBJECT(this_ptr)));

    array_init(return_value);
    for (item = list; item; item = item->next) {
        zval *php_item = NULL;
        phpg_gobject_new(&php_item, G_OBJECT(item->data) TSRMLS_CC);
        add_next_index_zval(return_value, php_item);
    }

    g_list_free(list);
}

#line 8973 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkScreen, make_display_name)
{
	gchar *php_retval, *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_make_display_name(GDK_SCREEN(PHPG_GOBJECT(this_ptr)));
    if (php_retval) {
        cp_ret = phpg_from_utf8(php_retval, strlen(php_retval), &cp_len, &free_result TSRMLS_CC);
        if (cp_ret) {
            RETVAL_STRINGL((char *)cp_ret, cp_len, 1);
        } else {
            php_error(E_WARNING, "%s::%s(): could not convert return value from UTF-8", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        }
        g_free(php_retval);
        if (free_result)
            g_free(cp_ret);
    } else
        RETVAL_NULL();
}


static PHP_METHOD(GdkScreen, set_default_colormap)
{
	zval *colormap;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &colormap, gdkcolormap_ce))
		return;

    gdk_screen_set_default_colormap(GDK_SCREEN(PHPG_GOBJECT(this_ptr)), GDK_COLORMAP(PHPG_GOBJECT(colormap)));

}


static PHP_METHOD(GdkScreen, width)
{
	long php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_width();
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkScreen, width_mm)
{
	long php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_screen_width_mm();
	RETVAL_LONG(php_retval);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkscreen_broadcast_client_message, 0)
    ZEND_ARG_OBJ_INFO(0, event, GdkEvent, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkscreen_get_monitor_at_point, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkscreen_get_monitor_at_window, 0)
    ZEND_ARG_OBJ_INFO(0, window, GdkWindow, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkscreen_get_monitor_geometry, 0)
    ZEND_ARG_INFO(0, monitor_num)
    ZEND_ARG_OBJ_INFO(0, dest, GdkRectangle, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkscreen_set_default_colormap, 0)
    ZEND_ARG_OBJ_INFO(0, colormap, GdkColormap, 1)
ZEND_END_ARG_INFO();

static function_entry gdkscreen_methods[] = {
	PHP_ME(GdkScreen, broadcast_client_message, arginfo_gdk_gdkscreen_broadcast_client_message, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, get_default,          NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkScreen, get_default_colormap, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, get_display,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, get_height,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, get_height_mm,        NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, get_monitor_at_point, arginfo_gdk_gdkscreen_get_monitor_at_point, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, get_monitor_at_window, arginfo_gdk_gdkscreen_get_monitor_at_window, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, get_monitor_geometry, arginfo_gdk_gdkscreen_get_monitor_geometry, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, get_n_monitors,       NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, get_number,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, get_rgb_colormap,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, get_rgb_visual,       NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, get_root_window,      NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, get_system_colormap,  NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, get_system_visual,    NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, get_toplevel_windows, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, get_width,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, get_width_mm,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, height,               NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkScreen, height_mm,            NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkScreen, list_visuals,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, make_display_name,    NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, set_default_colormap, arginfo_gdk_gdkscreen_set_default_colormap, ZEND_ACC_PUBLIC)
	PHP_ME(GdkScreen, width,                NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkScreen, width_mm,             NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{ NULL, NULL, NULL }
};

PHPG_PROP_READER(GdkVisual, type)
{
	long php_retval;

    php_retval = GDK_VISUAL(((phpg_gobject_t *)object)->obj)->type;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkVisual, depth)
{
	long php_retval;

    php_retval = GDK_VISUAL(((phpg_gobject_t *)object)->obj)->depth;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkVisual, byte_order)
{
	long php_retval;

    php_retval = GDK_VISUAL(((phpg_gobject_t *)object)->obj)->byte_order;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkVisual, colormap_size)
{
	long php_retval;

    php_retval = GDK_VISUAL(((phpg_gobject_t *)object)->obj)->colormap_size;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkVisual, bits_per_rgb)
{
	long php_retval;

    php_retval = GDK_VISUAL(((phpg_gobject_t *)object)->obj)->bits_per_rgb;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkVisual, red_mask)
{
	long php_retval;

    php_retval = GDK_VISUAL(((phpg_gobject_t *)object)->obj)->red_mask;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkVisual, red_shift)
{
	long php_retval;

    php_retval = GDK_VISUAL(((phpg_gobject_t *)object)->obj)->red_shift;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkVisual, red_prec)
{
	long php_retval;

    php_retval = GDK_VISUAL(((phpg_gobject_t *)object)->obj)->red_prec;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkVisual, green_mask)
{
	long php_retval;

    php_retval = GDK_VISUAL(((phpg_gobject_t *)object)->obj)->green_mask;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkVisual, green_shift)
{
	long php_retval;

    php_retval = GDK_VISUAL(((phpg_gobject_t *)object)->obj)->green_shift;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkVisual, green_prec)
{
	long php_retval;

    php_retval = GDK_VISUAL(((phpg_gobject_t *)object)->obj)->green_prec;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkVisual, blue_mask)
{
	long php_retval;

    php_retval = GDK_VISUAL(((phpg_gobject_t *)object)->obj)->blue_mask;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkVisual, blue_shift)
{
	long php_retval;

    php_retval = GDK_VISUAL(((phpg_gobject_t *)object)->obj)->blue_shift;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkVisual, blue_prec)
{
	long php_retval;

    php_retval = GDK_VISUAL(((phpg_gobject_t *)object)->obj)->blue_prec;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


static prop_info_t gdkvisual_prop_info[] = {
	{ "type", PHPG_PROP_READ_FN(GdkVisual, type), NULL },
	{ "depth", PHPG_PROP_READ_FN(GdkVisual, depth), NULL },
	{ "byte_order", PHPG_PROP_READ_FN(GdkVisual, byte_order), NULL },
	{ "colormap_size", PHPG_PROP_READ_FN(GdkVisual, colormap_size), NULL },
	{ "bits_per_rgb", PHPG_PROP_READ_FN(GdkVisual, bits_per_rgb), NULL },
	{ "red_mask", PHPG_PROP_READ_FN(GdkVisual, red_mask), NULL },
	{ "red_shift", PHPG_PROP_READ_FN(GdkVisual, red_shift), NULL },
	{ "red_prec", PHPG_PROP_READ_FN(GdkVisual, red_prec), NULL },
	{ "green_mask", PHPG_PROP_READ_FN(GdkVisual, green_mask), NULL },
	{ "green_shift", PHPG_PROP_READ_FN(GdkVisual, green_shift), NULL },
	{ "green_prec", PHPG_PROP_READ_FN(GdkVisual, green_prec), NULL },
	{ "blue_mask", PHPG_PROP_READ_FN(GdkVisual, blue_mask), NULL },
	{ "blue_shift", PHPG_PROP_READ_FN(GdkVisual, blue_shift), NULL },
	{ "blue_prec", PHPG_PROP_READ_FN(GdkVisual, blue_prec), NULL },
	{ NULL, NULL, NULL },
};

#line 100 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkVisual, list_visuals)
{
    GList *list, *item;

    list = gdk_list_visuals();

    array_init(return_value);
    for (item = list; item; item = item->next) {
        zval *php_item = NULL;
        phpg_gobject_new(&php_item, G_OBJECT(item->data) TSRMLS_CC);
        add_next_index_zval(return_value, php_item);
    }

    g_list_free(list);
}

#line 9274 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkVisual, get_best)
{
	GdkVisual* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_visual_get_best();
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkVisual, get_best_depth)
{
	long php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_visual_get_best_depth();
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkVisual, get_best_type)
{
	long php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_visual_get_best_type();
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkVisual, get_best_with_both)
{
	long depth;
	GdkVisualType visual_type;
	zval *php_visual_type = NULL;
	GdkVisual* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iV", &depth, &php_visual_type))
		return;

	if (php_visual_type && phpg_gvalue_get_enum(GDK_TYPE_VISUAL_TYPE, php_visual_type, (gint *)&visual_type) == FAILURE) {
		return;
	}

    php_retval = gdk_visual_get_best_with_both((gint)depth, visual_type);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
    if (php_retval != NULL) {
        g_object_unref(php_retval);
    }
}


static PHP_METHOD(GdkVisual, get_best_with_depth)
{
	long depth;
	GdkVisual* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &depth))
		return;

    php_retval = gdk_visual_get_best_with_depth((gint)depth);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkVisual, get_best_with_type)
{
	GdkVisualType visual_type;
	zval *php_visual_type = NULL;
	GdkVisual* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_visual_type))
		return;

	if (php_visual_type && phpg_gvalue_get_enum(GDK_TYPE_VISUAL_TYPE, php_visual_type, (gint *)&visual_type) == FAILURE) {
		return;
	}

    php_retval = gdk_visual_get_best_with_type(visual_type);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkVisual, get_screen)
{
	GdkScreen* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_visual_get_screen(GDK_VISUAL(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkVisual, get_system)
{
	GdkVisual* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_visual_get_system();
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkvisual_get_best_with_both, 0)
    ZEND_ARG_INFO(0, depth)
    ZEND_ARG_INFO(0, visual_type)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkvisual_get_best_with_depth, 0)
    ZEND_ARG_INFO(0, depth)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkvisual_get_best_with_type, 0)
    ZEND_ARG_INFO(0, visual_type)
ZEND_END_ARG_INFO();

static function_entry gdkvisual_methods[] = {
	PHP_ME(GdkVisual, get_best,             NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkVisual, get_best_depth,       NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkVisual, get_best_type,        NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkVisual, get_best_with_both,   arginfo_gdk_gdkvisual_get_best_with_both, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkVisual, get_best_with_depth,  arginfo_gdk_gdkvisual_get_best_with_depth, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkVisual, get_best_with_type,   arginfo_gdk_gdkvisual_get_best_with_type, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkVisual, get_screen,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkVisual, get_system,           NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkVisual, list_visuals,         NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(GdkEvent, __construct)
{
	GdkEventType type;
	zval *php_type = NULL;

    phpg_gboxed_t *pobj = NULL;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_type)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkEvent);
	}

	if (php_type && phpg_gvalue_get_enum(GDK_TYPE_EVENT_TYPE, php_type, (gint *)&type) == FAILURE) {
		PHPG_THROW_CONSTRUCT_EXCEPTION(GdkEvent);
	}

    pobj = zend_object_store_get_object(this_ptr TSRMLS_CC);
    pobj->gtype = GDK_TYPE_EVENT;
    pobj->boxed = gdk_event_new(type);

	if (!pobj->boxed) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkEvent);
	}
    pobj->free_on_destroy = TRUE;
}

#line 760 "ext/gtk+/gdk.overrides"
static zval* phpg_gdkevent_read_property_handler(zval *object, zval *member, int type TSRMLS_DC)
{
    zval tmp_member;
    zval *result = NULL;
    GdkEvent *event = (GdkEvent *) PHPG_GBOXED(object);
    char *name;

	if (member->type != IS_STRING) {
		tmp_member = *member;
		zval_copy_ctor(&tmp_member);
		convert_to_string(&tmp_member);
		member = &tmp_member;
	}

    name = Z_STRVAL_P(member);

    switch (event->type) {

        case GDK_NOTHING:
        case GDK_DELETE:
        case GDK_DESTROY:
            break;

        case GDK_EXPOSE:
            if (!strcmp(name, "area")) {
                phpg_gboxed_new(&result, GDK_TYPE_RECTANGLE, &event->expose.area, TRUE, TRUE TSRMLS_CC);
            } else if (!strcmp(name, "count")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->expose.count);
            }
            break;

        case GDK_MOTION_NOTIFY:
            if (!strcmp(name, "time")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->motion.time);
            } else if (!strcmp(name, "x")) {
                ALLOC_ZVAL(result);
                ZVAL_DOUBLE(result, event->motion.x);
            } else if (!strcmp(name, "y")) {
                ALLOC_ZVAL(result);
                ZVAL_DOUBLE(result, event->motion.y);
            } else if (!strcmp(name, "axes")) {
                ALLOC_ZVAL(result);
                if (event->motion.axes) {
                    gint i = 0;
                    array_init(result);
                    for (i = 0; i < event->motion.device->num_axes; i++) {
                        add_next_index_double(result, event->motion.axes[i]);
                    }
                } else {
                    ZVAL_NULL(result);
                }
            } else if (!strcmp(name, "state")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->motion.state);
            } else if (!strcmp(name, "is_hint")) {
                ALLOC_ZVAL(result);
                ZVAL_BOOL(result, event->motion.is_hint);
            } else if (!strcmp(name, "device")) {
                ALLOC_ZVAL(result);
                phpg_gobject_new(&result, (GObject *)event->motion.device TSRMLS_CC);
            } else if (!strcmp(name, "x_root")) {
                ALLOC_ZVAL(result);
                ZVAL_DOUBLE(result, event->motion.x_root);
            } else if (!strcmp(name, "y_root")) {
                ALLOC_ZVAL(result);
                ZVAL_DOUBLE(result, event->motion.y_root);
            }
            break;

        case GDK_BUTTON_PRESS:
        case GDK_2BUTTON_PRESS:
        case GDK_3BUTTON_PRESS:
        case GDK_BUTTON_RELEASE:
            if (!strcmp(name, "time")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->button.time);
            } else if (!strcmp(name, "x")) {
                ALLOC_ZVAL(result);
                ZVAL_DOUBLE(result, event->button.x);
            } else if (!strcmp(name, "y")) {
                ALLOC_ZVAL(result);
                ZVAL_DOUBLE(result, event->button.y);
            } else if (!strcmp(name, "axes")) {
                ALLOC_ZVAL(result);
                if (event->button.axes) {
                    gint i = 0;
                    array_init(result);
                    for (i = 0; i < event->button.device->num_axes; i++) {
                        add_next_index_double(result, event->button.axes[i]);
                    }
                } else {
                    ZVAL_NULL(result);
                }
            } else if (!strcmp(name, "state")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->button.state);
            } else if (!strcmp(name, "button")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->button.button);
            } else if (!strcmp(name, "device")) {
                ALLOC_ZVAL(result);
                phpg_gobject_new(&result, (GObject *)event->button.device TSRMLS_CC);
            } else if (!strcmp(name, "x_root")) {
                ALLOC_ZVAL(result);
                ZVAL_DOUBLE(result, event->button.x_root);
            } else if (!strcmp(name, "y_root")) {
                ALLOC_ZVAL(result);
                ZVAL_DOUBLE(result, event->button.y_root);
            }
            break;

        case GDK_KEY_PRESS:
        case GDK_KEY_RELEASE:
            if (!strcmp(name, "time")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->key.time);
            } else if (!strcmp(name, "state")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->key.state);
            } else if (!strcmp(name, "keyval")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->key.keyval);
            } else if (!strcmp(name, "string")) {
                ALLOC_ZVAL(result);
                ZVAL_STRINGL(result, event->key.string, event->key.length, 1);
            } else if (!strcmp(name, "hardware_keycode")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->key.hardware_keycode);
            } else if (!strcmp(name, "group")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->key.group);
            }
            break;

        case GDK_ENTER_NOTIFY:
        case GDK_LEAVE_NOTIFY:
            if (!strcmp(name, "subwindow")) {
                ALLOC_ZVAL(result);
                phpg_gobject_new(&result, (GObject *)event->crossing.subwindow TSRMLS_CC);
            } else if (!strcmp(name, "time")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->crossing.time);
            } else if (!strcmp(name, "x")) {
                ALLOC_ZVAL(result);
                ZVAL_DOUBLE(result, event->crossing.x);
            } else if (!strcmp(name, "y")) {
                ALLOC_ZVAL(result);
                ZVAL_DOUBLE(result, event->crossing.y);
            } else if (!strcmp(name, "x_root")) {
                ALLOC_ZVAL(result);
                ZVAL_DOUBLE(result, event->crossing.x_root);
            } else if (!strcmp(name, "y_root")) {
                ALLOC_ZVAL(result);
                ZVAL_DOUBLE(result, event->crossing.y_root);
            } else if (!strcmp(name, "mode")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->crossing.mode);
            } else if (!strcmp(name, "detail")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->crossing.detail);
            } else if (!strcmp(name, "focus")) {
                ALLOC_ZVAL(result);
                ZVAL_BOOL(result, event->crossing.focus);
            } else if (!strcmp(name, "state")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->crossing.state);
            }
            break;

        case GDK_FOCUS_CHANGE:
            if (!strcmp(name, "in")) {
                ALLOC_ZVAL(result);
                ZVAL_BOOL(result, event->focus_change.in);
            }
            break;

        case GDK_CONFIGURE:
            if (!strcmp(name, "x")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->configure.x);
            } else if (!strcmp(name, "y")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->configure.y);
            } else if (!strcmp(name, "width")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->configure.width);
            } else if (!strcmp(name, "height")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->configure.height);
            }
            break;

        case GDK_MAP:
        case GDK_UNMAP:
            break;

        case GDK_PROPERTY_NOTIFY:
            if (!strcmp(name, "atom")) { /* TODO GdkAtom is a struct */
                ALLOC_ZVAL(result);
                ZVAL_NULL(result);
            } else if (!strcmp(name, "time")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->property.time);
            } else if (!strcmp(name, "state")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->property.state);
            }
            break;

        case GDK_SELECTION_CLEAR:
        case GDK_SELECTION_REQUEST:
        case GDK_SELECTION_NOTIFY:
            if (!strcmp(name, "selection")) { /* TODO GdkAtom is a struct */
                ALLOC_ZVAL(result);
                ZVAL_NULL(result);
            } else if (!strcmp(name, "target")) { /* TODO GdkAtom */
                ALLOC_ZVAL(result);
                ZVAL_NULL(result);
            } else if (!strcmp(name, "property")) { /* TODO GdkAtom */
                ALLOC_ZVAL(result);
                ZVAL_NULL(result);
            } else if (!strcmp(name, "time")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->selection.time);
            } else if (!strcmp(name, "requestor")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->selection.requestor);
            }
            break;

        case GDK_PROXIMITY_IN:
        case GDK_PROXIMITY_OUT:
            if (!strcmp(name, "time")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->proximity.time);
            } else if (!strcmp(name, "device")) {
                ALLOC_ZVAL(result);
                phpg_gobject_new(&result, (GObject *)event->proximity.device TSRMLS_CC);
            }
            break;

        case GDK_DRAG_ENTER:
        case GDK_DRAG_LEAVE:
        case GDK_DRAG_MOTION:
        case GDK_DRAG_STATUS:
        case GDK_DROP_START:
        case GDK_DROP_FINISHED:
            if (!strcmp(name, "context")) { /* GdkDragContext is a struct */
                ALLOC_ZVAL(result);
                phpg_gobject_new(&result, (GObject *)event->dnd.context TSRMLS_CC);
            } else if (!strcmp(name, "time")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->dnd.time);
            } else if (!strcmp(name, "x_root")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->dnd.x_root);
            } else if (!strcmp(name, "y_root")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->dnd.y_root);
            }
            break;

        case GDK_CLIENT_EVENT:
            if (!strcmp(name, "message_type")) { /* TODO GdkAtom is a struct */
                ALLOC_ZVAL(result);
                ZVAL_NULL(result);
            } else if (!strcmp(name, "data_format")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->client.data_format);
            } else if (!strcmp(name, "data.b")) {
                ALLOC_ZVAL(result);
                ZVAL_STRINGL(result, event->client.data.b, 20, 1); /* Why 20? */
            }
            break;

        case GDK_VISIBILITY_NOTIFY:
            if (!strcmp(name, "state")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->visibility.state);
            }
            break;

        case GDK_NO_EXPOSE:
            break;

        case GDK_SCROLL:
            if (!strcmp(name, "time")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->scroll.time);
            } else if (!strcmp(name, "x")) {
                ALLOC_ZVAL(result);
                ZVAL_DOUBLE(result, event->scroll.x);
            } else if (!strcmp(name, "y")) {
                ALLOC_ZVAL(result);
                ZVAL_DOUBLE(result, event->scroll.y);
            } else if (!strcmp(name, "state")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->scroll.state);
            } else if (!strcmp(name, "direction")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->scroll.direction);
            } else if (!strcmp(name, "device")) {
                ALLOC_ZVAL(result);
                phpg_gobject_new(&result, (GObject *)event->scroll.device TSRMLS_CC);
            } else if (!strcmp(name, "x_root")) {
                ALLOC_ZVAL(result);
                ZVAL_DOUBLE(result, event->scroll.x_root);
            } else if (!strcmp(name, "y_root")) {
                ALLOC_ZVAL(result);
                ZVAL_DOUBLE(result, event->scroll.y_root);
            }
            break;

        case GDK_WINDOW_STATE:
            if (!strcmp(name, "changed_mask")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->window_state.changed_mask);
            } else if (!strcmp(name, "new_window_state")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->window_state.new_window_state);
            }
            break;

        case GDK_SETTING:
            if (!strcmp(name, "action")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->setting.action);
            } else if (!strcmp(name, "name")) {
                ALLOC_ZVAL(result);
                ZVAL_STRINGL(result, event->setting.name, strlen(event->setting.name), 1);
            }
            break;

        case GDK_OWNER_CHANGE:
            if (!strcmp(name, "owner")) {
                ALLOC_ZVAL(result);
                ZVAL_NULL(result);
            } else if (!strcmp(name, "reason")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->owner_change.reason);
            } else if (!strcmp(name, "selection")) { /* TODO GdkAtom is a struct */
                ALLOC_ZVAL(result);
                ZVAL_NULL(result);
            } else if (!strcmp(name, "time")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->owner_change.time);
            } else if (!strcmp(name, "selection_time")) {
                ALLOC_ZVAL(result);
                ZVAL_LONG(result, event->owner_change.selection_time);
            }
            break;

        default:
            break;
    }

    if (!strcmp(name, "type")) {
        ALLOC_ZVAL(result);
        ZVAL_LONG(result, event->type);
    } else if (!strcmp(name, "window")) {
        ALLOC_ZVAL(result);
        phpg_gobject_new(&result, (GObject *)event->any.window TSRMLS_CC);
    } else if (!strcmp(name, "send_event")) {
        ALLOC_ZVAL(result);
        ZVAL_BOOL(result, event->any.send_event);
    }

    if (result) {
		Z_SET_REFCOUNT_P(result, 0);
		Z_UNSET_ISREF_P(result);
    } else {
        result = zend_get_std_object_handlers()->read_property(object, member, type TSRMLS_CC);
    }

	if (member == &tmp_member) {
		zval_dtor(member);
	}

    return result;
}

#line 9831 "ext/gtk+/gen_gdk.c"


#line 1147 "ext/gtk+/gdk.overrides"
HashTable* phpg_gdkevent_get_properties_handler(zval *object TSRMLS_DC)
{
    phpg_head_t *poh = NULL;
    GdkEvent *event = (GdkEvent *) PHPG_GBOXED(object);

    poh = (phpg_head_t *) zend_object_store_get_object(object TSRMLS_CC);

    switch (event->type) {

        case GDK_NOTHING:
        case GDK_DELETE:
        case GDK_DESTROY:
            break;

        case GDK_EXPOSE:
            phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC,
                                       STRS(area), STRS(count), NULL);
            break;

        case GDK_MOTION_NOTIFY:
            phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC,
                                       STRS(time), STRS(x), STRS(y), STRS(axes),
                                       STRS(state), STRS(is_hint), STRS(device),
                                       STRS(x_root), STRS(y_root), NULL);
            break;

        case GDK_BUTTON_PRESS:
        case GDK_2BUTTON_PRESS:
        case GDK_3BUTTON_PRESS:
        case GDK_BUTTON_RELEASE:
            phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC,
                                       STRS(time), STRS(x), STRS(y), STRS(axes),
                                       STRS(state), STRS(button), STRS(device),
                                       STRS(x_root), STRS(y_root), NULL);
            break;

        case GDK_KEY_PRESS:
        case GDK_KEY_RELEASE:
            phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC,
                                       STRS(time), STRS(state), STRS(keyval), STRS(string),
                                       STRS(hardware_keycode), STRS(group), NULL);
            break;

        case GDK_ENTER_NOTIFY:
        case GDK_LEAVE_NOTIFY:
            phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC,
                                       STRS(subwindow), STRS(time), STRS(x), STRS(y),
                                       STRS(x_root), STRS(y_root), STRS(mode), STRS(detail),
                                       STRS(focus), STRS(state), NULL);
            break;

        case GDK_FOCUS_CHANGE:
            phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC,
                                       STRS(in), NULL);

        case GDK_CONFIGURE:
            phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC,
                                       STRS(x), STRS(y), STRS(width), STRS(height), NULL);
            break;

        case GDK_MAP:
        case GDK_UNMAP:
            break;

        case GDK_PROPERTY_NOTIFY:
            phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC,
                                       STRS(atom), STRS(time), STRS(state), NULL);
            break;

        case GDK_SELECTION_CLEAR:
        case GDK_SELECTION_REQUEST:
        case GDK_SELECTION_NOTIFY:
            phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC,
                                       STRS(selection), STRS(target), STRS(property),
                                       STRS(time), STRS(requestor), NULL);
            break;

        case GDK_PROXIMITY_IN:
        case GDK_PROXIMITY_OUT:
            phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC,
                                       STRS(time), STRS(device), NULL);
            break;

        case GDK_DRAG_ENTER:
        case GDK_DRAG_LEAVE:
        case GDK_DRAG_MOTION:
        case GDK_DRAG_STATUS:
        case GDK_DROP_START:
        case GDK_DROP_FINISHED:
            phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC, STRS(context),
                                       STRS(time), STRS(x_root), STRS(y_root), NULL);
            break;

        case GDK_CLIENT_EVENT:
            phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC,
                                       STRS(message_type), STRS(data_format), STRS(data), NULL);
            break;

        case GDK_VISIBILITY_NOTIFY:
            phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC,
                                       STRS(state), NULL);
            break;

        case GDK_NO_EXPOSE:
            break;

        case GDK_SCROLL:
            phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC, STRS(time),
                                       STRS(x), STRS(y), STRS(state), STRS(direction),
                                       STRS(device), STRS(x_root), STRS(y_root), NULL);
            break;

        case GDK_WINDOW_STATE:
            phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC,
                                       STRS(changed_mask), STRS(new_window_state), NULL);
            break;

        case GDK_SETTING:
            phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC,
                                       STRS(action), STRS(name), NULL);
            break;

        case GDK_OWNER_CHANGE:
            phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC, STRS(owner),
                                       STRS(reason), STRS(selection), STRS(time), STRS(selection_time), NULL);
            break;

        default:
            break;
    }

    phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC,
                               STRS(type), STRS(window), STRS(send_event), NULL);

	return poh->zobj.properties;
}


#line 9973 "ext/gtk+/gen_gdk.c"



static zend_object_handlers gdkevent_object_handlers;

static zend_object_value phpg_create_gdkevent(zend_class_entry *ce TSRMLS_DC)
{
    zend_object_value zov;

    zov = phpg_create_gboxed(ce TSRMLS_CC);
    zov.handlers = &gdkevent_object_handlers;

    return zov;
}

static PHP_METHOD(GdkEvent, copy)
{
	GdkEvent *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_event_copy((GdkEvent *)PHPG_GBOXED(this_ptr));
	phpg_gboxed_new(&return_value, GDK_TYPE_EVENT, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(GdkEvent, free)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_event_free((GdkEvent *)PHPG_GBOXED(this_ptr));

}

#line 1294 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkEvent, get_axis)
{
    zval *php_axis_use;
    GdkAxisUse axis_use;
    gdouble value;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_axis_use))
        return;

    if (phpg_gvalue_get_enum(GDK_TYPE_AXIS_USE, php_axis_use, (gint *) &axis_use) == FAILURE)
        return;

    if (gdk_event_get_axis((GdkEvent *) PHPG_GBOXED(this_ptr), axis_use, &value)) {
        RETURN_DOUBLE(value);
    } else {
        RETURN_FALSE;
    }
}


#line 10039 "ext/gtk+/gen_gdk.c"


#line 1318 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkEvent, get_coords)
{
    gdouble x_win, y_win;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    if (gdk_event_get_coords((GdkEvent *) PHPG_GBOXED(this_ptr), &x_win, &y_win)) {
        php_gtk_build_value(&return_value, "(dd)", x_win, y_win);
    } else {
        RETURN_FALSE;
    }
}


#line 10060 "ext/gtk+/gen_gdk.c"


#line 1337 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkEvent, get_root_coords)
{
    gdouble x_win, y_win;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    if (gdk_event_get_root_coords((GdkEvent *) PHPG_GBOXED(this_ptr), &x_win, &y_win)) {
        php_gtk_build_value(&return_value, "(dd)", x_win, y_win);
    } else {
        RETURN_FALSE;
    }
}


#line 10081 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkEvent, get_screen)
{
	GdkScreen* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_event_get_screen((GdkEvent *)PHPG_GBOXED(this_ptr));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}

#line 1356 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkEvent, get_state)
{
    GdkModifierType state = 0;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    gdk_event_get_state((GdkEvent *) PHPG_GBOXED(this_ptr), &state);

    RETURN_LONG((long)state);
}

#line 10113 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkEvent, get_time)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_event_get_time((GdkEvent *)PHPG_GBOXED(this_ptr));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkEvent, put)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    gdk_event_put((GdkEvent *)PHPG_GBOXED(this_ptr));

}


static PHP_METHOD(GdkEvent, set_screen)
{
	zval *screen;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &screen, gdkscreen_ce))
		return;

    gdk_event_set_screen((GdkEvent *)PHPG_GBOXED(this_ptr), GDK_SCREEN(PHPG_GOBJECT(screen)));

}


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkevent_event_new, 0)
    ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO();
static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkevent_get_axis, 0)
    ZEND_ARG_INFO(0, axis_type)
ZEND_END_ARG_INFO();


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkevent_set_screen, 0)
    ZEND_ARG_OBJ_INFO(0, screen, GdkScreen, 1)
ZEND_END_ARG_INFO();

static function_entry gdkevent_methods[] = {
	PHP_ME(GdkEvent, __construct,          arginfo_gdk_gdkevent_event_new, ZEND_ACC_PUBLIC)
	PHP_ME(GdkEvent, copy,                 NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkEvent, free,                 NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkEvent, get_axis,             arginfo_gdk_gdkevent_get_axis, ZEND_ACC_PUBLIC)
	PHP_ME(GdkEvent, get_coords,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkEvent, get_root_coords,      NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkEvent, get_screen,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkEvent, get_state,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkEvent, get_time,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkEvent, put,                  NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkEvent, set_screen,           arginfo_gdk_gdkevent_set_screen, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(GdkFont, __construct)
{
	char *font_name;
	zend_bool free_font_name = FALSE;

    phpg_gboxed_t *pobj = NULL;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &font_name, &free_font_name)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkFont);
	}

    pobj = zend_object_store_get_object(this_ptr TSRMLS_CC);
    pobj->gtype = GDK_TYPE_FONT;
    pobj->boxed = gdk_font_load(font_name);
	if (free_font_name) g_free(font_name);

	if (!pobj->boxed) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkFont);
	}
    pobj->free_on_destroy = TRUE;
}


PHPG_PROP_READER(GdkFont, type)
{
	long php_retval;

    php_retval = ((GdkFont *)((phpg_gboxed_t *)object)->boxed)->type;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkFont, ascent)
{
	long php_retval;

    php_retval = ((GdkFont *)((phpg_gboxed_t *)object)->boxed)->ascent;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkFont, descent)
{
	long php_retval;

    php_retval = ((GdkFont *)((phpg_gboxed_t *)object)->boxed)->descent;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


static prop_info_t gdkfont_prop_info[] = {
	{ "type", PHPG_PROP_READ_FN(GdkFont, type), NULL },
	{ "ascent", PHPG_PROP_READ_FN(GdkFont, ascent), NULL },
	{ "descent", PHPG_PROP_READ_FN(GdkFont, descent), NULL },
	{ NULL, NULL, NULL },
};


static PHP_METHOD(GdkFont, char_height)
{
	char character;
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "c", &character))
		return;

    php_retval = gdk_char_height((GdkFont *)PHPG_GBOXED(this_ptr), character);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkFont, char_measure)
{
	char character;
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "c", &character))
		return;

    php_retval = gdk_char_measure((GdkFont *)PHPG_GBOXED(this_ptr), character);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkFont, char_width)
{
	char character;
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "c", &character))
		return;

    php_retval = gdk_char_width((GdkFont *)PHPG_GBOXED(this_ptr), character);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkFont, get_display)
{
	GdkDisplay* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_font_get_display((GdkFont *)PHPG_GBOXED(this_ptr));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(GdkFont, id)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_font_id((GdkFont *)PHPG_GBOXED(this_ptr));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkFont, string_height)
{
	char *string;
	zend_bool free_string = FALSE;
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &string, &free_string))
		return;

    php_retval = gdk_string_height((GdkFont *)PHPG_GBOXED(this_ptr), string);
	if (free_string) g_free(string);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkFont, string_measure)
{
	char *string;
	zend_bool free_string = FALSE;
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &string, &free_string))
		return;

    php_retval = gdk_string_measure((GdkFont *)PHPG_GBOXED(this_ptr), string);
	if (free_string) g_free(string);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkFont, string_width)
{
	char *string;
	zend_bool free_string = FALSE;
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &string, &free_string))
		return;

    php_retval = gdk_string_width((GdkFont *)PHPG_GBOXED(this_ptr), string);
	if (free_string) g_free(string);
	RETVAL_LONG(php_retval);
}

#line 3045 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkFont, extents)
{
	char *text;
	int length, lbearing, rbearing, width, ascent, descent;

	NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "s#", &text, &length))
		return;

    gdk_text_extents((GdkFont *)PHPG_GBOXED(this_ptr), text, length, &lbearing, &rbearing, &width, &ascent, &descent);
    php_gtk_build_value(&return_value, "(iiiii)", lbearing, rbearing, width, ascent, descent);
}

#line 10387 "ext/gtk+/gen_gdk.c"



static PHP_METHOD(GdkFont, height)
{
	char *text;
	zend_bool free_text = FALSE;
	long text_length = -1, php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u|i", &text, &free_text, &text_length))
		return;

    php_retval = gdk_text_height((GdkFont *)PHPG_GBOXED(this_ptr), text, (gint)text_length);
	if (free_text) g_free(text);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkFont, measure)
{
	char *text;
	zend_bool free_text = FALSE;
	long text_length = -1, php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u|i", &text, &free_text, &text_length))
		return;

    php_retval = gdk_text_measure((GdkFont *)PHPG_GBOXED(this_ptr), text, (gint)text_length);
	if (free_text) g_free(text);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(GdkFont, width)
{
	char *text;
	zend_bool free_text = FALSE;
	long text_length = -1, php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u|i", &text, &free_text, &text_length))
		return;

    php_retval = gdk_text_width((GdkFont *)PHPG_GBOXED(this_ptr), text, (gint)text_length);
	if (free_text) g_free(text);
	RETVAL_LONG(php_retval);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkfont_font_load, 0)
    ZEND_ARG_INFO(0, font_name)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkfont_char_height, 0)
    ZEND_ARG_INFO(0, character)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkfont_char_measure, 0)
    ZEND_ARG_INFO(0, character)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkfont_char_width, 0)
    ZEND_ARG_INFO(0, character)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkfont_string_height, 0)
    ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkfont_string_measure, 0)
    ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkfont_string_width, 0)
    ZEND_ARG_INFO(0, string)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkfont_height, 0, 0, 1)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, text_length)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkfont_measure, 0, 0, 1)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, text_length)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkfont_width, 0, 0, 1)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, text_length)
ZEND_END_ARG_INFO();

static function_entry gdkfont_methods[] = {
	PHP_ME(GdkFont, __construct,          arginfo_gdk_gdkfont_font_load, ZEND_ACC_PUBLIC)
	PHP_ME(GdkFont, char_height,          arginfo_gdk_gdkfont_char_height, ZEND_ACC_PUBLIC)
	PHP_ME(GdkFont, char_measure,         arginfo_gdk_gdkfont_char_measure, ZEND_ACC_PUBLIC)
	PHP_ME(GdkFont, char_width,           arginfo_gdk_gdkfont_char_width, ZEND_ACC_PUBLIC)
	PHP_ME(GdkFont, extents,              NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkFont, get_display,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkFont, height,               arginfo_gdk_gdkfont_height, ZEND_ACC_PUBLIC)
	PHP_ME(GdkFont, id,                   NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GdkFont, measure,              arginfo_gdk_gdkfont_measure, ZEND_ACC_PUBLIC)
	PHP_ME(GdkFont, string_height,        arginfo_gdk_gdkfont_string_height, ZEND_ACC_PUBLIC)
	PHP_ME(GdkFont, string_measure,       arginfo_gdk_gdkfont_string_measure, ZEND_ACC_PUBLIC)
	PHP_ME(GdkFont, string_width,         arginfo_gdk_gdkfont_string_width, ZEND_ACC_PUBLIC)
	PHP_ME(GdkFont, width,                arginfo_gdk_gdkfont_width, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
#line 161 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkColor, __construct)
{
    guint red = 0;
    guint green = 0;
    guint blue = 0;
    guint pixel = 0;
    GdkColor color;
    phpg_gboxed_t *pobj = NULL;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "|iiii", &red, &green, &blue, &pixel))
        return;

    color.red = clamp_int(red, 0, MAX_INTENSITY);
    color.green = clamp_int(green, 0, MAX_INTENSITY);
    color.blue = clamp_int(blue, 0, MAX_INTENSITY);
    color.pixel = pixel;

    pobj = zend_object_store_get_object(this_ptr TSRMLS_CC);
    pobj->gtype = GDK_TYPE_COLOR;
    pobj->boxed = g_boxed_copy(GDK_TYPE_COLOR, &color);
    pobj->free_on_destroy = TRUE;
}

#line 10535 "ext/gtk+/gen_gdk.c"


#line 235 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkColor, pixel)
{
	RETVAL_LONG(((GdkColor *)((phpg_gboxed_t *)object)->boxed)->pixel);
    return SUCCESS;
}

#line 10545 "ext/gtk+/gen_gdk.c"


#line 214 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkColor, red)
{
	RETVAL_LONG(((GdkColor *)((phpg_gboxed_t *)object)->boxed)->red);
    return SUCCESS;
}
#line 10554 "ext/gtk+/gen_gdk.c"


#line 221 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkColor, green)
{
	RETVAL_LONG(((GdkColor *)((phpg_gboxed_t *)object)->boxed)->green);
    return SUCCESS;
}
#line 10563 "ext/gtk+/gen_gdk.c"


#line 228 "ext/gtk+/gdk.overrides"
PHPG_PROP_READER(GdkColor, blue)
{
	RETVAL_LONG(((GdkColor *)((phpg_gboxed_t *)object)->boxed)->blue);
    return SUCCESS;
}
#line 10572 "ext/gtk+/gen_gdk.c"



static prop_info_t gdkcolor_prop_info[] = {
	{ "pixel", PHPG_PROP_READ_FN(GdkColor, pixel), NULL },
	{ "red", PHPG_PROP_READ_FN(GdkColor, red), NULL },
	{ "green", PHPG_PROP_READ_FN(GdkColor, green), NULL },
	{ "blue", PHPG_PROP_READ_FN(GdkColor, blue), NULL },
	{ NULL, NULL, NULL },
};

#line 243 "ext/gtk+/gdk.overrides"
void phpg_gdkcolor_write_property_handler(zval *object, zval *member, zval *value TSRMLS_DC)
{
    zval tmp_value;
	zval tmp_member;
    GdkColor *color;

 	if (member->type != IS_STRING) {
		tmp_member = *member;
		zval_copy_ctor(&tmp_member);
		convert_to_string(&tmp_member);
		member = &tmp_member;
	}

    if (value->type != IS_LONG) {
        tmp_value = *value;
        zval_copy_ctor(&tmp_value);
        convert_to_long(&tmp_value);
        value = &tmp_value;
    }

    color = (GdkColor *)PHPG_GBOXED(object);
    if (!strcmp(Z_STRVAL_P(member), "pixel")) {
        color->pixel = Z_LVAL_P(value);
    } else {
        if (!strcmp(Z_STRVAL_P(member), "red")) {
            color->red = clamp_int(Z_LVAL_P(value), 0, MAX_INTENSITY);
        } else if (!strcmp(Z_STRVAL_P(member), "green")) {
            color->green = clamp_int(Z_LVAL_P(value), 0, MAX_INTENSITY);
        } else if (!strcmp(Z_STRVAL_P(member), "blue")) {
            color->blue = clamp_int(Z_LVAL_P(value), 0, MAX_INTENSITY);
        }
    }

	if (member == &tmp_member) {
		zval_dtor(member);
	}
	if (value == &tmp_value) {
		zval_dtor(value);
	}
}

#line 10626 "ext/gtk+/gen_gdk.c"


#line 286 "ext/gtk+/gdk.overrides"
HashTable* phpg_gdkcolor_get_properties_handler(zval *object TSRMLS_DC)
{
    phpg_head_t *poh = NULL;
    poh = (phpg_head_t *) zend_object_store_get_object(object TSRMLS_CC);
    phpg_get_properties_helper(object, poh->zobj.properties TSRMLS_CC,
                               STRS(red), STRS(green), STRS(blue), STRS(pixel), NULL);

	return poh->zobj.properties;
}

#line 10640 "ext/gtk+/gen_gdk.c"



static zend_object_handlers gdkcolor_object_handlers;

static zend_object_value phpg_create_gdkcolor(zend_class_entry *ce TSRMLS_DC)
{
    zend_object_value zov;

    zov = phpg_create_gboxed(ce TSRMLS_CC);
    zov.handlers = &gdkcolor_object_handlers;

    return zov;
}
#line 194 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkColor, parse)
{
	gchar *color_spec;
	GdkColor color;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "s", &color_spec)) {
		return;
	}

	if (gdk_color_parse(color_spec, &color)) {
        phpg_gboxed_new(&return_value, GDK_TYPE_COLOR, &color, TRUE, TRUE TSRMLS_CC);
    } else {
        php_error(E_WARNING, "%s::%s() could not parse color spec '%s'",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C), color_spec);
        RETURN_FALSE;
    }
}

#line 10674 "ext/gtk+/gen_gdk.c"


static
ZEND_BEGIN_ARG_INFO_EX(arginfo_gdk_gdkcolor_gdk_color_new, 0, 0, 0)
    ZEND_ARG_INFO(0, red)
    ZEND_ARG_INFO(0, blue)
    ZEND_ARG_INFO(0, green)
    ZEND_ARG_INFO(0, allocated)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkcolor_color_parse, 0)
    ZEND_ARG_INFO(0, color)
ZEND_END_ARG_INFO();



static function_entry gdkcolor_methods[] = {
	PHP_ME(GdkColor, __construct,          arginfo_gdk_gdkcolor_gdk_color_new, ZEND_ACC_PUBLIC)
	PHP_ME(GdkColor, parse,          arginfo_gdk_gdkcolor_color_parse, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(GdkCursor, __construct)
{
	GdkCursorType cursor_type;
	zval *php_cursor_type = NULL;

    phpg_gboxed_t *pobj = NULL;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_cursor_type)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkCursor);
	}

	if (php_cursor_type && phpg_gvalue_get_enum(GDK_TYPE_CURSOR_TYPE, php_cursor_type, (gint *)&cursor_type) == FAILURE) {
		PHPG_THROW_CONSTRUCT_EXCEPTION(GdkCursor);
	}

    pobj = zend_object_store_get_object(this_ptr TSRMLS_CC);
    pobj->gtype = GDK_TYPE_CURSOR;
    pobj->boxed = gdk_cursor_new(cursor_type);

	if (!pobj->boxed) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkCursor);
	}
    pobj->free_on_destroy = TRUE;
}


static PHP_METHOD(GdkCursor, new_for_display)
{
	zval *display, *php_cursor_type = NULL;
	GdkCursorType cursor_type;
	GdkCursor *wrapped_obj = NULL;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OV", &display, gdkdisplay_ce, &php_cursor_type)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkCursor);
	}

	if (php_cursor_type && phpg_gvalue_get_enum(GDK_TYPE_CURSOR_TYPE, php_cursor_type, (gint *)&cursor_type) == FAILURE) {
		PHPG_THROW_CONSTRUCT_EXCEPTION(GdkCursor);
	}

    wrapped_obj = gdk_cursor_new_for_display(GDK_DISPLAY(PHPG_GOBJECT(display)), cursor_type);

	if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkCursor);
	}
    phpg_gboxed_new(&return_value, GDK_TYPE_CURSOR, wrapped_obj, FALSE, TRUE TSRMLS_CC);
}


static PHP_METHOD(GdkCursor, new_from_pixbuf)
{
	zval *display, *source;
	long x, y;
	GdkCursor *wrapped_obj = NULL;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OOii", &display, gdkdisplay_ce, &source, gdkpixbuf_ce, &x, &y)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkCursor);
	}

    wrapped_obj = gdk_cursor_new_from_pixbuf(GDK_DISPLAY(PHPG_GOBJECT(display)), GDK_PIXBUF(PHPG_GOBJECT(source)), (gint)x, (gint)y);

	if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkCursor);
	}
    phpg_gboxed_new(&return_value, GDK_TYPE_CURSOR, wrapped_obj, FALSE, TRUE TSRMLS_CC);
}


static PHP_METHOD(GdkCursor, new_from_pixmap)
{
	zval *source, *mask, *php_fg, *php_bg;
	GdkColor *fg = NULL, *bg = NULL;
	long x, y;
	GdkCursor *wrapped_obj = NULL;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OOOOii", &source, gdkpixmap_ce, &mask, gdkpixmap_ce, &php_fg, gboxed_ce, &php_bg, gboxed_ce, &x, &y)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkCursor);
	}

    if (phpg_gboxed_check(php_fg, GDK_TYPE_COLOR, FALSE TSRMLS_CC)) {
        fg = (GdkColor *) PHPG_GBOXED(php_fg);
    } else {
        php_error(E_WARNING, "%s::%s() expects fg argument to be a valid GdkColor object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkCursor);
    }

    if (phpg_gboxed_check(php_bg, GDK_TYPE_COLOR, FALSE TSRMLS_CC)) {
        bg = (GdkColor *) PHPG_GBOXED(php_bg);
    } else {
        php_error(E_WARNING, "%s::%s() expects bg argument to be a valid GdkColor object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkCursor);
    }

    wrapped_obj = gdk_cursor_new_from_pixmap(GDK_PIXMAP(PHPG_GOBJECT(source)), GDK_PIXMAP(PHPG_GOBJECT(mask)), fg, bg, (gint)x, (gint)y);

	if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkCursor);
	}
    phpg_gboxed_new(&return_value, GDK_TYPE_CURSOR, wrapped_obj, FALSE, TRUE TSRMLS_CC);
}


PHPG_PROP_READER(GdkCursor, type)
{
	long php_retval;

    php_retval = ((GdkCursor *)((phpg_gboxed_t *)object)->boxed)->type;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


static prop_info_t gdkcursor_prop_info[] = {
	{ "type", PHPG_PROP_READ_FN(GdkCursor, type), NULL },
	{ NULL, NULL, NULL },
};


static PHP_METHOD(GdkCursor, get_display)
{
	GdkDisplay* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = gdk_cursor_get_display((GdkCursor *)PHPG_GBOXED(this_ptr));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkcursor_cursor_new, 0)
    ZEND_ARG_INFO(0, cursor_type)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkcursor_cursor_new_for_display, 0)
    ZEND_ARG_OBJ_INFO(0, display, GdkDisplay, 1)
    ZEND_ARG_INFO(0, cursor_type)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkcursor_cursor_new_from_pixbuf, 0)
    ZEND_ARG_OBJ_INFO(0, display, GdkDisplay, 1)
    ZEND_ARG_OBJ_INFO(0, source, GdkPixbuf, 1)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkcursor_cursor_new_from_pixmap, 0)
    ZEND_ARG_OBJ_INFO(0, source, GdkPixmap, 1)
    ZEND_ARG_OBJ_INFO(0, mask, GdkPixmap, 1)
    ZEND_ARG_OBJ_INFO(0, fg, GdkColor, 1)
    ZEND_ARG_OBJ_INFO(0, bg, GdkColor, 1)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO();

static function_entry gdkcursor_methods[] = {
	PHP_ME(GdkCursor, __construct,          arginfo_gdk_gdkcursor_cursor_new, ZEND_ACC_PUBLIC)
	PHP_ME(GdkCursor, new_for_display,      arginfo_gdk_gdkcursor_cursor_new_for_display, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkCursor, new_from_pixbuf,      arginfo_gdk_gdkcursor_cursor_new_from_pixbuf, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkCursor, new_from_pixmap,      arginfo_gdk_gdkcursor_cursor_new_from_pixmap, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GdkCursor, get_display,          NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
#line 2704 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkRectangle, __construct)
{
    phpg_gboxed_t *pobj = NULL;
    GdkRectangle rect = { 0, 0, 0, 0 };

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iiii", &(rect.x), &(rect.y),
                            &(rect.width), &(rect.height))) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GdkRectangle);
    }

    pobj = zend_object_store_get_object(this_ptr TSRMLS_CC);
    pobj->gtype = GDK_TYPE_RECTANGLE;
    pobj->boxed = g_boxed_copy(GDK_TYPE_RECTANGLE, &rect);
    pobj->free_on_destroy = TRUE;
}

#line 10886 "ext/gtk+/gen_gdk.c"



PHPG_PROP_READER(GdkRectangle, x)
{
	long php_retval;

    php_retval = ((GdkRectangle *)((phpg_gboxed_t *)object)->boxed)->x;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkRectangle, y)
{
	long php_retval;

    php_retval = ((GdkRectangle *)((phpg_gboxed_t *)object)->boxed)->y;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkRectangle, width)
{
	long php_retval;

    php_retval = ((GdkRectangle *)((phpg_gboxed_t *)object)->boxed)->width;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(GdkRectangle, height)
{
	long php_retval;

    php_retval = ((GdkRectangle *)((phpg_gboxed_t *)object)->boxed)->height;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


static prop_info_t gdkrectangle_prop_info[] = {
	{ "x", PHPG_PROP_READ_FN(GdkRectangle, x), NULL },
	{ "y", PHPG_PROP_READ_FN(GdkRectangle, y), NULL },
	{ "width", PHPG_PROP_READ_FN(GdkRectangle, width), NULL },
	{ "height", PHPG_PROP_READ_FN(GdkRectangle, height), NULL },
	{ NULL, NULL, NULL },
};

#line 2729 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkRectangle, intersect)
{
    GdkRectangle rect, dest;
    zval *php_rect;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_rect TSRMLS_CC))
		return;

    if (phpg_rectangle_from_zval(php_rect, &rect TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects area argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    if (gdk_rectangle_intersect((GdkRectangle*)PHPG_GBOXED(this_ptr), &rect, &dest)) {
        phpg_gboxed_new(&return_value, GDK_TYPE_RECTANGLE, &dest, TRUE, TRUE TSRMLS_CC);
    } else {
        RETURN_FALSE;
    }
}

#line 10961 "ext/gtk+/gen_gdk.c"


#line 2760 "ext/gtk+/gdk.overrides"
static PHP_METHOD(GdkRectangle, union)
{
    GdkRectangle rect, dest;
    zval *php_rect;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_rect))
		return;

    if (phpg_rectangle_from_zval(php_rect, &rect TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects area argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    gdk_rectangle_union((GdkRectangle*)PHPG_GBOXED(this_ptr), &rect, &dest);
    phpg_gboxed_new(&return_value, GDK_TYPE_RECTANGLE, &dest, TRUE, TRUE TSRMLS_CC);
}

#line 10984 "ext/gtk+/gen_gdk.c"


static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkrectangle_gdk_rectangle_new, 0)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkrectangle_intersect, 0)
    ZEND_ARG_OBJ_INFO(0, rect, GdkRectangle, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_gdk_gdkrectangle_union, 0)
    ZEND_ARG_OBJ_INFO(0, rect, GdkRectangle, 1)
ZEND_END_ARG_INFO();


static function_entry gdkrectangle_methods[] = {
	PHP_ME(GdkRectangle, __construct,          arginfo_gdk_gdkrectangle_gdk_rectangle_new, ZEND_ACC_PUBLIC)
	PHP_ME(GdkRectangle, intersect,            arginfo_gdk_gdkrectangle_intersect, ZEND_ACC_PUBLIC)
	PHP_ME(GdkRectangle, union,                arginfo_gdk_gdkrectangle_union, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

void phpg_gdk_register_classes(void)
{
	TSRMLS_FETCH();

	gdk_ce = phpg_register_class("Gdk", gdk_methods, NULL, 0, NULL, NULL, 0 TSRMLS_CC);

	gdkcolormap_ce = phpg_register_class("GdkColormap", gdkcolormap_methods, gobject_ce, 0, NULL, NULL, GDK_TYPE_COLORMAP TSRMLS_CC);

	gdkdevice_ce = phpg_register_class("GdkDevice", gdkdevice_methods, gobject_ce, 0, gdkdevice_prop_info, NULL, GDK_TYPE_DEVICE TSRMLS_CC);

	gdkdisplay_ce = phpg_register_class("GdkDisplay", gdkdisplay_methods, gobject_ce, 0, NULL, NULL, GDK_TYPE_DISPLAY TSRMLS_CC);

	gdkdisplaymanager_ce = phpg_register_class("GdkDisplayManager", gdkdisplaymanager_methods, gobject_ce, 0, NULL, NULL, GDK_TYPE_DISPLAY_MANAGER TSRMLS_CC);

	gdkdragcontext_ce = phpg_register_class("GdkDragContext", gdkdragcontext_methods, gobject_ce, 0, gdkdragcontext_prop_info, NULL, GDK_TYPE_DRAG_CONTEXT TSRMLS_CC);

	gdkdrawable_ce = phpg_register_class("GdkDrawable", gdkdrawable_methods, gobject_ce, 0, gdkdrawable_prop_info, NULL, GDK_TYPE_DRAWABLE TSRMLS_CC);

	gdkwindow_ce = phpg_register_class("GdkWindow", gdkwindow_methods, gdkdrawable_ce, 0, NULL, NULL, GDK_TYPE_WINDOW TSRMLS_CC);

	gdkpixmap_ce = phpg_register_class("GdkPixmap", gdkpixmap_methods, gdkdrawable_ce, 0, NULL, NULL, GDK_TYPE_PIXMAP TSRMLS_CC);

	gdkgc_ce = phpg_register_class("GdkGC", gdkgc_methods, gobject_ce, 0, gdkgc_prop_info, NULL, GDK_TYPE_GC TSRMLS_CC);

	gdkimage_ce = phpg_register_class("GdkImage", gdkimage_methods, gobject_ce, 0, NULL, NULL, GDK_TYPE_IMAGE TSRMLS_CC);

	gdkkeymap_ce = phpg_register_class("GdkKeymap", gdkkeymap_methods, gobject_ce, 0, NULL, NULL, GDK_TYPE_KEYMAP TSRMLS_CC);

	gdkpixbuf_ce = phpg_register_class("GdkPixbuf", gdkpixbuf_methods, gobject_ce, 0, NULL, NULL, GDK_TYPE_PIXBUF TSRMLS_CC);

	gdkpixbufanimation_ce = phpg_register_class("GdkPixbufAnimation", gdkpixbufanimation_methods, gobject_ce, 0, NULL, NULL, GDK_TYPE_PIXBUF_ANIMATION TSRMLS_CC);

	gdkpixbufanimationiter_ce = phpg_register_class("GdkPixbufAnimationIter", gdkpixbufanimationiter_methods, gobject_ce, 0, NULL, NULL, GDK_TYPE_PIXBUF_ANIMATION_ITER TSRMLS_CC);

	gdkpixbufloader_ce = phpg_register_class("GdkPixbufLoader", gdkpixbufloader_methods, gobject_ce, 0, NULL, NULL, GDK_TYPE_PIXBUF_LOADER TSRMLS_CC);

	gdkscreen_ce = phpg_register_class("GdkScreen", gdkscreen_methods, gobject_ce, 0, NULL, NULL, GDK_TYPE_SCREEN TSRMLS_CC);

	gdkvisual_ce = phpg_register_class("GdkVisual", gdkvisual_methods, gobject_ce, 0, gdkvisual_prop_info, NULL, GDK_TYPE_VISUAL TSRMLS_CC);

    gdkevent_ce = phpg_register_boxed("GdkEvent", gdkevent_methods, NULL, phpg_create_gdkevent, GDK_TYPE_EVENT TSRMLS_CC);
	gdkevent_object_handlers = php_gtk_handlers;
	gdkevent_object_handlers.read_property = phpg_gdkevent_read_property_handler;
	gdkevent_object_handlers.get_properties = phpg_gdkevent_get_properties_handler;

    gdkfont_ce = phpg_register_boxed("GdkFont", gdkfont_methods, gdkfont_prop_info, NULL, GDK_TYPE_FONT TSRMLS_CC);

    gdkcolor_ce = phpg_register_boxed("GdkColor", gdkcolor_methods, gdkcolor_prop_info, phpg_create_gdkcolor, GDK_TYPE_COLOR TSRMLS_CC);
	gdkcolor_object_handlers = php_gtk_handlers;
	gdkcolor_object_handlers.write_property = phpg_gdkcolor_write_property_handler;
	gdkcolor_object_handlers.get_properties = phpg_gdkcolor_get_properties_handler;

    gdkcursor_ce = phpg_register_boxed("GdkCursor", gdkcursor_methods, gdkcursor_prop_info, NULL, GDK_TYPE_CURSOR TSRMLS_CC);

    gdkrectangle_ce = phpg_register_boxed("GdkRectangle", gdkrectangle_methods, gdkrectangle_prop_info, NULL, GDK_TYPE_RECTANGLE TSRMLS_CC);
}

void phpg_gdk_register_constants(const char *strip_prefix)
{
    TSRMLS_FETCH();
	phpg_register_enum(GDK_TYPE_COLORSPACE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_CURSOR_TYPE, strip_prefix, gdk_ce);
	phpg_register_flags(GDK_TYPE_DRAG_ACTION, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_DRAG_PROTOCOL, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_FILTER_RETURN, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_EVENT_TYPE, strip_prefix, gdk_ce);
	phpg_register_flags(GDK_TYPE_EVENT_MASK, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_VISIBILITY_STATE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_SCROLL_DIRECTION, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_NOTIFY_TYPE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_CROSSING_MODE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_PROPERTY_STATE, strip_prefix, gdk_ce);
	phpg_register_flags(GDK_TYPE_WINDOW_STATE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_SETTING_ACTION, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_FONT_TYPE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_CAP_STYLE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_FILL, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_FUNCTION, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_JOIN_STYLE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_LINE_STYLE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_SUBWINDOW_MODE, strip_prefix, gdk_ce);
	phpg_register_flags(GDK_TYPE_GC_VALUES_MASK, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_IMAGE_TYPE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_EXTENSION_MODE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_INPUT_SOURCE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_INPUT_MODE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_AXIS_USE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_PROP_MODE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_FILL_RULE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_OVERLAP_TYPE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_RGB_DITHER, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_BYTE_ORDER, strip_prefix, gdk_ce);
	phpg_register_flags(GDK_TYPE_MODIFIER_TYPE, strip_prefix, gdk_ce);
	phpg_register_flags(GDK_TYPE_INPUT_CONDITION, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_STATUS, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_GRAB_STATUS, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_VISUAL_TYPE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_WINDOW_CLASS, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_WINDOW_TYPE, strip_prefix, gdk_ce);
	phpg_register_flags(GDK_TYPE_WINDOW_ATTRIBUTES_TYPE, strip_prefix, gdk_ce);
	phpg_register_flags(GDK_TYPE_WINDOW_HINTS, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_WINDOW_TYPE_HINT, strip_prefix, gdk_ce);
	phpg_register_flags(GDK_TYPE_WM_DECORATION, strip_prefix, gdk_ce);
	phpg_register_flags(GDK_TYPE_WM_FUNCTION, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_GRAVITY, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_WINDOW_EDGE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_PIXBUF_ALPHA_MODE, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_PIXBUF_ERROR, strip_prefix, gdk_ce);
	phpg_register_enum(GDK_TYPE_INTERP_TYPE, strip_prefix, gdk_ce);


    /* register gtype constants for all classes */

	phpg_register_int_constant(gdkcolormap_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_COLORMAP);
	phpg_register_int_constant(gdkdevice_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_DEVICE);
	phpg_register_int_constant(gdkdisplay_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_DISPLAY);
	phpg_register_int_constant(gdkdisplaymanager_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_DISPLAY_MANAGER);
	phpg_register_int_constant(gdkdragcontext_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_DRAG_CONTEXT);
	phpg_register_int_constant(gdkdrawable_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_DRAWABLE);
	phpg_register_int_constant(gdkwindow_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_WINDOW);
	phpg_register_int_constant(gdkpixmap_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_PIXMAP);
	phpg_register_int_constant(gdkgc_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_GC);
	phpg_register_int_constant(gdkimage_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_IMAGE);
	phpg_register_int_constant(gdkkeymap_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_KEYMAP);
	phpg_register_int_constant(gdkpixbuf_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_PIXBUF);
	phpg_register_int_constant(gdkpixbufanimation_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_PIXBUF_ANIMATION);
	phpg_register_int_constant(gdkpixbufanimationiter_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_PIXBUF_ANIMATION_ITER);
	phpg_register_int_constant(gdkpixbufloader_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_PIXBUF_LOADER);
	phpg_register_int_constant(gdkscreen_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_SCREEN);
	phpg_register_int_constant(gdkvisual_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_VISUAL);
	phpg_register_int_constant(gdkevent_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_EVENT);
	phpg_register_int_constant(gdkfont_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_FONT);
	phpg_register_int_constant(gdkcolor_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_COLOR);
	phpg_register_int_constant(gdkcursor_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_CURSOR);
	phpg_register_int_constant(gdkrectangle_ce, "gtype", sizeof("gtype")-1, GDK_TYPE_RECTANGLE);

}

#endif /* HAVE_PHP_GTK */
