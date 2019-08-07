#include "php_gtk.h"

#if HAVE_PHP_GTK
#define PANGO_ENABLE_BACKEND
#define PANGO_ENABLE_ENGINE
#include <pango/pango.h>


PHP_GTK_EXPORT_CE(pangocontext_ce);
PHP_GTK_EXPORT_CE(pangofont_ce);
PHP_GTK_EXPORT_CE(pangofontface_ce);
PHP_GTK_EXPORT_CE(pangofontfamily_ce);
PHP_GTK_EXPORT_CE(pangofontmap_ce);
PHP_GTK_EXPORT_CE(pangofontset_ce);
PHP_GTK_EXPORT_CE(pangofontsetsimple_ce);
PHP_GTK_EXPORT_CE(pangolayout_ce);
PHP_GTK_EXPORT_CE(pangoattrlist_ce);
PHP_GTK_EXPORT_CE(pangocolor_ce);
PHP_GTK_EXPORT_CE(pangofontdescription_ce);
PHP_GTK_EXPORT_CE(pangofontmetrics_ce);
PHP_GTK_EXPORT_CE(pangoglyphstring_ce);
PHP_GTK_EXPORT_CE(pangolanguage_ce);
PHP_GTK_EXPORT_CE(pangolayoutiter_ce);
PHP_GTK_EXPORT_CE(pangotabarray_ce);
PHP_GTK_EXPORT_CE(pango_ce);

static PHP_METHOD(Pango, attr_type_register)
{
	char *name;
	zend_bool free_name = FALSE;
	long php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &name, &free_name))
		return;

    php_retval = pango_attr_type_register(name);
	if (free_name) g_free(name);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(Pango, PIXELS)
{
	long size, php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &size))
		return;

    php_retval = PANGO_PIXELS((gint)size);
	RETVAL_LONG(php_retval);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pango_pango_attr_type_register, 0)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pango_PIXELS, 0)
    ZEND_ARG_INFO(0, size)
ZEND_END_ARG_INFO();

static function_entry pango_methods[] = {
	PHP_ME(Pango, PIXELS,               arginfo_pango_pango_PIXELS, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Pango, attr_type_register, arginfo_pango_pango_pango_attr_type_register, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(PangoContext, __construct)
{
    GObject *wrapped_obj;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "")) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoContext);
    }


    wrapped_obj = (GObject *) g_object_newv(phpg_gtype_from_zval(this_ptr), 0, NULL);

    if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoContext);
    }

    phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}


static PHP_METHOD(PangoContext, add_font_map)
{
	zval *font_map;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &font_map, pangofontmap_ce))
		return;

    pango_context_set_font_map(PANGO_CONTEXT(PHPG_GOBJECT(this_ptr)), PANGO_FONT_MAP(PHPG_GOBJECT(font_map)));

}


static PHP_METHOD(PangoContext, load_font)
{
	PangoFontDescription *desc = NULL;
	zval *php_desc;
	PangoFont* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_desc, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_desc, PANGO_TYPE_FONT_DESCRIPTION, FALSE TSRMLS_CC)) {
        desc = (PangoFontDescription *) PHPG_GBOXED(php_desc);
    } else {
        php_error(E_WARNING, "%s::%s() expects desc argument to be a valid PangoFontDescription object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    php_retval = pango_context_load_font(PANGO_CONTEXT(PHPG_GOBJECT(this_ptr)), desc);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(PangoContext, load_fontset)
{
	PangoFontDescription *desc = NULL;
	zval *php_desc, *php_language;
	PangoLanguage *language = NULL;
	PangoFontset* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OO", &php_desc, gboxed_ce, &php_language, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_desc, PANGO_TYPE_FONT_DESCRIPTION, FALSE TSRMLS_CC)) {
        desc = (PangoFontDescription *) PHPG_GBOXED(php_desc);
    } else {
        php_error(E_WARNING, "%s::%s() expects desc argument to be a valid PangoFontDescription object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    if (phpg_gboxed_check(php_language, PANGO_TYPE_LANGUAGE, FALSE TSRMLS_CC)) {
        language = (PangoLanguage *) PHPG_GBOXED(php_language);
    } else {
        php_error(E_WARNING, "%s::%s() expects language argument to be a valid PangoLanguage object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    php_retval = pango_context_load_fontset(PANGO_CONTEXT(PHPG_GOBJECT(this_ptr)), desc, language);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(PangoContext, get_metrics)
{
	PangoFontDescription *desc = NULL;
	zval *php_desc, *php_language = NULL;
	PangoLanguage *language = NULL;
	PangoFontMetrics *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O|N", &php_desc, gboxed_ce, &php_language, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_desc, PANGO_TYPE_FONT_DESCRIPTION, FALSE TSRMLS_CC)) {
        desc = (PangoFontDescription *) PHPG_GBOXED(php_desc);
    } else {
        php_error(E_WARNING, "%s::%s() expects desc argument to be a valid PangoFontDescription object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    if (php_language) {
        if (Z_TYPE_P(php_language) == IS_NULL) {
            language = NULL;
        } else {
            if (phpg_gboxed_check(php_language, PANGO_TYPE_LANGUAGE, FALSE TSRMLS_CC)) {
                language = (PangoLanguage *) PHPG_GBOXED(php_language);
            } else {
                php_error(E_WARNING, "%s::%s() expects language argument to be a valid PangoLanguage object or null", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
                return;
            }
        }
    }

    php_retval = pango_context_get_metrics(PANGO_CONTEXT(PHPG_GOBJECT(this_ptr)), desc, language);
	phpg_gboxed_new(&return_value, PANGO_TYPE_FONT_METRICS, php_retval, FALSE, TRUE TSRMLS_CC);

}


static PHP_METHOD(PangoContext, set_font_description)
{
	PangoFontDescription *desc = NULL;
	zval *php_desc;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_desc, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_desc, PANGO_TYPE_FONT_DESCRIPTION, FALSE TSRMLS_CC)) {
        desc = (PangoFontDescription *) PHPG_GBOXED(php_desc);
    } else {
        php_error(E_WARNING, "%s::%s() expects desc argument to be a valid PangoFontDescription object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    pango_context_set_font_description(PANGO_CONTEXT(PHPG_GOBJECT(this_ptr)), desc);

}


static PHP_METHOD(PangoContext, get_font_description)
{
	PangoFontDescription *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_context_get_font_description(PANGO_CONTEXT(PHPG_GOBJECT(this_ptr)));
	phpg_gboxed_new(&return_value, PANGO_TYPE_FONT_DESCRIPTION, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(PangoContext, get_language)
{
	PangoLanguage *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_context_get_language(PANGO_CONTEXT(PHPG_GOBJECT(this_ptr)));
	phpg_gboxed_new(&return_value, PANGO_TYPE_LANGUAGE, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(PangoContext, set_language)
{
	PangoLanguage *language = NULL;
	zval *php_language;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_language, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_language, PANGO_TYPE_LANGUAGE, FALSE TSRMLS_CC)) {
        language = (PangoLanguage *) PHPG_GBOXED(php_language);
    } else {
        php_error(E_WARNING, "%s::%s() expects language argument to be a valid PangoLanguage object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    pango_context_set_language(PANGO_CONTEXT(PHPG_GOBJECT(this_ptr)), language);

}


static PHP_METHOD(PangoContext, set_base_dir)
{
	PangoDirection direction;
	zval *php_direction = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_direction))
		return;

	if (php_direction && phpg_gvalue_get_enum(PANGO_TYPE_DIRECTION, php_direction, (gint *)&direction) == FAILURE) {
		return;
	}

    pango_context_set_base_dir(PANGO_CONTEXT(PHPG_GOBJECT(this_ptr)), direction);

}


static PHP_METHOD(PangoContext, get_base_dir)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_context_get_base_dir(PANGO_CONTEXT(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangocontext_add_font_map, 0)
    ZEND_ARG_OBJ_INFO(0, font_map, PangoFontMap, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangocontext_load_font, 0)
    ZEND_ARG_OBJ_INFO(0, desc, PangoFontDescription, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangocontext_load_fontset, 0)
    ZEND_ARG_OBJ_INFO(0, desc, PangoFontDescription, 1)
    ZEND_ARG_OBJ_INFO(0, language, PangoLanguage, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_pango_pangocontext_get_metrics, 0, 0, 1)
    ZEND_ARG_OBJ_INFO(0, desc, PangoFontDescription, 1)
    ZEND_ARG_OBJ_INFO(0, language, PangoLanguage, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangocontext_set_font_description, 0)
    ZEND_ARG_OBJ_INFO(0, desc, PangoFontDescription, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangocontext_set_language, 0)
    ZEND_ARG_OBJ_INFO(0, language, PangoLanguage, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangocontext_set_base_dir, 0)
    ZEND_ARG_INFO(0, direction)
ZEND_END_ARG_INFO();

static function_entry pangocontext_methods[] = {
	PHP_ME(PangoContext, __construct,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoContext, add_font_map,         arginfo_pango_pangocontext_add_font_map, ZEND_ACC_PUBLIC)
	PHP_ME(PangoContext, get_base_dir,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoContext, get_font_description, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoContext, get_language,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoContext, get_metrics,          arginfo_pango_pangocontext_get_metrics, ZEND_ACC_PUBLIC)
	PHP_ME(PangoContext, load_font,            arginfo_pango_pangocontext_load_font, ZEND_ACC_PUBLIC)
	PHP_ME(PangoContext, load_fontset,         arginfo_pango_pangocontext_load_fontset, ZEND_ACC_PUBLIC)
	PHP_ME(PangoContext, set_base_dir,         arginfo_pango_pangocontext_set_base_dir, ZEND_ACC_PUBLIC)
	PHP_ME(PangoContext, set_font_description, arginfo_pango_pangocontext_set_font_description, ZEND_ACC_PUBLIC)
	PHP_ME(PangoContext, set_language,         arginfo_pango_pangocontext_set_language, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(PangoFont, describe)
{
	PangoFontDescription *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_describe(PANGO_FONT(PHPG_GOBJECT(this_ptr)));
	phpg_gboxed_new(&return_value, PANGO_TYPE_FONT_DESCRIPTION, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(PangoFont, get_metrics)
{
	PangoLanguage *language = NULL;
	zval *php_language = NULL;
	PangoFontMetrics *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "|N", &php_language, gboxed_ce))
		return;

    if (php_language) {
        if (Z_TYPE_P(php_language) == IS_NULL) {
            language = NULL;
        } else {
            if (phpg_gboxed_check(php_language, PANGO_TYPE_LANGUAGE, FALSE TSRMLS_CC)) {
                language = (PangoLanguage *) PHPG_GBOXED(php_language);
            } else {
                php_error(E_WARNING, "%s::%s() expects language argument to be a valid PangoLanguage object or null", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
                return;
            }
        }
    }

    php_retval = pango_font_get_metrics(PANGO_FONT(PHPG_GOBJECT(this_ptr)), language);
	phpg_gboxed_new(&return_value, PANGO_TYPE_FONT_METRICS, php_retval, TRUE, TRUE TSRMLS_CC);

}


static
ZEND_BEGIN_ARG_INFO_EX(arginfo_pango_pangofont_get_metrics, 0, 0, 0)
    ZEND_ARG_OBJ_INFO(0, language, PangoLanguage, 1)
ZEND_END_ARG_INFO();

static function_entry pangofont_methods[] = {
	PHP_ME(PangoFont, describe,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFont, get_metrics,          arginfo_pango_pangofont_get_metrics, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(PangoFontFace, describe)
{
	PangoFontDescription *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_face_describe(PANGO_FONT_FACE(PHPG_GOBJECT(this_ptr)));
	phpg_gboxed_new(&return_value, PANGO_TYPE_FONT_DESCRIPTION, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(PangoFontFace, get_face_name)
{
	const gchar *php_retval;
	gchar *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_face_get_face_name(PANGO_FONT_FACE(PHPG_GOBJECT(this_ptr)));
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

#line 64 "ext/gtk+/pango.overrides"
static PHP_METHOD(PangoFontFace, list_sizes)
{
    int *sizes, n_sizes, i;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    pango_font_face_list_sizes(PANGO_FONT_FACE(PHPG_GOBJECT(this_ptr)), &sizes, &n_sizes);

    array_init(return_value);
    for (i = 0; i < n_sizes; i++) {
        add_next_index_long(return_value, sizes[i]);
    }

    g_free(sizes);
}

#line 479 "ext/gtk+/gen_pango.c"



static function_entry pangofontface_methods[] = {
	PHP_ME(PangoFontFace, describe,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontFace, get_face_name,        NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontFace, list_sizes,           NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(PangoFontFamily, get_name)
{
	const gchar *php_retval;
	gchar *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_family_get_name(PANGO_FONT_FAMILY(PHPG_GOBJECT(this_ptr)));
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


static PHP_METHOD(PangoFontFamily, is_monospace)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_family_is_monospace(PANGO_FONT_FAMILY(PHPG_GOBJECT(this_ptr)));
	RETVAL_BOOL(php_retval);
}


static function_entry pangofontfamily_methods[] = {
	PHP_ME(PangoFontFamily, get_name,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontFamily, is_monospace,         NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(PangoFontMap, load_font)
{
	zval *context, *php_desc;
	PangoFontDescription *desc = NULL;
	PangoFont* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OO", &context, pangocontext_ce, &php_desc, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_desc, PANGO_TYPE_FONT_DESCRIPTION, FALSE TSRMLS_CC)) {
        desc = (PangoFontDescription *) PHPG_GBOXED(php_desc);
    } else {
        php_error(E_WARNING, "%s::%s() expects desc argument to be a valid PangoFontDescription object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    php_retval = pango_font_map_load_font(PANGO_FONT_MAP(PHPG_GOBJECT(this_ptr)), PANGO_CONTEXT(PHPG_GOBJECT(context)), desc);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(PangoFontMap, load_fontset)
{
	zval *context, *php_desc, *php_language;
	PangoFontDescription *desc = NULL;
	PangoLanguage *language = NULL;
	PangoFontset* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OOO", &context, pangocontext_ce, &php_desc, gboxed_ce, &php_language, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_desc, PANGO_TYPE_FONT_DESCRIPTION, FALSE TSRMLS_CC)) {
        desc = (PangoFontDescription *) PHPG_GBOXED(php_desc);
    } else {
        php_error(E_WARNING, "%s::%s() expects desc argument to be a valid PangoFontDescription object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    if (phpg_gboxed_check(php_language, PANGO_TYPE_LANGUAGE, FALSE TSRMLS_CC)) {
        language = (PangoLanguage *) PHPG_GBOXED(php_language);
    } else {
        php_error(E_WARNING, "%s::%s() expects language argument to be a valid PangoLanguage object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    php_retval = pango_font_map_load_fontset(PANGO_FONT_MAP(PHPG_GOBJECT(this_ptr)), PANGO_CONTEXT(PHPG_GOBJECT(context)), desc, language);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(PangoFontMap, get_shape_engine_type)
{
	const gchar *php_retval;
	gchar *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_map_get_shape_engine_type(PANGO_FONT_MAP(PHPG_GOBJECT(this_ptr)));
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


static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangofontmap_load_font, 0)
    ZEND_ARG_OBJ_INFO(0, context, PangoContext, 1)
    ZEND_ARG_OBJ_INFO(0, desc, PangoFontDescription, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangofontmap_load_fontset, 0)
    ZEND_ARG_OBJ_INFO(0, context, PangoContext, 1)
    ZEND_ARG_OBJ_INFO(0, desc, PangoFontDescription, 1)
    ZEND_ARG_OBJ_INFO(0, language, PangoLanguage, 1)
ZEND_END_ARG_INFO();

static function_entry pangofontmap_methods[] = {
	PHP_ME(PangoFontMap, get_shape_engine_type, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontMap, load_font,            arginfo_pango_pangofontmap_load_font, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontMap, load_fontset,         arginfo_pango_pangofontmap_load_fontset, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(PangoFontset, get_font)
{
	long wc;
	PangoFont* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &wc))
		return;

    php_retval = pango_fontset_get_font(PANGO_FONTSET(PHPG_GOBJECT(this_ptr)), (guint)wc);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(PangoFontset, get_metrics)
{
	PangoFontMetrics *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_fontset_get_metrics(PANGO_FONTSET(PHPG_GOBJECT(this_ptr)));
	phpg_gboxed_new(&return_value, PANGO_TYPE_FONT_METRICS, php_retval, TRUE, TRUE TSRMLS_CC);

}


static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangofontset_get_font, 0)
    ZEND_ARG_INFO(0, wc)
ZEND_END_ARG_INFO();

static function_entry pangofontset_methods[] = {
	PHP_ME(PangoFontset, get_font,             arginfo_pango_pangofontset_get_font, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontset, get_metrics,          NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(PangoFontsetSimple, __construct)
{
	PangoLanguage *language = NULL;
	zval *php_language;
	GObject *wrapped_obj;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_language, gboxed_ce)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoFontsetSimple);
	}

    if (phpg_gboxed_check(php_language, PANGO_TYPE_LANGUAGE, FALSE TSRMLS_CC)) {
        language = (PangoLanguage *) PHPG_GBOXED(php_language);
    } else {
        php_error(E_WARNING, "%s::%s() expects language argument to be a valid PangoLanguage object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoFontsetSimple);
    }

	wrapped_obj = (GObject *) pango_fontset_simple_new(language);

	if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoFontsetSimple);
	}

    phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}


static PHP_METHOD(PangoFontsetSimple, append)
{
	zval *font;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &font, pangofont_ce))
		return;

    pango_fontset_simple_append(PANGO_FONTSET_SIMPLE(PHPG_GOBJECT(this_ptr)), PANGO_FONT(PHPG_GOBJECT(font)));

}


static PHP_METHOD(PangoFontsetSimple, size)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_fontset_simple_size(PANGO_FONTSET_SIMPLE(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangofontsetsimple_pango_fontset_simple_new, 0)
    ZEND_ARG_OBJ_INFO(0, language, PangoLanguage, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangofontsetsimple_append, 0)
    ZEND_ARG_OBJ_INFO(0, font, PangoFont, 1)
ZEND_END_ARG_INFO();

static function_entry pangofontsetsimple_methods[] = {
	PHP_ME(PangoFontsetSimple, __construct,          arginfo_pango_pangofontsetsimple_pango_fontset_simple_new, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontsetSimple, append,               arginfo_pango_pangofontsetsimple_append, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontsetSimple, size,                 NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(PangoLayout, __construct)
{
	zval *context;
	GObject *wrapped_obj;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &context, pangocontext_ce)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoLayout);
	}

	wrapped_obj = (GObject *) pango_layout_new(PANGO_CONTEXT(PHPG_GOBJECT(context)));

	if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoLayout);
	}

    phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}


static PHP_METHOD(PangoLayout, copy)
{
	PangoLayout* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_copy(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(PangoLayout, get_context)
{
	PangoContext* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_get_context(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(PangoLayout, set_attributes)
{
	PangoAttrList *attrs = NULL;
	zval *php_attrs;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_attrs, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_attrs, PANGO_TYPE_ATTR_LIST, FALSE TSRMLS_CC)) {
        attrs = (PangoAttrList *) PHPG_GBOXED(php_attrs);
    } else {
        php_error(E_WARNING, "%s::%s() expects attrs argument to be a valid PangoAttrList object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    pango_layout_set_attributes(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), attrs);

}


static PHP_METHOD(PangoLayout, get_attributes)
{
	PangoAttrList *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_get_attributes(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));
	phpg_gboxed_new(&return_value, PANGO_TYPE_ATTR_LIST, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(PangoLayout, set_text)
{
	char *text;
	zend_bool free_text = FALSE;
	long length;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "ui", &text, &free_text, &length))
		return;

    pango_layout_set_text(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), text, (int)length);
	if (free_text) g_free(text);

}


static PHP_METHOD(PangoLayout, get_text)
{
	const gchar *php_retval;
	gchar *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_get_text(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));
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


static PHP_METHOD(PangoLayout, set_markup)
{
	char *markup;
	zend_bool free_markup = FALSE;
	long length;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "ui", &markup, &free_markup, &length))
		return;

    pango_layout_set_markup(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), markup, (int)length);
	if (free_markup) g_free(markup);

}


static PHP_METHOD(PangoLayout, set_font_description)
{
	PangoFontDescription *desc = NULL;
	zval *php_desc;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "N", &php_desc, gboxed_ce))
		return;

    if (Z_TYPE_P(php_desc) != IS_NULL) {
        if (phpg_gboxed_check(php_desc, PANGO_TYPE_FONT_DESCRIPTION, FALSE TSRMLS_CC)) {
            desc = (PangoFontDescription *) PHPG_GBOXED(php_desc);
        } else {
            php_error(E_WARNING, "%s::%s() expects desc argument to be a valid PangoFontDescription object or null", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
            return;
        }
    }

    pango_layout_set_font_description(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), desc);

}


static PHP_METHOD(PangoLayout, set_width)
{
	long width;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &width))
		return;

    pango_layout_set_width(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), (int)width);

}


static PHP_METHOD(PangoLayout, get_width)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_get_width(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(PangoLayout, set_wrap)
{
	PangoWrapMode wrap;
	zval *php_wrap = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_wrap))
		return;

	if (php_wrap && phpg_gvalue_get_enum(PANGO_TYPE_WRAP_MODE, php_wrap, (gint *)&wrap) == FAILURE) {
		return;
	}

    pango_layout_set_wrap(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), wrap);

}


static PHP_METHOD(PangoLayout, get_wrap)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_get_wrap(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(PangoLayout, set_indent)
{
	long indent;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &indent))
		return;

    pango_layout_set_indent(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), (int)indent);

}


static PHP_METHOD(PangoLayout, get_indent)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_get_indent(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(PangoLayout, set_spacing)
{
	long spacing;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &spacing))
		return;

    pango_layout_set_spacing(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), (int)spacing);

}


static PHP_METHOD(PangoLayout, get_spacing)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_get_spacing(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(PangoLayout, set_justify)
{
	zend_bool justify;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &justify))
		return;

    pango_layout_set_justify(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), (gboolean)justify);

}


static PHP_METHOD(PangoLayout, get_justify)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_get_justify(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(PangoLayout, set_auto_dir)
{
	zend_bool auto_dir;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &auto_dir))
		return;

    pango_layout_set_auto_dir(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), (gboolean)auto_dir);

}


static PHP_METHOD(PangoLayout, get_auto_dir)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_get_auto_dir(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(PangoLayout, set_alignment)
{
	PangoAlignment alignment;
	zval *php_alignment = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_alignment))
		return;

	if (php_alignment && phpg_gvalue_get_enum(PANGO_TYPE_ALIGNMENT, php_alignment, (gint *)&alignment) == FAILURE) {
		return;
	}

    pango_layout_set_alignment(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), alignment);

}


static PHP_METHOD(PangoLayout, get_alignment)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_get_alignment(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(PangoLayout, set_tabs)
{
	PangoTabArray *tabs = NULL;
	zval *php_tabs;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "N", &php_tabs, gboxed_ce))
		return;

    if (Z_TYPE_P(php_tabs) != IS_NULL) {
        if (phpg_gboxed_check(php_tabs, PANGO_TYPE_TAB_ARRAY, FALSE TSRMLS_CC)) {
            tabs = (PangoTabArray *) PHPG_GBOXED(php_tabs);
        } else {
            php_error(E_WARNING, "%s::%s() expects tabs argument to be a valid PangoTabArray object or null", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
            return;
        }
    }

    pango_layout_set_tabs(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), tabs);

}


static PHP_METHOD(PangoLayout, get_tabs)
{
	PangoTabArray *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_get_tabs(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));
	phpg_gboxed_new(&return_value, PANGO_TYPE_TAB_ARRAY, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(PangoLayout, set_single_paragraph_mode)
{
	zend_bool setting;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "b", &setting))
		return;

    pango_layout_set_single_paragraph_mode(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), (gboolean)setting);

}


static PHP_METHOD(PangoLayout, get_single_paragraph_mode)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_get_single_paragraph_mode(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(PangoLayout, context_changed)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    pango_layout_context_changed(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(PangoLayout, index_to_pos)
{
	long index;
	PangoRectangle pos = { 0, 0, 0, 0 };
	zval *php_pos;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iV", &index, &php_pos))
		return;

    if (phpg_rectangle_from_zval(php_pos, (GdkRectangle*)&pos TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects pos argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    pango_layout_index_to_pos(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), (int)index, &pos);

}


static PHP_METHOD(PangoLayout, get_cursor_pos)
{
	long index;
	PangoRectangle strong_pos = { 0, 0, 0, 0 }, weak_pos = { 0, 0, 0, 0 };
	zval *php_strong_pos, *php_weak_pos;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iVV", &index, &php_strong_pos, &php_weak_pos))
		return;

    if (phpg_rectangle_from_zval(php_strong_pos, (GdkRectangle*)&strong_pos TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects strong_pos argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    if (phpg_rectangle_from_zval(php_weak_pos, (GdkRectangle*)&weak_pos TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects weak_pos argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    pango_layout_get_cursor_pos(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), (int)index, &strong_pos, &weak_pos);

}

#line 185 "ext/gtk+/pango.overrides"
static PHP_METHOD(PangoLayout, xy_to_index)
{
    int x, y, index, trailing;
    gboolean res;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "ii", &x, &y))
        return;

    res = pango_layout_xy_to_index(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), x, y, &index, &trailing);

    if (res)
        php_gtk_build_value(&return_value, "(ii)", index, trailing);
    else
        RETVAL_BOOL(res);
}

#line 1276 "ext/gtk+/gen_pango.c"



static PHP_METHOD(PangoLayout, get_extents)
{
	PangoRectangle ink_rect = { 0, 0, 0, 0 }, logical_rect = { 0, 0, 0, 0 };
	zval *php_ink_rect, *php_logical_rect;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "VV", &php_ink_rect, &php_logical_rect))
		return;

    if (phpg_rectangle_from_zval(php_ink_rect, (GdkRectangle*)&ink_rect TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects ink_rect argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    if (phpg_rectangle_from_zval(php_logical_rect, (GdkRectangle*)&logical_rect TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects logical_rect argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    pango_layout_get_extents(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), &ink_rect, &logical_rect);

}

#line 89 "ext/gtk+/pango.overrides"
static PHP_METHOD(PangoLayout, get_pixel_extents)
{
    PangoRectangle ink, logical;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    pango_layout_get_pixel_extents(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), &ink, &logical);

    php_gtk_build_value(&return_value, "((iiii)(iiii))", ink.x, ink.y, ink.width,
                        ink.height, logical.x, logical.y, logical.width,
                        logical.height);
}

#line 1319 "ext/gtk+/gen_pango.c"


#line 123 "ext/gtk+/pango.overrides"
static PHP_METHOD(PangoLayout, get_size)
{
    int height, width;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    pango_layout_get_size(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), &height, &width);

    php_gtk_build_value(&return_value, "(ii)", height, width);
}

#line 1337 "ext/gtk+/gen_pango.c"


#line 107 "ext/gtk+/pango.overrides"
static PHP_METHOD(PangoLayout, get_pixel_size)
{
    int height, width;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    pango_layout_get_pixel_size(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), &height, &width);

    php_gtk_build_value(&return_value, "(ii)", height, width);
}

#line 1355 "ext/gtk+/gen_pango.c"



static PHP_METHOD(PangoLayout, get_line_count)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_get_line_count(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}

#line 139 "ext/gtk+/pango.overrides"
static PHP_METHOD(PangoLayout, get_line)
{
    PangoLayoutLine *line;
    int num, max;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &num))
        return;

    max = pango_layout_get_line_count(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));

    if ((num < 1) || (num > max)) {
        php_error(E_WARNING, "%s::%s() expects number argument to be between 0 and the maximum number of lines (as given by get_line_count)",
            get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    line = pango_layout_get_line(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)), num);

    phpg_gobject_new(&return_value, G_OBJECT(line) TSRMLS_CC);
}

#line 1396 "ext/gtk+/gen_pango.c"


#line 164 "ext/gtk+/pango.overrides"
static PHP_METHOD(PangoLayout, get_lines)
{
    GSList *list, *tmp;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
        return;

    list = pango_layout_get_lines(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));

    array_init(return_value);
    for (tmp = list; tmp; tmp = tmp->next) {
        zval *line = NULL;
        phpg_gobject_new(&line, G_OBJECT(tmp->data) TSRMLS_CC);
        add_next_index_zval(return_value, line);
    }
}

#line 1419 "ext/gtk+/gen_pango.c"



static PHP_METHOD(PangoLayout, get_iter)
{
	PangoLayoutIter *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_get_iter(PANGO_LAYOUT(PHPG_GOBJECT(this_ptr)));
	phpg_gboxed_new(&return_value, PANGO_TYPE_LAYOUT_ITER, php_retval, TRUE, TRUE TSRMLS_CC);

}


static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayout_pango_layout_new, 0)
    ZEND_ARG_OBJ_INFO(0, context, PangoContext, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayout_set_attributes, 0)
    ZEND_ARG_OBJ_INFO(0, attrs, PangoAttrList, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayout_set_text, 0)
    ZEND_ARG_INFO(0, text)
    ZEND_ARG_INFO(0, length)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayout_set_markup, 0)
    ZEND_ARG_INFO(0, markup)
    ZEND_ARG_INFO(0, length)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayout_set_font_description, 0)
    ZEND_ARG_OBJ_INFO(0, desc, PangoFontDescription, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayout_set_width, 0)
    ZEND_ARG_INFO(0, width)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayout_set_wrap, 0)
    ZEND_ARG_INFO(0, wrap)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayout_set_indent, 0)
    ZEND_ARG_INFO(0, indent)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayout_set_spacing, 0)
    ZEND_ARG_INFO(0, spacing)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayout_set_justify, 0)
    ZEND_ARG_INFO(0, justify)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayout_set_auto_dir, 0)
    ZEND_ARG_INFO(0, auto_dir)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayout_set_alignment, 0)
    ZEND_ARG_INFO(0, alignment)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayout_set_tabs, 0)
    ZEND_ARG_OBJ_INFO(0, tabs, PangoTabArray, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayout_set_single_paragraph_mode, 0)
    ZEND_ARG_INFO(0, setting)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayout_index_to_pos, 0)
    ZEND_ARG_INFO(0, index)
    ZEND_ARG_INFO(0, pos)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayout_get_cursor_pos, 0)
    ZEND_ARG_INFO(0, index)
    ZEND_ARG_INFO(0, strong_pos)
    ZEND_ARG_INFO(0, weak_pos)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayout_get_extents, 0)
    ZEND_ARG_INFO(0, ink_rect)
    ZEND_ARG_INFO(0, logical_rect)
ZEND_END_ARG_INFO();

static function_entry pangolayout_methods[] = {
	PHP_ME(PangoLayout, __construct,          arginfo_pango_pangolayout_pango_layout_new, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, context_changed,      NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, copy,                 NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_alignment,        NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_attributes,       NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_auto_dir,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_context,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_cursor_pos,       arginfo_pango_pangolayout_get_cursor_pos, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_extents,          arginfo_pango_pangolayout_get_extents, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_indent,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_iter,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_justify,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_line,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_line_count,       NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_lines,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_pixel_extents,    NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_pixel_size,       NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_single_paragraph_mode, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_size,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_spacing,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_tabs,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_text,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_width,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, get_wrap,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, index_to_pos,         arginfo_pango_pangolayout_index_to_pos, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, set_alignment,        arginfo_pango_pangolayout_set_alignment, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, set_attributes,       arginfo_pango_pangolayout_set_attributes, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, set_auto_dir,         arginfo_pango_pangolayout_set_auto_dir, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, set_font_description, arginfo_pango_pangolayout_set_font_description, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, set_indent,           arginfo_pango_pangolayout_set_indent, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, set_justify,          arginfo_pango_pangolayout_set_justify, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, set_markup,           arginfo_pango_pangolayout_set_markup, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, set_single_paragraph_mode, arginfo_pango_pangolayout_set_single_paragraph_mode, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, set_spacing,          arginfo_pango_pangolayout_set_spacing, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, set_tabs,             arginfo_pango_pangolayout_set_tabs, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, set_text,             arginfo_pango_pangolayout_set_text, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, set_width,            arginfo_pango_pangolayout_set_width, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, set_wrap,             arginfo_pango_pangolayout_set_wrap, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayout, xy_to_index,          NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(PangoAttrList, __construct)
{

    phpg_gboxed_t *pobj = NULL;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "")) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoAttrList);
	}

    pobj = zend_object_store_get_object(this_ptr TSRMLS_CC);
    pobj->gtype = PANGO_TYPE_ATTR_LIST;
    pobj->boxed = pango_attr_list_new();

	if (!pobj->boxed) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoAttrList);
	}
    pobj->free_on_destroy = TRUE;
}


static PHP_METHOD(PangoAttrList, ref)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    pango_attr_list_ref((PangoAttrList *)PHPG_GBOXED(this_ptr));

}


static PHP_METHOD(PangoAttrList, unref)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    pango_attr_list_unref((PangoAttrList *)PHPG_GBOXED(this_ptr));

}


static PHP_METHOD(PangoAttrList, copy)
{
	PangoAttrList *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_attr_list_copy((PangoAttrList *)PHPG_GBOXED(this_ptr));
	phpg_gboxed_new(&return_value, PANGO_TYPE_ATTR_LIST, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(PangoAttrList, splice)
{
	PangoAttrList *other = NULL;
	zval *php_other;
	long pos, len;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Oii", &php_other, gboxed_ce, &pos, &len))
		return;

    if (phpg_gboxed_check(php_other, PANGO_TYPE_ATTR_LIST, FALSE TSRMLS_CC)) {
        other = (PangoAttrList *) PHPG_GBOXED(php_other);
    } else {
        php_error(E_WARNING, "%s::%s() expects other argument to be a valid PangoAttrList object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    pango_attr_list_splice((PangoAttrList *)PHPG_GBOXED(this_ptr), other, (gint)pos, (gint)len);

}


static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangoattrlist_splice, 0)
    ZEND_ARG_OBJ_INFO(0, other, PangoAttrList, 1)
    ZEND_ARG_INFO(0, pos)
    ZEND_ARG_INFO(0, len)
ZEND_END_ARG_INFO();

static function_entry pangoattrlist_methods[] = {
	PHP_ME(PangoAttrList, __construct,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoAttrList, copy,                 NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoAttrList, ref,                  NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoAttrList, splice,               arginfo_pango_pangoattrlist_splice, ZEND_ACC_PUBLIC)
	PHP_ME(PangoAttrList, unref,                NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
#line 15 "ext/gtk+/pango.overrides"
static PHP_METHOD(PangoColor, __construct)
{
    /* TODO */
}

#line 1678 "ext/gtk+/gen_pango.c"



PHPG_PROP_READER(PangoColor, red)
{
	long php_retval;

    php_retval = ((PangoColor *)((phpg_gboxed_t *)object)->boxed)->red;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(PangoColor, green)
{
	long php_retval;

    php_retval = ((PangoColor *)((phpg_gboxed_t *)object)->boxed)->green;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


PHPG_PROP_READER(PangoColor, blue)
{
	long php_retval;

    php_retval = ((PangoColor *)((phpg_gboxed_t *)object)->boxed)->blue;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


static prop_info_t pangocolor_prop_info[] = {
	{ "red", PHPG_PROP_READ_FN(PangoColor, red), NULL },
	{ "green", PHPG_PROP_READ_FN(PangoColor, green), NULL },
	{ "blue", PHPG_PROP_READ_FN(PangoColor, blue), NULL },
	{ NULL, NULL, NULL },
};


static PHP_METHOD(PangoColor, copy)
{
	PangoColor *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_color_copy((PangoColor *)PHPG_GBOXED(this_ptr));
	phpg_gboxed_new(&return_value, PANGO_TYPE_COLOR, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(PangoColor, free)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    pango_color_free((PangoColor *)PHPG_GBOXED(this_ptr));

}


static function_entry pangocolor_methods[] = {
	PHP_ME(PangoColor, __construct,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoColor, copy,                 NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoColor, free,                 NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
#line 35 "ext/gtk+/pango.overrides"
static PHP_METHOD(PangoFontDescription, __construct)
{
	char *str = NULL;
	PangoFontDescription *wrapped_obj = NULL;
    phpg_gboxed_t *pobj = NULL;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "|s", &str)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoFontDescription);
	}

    if (str) {
        wrapped_obj = pango_font_description_from_string(str);
    } else {
        wrapped_obj = pango_font_description_new();
    }
	if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoFontDescription);
	}

    pobj = zend_object_store_get_object(this_ptr TSRMLS_CC);
    pobj->gtype = PANGO_TYPE_FONT_DESCRIPTION;
    pobj->boxed = wrapped_obj;
    pobj->free_on_destroy = TRUE;
}

#line 1780 "ext/gtk+/gen_pango.c"



static PHP_METHOD(PangoFontDescription, from_string)
{
	char *str;
	zend_bool free_str = FALSE;
	PangoFontDescription *wrapped_obj = NULL;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &str, &free_str)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoFontDescription);
	}

    wrapped_obj = pango_font_description_from_string(str);
	if (free_str) g_free(str);

	if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoFontDescription);
	}
    phpg_gboxed_new(&return_value, PANGO_TYPE_FONT_DESCRIPTION, wrapped_obj, FALSE, TRUE TSRMLS_CC);
}


static PHP_METHOD(PangoFontDescription, copy)
{
	PangoFontDescription *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_description_copy((PangoFontDescription *)PHPG_GBOXED(this_ptr));
	phpg_gboxed_new(&return_value, PANGO_TYPE_FONT_DESCRIPTION, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(PangoFontDescription, copy_static)
{
	PangoFontDescription *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_description_copy_static((PangoFontDescription *)PHPG_GBOXED(this_ptr));
	phpg_gboxed_new(&return_value, PANGO_TYPE_FONT_DESCRIPTION, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(PangoFontDescription, hash)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_description_hash((PangoFontDescription *)PHPG_GBOXED(this_ptr));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(PangoFontDescription, equal)
{
	PangoFontDescription *desc2 = NULL;
	zval *php_desc2;
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &php_desc2, gboxed_ce))
		return;

    if (phpg_gboxed_check(php_desc2, PANGO_TYPE_FONT_DESCRIPTION, FALSE TSRMLS_CC)) {
        desc2 = (PangoFontDescription *) PHPG_GBOXED(php_desc2);
    } else {
        php_error(E_WARNING, "%s::%s() expects desc2 argument to be a valid PangoFontDescription object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    php_retval = pango_font_description_equal((PangoFontDescription *)PHPG_GBOXED(this_ptr), desc2);
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(PangoFontDescription, set_family)
{
	char *family;
	zend_bool free_family = FALSE;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &family, &free_family))
		return;

    pango_font_description_set_family((PangoFontDescription *)PHPG_GBOXED(this_ptr), family);
	if (free_family) g_free(family);

}


static PHP_METHOD(PangoFontDescription, set_family_static)
{
	char *family;
	zend_bool free_family = FALSE;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &family, &free_family))
		return;

    pango_font_description_set_family_static((PangoFontDescription *)PHPG_GBOXED(this_ptr), family);
	if (free_family) g_free(family);

}


static PHP_METHOD(PangoFontDescription, get_family)
{
	const gchar *php_retval;
	gchar *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_description_get_family((PangoFontDescription *)PHPG_GBOXED(this_ptr));
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


static PHP_METHOD(PangoFontDescription, set_style)
{
	PangoStyle style;
	zval *php_style = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_style))
		return;

	if (php_style && phpg_gvalue_get_enum(PANGO_TYPE_STYLE, php_style, (gint *)&style) == FAILURE) {
		return;
	}

    pango_font_description_set_style((PangoFontDescription *)PHPG_GBOXED(this_ptr), style);

}


static PHP_METHOD(PangoFontDescription, get_style)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_description_get_style((PangoFontDescription *)PHPG_GBOXED(this_ptr));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(PangoFontDescription, set_variant)
{
	PangoVariant variant;
	zval *php_variant = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_variant))
		return;

	if (php_variant && phpg_gvalue_get_enum(PANGO_TYPE_VARIANT, php_variant, (gint *)&variant) == FAILURE) {
		return;
	}

    pango_font_description_set_variant((PangoFontDescription *)PHPG_GBOXED(this_ptr), variant);

}


static PHP_METHOD(PangoFontDescription, get_variant)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_description_get_variant((PangoFontDescription *)PHPG_GBOXED(this_ptr));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(PangoFontDescription, set_weight)
{
	PangoWeight weight;
	zval *php_weight = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_weight))
		return;

	if (php_weight && phpg_gvalue_get_enum(PANGO_TYPE_WEIGHT, php_weight, (gint *)&weight) == FAILURE) {
		return;
	}

    pango_font_description_set_weight((PangoFontDescription *)PHPG_GBOXED(this_ptr), weight);

}


static PHP_METHOD(PangoFontDescription, get_weight)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_description_get_weight((PangoFontDescription *)PHPG_GBOXED(this_ptr));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(PangoFontDescription, set_stretch)
{
	PangoStretch stretch;
	zval *php_stretch = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_stretch))
		return;

	if (php_stretch && phpg_gvalue_get_enum(PANGO_TYPE_STRETCH, php_stretch, (gint *)&stretch) == FAILURE) {
		return;
	}

    pango_font_description_set_stretch((PangoFontDescription *)PHPG_GBOXED(this_ptr), stretch);

}


static PHP_METHOD(PangoFontDescription, get_stretch)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_description_get_stretch((PangoFontDescription *)PHPG_GBOXED(this_ptr));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(PangoFontDescription, set_size)
{
	long size;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &size))
		return;

    pango_font_description_set_size((PangoFontDescription *)PHPG_GBOXED(this_ptr), (gint)size);

}


static PHP_METHOD(PangoFontDescription, get_size)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_description_get_size((PangoFontDescription *)PHPG_GBOXED(this_ptr));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(PangoFontDescription, get_set_fields)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_description_get_set_fields((PangoFontDescription *)PHPG_GBOXED(this_ptr));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(PangoFontDescription, unset_fields)
{
	PangoFontMask to_unset;
	zval *php_to_unset = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_to_unset))
		return;

	if (php_to_unset && phpg_gvalue_get_flags(PANGO_TYPE_FONT_MASK, php_to_unset, (gint *)&to_unset) == FAILURE) {
		return;
	}

    pango_font_description_unset_fields((PangoFontDescription *)PHPG_GBOXED(this_ptr), to_unset);

}


static PHP_METHOD(PangoFontDescription, merge)
{
	PangoFontDescription *desc_to_merge = NULL;
	zval *php_desc_to_merge;
	zend_bool replace_existing;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Ob", &php_desc_to_merge, gboxed_ce, &replace_existing))
		return;

    if (phpg_gboxed_check(php_desc_to_merge, PANGO_TYPE_FONT_DESCRIPTION, FALSE TSRMLS_CC)) {
        desc_to_merge = (PangoFontDescription *) PHPG_GBOXED(php_desc_to_merge);
    } else {
        php_error(E_WARNING, "%s::%s() expects desc_to_merge argument to be a valid PangoFontDescription object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    pango_font_description_merge((PangoFontDescription *)PHPG_GBOXED(this_ptr), desc_to_merge, (gboolean)replace_existing);

}


static PHP_METHOD(PangoFontDescription, merge_static)
{
	PangoFontDescription *desc_to_merge = NULL;
	zval *php_desc_to_merge;
	zend_bool replace_existing;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Ob", &php_desc_to_merge, gboxed_ce, &replace_existing))
		return;

    if (phpg_gboxed_check(php_desc_to_merge, PANGO_TYPE_FONT_DESCRIPTION, FALSE TSRMLS_CC)) {
        desc_to_merge = (PangoFontDescription *) PHPG_GBOXED(php_desc_to_merge);
    } else {
        php_error(E_WARNING, "%s::%s() expects desc_to_merge argument to be a valid PangoFontDescription object",
                  get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }

    pango_font_description_merge_static((PangoFontDescription *)PHPG_GBOXED(this_ptr), desc_to_merge, (gboolean)replace_existing);

}


static PHP_METHOD(PangoFontDescription, better_match)
{
	PangoFontDescription *old_match = NULL, *new_match = NULL;
	zval *php_old_match = NULL, *php_new_match = NULL;
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "|NN", &php_old_match, gboxed_ce, &php_new_match, gboxed_ce))
		return;

    if (php_old_match) {
        if (Z_TYPE_P(php_old_match) == IS_NULL) {
            old_match = NULL;
        } else {
            if (phpg_gboxed_check(php_old_match, PANGO_TYPE_FONT_DESCRIPTION, FALSE TSRMLS_CC)) {
                old_match = (PangoFontDescription *) PHPG_GBOXED(php_old_match);
            } else {
                php_error(E_WARNING, "%s::%s() expects old_match argument to be a valid PangoFontDescription object or null", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
                return;
            }
        }
    }

    if (php_new_match) {
        if (Z_TYPE_P(php_new_match) == IS_NULL) {
            new_match = NULL;
        } else {
            if (phpg_gboxed_check(php_new_match, PANGO_TYPE_FONT_DESCRIPTION, FALSE TSRMLS_CC)) {
                new_match = (PangoFontDescription *) PHPG_GBOXED(php_new_match);
            } else {
                php_error(E_WARNING, "%s::%s() expects new_match argument to be a valid PangoFontDescription object or null", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
                return;
            }
        }
    }

    php_retval = pango_font_description_better_match((PangoFontDescription *)PHPG_GBOXED(this_ptr), old_match, new_match);
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(PangoFontDescription, to_string)
{
	gchar *php_retval, *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_description_to_string((PangoFontDescription *)PHPG_GBOXED(this_ptr));
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


static PHP_METHOD(PangoFontDescription, to_filename)
{
	gchar *php_retval, *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_description_to_filename((PangoFontDescription *)PHPG_GBOXED(this_ptr));
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

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_pango_pangofontdescription_pango_font_description_new, 0, 0, 0)
    ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO();


static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangofontdescription_pango_font_description_from_string, 0)
    ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangofontdescription_equal, 0)
    ZEND_ARG_OBJ_INFO(0, desc2, PangoFontDescription, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangofontdescription_set_family, 0)
    ZEND_ARG_INFO(0, family)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangofontdescription_set_family_static, 0)
    ZEND_ARG_INFO(0, family)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangofontdescription_set_style, 0)
    ZEND_ARG_INFO(0, style)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangofontdescription_set_variant, 0)
    ZEND_ARG_INFO(0, variant)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangofontdescription_set_weight, 0)
    ZEND_ARG_INFO(0, weight)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangofontdescription_set_stretch, 0)
    ZEND_ARG_INFO(0, stretch)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangofontdescription_set_size, 0)
    ZEND_ARG_INFO(0, size)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangofontdescription_unset_fields, 0)
    ZEND_ARG_INFO(0, to_unset)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangofontdescription_merge, 0)
    ZEND_ARG_OBJ_INFO(0, desc_to_merge, PangoFontDescription, 1)
    ZEND_ARG_INFO(0, replace_existing)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangofontdescription_merge_static, 0)
    ZEND_ARG_OBJ_INFO(0, desc_to_merge, PangoFontDescription, 1)
    ZEND_ARG_INFO(0, replace_existing)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_pango_pangofontdescription_better_match, 0, 0, 0)
    ZEND_ARG_OBJ_INFO(0, old_match, PangoFontDescription, 1)
    ZEND_ARG_OBJ_INFO(0, new_match, PangoFontDescription, 1)
ZEND_END_ARG_INFO();

static function_entry pangofontdescription_methods[] = {
	PHP_ME(PangoFontDescription, __construct,          arginfo_pango_pangofontdescription_pango_font_description_new, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, from_string,          arginfo_pango_pangofontdescription_pango_font_description_from_string, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(PangoFontDescription, better_match,         arginfo_pango_pangofontdescription_better_match, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, copy,                 NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, copy_static,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, equal,                arginfo_pango_pangofontdescription_equal, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, get_family,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, get_set_fields,       NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, get_size,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, get_stretch,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, get_style,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, get_variant,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, get_weight,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, hash,                 NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, merge,                arginfo_pango_pangofontdescription_merge, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, merge_static,         arginfo_pango_pangofontdescription_merge_static, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, set_family,           arginfo_pango_pangofontdescription_set_family, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, set_family_static,    arginfo_pango_pangofontdescription_set_family_static, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, set_size,             arginfo_pango_pangofontdescription_set_size, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, set_stretch,          arginfo_pango_pangofontdescription_set_stretch, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, set_style,            arginfo_pango_pangofontdescription_set_style, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, set_variant,          arginfo_pango_pangofontdescription_set_variant, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, set_weight,           arginfo_pango_pangofontdescription_set_weight, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, to_filename,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, to_string,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontDescription, unset_fields,         arginfo_pango_pangofontdescription_unset_fields, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(PangoFontMetrics, ref)
{
	PangoFontMetrics *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_metrics_ref((PangoFontMetrics *)PHPG_GBOXED(this_ptr));
	phpg_gboxed_new(&return_value, PANGO_TYPE_FONT_METRICS, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(PangoFontMetrics, unref)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    pango_font_metrics_unref((PangoFontMetrics *)PHPG_GBOXED(this_ptr));

}


static PHP_METHOD(PangoFontMetrics, get_ascent)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_metrics_get_ascent((PangoFontMetrics *)PHPG_GBOXED(this_ptr));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(PangoFontMetrics, get_descent)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_metrics_get_descent((PangoFontMetrics *)PHPG_GBOXED(this_ptr));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(PangoFontMetrics, get_approximate_char_width)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_metrics_get_approximate_char_width((PangoFontMetrics *)PHPG_GBOXED(this_ptr));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(PangoFontMetrics, get_approximate_digit_width)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_font_metrics_get_approximate_digit_width((PangoFontMetrics *)PHPG_GBOXED(this_ptr));
	RETVAL_LONG(php_retval);
}


static function_entry pangofontmetrics_methods[] = {
#if ZEND_EXTENSION_API_NO > 220051025
	PHP_ME_MAPPING(__construct, no_direct_constructor, NULL, 0)
#else
	PHP_ME_MAPPING(__construct, no_direct_constructor, NULL)
#endif
	PHP_ME(PangoFontMetrics, get_approximate_char_width, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontMetrics, get_approximate_digit_width, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontMetrics, get_ascent,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontMetrics, get_descent,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontMetrics, ref,                  NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoFontMetrics, unref,                NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(PangoGlyphString, __construct)
{

    phpg_gboxed_t *pobj = NULL;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "")) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoGlyphString);
	}

    pobj = zend_object_store_get_object(this_ptr TSRMLS_CC);
    pobj->gtype = PANGO_TYPE_GLYPH_STRING;
    pobj->boxed = pango_glyph_string_new();

	if (!pobj->boxed) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoGlyphString);
	}
    pobj->free_on_destroy = TRUE;
}


PHPG_PROP_READER(PangoGlyphString, num_glyphs)
{
	long php_retval;

    php_retval = ((PangoGlyphString *)((phpg_gboxed_t *)object)->boxed)->num_glyphs;
	RETVAL_LONG(php_retval);
    return SUCCESS;
}


static prop_info_t pangoglyphstring_prop_info[] = {
	{ "num_glyphs", PHPG_PROP_READ_FN(PangoGlyphString, num_glyphs), NULL },
	{ NULL, NULL, NULL },
};


static PHP_METHOD(PangoGlyphString, set_size)
{
	long new_len;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &new_len))
		return;

    pango_glyph_string_set_size((PangoGlyphString *)PHPG_GBOXED(this_ptr), (gint)new_len);

}


static PHP_METHOD(PangoGlyphString, copy)
{
	PangoGlyphString *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_glyph_string_copy((PangoGlyphString *)PHPG_GBOXED(this_ptr));
	phpg_gboxed_new(&return_value, PANGO_TYPE_GLYPH_STRING, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(PangoGlyphString, free)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    pango_glyph_string_free((PangoGlyphString *)PHPG_GBOXED(this_ptr));

}


static PHP_METHOD(PangoGlyphString, extents)
{
	zval *font, *php_ink_rect, *php_logical_rect;
	PangoRectangle ink_rect = { 0, 0, 0, 0 }, logical_rect = { 0, 0, 0, 0 };

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "OVV", &font, pangofont_ce, &php_ink_rect, &php_logical_rect))
		return;

    if (phpg_rectangle_from_zval(php_ink_rect, (GdkRectangle*)&ink_rect TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects ink_rect argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    if (phpg_rectangle_from_zval(php_logical_rect, (GdkRectangle*)&logical_rect TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects logical_rect argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    pango_glyph_string_extents((PangoGlyphString *)PHPG_GBOXED(this_ptr), PANGO_FONT(PHPG_GOBJECT(font)), &ink_rect, &logical_rect);

}


static PHP_METHOD(PangoGlyphString, extents_range)
{
	long start, end;
	zval *font, *php_ink_rect, *php_logical_rect;
	PangoRectangle ink_rect = { 0, 0, 0, 0 }, logical_rect = { 0, 0, 0, 0 };

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iiOVV", &start, &end, &font, pangofont_ce, &php_ink_rect, &php_logical_rect))
		return;

    if (phpg_rectangle_from_zval(php_ink_rect, (GdkRectangle*)&ink_rect TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects ink_rect argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    if (phpg_rectangle_from_zval(php_logical_rect, (GdkRectangle*)&logical_rect TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects logical_rect argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    pango_glyph_string_extents_range((PangoGlyphString *)PHPG_GBOXED(this_ptr), (int)start, (int)end, PANGO_FONT(PHPG_GOBJECT(font)), &ink_rect, &logical_rect);

}


static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangoglyphstring_set_size, 0)
    ZEND_ARG_INFO(0, new_len)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangoglyphstring_extents, 0)
    ZEND_ARG_OBJ_INFO(0, font, PangoFont, 1)
    ZEND_ARG_INFO(0, ink_rect)
    ZEND_ARG_INFO(0, logical_rect)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangoglyphstring_extents_range, 0)
    ZEND_ARG_INFO(0, start)
    ZEND_ARG_INFO(0, end)
    ZEND_ARG_OBJ_INFO(0, font, PangoFont, 1)
    ZEND_ARG_INFO(0, ink_rect)
    ZEND_ARG_INFO(0, logical_rect)
ZEND_END_ARG_INFO();

static function_entry pangoglyphstring_methods[] = {
	PHP_ME(PangoGlyphString, __construct,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoGlyphString, copy,                 NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoGlyphString, extents,              arginfo_pango_pangoglyphstring_extents, ZEND_ACC_PUBLIC)
	PHP_ME(PangoGlyphString, extents_range,        arginfo_pango_pangoglyphstring_extents_range, ZEND_ACC_PUBLIC)
	PHP_ME(PangoGlyphString, free,                 NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoGlyphString, set_size,             arginfo_pango_pangoglyphstring_set_size, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(PangoLanguage, __construct)
{
	char *language;
	zend_bool free_language = FALSE;

    phpg_gboxed_t *pobj = NULL;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &language, &free_language)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoLanguage);
	}

    pobj = zend_object_store_get_object(this_ptr TSRMLS_CC);
    pobj->gtype = PANGO_TYPE_LANGUAGE;
    pobj->boxed = pango_language_from_string(language);
	if (free_language) g_free(language);

	if (!pobj->boxed) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoLanguage);
	}
    pobj->free_on_destroy = TRUE;
}


static PHP_METHOD(PangoLanguage, matches)
{
	char *range_list;
	zend_bool free_range_list = FALSE;
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &range_list, &free_range_list))
		return;

    php_retval = pango_language_matches((PangoLanguage *)PHPG_GBOXED(this_ptr), range_list);
	if (free_range_list) g_free(range_list);
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(PangoLanguage, to_string)
{
	const gchar *php_retval;
	gchar *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_language_to_string((PangoLanguage *)PHPG_GBOXED(this_ptr));
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


static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolanguage_pango_language_from_string, 0)
    ZEND_ARG_INFO(0, language)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolanguage_matches, 0)
    ZEND_ARG_INFO(0, range_list)
ZEND_END_ARG_INFO();

static function_entry pangolanguage_methods[] = {
	PHP_ME(PangoLanguage, __construct,          arginfo_pango_pangolanguage_pango_language_from_string, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLanguage, matches,              arginfo_pango_pangolanguage_matches, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLanguage, to_string,            NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(PangoLayoutIter, free)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    pango_layout_iter_free((PangoLayoutIter *)PHPG_GBOXED(this_ptr));

}


static PHP_METHOD(PangoLayoutIter, get_index)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_iter_get_index((PangoLayoutIter *)PHPG_GBOXED(this_ptr));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(PangoLayoutIter, at_last_line)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_iter_at_last_line((PangoLayoutIter *)PHPG_GBOXED(this_ptr));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(PangoLayoutIter, next_char)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_iter_next_char((PangoLayoutIter *)PHPG_GBOXED(this_ptr));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(PangoLayoutIter, next_cluster)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_iter_next_cluster((PangoLayoutIter *)PHPG_GBOXED(this_ptr));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(PangoLayoutIter, next_run)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_iter_next_run((PangoLayoutIter *)PHPG_GBOXED(this_ptr));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(PangoLayoutIter, next_line)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_iter_next_line((PangoLayoutIter *)PHPG_GBOXED(this_ptr));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(PangoLayoutIter, get_char_extents)
{
	PangoRectangle logical_rect = { 0, 0, 0, 0 };
	zval *php_logical_rect;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_logical_rect))
		return;

    if (phpg_rectangle_from_zval(php_logical_rect, (GdkRectangle*)&logical_rect TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects logical_rect argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    pango_layout_iter_get_char_extents((PangoLayoutIter *)PHPG_GBOXED(this_ptr), &logical_rect);

}


static PHP_METHOD(PangoLayoutIter, get_cluster_extents)
{
	PangoRectangle ink_rect = { 0, 0, 0, 0 }, logical_rect = { 0, 0, 0, 0 };
	zval *php_ink_rect, *php_logical_rect;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "VV", &php_ink_rect, &php_logical_rect))
		return;

    if (phpg_rectangle_from_zval(php_ink_rect, (GdkRectangle*)&ink_rect TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects ink_rect argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    if (phpg_rectangle_from_zval(php_logical_rect, (GdkRectangle*)&logical_rect TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects logical_rect argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    pango_layout_iter_get_cluster_extents((PangoLayoutIter *)PHPG_GBOXED(this_ptr), &ink_rect, &logical_rect);

}


static PHP_METHOD(PangoLayoutIter, get_run_extents)
{
	PangoRectangle ink_rect = { 0, 0, 0, 0 }, logical_rect = { 0, 0, 0, 0 };
	zval *php_ink_rect, *php_logical_rect;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "VV", &php_ink_rect, &php_logical_rect))
		return;

    if (phpg_rectangle_from_zval(php_ink_rect, (GdkRectangle*)&ink_rect TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects ink_rect argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    if (phpg_rectangle_from_zval(php_logical_rect, (GdkRectangle*)&logical_rect TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects logical_rect argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    pango_layout_iter_get_run_extents((PangoLayoutIter *)PHPG_GBOXED(this_ptr), &ink_rect, &logical_rect);

}


static PHP_METHOD(PangoLayoutIter, get_line_extents)
{
	PangoRectangle ink_rect = { 0, 0, 0, 0 }, logical_rect = { 0, 0, 0, 0 };
	zval *php_ink_rect, *php_logical_rect;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "VV", &php_ink_rect, &php_logical_rect))
		return;

    if (phpg_rectangle_from_zval(php_ink_rect, (GdkRectangle*)&ink_rect TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects ink_rect argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    if (phpg_rectangle_from_zval(php_logical_rect, (GdkRectangle*)&logical_rect TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects logical_rect argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    pango_layout_iter_get_line_extents((PangoLayoutIter *)PHPG_GBOXED(this_ptr), &ink_rect, &logical_rect);

}


static PHP_METHOD(PangoLayoutIter, get_layout_extents)
{
	PangoRectangle ink_rect = { 0, 0, 0, 0 }, logical_rect = { 0, 0, 0, 0 };
	zval *php_ink_rect, *php_logical_rect;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "VV", &php_ink_rect, &php_logical_rect))
		return;

    if (phpg_rectangle_from_zval(php_ink_rect, (GdkRectangle*)&ink_rect TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects ink_rect argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    if (phpg_rectangle_from_zval(php_logical_rect, (GdkRectangle*)&logical_rect TSRMLS_CC) == FAILURE) {
        php_error(E_WARNING, "%s::%s() expects logical_rect argument to be either a 4-element array or a GdkRectangle object", get_active_class_name(NULL TSRMLS_CC), get_active_function_name(TSRMLS_C));
        return;
    }
    pango_layout_iter_get_layout_extents((PangoLayoutIter *)PHPG_GBOXED(this_ptr), &ink_rect, &logical_rect);

}


static PHP_METHOD(PangoLayoutIter, get_baseline)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_layout_iter_get_baseline((PangoLayoutIter *)PHPG_GBOXED(this_ptr));
	RETVAL_LONG(php_retval);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayoutiter_get_char_extents, 0)
    ZEND_ARG_INFO(0, logical_rect)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayoutiter_get_cluster_extents, 0)
    ZEND_ARG_INFO(0, ink_rect)
    ZEND_ARG_INFO(0, logical_rect)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayoutiter_get_run_extents, 0)
    ZEND_ARG_INFO(0, ink_rect)
    ZEND_ARG_INFO(0, logical_rect)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayoutiter_get_line_extents, 0)
    ZEND_ARG_INFO(0, ink_rect)
    ZEND_ARG_INFO(0, logical_rect)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangolayoutiter_get_layout_extents, 0)
    ZEND_ARG_INFO(0, ink_rect)
    ZEND_ARG_INFO(0, logical_rect)
ZEND_END_ARG_INFO();

static function_entry pangolayoutiter_methods[] = {
#if ZEND_EXTENSION_API_NO > 220051025
	PHP_ME_MAPPING(__construct, no_direct_constructor, NULL, 0)
#else
	PHP_ME_MAPPING(__construct, no_direct_constructor, NULL)
#endif
	PHP_ME(PangoLayoutIter, at_last_line,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayoutIter, free,                 NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayoutIter, get_baseline,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayoutIter, get_char_extents,     arginfo_pango_pangolayoutiter_get_char_extents, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayoutIter, get_cluster_extents,  arginfo_pango_pangolayoutiter_get_cluster_extents, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayoutIter, get_index,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayoutIter, get_layout_extents,   arginfo_pango_pangolayoutiter_get_layout_extents, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayoutIter, get_line_extents,     arginfo_pango_pangolayoutiter_get_line_extents, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayoutIter, get_run_extents,      arginfo_pango_pangolayoutiter_get_run_extents, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayoutIter, next_char,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayoutIter, next_cluster,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayoutIter, next_line,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoLayoutIter, next_run,             NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(PangoTabArray, __construct)
{
	long initial_size;
	zend_bool positions_in_pixels;

    phpg_gboxed_t *pobj = NULL;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "ib", &initial_size, &positions_in_pixels)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoTabArray);
	}

    pobj = zend_object_store_get_object(this_ptr TSRMLS_CC);
    pobj->gtype = PANGO_TYPE_TAB_ARRAY;
    pobj->boxed = pango_tab_array_new((gint)initial_size, (gboolean)positions_in_pixels);

	if (!pobj->boxed) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(PangoTabArray);
	}
    pobj->free_on_destroy = TRUE;
}


static PHP_METHOD(PangoTabArray, copy)
{
	PangoTabArray *php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_tab_array_copy((PangoTabArray *)PHPG_GBOXED(this_ptr));
	phpg_gboxed_new(&return_value, PANGO_TYPE_TAB_ARRAY, php_retval, TRUE, TRUE TSRMLS_CC);

}


static PHP_METHOD(PangoTabArray, free)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    pango_tab_array_free((PangoTabArray *)PHPG_GBOXED(this_ptr));

}


static PHP_METHOD(PangoTabArray, get_size)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_tab_array_get_size((PangoTabArray *)PHPG_GBOXED(this_ptr));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(PangoTabArray, resize)
{
	long new_size;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &new_size))
		return;

    pango_tab_array_resize((PangoTabArray *)PHPG_GBOXED(this_ptr), (gint)new_size);

}


static PHP_METHOD(PangoTabArray, set_tab)
{
	long tab_index, location;
	PangoTabAlign alignment;
	zval *php_alignment = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "iVi", &tab_index, &php_alignment, &location))
		return;

	if (php_alignment && phpg_gvalue_get_enum(PANGO_TYPE_TAB_ALIGN, php_alignment, (gint *)&alignment) == FAILURE) {
		return;
	}

    pango_tab_array_set_tab((PangoTabArray *)PHPG_GBOXED(this_ptr), (gint)tab_index, alignment, (gint)location);

}


static PHP_METHOD(PangoTabArray, get_positions_in_pixels)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = pango_tab_array_get_positions_in_pixels((PangoTabArray *)PHPG_GBOXED(this_ptr));
	RETVAL_BOOL(php_retval);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangotabarray_pango_tab_array_new, 0)
    ZEND_ARG_INFO(0, initial_size)
    ZEND_ARG_INFO(0, positions_in_pixels)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangotabarray_resize, 0)
    ZEND_ARG_INFO(0, new_size)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_pango_pangotabarray_set_tab, 0)
    ZEND_ARG_INFO(0, tab_index)
    ZEND_ARG_INFO(0, alignment)
    ZEND_ARG_INFO(0, location)
ZEND_END_ARG_INFO();

static function_entry pangotabarray_methods[] = {
	PHP_ME(PangoTabArray, __construct,          arginfo_pango_pangotabarray_pango_tab_array_new, ZEND_ACC_PUBLIC)
	PHP_ME(PangoTabArray, copy,                 NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoTabArray, free,                 NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoTabArray, get_positions_in_pixels, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoTabArray, get_size,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(PangoTabArray, resize,               arginfo_pango_pangotabarray_resize, ZEND_ACC_PUBLIC)
	PHP_ME(PangoTabArray, set_tab,              arginfo_pango_pangotabarray_set_tab, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

void phpg_pango_register_classes(void)
{
	TSRMLS_FETCH();

	pango_ce = phpg_register_class("Pango", pango_methods, NULL, 0, NULL, NULL, 0 TSRMLS_CC);

	pangocontext_ce = phpg_register_class("PangoContext", pangocontext_methods, gobject_ce, 0, NULL, NULL, PANGO_TYPE_CONTEXT TSRMLS_CC);

	pangofont_ce = phpg_register_class("PangoFont", pangofont_methods, gobject_ce, 0, NULL, NULL, PANGO_TYPE_FONT TSRMLS_CC);

	pangofontface_ce = phpg_register_class("PangoFontFace", pangofontface_methods, gobject_ce, 0, NULL, NULL, PANGO_TYPE_FONT_FACE TSRMLS_CC);

	pangofontfamily_ce = phpg_register_class("PangoFontFamily", pangofontfamily_methods, gobject_ce, 0, NULL, NULL, PANGO_TYPE_FONT_FAMILY TSRMLS_CC);

	pangofontmap_ce = phpg_register_class("PangoFontMap", pangofontmap_methods, gobject_ce, 0, NULL, NULL, PANGO_TYPE_FONT_MAP TSRMLS_CC);

	pangofontset_ce = phpg_register_class("PangoFontset", pangofontset_methods, gobject_ce, 0, NULL, NULL, PANGO_TYPE_FONTSET TSRMLS_CC);

	pangofontsetsimple_ce = phpg_register_class("PangoFontsetSimple", pangofontsetsimple_methods, pangofontset_ce, 0, NULL, NULL, PANGO_TYPE_FONTSET_SIMPLE TSRMLS_CC);

	pangolayout_ce = phpg_register_class("PangoLayout", pangolayout_methods, gobject_ce, 0, NULL, NULL, PANGO_TYPE_LAYOUT TSRMLS_CC);

    pangoattrlist_ce = phpg_register_boxed("PangoAttrList", pangoattrlist_methods, NULL, NULL, PANGO_TYPE_ATTR_LIST TSRMLS_CC);

    pangocolor_ce = phpg_register_boxed("PangoColor", pangocolor_methods, pangocolor_prop_info, NULL, PANGO_TYPE_COLOR TSRMLS_CC);

    pangofontdescription_ce = phpg_register_boxed("PangoFontDescription", pangofontdescription_methods, NULL, NULL, PANGO_TYPE_FONT_DESCRIPTION TSRMLS_CC);

    pangofontmetrics_ce = phpg_register_boxed("PangoFontMetrics", pangofontmetrics_methods, NULL, NULL, PANGO_TYPE_FONT_METRICS TSRMLS_CC);

    pangoglyphstring_ce = phpg_register_boxed("PangoGlyphString", pangoglyphstring_methods, pangoglyphstring_prop_info, NULL, PANGO_TYPE_GLYPH_STRING TSRMLS_CC);

    pangolanguage_ce = phpg_register_boxed("PangoLanguage", pangolanguage_methods, NULL, NULL, PANGO_TYPE_LANGUAGE TSRMLS_CC);

    pangolayoutiter_ce = phpg_register_boxed("PangoLayoutIter", pangolayoutiter_methods, NULL, NULL, PANGO_TYPE_LAYOUT_ITER TSRMLS_CC);

    pangotabarray_ce = phpg_register_boxed("PangoTabArray", pangotabarray_methods, NULL, NULL, PANGO_TYPE_TAB_ARRAY TSRMLS_CC);
}

void phpg_pango_register_constants(const char *strip_prefix)
{
    TSRMLS_FETCH();
	phpg_register_enum(PANGO_TYPE_ALIGNMENT, strip_prefix, pango_ce);
	phpg_register_enum(PANGO_TYPE_ATTR_TYPE, strip_prefix, pango_ce);
	phpg_register_enum(PANGO_TYPE_COVERAGE_LEVEL, strip_prefix, pango_ce);
	phpg_register_enum(PANGO_TYPE_DIRECTION, strip_prefix, pango_ce);
	phpg_register_enum(PANGO_TYPE_ELLIPSIZE_MODE, strip_prefix, pango_ce);
	phpg_register_enum(PANGO_TYPE_STRETCH, strip_prefix, pango_ce);
	phpg_register_enum(PANGO_TYPE_STYLE, strip_prefix, pango_ce);
	phpg_register_enum(PANGO_TYPE_TAB_ALIGN, strip_prefix, pango_ce);
	phpg_register_enum(PANGO_TYPE_UNDERLINE, strip_prefix, pango_ce);
	phpg_register_enum(PANGO_TYPE_VARIANT, strip_prefix, pango_ce);
	phpg_register_enum(PANGO_TYPE_WEIGHT, strip_prefix, pango_ce);
	phpg_register_enum(PANGO_TYPE_WRAP_MODE, strip_prefix, pango_ce);
	phpg_register_flags(PANGO_TYPE_FONT_MASK, strip_prefix, pango_ce);


    /* register gtype constants for all classes */

	phpg_register_int_constant(pangocontext_ce, "gtype", sizeof("gtype")-1, PANGO_TYPE_CONTEXT);
	phpg_register_int_constant(pangofont_ce, "gtype", sizeof("gtype")-1, PANGO_TYPE_FONT);
	phpg_register_int_constant(pangofontface_ce, "gtype", sizeof("gtype")-1, PANGO_TYPE_FONT_FACE);
	phpg_register_int_constant(pangofontfamily_ce, "gtype", sizeof("gtype")-1, PANGO_TYPE_FONT_FAMILY);
	phpg_register_int_constant(pangofontmap_ce, "gtype", sizeof("gtype")-1, PANGO_TYPE_FONT_MAP);
	phpg_register_int_constant(pangofontset_ce, "gtype", sizeof("gtype")-1, PANGO_TYPE_FONTSET);
	phpg_register_int_constant(pangofontsetsimple_ce, "gtype", sizeof("gtype")-1, PANGO_TYPE_FONTSET_SIMPLE);
	phpg_register_int_constant(pangolayout_ce, "gtype", sizeof("gtype")-1, PANGO_TYPE_LAYOUT);
	phpg_register_int_constant(pangoattrlist_ce, "gtype", sizeof("gtype")-1, PANGO_TYPE_ATTR_LIST);
	phpg_register_int_constant(pangocolor_ce, "gtype", sizeof("gtype")-1, PANGO_TYPE_COLOR);
	phpg_register_int_constant(pangofontdescription_ce, "gtype", sizeof("gtype")-1, PANGO_TYPE_FONT_DESCRIPTION);
	phpg_register_int_constant(pangofontmetrics_ce, "gtype", sizeof("gtype")-1, PANGO_TYPE_FONT_METRICS);
	phpg_register_int_constant(pangoglyphstring_ce, "gtype", sizeof("gtype")-1, PANGO_TYPE_GLYPH_STRING);
	phpg_register_int_constant(pangolanguage_ce, "gtype", sizeof("gtype")-1, PANGO_TYPE_LANGUAGE);
	phpg_register_int_constant(pangolayoutiter_ce, "gtype", sizeof("gtype")-1, PANGO_TYPE_LAYOUT_ITER);
	phpg_register_int_constant(pangotabarray_ce, "gtype", sizeof("gtype")-1, PANGO_TYPE_TAB_ARRAY);

}

#endif /* HAVE_PHP_GTK */
