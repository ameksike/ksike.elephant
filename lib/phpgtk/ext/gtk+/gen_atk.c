#include "php_gtk.h"

#if HAVE_PHP_GTK
#include <atk/atk.h>
#include <atk/atk-enum-types.h>
#include <atk/atknoopobjectfactory.h>
#include <atk/atknoopobject.h>


PHP_GTK_EXPORT_CE(atkhyperlink_ce);
PHP_GTK_EXPORT_CE(atkobject_ce);
PHP_GTK_EXPORT_CE(atknoopobject_ce);
PHP_GTK_EXPORT_CE(atkobjectfactory_ce);
PHP_GTK_EXPORT_CE(atknoopobjectfactory_ce);
PHP_GTK_EXPORT_CE(atkregistry_ce);
PHP_GTK_EXPORT_CE(atkrelation_ce);
PHP_GTK_EXPORT_CE(atkrelationset_ce);
PHP_GTK_EXPORT_CE(atkstateset_ce);
PHP_GTK_EXPORT_CE(atkutil_ce);
PHP_GTK_EXPORT_CE(atk_ce);

static PHP_METHOD(Atk, get_default_registry)
{
	AtkRegistry* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_get_default_registry();
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(Atk, relation_type_register)
{
	char *name;
	zend_bool free_name = FALSE;
	long php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &name, &free_name))
		return;

    php_retval = atk_relation_type_register(name);
	if (free_name) g_free(name);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(Atk, relation_type_for_name)
{
	char *name;
	zend_bool free_name = FALSE;
	long php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &name, &free_name))
		return;

    php_retval = atk_relation_type_for_name(name);
	if (free_name) g_free(name);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(Atk, state_type_for_name)
{
	char *name;
	zend_bool free_name = FALSE;
	long php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &name, &free_name))
		return;

    php_retval = atk_state_type_for_name(name);
	if (free_name) g_free(name);
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(Atk, text_attribute_get_name)
{
	AtkTextAttribute attr;
	zval *php_attr = NULL;
	const gchar *php_retval;
	gchar *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_attr))
		return;

	if (php_attr && phpg_gvalue_get_enum(ATK_TYPE_TEXT_ATTRIBUTE, php_attr, (gint *)&attr) == FAILURE) {
		return;
	}

    php_retval = atk_text_attribute_get_name(attr);
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


static PHP_METHOD(Atk, text_attribute_get_value)
{
	AtkTextAttribute attr;
	zval *php_attr = NULL;
	long index;
	const gchar *php_retval;
	gchar *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "Vi", &php_attr, &index))
		return;

	if (php_attr && phpg_gvalue_get_enum(ATK_TYPE_TEXT_ATTRIBUTE, php_attr, (gint *)&attr) == FAILURE) {
		return;
	}

    php_retval = atk_text_attribute_get_value(attr, (gint)index);
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


static PHP_METHOD(Atk, remove_focus_tracker)
{
	long tracker_id;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &tracker_id))
		return;

    atk_remove_focus_tracker((guint)tracker_id);

}


static PHP_METHOD(Atk, focus_tracker_notify)
{
	zval *object;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &object, atkobject_ce))
		return;

    atk_focus_tracker_notify(ATK_OBJECT(PHPG_GOBJECT(object)));

}


static PHP_METHOD(Atk, remove_global_event_listener)
{
	long listener_id;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &listener_id))
		return;

    atk_remove_global_event_listener((guint)listener_id);

}


static PHP_METHOD(Atk, remove_key_event_listener)
{
	long listener_id;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &listener_id))
		return;

    atk_remove_key_event_listener((guint)listener_id);

}


static PHP_METHOD(Atk, get_root)
{
	AtkObject* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_get_root();
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(Atk, get_toolkit_name)
{
	const gchar *php_retval;
	gchar *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_get_toolkit_name();
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


static PHP_METHOD(Atk, get_toolkit_version)
{
	const gchar *php_retval;
	gchar *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_get_toolkit_version();
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


static PHP_METHOD(Atk, role_for_name)
{
	char *name;
	zend_bool free_name = FALSE;
	long php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &name, &free_name))
		return;

    php_retval = atk_role_for_name(name);
	if (free_name) g_free(name);
	RETVAL_LONG(php_retval);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atk_relation_type_register, 0)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atk_relation_type_for_name, 0)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atk_state_type_for_name, 0)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atk_text_attribute_get_name, 0)
    ZEND_ARG_INFO(0, attr)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atk_text_attribute_get_value, 0)
    ZEND_ARG_INFO(0, attr)
    ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atk_remove_focus_tracker, 0)
    ZEND_ARG_INFO(0, tracker_id)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atk_focus_tracker_notify, 0)
    ZEND_ARG_OBJ_INFO(0, object, AtkObject, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atk_remove_global_event_listener, 0)
    ZEND_ARG_INFO(0, listener_id)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atk_remove_key_event_listener, 0)
    ZEND_ARG_INFO(0, listener_id)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atk_role_for_name, 0)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO();

static function_entry atk_methods[] = {
	PHP_ME(Atk, focus_tracker_notify, arginfo_atk_atk_focus_tracker_notify, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Atk, get_default_registry, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Atk, get_root,             NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Atk, get_toolkit_name,     NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Atk, get_toolkit_version,  NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Atk, relation_type_for_name, arginfo_atk_atk_relation_type_for_name, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Atk, relation_type_register, arginfo_atk_atk_relation_type_register, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Atk, remove_focus_tracker, arginfo_atk_atk_remove_focus_tracker, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Atk, remove_global_event_listener, arginfo_atk_atk_remove_global_event_listener, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Atk, remove_key_event_listener, arginfo_atk_atk_remove_key_event_listener, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Atk, role_for_name,        arginfo_atk_atk_role_for_name, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Atk, state_type_for_name,  arginfo_atk_atk_state_type_for_name, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Atk, text_attribute_get_name, arginfo_atk_atk_text_attribute_get_name, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Atk, text_attribute_get_value, arginfo_atk_atk_text_attribute_get_value, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(AtkHyperlink, get_uri)
{
	long i;
	gchar *php_retval, *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &i))
		return;

    php_retval = atk_hyperlink_get_uri(ATK_HYPERLINK(PHPG_GOBJECT(this_ptr)), (gint)i);
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


static PHP_METHOD(AtkHyperlink, get_object)
{
	long i;
	AtkObject* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &i))
		return;

    php_retval = atk_hyperlink_get_object(ATK_HYPERLINK(PHPG_GOBJECT(this_ptr)), (gint)i);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(AtkHyperlink, get_end_index)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_hyperlink_get_end_index(ATK_HYPERLINK(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(AtkHyperlink, get_start_index)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_hyperlink_get_start_index(ATK_HYPERLINK(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(AtkHyperlink, is_valid)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_hyperlink_is_valid(ATK_HYPERLINK(PHPG_GOBJECT(this_ptr)));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(AtkHyperlink, get_n_anchors)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_hyperlink_get_n_anchors(ATK_HYPERLINK(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkhyperlink_get_uri, 0)
    ZEND_ARG_INFO(0, i)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkhyperlink_get_object, 0)
    ZEND_ARG_INFO(0, i)
ZEND_END_ARG_INFO();

static function_entry atkhyperlink_methods[] = {
	PHP_ME(AtkHyperlink, get_end_index,        NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkHyperlink, get_n_anchors,        NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkHyperlink, get_object,           arginfo_atk_atkhyperlink_get_object, ZEND_ACC_PUBLIC)
	PHP_ME(AtkHyperlink, get_start_index,      NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkHyperlink, get_uri,              arginfo_atk_atkhyperlink_get_uri, ZEND_ACC_PUBLIC)
	PHP_ME(AtkHyperlink, is_valid,             NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(AtkObject, get_name)
{
	const gchar *php_retval;
	gchar *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_object_get_name(ATK_OBJECT(PHPG_GOBJECT(this_ptr)));
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


static PHP_METHOD(AtkObject, get_description)
{
	const gchar *php_retval;
	gchar *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_object_get_description(ATK_OBJECT(PHPG_GOBJECT(this_ptr)));
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


static PHP_METHOD(AtkObject, get_parent)
{
	AtkObject* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_object_get_parent(ATK_OBJECT(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(AtkObject, get_n_accessible_children)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_object_get_n_accessible_children(ATK_OBJECT(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(AtkObject, ref_accessible_child)
{
	long i;
	AtkObject* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &i))
		return;

    php_retval = atk_object_ref_accessible_child(ATK_OBJECT(PHPG_GOBJECT(this_ptr)), (gint)i);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(AtkObject, ref_relation_set)
{
	AtkRelationSet* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_object_ref_relation_set(ATK_OBJECT(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(AtkObject, get_role)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_object_get_role(ATK_OBJECT(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(AtkObject, get_layer)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_object_get_layer(ATK_OBJECT(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(AtkObject, get_mdi_zorder)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_object_get_mdi_zorder(ATK_OBJECT(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(AtkObject, ref_state_set)
{
	AtkStateSet* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_object_ref_state_set(ATK_OBJECT(PHPG_GOBJECT(this_ptr)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(AtkObject, get_index_in_parent)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_object_get_index_in_parent(ATK_OBJECT(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(AtkObject, set_name)
{
	char *name;
	zend_bool free_name = FALSE;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &name, &free_name))
		return;

    atk_object_set_name(ATK_OBJECT(PHPG_GOBJECT(this_ptr)), name);
	if (free_name) g_free(name);

}


static PHP_METHOD(AtkObject, set_description)
{
	char *description;
	zend_bool free_description = FALSE;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &description, &free_description))
		return;

    atk_object_set_description(ATK_OBJECT(PHPG_GOBJECT(this_ptr)), description);
	if (free_description) g_free(description);

}


static PHP_METHOD(AtkObject, set_parent)
{
	zval *parent;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &parent, atkobject_ce))
		return;

    atk_object_set_parent(ATK_OBJECT(PHPG_GOBJECT(this_ptr)), ATK_OBJECT(PHPG_GOBJECT(parent)));

}


static PHP_METHOD(AtkObject, set_role)
{
	AtkRole role;
	zval *php_role = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_role))
		return;

	if (php_role && phpg_gvalue_get_enum(ATK_TYPE_ROLE, php_role, (gint *)&role) == FAILURE) {
		return;
	}

    atk_object_set_role(ATK_OBJECT(PHPG_GOBJECT(this_ptr)), role);

}


static PHP_METHOD(AtkObject, remove_property_change_handler)
{
	long handler_id;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &handler_id))
		return;

    atk_object_remove_property_change_handler(ATK_OBJECT(PHPG_GOBJECT(this_ptr)), (guint)handler_id);

}


static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkobject_ref_accessible_child, 0)
    ZEND_ARG_INFO(0, i)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkobject_set_name, 0)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkobject_set_description, 0)
    ZEND_ARG_INFO(0, description)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkobject_set_parent, 0)
    ZEND_ARG_OBJ_INFO(0, parent, AtkObject, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkobject_set_role, 0)
    ZEND_ARG_INFO(0, role)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkobject_remove_property_change_handler, 0)
    ZEND_ARG_INFO(0, handler_id)
ZEND_END_ARG_INFO();

static function_entry atkobject_methods[] = {
	PHP_ME(AtkObject, get_description,      NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkObject, get_index_in_parent,  NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkObject, get_layer,            NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkObject, get_mdi_zorder,       NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkObject, get_n_accessible_children, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkObject, get_name,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkObject, get_parent,           NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkObject, get_role,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkObject, ref_accessible_child, arginfo_atk_atkobject_ref_accessible_child, ZEND_ACC_PUBLIC)
	PHP_ME(AtkObject, ref_relation_set,     NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkObject, ref_state_set,        NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkObject, remove_property_change_handler, arginfo_atk_atkobject_remove_property_change_handler, ZEND_ACC_PUBLIC)
	PHP_ME(AtkObject, set_description,      arginfo_atk_atkobject_set_description, ZEND_ACC_PUBLIC)
	PHP_ME(AtkObject, set_name,             arginfo_atk_atkobject_set_name, ZEND_ACC_PUBLIC)
	PHP_ME(AtkObject, set_parent,           arginfo_atk_atkobject_set_parent, ZEND_ACC_PUBLIC)
	PHP_ME(AtkObject, set_role,             arginfo_atk_atkobject_set_role, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(AtkNoOpObject, __construct)
{
	zval *obj;
	GObject *wrapped_obj;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &obj, gobject_ce)) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(AtkNoOpObject);
	}

	wrapped_obj = (GObject *) atk_no_op_object_new(G_OBJECT(PHPG_GOBJECT(obj)));

	if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(AtkNoOpObject);
	}

    phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atknoopobject_atk_no_op_object_new, 0)
    ZEND_ARG_OBJ_INFO(0, obj, GObject, 1)
ZEND_END_ARG_INFO();

static function_entry atknoopobject_methods[] = {
	PHP_ME(AtkNoOpObject, __construct,          arginfo_atk_atknoopobject_atk_no_op_object_new, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(AtkObjectFactory, create_accessible)
{
	zval *obj;
	AtkObject* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &obj, gobject_ce))
		return;

    php_retval = atk_object_factory_create_accessible(ATK_OBJECT_FACTORY(PHPG_GOBJECT(this_ptr)), G_OBJECT(PHPG_GOBJECT(obj)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(AtkObjectFactory, invalidate)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    atk_object_factory_invalidate(ATK_OBJECT_FACTORY(PHPG_GOBJECT(this_ptr)));

}


static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkobjectfactory_create_accessible, 0)
    ZEND_ARG_OBJ_INFO(0, obj, GObject, 1)
ZEND_END_ARG_INFO();

static function_entry atkobjectfactory_methods[] = {
	PHP_ME(AtkObjectFactory, create_accessible,    arginfo_atk_atkobjectfactory_create_accessible, ZEND_ACC_PUBLIC)
	PHP_ME(AtkObjectFactory, invalidate,           NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(AtkNoOpObjectFactory, __construct)
{
    GObject *wrapped_obj;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "")) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(AtkNoOpObjectFactory);
    }


    wrapped_obj = (GObject *) g_object_newv(phpg_gtype_from_zval(this_ptr), 0, NULL);

    if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(AtkNoOpObjectFactory);
    }

    phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}


static function_entry atknoopobjectfactory_methods[] = {
	PHP_ME(AtkNoOpObjectFactory, __construct,          NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(AtkRegistry, set_factory_type)
{
	GType type, factory_type;
	zval *php_type = NULL, *php_factory_type = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "VV", &php_type, &php_factory_type))
		return;
    if ((type = phpg_gtype_from_zval(php_type)) == 0) {
        return;
    }
    if ((factory_type = phpg_gtype_from_zval(php_factory_type)) == 0) {
        return;
    }

    atk_registry_set_factory_type(ATK_REGISTRY(PHPG_GOBJECT(this_ptr)), type, factory_type);

}


static PHP_METHOD(AtkRegistry, get_factory_type)
{
	GType type, php_retval;
	zval *php_type = NULL;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_type))
		return;
    if ((type = phpg_gtype_from_zval(php_type)) == 0) {
        return;
    }

    php_retval = atk_registry_get_factory_type(ATK_REGISTRY(PHPG_GOBJECT(this_ptr)), type);
    phpg_gtype_new(return_value, php_retval TSRMLS_CC);

}


static PHP_METHOD(AtkRegistry, get_factory)
{
	GType type;
	zval *php_type = NULL;
	AtkObjectFactory* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_type))
		return;
    if ((type = phpg_gtype_from_zval(php_type)) == 0) {
        return;
    }

    php_retval = atk_registry_get_factory(ATK_REGISTRY(PHPG_GOBJECT(this_ptr)), type);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkregistry_set_factory_type, 0)
    ZEND_ARG_OBJ_INFO(0, type, GType, 1)
    ZEND_ARG_OBJ_INFO(0, factory_type, GType, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkregistry_get_factory_type, 0)
    ZEND_ARG_OBJ_INFO(0, type, GType, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkregistry_get_factory, 0)
    ZEND_ARG_OBJ_INFO(0, type, GType, 1)
ZEND_END_ARG_INFO();

static function_entry atkregistry_methods[] = {
	PHP_ME(AtkRegistry, get_factory,          arginfo_atk_atkregistry_get_factory, ZEND_ACC_PUBLIC)
	PHP_ME(AtkRegistry, get_factory_type,     arginfo_atk_atkregistry_get_factory_type, ZEND_ACC_PUBLIC)
	PHP_ME(AtkRegistry, set_factory_type,     arginfo_atk_atkregistry_set_factory_type, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
#line 25 "ext/gtk+/atk.overrides"
static PHP_METHOD(AtkRelation, __construct)
{
	zval *php_targets, *php_relationship = NULL;
	gint n_targets, i = 0;
	AtkRelationType relationship;
	AtkObject **targets = NULL;
	zval **temp_target;
	GObject *wrapped_obj = NULL;

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "aV", &php_targets, &php_relationship)) {
		PHPG_THROW_CONSTRUCT_EXCEPTION(AtkRelationObject);
	}

	if (php_relationship && phpg_gvalue_get_enum(ATK_TYPE_RELATION_TYPE, php_relationship, (gint *)&relationship) == FAILURE) {
		PHPG_THROW_CONSTRUCT_EXCEPTION(AtkRelationObject);
	}

	n_targets = zend_hash_num_elements(Z_ARRVAL_P(php_targets));
	targets = safe_emalloc(n_targets+1, sizeof(AtkObject *), 0);

	zend_hash_internal_pointer_reset(Z_ARRVAL_P(php_targets));
	while (zend_hash_get_current_data(Z_ARRVAL_P(php_targets), (void **)&temp_target) == SUCCESS) {
		targets[i] = ATK_OBJECT(PHPG_GOBJECT(*temp_target));
		zend_hash_move_forward(Z_ARRVAL_P(php_targets));
		i++;
	}

	wrapped_obj = (GObject *) atk_relation_new(targets, n_targets, relationship);
	efree(targets);

	if (!wrapped_obj) {
		PHPG_THROW_CONSTRUCT_EXCEPTION(AtkRelationObject);
	}
	phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}

#line 982 "ext/gtk+/gen_atk.c"



static PHP_METHOD(AtkRelation, get_relation_type)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_relation_get_relation_type(ATK_RELATION(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkrelation_relation_new, 0)
    ZEND_ARG_INFO(0, targets)
    ZEND_ARG_INFO(0, relationship)
ZEND_END_ARG_INFO();


static function_entry atkrelation_methods[] = {
	PHP_ME(AtkRelation, __construct,          arginfo_atk_atkrelation_relation_new, ZEND_ACC_PUBLIC)
	PHP_ME(AtkRelation, get_relation_type,    NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(AtkRelationSet, __construct)
{
    GObject *wrapped_obj;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "")) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(AtkRelationSet);
    }


    wrapped_obj = (GObject *) g_object_newv(phpg_gtype_from_zval(this_ptr), 0, NULL);

    if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(AtkRelationSet);
    }

    phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}


static PHP_METHOD(AtkRelationSet, contains)
{
	AtkRelationType relationship;
	zval *php_relationship = NULL;
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_relationship))
		return;

	if (php_relationship && phpg_gvalue_get_enum(ATK_TYPE_RELATION_TYPE, php_relationship, (gint *)&relationship) == FAILURE) {
		return;
	}

    php_retval = atk_relation_set_contains(ATK_RELATION_SET(PHPG_GOBJECT(this_ptr)), relationship);
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(AtkRelationSet, remove)
{
	zval *relation;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &relation, atkrelation_ce))
		return;

    atk_relation_set_remove(ATK_RELATION_SET(PHPG_GOBJECT(this_ptr)), ATK_RELATION(PHPG_GOBJECT(relation)));

}


static PHP_METHOD(AtkRelationSet, add)
{
	zval *relation;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &relation, atkrelation_ce))
		return;

    atk_relation_set_add(ATK_RELATION_SET(PHPG_GOBJECT(this_ptr)), ATK_RELATION(PHPG_GOBJECT(relation)));

}


static PHP_METHOD(AtkRelationSet, get_n_relations)
{
	long php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_relation_set_get_n_relations(ATK_RELATION_SET(PHPG_GOBJECT(this_ptr)));
	RETVAL_LONG(php_retval);
}


static PHP_METHOD(AtkRelationSet, get_relation)
{
	long i;
	AtkRelation* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "i", &i))
		return;

    php_retval = atk_relation_set_get_relation(ATK_RELATION_SET(PHPG_GOBJECT(this_ptr)), (gint)i);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(AtkRelationSet, get_relation_by_type)
{
	AtkRelationType relationship;
	zval *php_relationship = NULL;
	AtkRelation* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_relationship))
		return;

	if (php_relationship && phpg_gvalue_get_enum(ATK_TYPE_RELATION_TYPE, php_relationship, (gint *)&relationship) == FAILURE) {
		return;
	}

    php_retval = atk_relation_set_get_relation_by_type(ATK_RELATION_SET(PHPG_GOBJECT(this_ptr)), relationship);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(AtkRelationSet, add_relation_by_type)
{
	AtkRelationType relationship;
	zval *php_relationship = NULL, *target;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "VO", &php_relationship, &target, atkobject_ce))
		return;

	if (php_relationship && phpg_gvalue_get_enum(ATK_TYPE_RELATION_TYPE, php_relationship, (gint *)&relationship) == FAILURE) {
		return;
	}

    atk_relation_set_add_relation_by_type(ATK_RELATION_SET(PHPG_GOBJECT(this_ptr)), relationship, ATK_OBJECT(PHPG_GOBJECT(target)));

}


static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkrelationset_contains, 0)
    ZEND_ARG_INFO(0, relationship)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkrelationset_remove, 0)
    ZEND_ARG_OBJ_INFO(0, relation, AtkRelation, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkrelationset_add, 0)
    ZEND_ARG_OBJ_INFO(0, relation, AtkRelation, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkrelationset_get_relation, 0)
    ZEND_ARG_INFO(0, i)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkrelationset_get_relation_by_type, 0)
    ZEND_ARG_INFO(0, relationship)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkrelationset_add_relation_by_type, 0)
    ZEND_ARG_INFO(0, relationship)
    ZEND_ARG_OBJ_INFO(0, target, AtkObject, 1)
ZEND_END_ARG_INFO();

static function_entry atkrelationset_methods[] = {
	PHP_ME(AtkRelationSet, __construct,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkRelationSet, add,                  arginfo_atk_atkrelationset_add, ZEND_ACC_PUBLIC)
	PHP_ME(AtkRelationSet, add_relation_by_type, arginfo_atk_atkrelationset_add_relation_by_type, ZEND_ACC_PUBLIC)
	PHP_ME(AtkRelationSet, contains,             arginfo_atk_atkrelationset_contains, ZEND_ACC_PUBLIC)
	PHP_ME(AtkRelationSet, get_n_relations,      NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkRelationSet, get_relation,         arginfo_atk_atkrelationset_get_relation, ZEND_ACC_PUBLIC)
	PHP_ME(AtkRelationSet, get_relation_by_type, arginfo_atk_atkrelationset_get_relation_by_type, ZEND_ACC_PUBLIC)
	PHP_ME(AtkRelationSet, remove,               arginfo_atk_atkrelationset_remove, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

static PHP_METHOD(AtkStateSet, __construct)
{
    GObject *wrapped_obj;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "")) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(AtkStateSet);
    }


    wrapped_obj = (GObject *) g_object_newv(phpg_gtype_from_zval(this_ptr), 0, NULL);

    if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(AtkStateSet);
    }

    phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}


static PHP_METHOD(AtkStateSet, is_empty)
{
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    php_retval = atk_state_set_is_empty(ATK_STATE_SET(PHPG_GOBJECT(this_ptr)));
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(AtkStateSet, add_state)
{
	AtkStateType type;
	zval *php_type = NULL;
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_type))
		return;

	if (php_type && phpg_gvalue_get_enum(ATK_TYPE_STATE_TYPE, php_type, (gint *)&type) == FAILURE) {
		return;
	}

    php_retval = atk_state_set_add_state(ATK_STATE_SET(PHPG_GOBJECT(this_ptr)), type);
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(AtkStateSet, clear_states)
{

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), ""))
		return;

    atk_state_set_clear_states(ATK_STATE_SET(PHPG_GOBJECT(this_ptr)));

}


static PHP_METHOD(AtkStateSet, contains_state)
{
	AtkStateType type;
	zval *php_type = NULL;
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_type))
		return;

	if (php_type && phpg_gvalue_get_enum(ATK_TYPE_STATE_TYPE, php_type, (gint *)&type) == FAILURE) {
		return;
	}

    php_retval = atk_state_set_contains_state(ATK_STATE_SET(PHPG_GOBJECT(this_ptr)), type);
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(AtkStateSet, remove_state)
{
	AtkStateType type;
	zval *php_type = NULL;
	gboolean php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "V", &php_type))
		return;

	if (php_type && phpg_gvalue_get_enum(ATK_TYPE_STATE_TYPE, php_type, (gint *)&type) == FAILURE) {
		return;
	}

    php_retval = atk_state_set_remove_state(ATK_STATE_SET(PHPG_GOBJECT(this_ptr)), type);
	RETVAL_BOOL(php_retval);
}


static PHP_METHOD(AtkStateSet, and_sets)
{
	zval *compare_set;
	AtkStateSet* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &compare_set, atkstateset_ce))
		return;

    php_retval = atk_state_set_and_sets(ATK_STATE_SET(PHPG_GOBJECT(this_ptr)), ATK_STATE_SET(PHPG_GOBJECT(compare_set)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(AtkStateSet, or_sets)
{
	zval *compare_set;
	AtkStateSet* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &compare_set, atkstateset_ce))
		return;

    php_retval = atk_state_set_or_sets(ATK_STATE_SET(PHPG_GOBJECT(this_ptr)), ATK_STATE_SET(PHPG_GOBJECT(compare_set)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static PHP_METHOD(AtkStateSet, xor_sets)
{
	zval *compare_set;
	AtkStateSet* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &compare_set, atkstateset_ce))
		return;

    php_retval = atk_state_set_xor_sets(ATK_STATE_SET(PHPG_GOBJECT(this_ptr)), ATK_STATE_SET(PHPG_GOBJECT(compare_set)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkstateset_add_state, 0)
    ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkstateset_contains_state, 0)
    ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkstateset_remove_state, 0)
    ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkstateset_and_sets, 0)
    ZEND_ARG_OBJ_INFO(0, compare_set, AtkStateSet, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkstateset_or_sets, 0)
    ZEND_ARG_OBJ_INFO(0, compare_set, AtkStateSet, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_atk_atkstateset_xor_sets, 0)
    ZEND_ARG_OBJ_INFO(0, compare_set, AtkStateSet, 1)
ZEND_END_ARG_INFO();

static function_entry atkstateset_methods[] = {
	PHP_ME(AtkStateSet, __construct,          NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkStateSet, add_state,            arginfo_atk_atkstateset_add_state, ZEND_ACC_PUBLIC)
	PHP_ME(AtkStateSet, and_sets,             arginfo_atk_atkstateset_and_sets, ZEND_ACC_PUBLIC)
	PHP_ME(AtkStateSet, clear_states,         NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkStateSet, contains_state,       arginfo_atk_atkstateset_contains_state, ZEND_ACC_PUBLIC)
	PHP_ME(AtkStateSet, is_empty,             NULL, ZEND_ACC_PUBLIC)
	PHP_ME(AtkStateSet, or_sets,              arginfo_atk_atkstateset_or_sets, ZEND_ACC_PUBLIC)
	PHP_ME(AtkStateSet, remove_state,         arginfo_atk_atkstateset_remove_state, ZEND_ACC_PUBLIC)
	PHP_ME(AtkStateSet, xor_sets,             arginfo_atk_atkstateset_xor_sets, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

void phpg_atk_register_classes(void)
{
	TSRMLS_FETCH();

	atk_ce = phpg_register_class("Atk", atk_methods, NULL, 0, NULL, NULL, 0 TSRMLS_CC);

	atkhyperlink_ce = phpg_register_class("AtkHyperlink", atkhyperlink_methods, gobject_ce, 0, NULL, NULL, ATK_TYPE_HYPERLINK TSRMLS_CC);

	atkobject_ce = phpg_register_class("AtkObject", atkobject_methods, gobject_ce, 0, NULL, NULL, ATK_TYPE_OBJECT TSRMLS_CC);

	atknoopobject_ce = phpg_register_class("AtkNoOpObject", atknoopobject_methods, atkobject_ce, 0, NULL, NULL, ATK_TYPE_NO_OP_OBJECT TSRMLS_CC);

	atkobjectfactory_ce = phpg_register_class("AtkObjectFactory", atkobjectfactory_methods, gobject_ce, 0, NULL, NULL, ATK_TYPE_OBJECT_FACTORY TSRMLS_CC);

	atknoopobjectfactory_ce = phpg_register_class("AtkNoOpObjectFactory", atknoopobjectfactory_methods, atkobjectfactory_ce, 0, NULL, NULL, ATK_TYPE_NO_OP_OBJECT_FACTORY TSRMLS_CC);

	atkregistry_ce = phpg_register_class("AtkRegistry", atkregistry_methods, gobject_ce, 0, NULL, NULL, ATK_TYPE_REGISTRY TSRMLS_CC);

	atkrelation_ce = phpg_register_class("AtkRelation", atkrelation_methods, gobject_ce, 0, NULL, NULL, ATK_TYPE_RELATION TSRMLS_CC);

	atkrelationset_ce = phpg_register_class("AtkRelationSet", atkrelationset_methods, gobject_ce, 0, NULL, NULL, ATK_TYPE_RELATION_SET TSRMLS_CC);

	atkstateset_ce = phpg_register_class("AtkStateSet", atkstateset_methods, gobject_ce, 0, NULL, NULL, ATK_TYPE_STATE_SET TSRMLS_CC);

	atkutil_ce = phpg_register_class("AtkUtil", NULL, gobject_ce, 0, NULL, NULL, ATK_TYPE_UTIL TSRMLS_CC);
}

void phpg_atk_register_constants(const char *strip_prefix)
{
    TSRMLS_FETCH();
	phpg_register_enum(ATK_TYPE_ROLE, strip_prefix, atk_ce);
	phpg_register_enum(ATK_TYPE_LAYER, strip_prefix, atk_ce);
	phpg_register_enum(ATK_TYPE_RELATION_TYPE, strip_prefix, atk_ce);
	phpg_register_enum(ATK_TYPE_STATE_TYPE, strip_prefix, atk_ce);
	phpg_register_enum(ATK_TYPE_TEXT_ATTRIBUTE, strip_prefix, atk_ce);
	phpg_register_enum(ATK_TYPE_TEXT_BOUNDARY, strip_prefix, atk_ce);
	phpg_register_enum(ATK_TYPE_KEY_EVENT_TYPE, strip_prefix, atk_ce);
	phpg_register_enum(ATK_TYPE_COORD_TYPE, strip_prefix, atk_ce);


    /* register gtype constants for all classes */

	phpg_register_int_constant(atkhyperlink_ce, "gtype", sizeof("gtype")-1, ATK_TYPE_HYPERLINK);
	phpg_register_int_constant(atkobject_ce, "gtype", sizeof("gtype")-1, ATK_TYPE_OBJECT);
	phpg_register_int_constant(atknoopobject_ce, "gtype", sizeof("gtype")-1, ATK_TYPE_NO_OP_OBJECT);
	phpg_register_int_constant(atkobjectfactory_ce, "gtype", sizeof("gtype")-1, ATK_TYPE_OBJECT_FACTORY);
	phpg_register_int_constant(atknoopobjectfactory_ce, "gtype", sizeof("gtype")-1, ATK_TYPE_NO_OP_OBJECT_FACTORY);
	phpg_register_int_constant(atkregistry_ce, "gtype", sizeof("gtype")-1, ATK_TYPE_REGISTRY);
	phpg_register_int_constant(atkrelation_ce, "gtype", sizeof("gtype")-1, ATK_TYPE_RELATION);
	phpg_register_int_constant(atkrelationset_ce, "gtype", sizeof("gtype")-1, ATK_TYPE_RELATION_SET);
	phpg_register_int_constant(atkstateset_ce, "gtype", sizeof("gtype")-1, ATK_TYPE_STATE_SET);
	phpg_register_int_constant(atkutil_ce, "gtype", sizeof("gtype")-1, ATK_TYPE_UTIL);

}

#endif /* HAVE_PHP_GTK */
