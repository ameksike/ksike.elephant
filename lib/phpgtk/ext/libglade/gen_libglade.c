#include "php_gtk.h"

#if HAVE_PHP_GTK
#include <glade/glade.h>
#include "php_gtk_api.h"

typedef struct {
    zval *instance;
    zval *extra;
} phpg_autoc_t;

static void phpg_glade_signal_connect_auto(const gchar *handler_name, GObject *object,
                                           const gchar *signal_name, const gchar *signal_data,
                                           GObject *connect_object, gboolean after, phpg_autoc_t *data);


PHP_GTK_EXPORT_CE(gladexml_ce);
PHP_GTK_EXPORT_CE(glade_ce);

static PHP_METHOD(Glade, get_widget_name)
{
	zval *widget;
	const gchar *php_retval;
	gchar *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &widget, gtkwidget_ce))
		return;

    php_retval = glade_get_widget_name(GTK_WIDGET(PHPG_GOBJECT(widget)));
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


static PHP_METHOD(Glade, get_widget_tree)
{
	zval *widget;
	GladeXML* php_retval;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "O", &widget, gtkwidget_ce))
		return;

    php_retval = glade_get_widget_tree(GTK_WIDGET(PHPG_GOBJECT(widget)));
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}


static
ZEND_BEGIN_ARG_INFO(arginfo_glade_glade_get_widget_name, 0)
    ZEND_ARG_OBJ_INFO(0, widget, GtkWidget, 1)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO(arginfo_glade_glade_get_widget_tree, 0)
    ZEND_ARG_OBJ_INFO(0, widget, GtkWidget, 1)
ZEND_END_ARG_INFO();

static function_entry glade_methods[] = {
	PHP_ME(Glade, get_widget_name,      arginfo_glade_glade_get_widget_name, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glade, get_widget_tree,      arginfo_glade_glade_get_widget_tree, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{ NULL, NULL, NULL }
};
#line 47 "ext/libglade/libglade.overrides"
static PHP_METHOD(GladeXML, __construct)
{
    char *fname, *root = NULL, *domain = NULL;
    zend_bool free_fname, free_root, free_domain;
    GObject *wrapped_obj;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u|uu", &fname, &free_fname, &root, &free_root, &domain, &free_domain)) {
        return;
    }

    wrapped_obj = (GObject *) glade_xml_new(fname, (const char *)root, (const char *)domain);

    if (free_fname) g_free(fname);
    if (free_root) g_free(root);
    if (free_domain) g_free(domain);

    if (!wrapped_obj) {
        PHPG_THROW_CONSTRUCT_EXCEPTION(GladeXML);
    }

    phpg_gobject_set_wrapper(this_ptr, wrapped_obj TSRMLS_CC);
}

#line 100 "ext/libglade/gen_libglade.c"


#line 81 "ext/libglade/libglade.overrides"
static PHP_METHOD(GladeXML, new_from_buffer)
{
    char *buf, *root = NULL, *domain = NULL;
    zend_bool free_buf, free_root, free_domain;
    int buf_len;
    GladeXML *glade_obj;

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u#|uu", &buf, &buf_len, &free_buf, &root, &free_root, &domain, &free_domain)) {
        return;
    }

    glade_obj = glade_xml_new_from_buffer(buf, buf_len, (const char *)root, (const char *)domain);

    if (free_buf) g_free(buf);
    if (free_root) g_free(root);
    if (free_domain) g_free(domain);

    phpg_gobject_new(&return_value, (GObject *)glade_obj TSRMLS_CC);
}

#line 124 "ext/libglade/gen_libglade.c"



PHPG_PROP_READER(GladeXML, filename)
{
	const gchar *php_retval;
	gchar *cp_ret;
	gsize cp_len;
	zend_bool free_result;

    php_retval = GLADE_XML(((phpg_gobject_t *)object)->obj)->filename;
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


static prop_info_t gladexml_prop_info[] = {
	{ "filename", PHPG_PROP_READ_FN(GladeXML, filename), NULL },
	{ NULL, NULL, NULL },
};

#line 137 "ext/libglade/libglade.overrides"
static void phpg_glade_signal_connect_one(const gchar *handler_name, GObject *object,
                                          const gchar *signal_name, const gchar *signal_data,
                                          GObject *connect_object, gboolean after,
                                          gpointer *data)
{
    phpg_cb_data_t *cbd = (phpg_cb_data_t *)data;
    int handler_id;
    GClosure *closure = NULL;
    zval *php_object = NULL, *php_connect_object = NULL;
    TSRMLS_FETCH();

    if (connect_object) {
        phpg_gobject_new(&php_connect_object, (GObject*)connect_object TSRMLS_CC);
        closure = phpg_closure_new(cbd->callback, cbd->user_args, PHPG_CONNECT_REPLACE, php_connect_object TSRMLS_CC);
        zval_ptr_dtor(&php_connect_object);
    } else {
        closure = phpg_closure_new(cbd->callback, cbd->user_args, PHPG_CONNECT_NORMAL, NULL TSRMLS_CC);
    }

    phpg_gobject_new(&php_object, (GObject*)object TSRMLS_CC);
    phpg_gobject_watch_closure(php_object, closure TSRMLS_CC);
    handler_id = g_signal_connect_closure(object, signal_name, closure, after);

    zval_ptr_dtor(&php_object);
}

static PHP_METHOD(GladeXML, signal_connect)
{
    char *handlername = NULL;
    zval *callback = NULL, *extra = NULL;
    zend_bool free_handlername;
    phpg_cb_data_t *data;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_varargs(ZEND_NUM_ARGS(), 2, &extra, "uV", &handlername, &free_handlername, &callback))
        return;

    zval_add_ref(&callback);
    data = phpg_cb_data_new(callback, extra TSRMLS_CC);

    glade_xml_signal_connect_full(GLADE_XML(PHPG_GOBJECT(this_ptr)), handlername, 
                                  (GladeXMLConnectFunc)phpg_glade_signal_connect_one, data);

    if (free_handlername) g_free(handlername);
    phpg_cb_data_destroy(data);

    RETURN_NULL();
}

#line 208 "ext/libglade/gen_libglade.c"


#line 189 "ext/libglade/libglade.overrides"
static void phpg_glade_signal_connect_auto(const gchar *handler_name, GObject *object,
                                           const gchar *signal_name, const gchar *signal_data,
                                           GObject *connect_object, gboolean after, phpg_autoc_t *data)
{
    zval *callback = NULL, *php_object = NULL, *user_args = NULL;
    zval **callback_data = NULL, **callback_ptr = NULL;
    GClosure *closure = NULL;
    int handler_id, len = 0, connect_normal = 1;
    char *php_class = NULL, *php_method = NULL;
    zend_class_entry *ce = NULL, **pce;
    TSRMLS_FETCH();

    /*
     * First, check if the handler represents a static method. This can be used to invoke
     * Gtk/Gdk functions, such as Gtk::main_quit(). It may refer to a user class, of
     * course, but those connections are much less useful.
     */
    if (strstr(handler_name, "::")) {
        len = strcspn(handler_name, ":");
        php_class = safe_estrndup(handler_name, len);
        php_method = strstr(handler_name, "::") + 2;
        if (zend_lookup_class(php_class, strlen(php_class), &pce TSRMLS_CC) == SUCCESS) {
            ce = *pce;
            if (ce->type == ZEND_INTERNAL_CLASS) {
                connect_normal = 0;
            }
        }
        MAKE_STD_ZVAL(callback);
        array_init(callback);
        add_next_index_string(callback, php_class, 1);
        add_next_index_string(callback, php_method, 1);
        efree(php_class);
    } else {
        /*
         * Secondly, check if we are supposed to connect handlers to methods of the
         * specified object - signal_autoconnect_instance().
         */
        if (data->instance) {
            MAKE_STD_ZVAL(callback);
            array_init(callback);
            zval_add_ref(&data->instance);
            add_next_index_zval(callback, data->instance);
            add_next_index_string(callback, (char *)handler_name, 1);
            user_args = data->extra;

            /*
             * We verify callability right away, because classes cannot acquire new
             * methods at runtime (unless you decide to stab yourself in the foot with
             * runkit).
             */ 
            if (!zend_is_callable(callback, 0, NULL)) {
                php_error(E_NOTICE, "Unable to auto-connect handler '%s': no such method in the specified object of class '%s'", handler_name, Z_OBJCE_P(data->instance)->name);
                return;
            }
        } else {
            /*
             * Thirdly, if we have no object, we must have a map representing non-default
             * handler mappings of the form:
             *
             *   array('handler' => <callback>)
             *   array('handler' => array(<callback> [, $arg1, $arg2, ...]))
             *   array('handler' => array(null [, $arg1, $arg2, ...]))
             *
             * where <callback> is the standard PHP callback form. If null is specified
             * instead of callback, the connection will be made to the function of the
             * same name as the handler.
             */
            if (data->extra && zend_hash_find(Z_ARRVAL_P(data->extra), (char *)handler_name, strlen(handler_name) + 1, (void **)&callback_data) == SUCCESS) {
                /* Check if the value is callable. */
                if (zend_is_callable(*callback_data, 0, NULL)) {
                    zval_add_ref(callback_data);
                    callback = *callback_data;
                } else {
                    /*
                     * If not, check that it is an array with at least one entry, which is
                     * assumed to be the callback reference.
                     */ 
                    if (Z_TYPE_PP(callback_data) != IS_ARRAY ||
                        zend_hash_index_find(Z_ARRVAL_PP(callback_data), 0, (void **)&callback_ptr) == FAILURE) {
                        php_error(E_NOTICE, "Unable to auto-connect handler '%s': invalid callback data structure", handler_name);
                        return; 
                    }
                    if (Z_TYPE_PP(callback_ptr) != IS_NULL) {
                        zval_add_ref(callback_ptr);
                        callback = *callback_ptr;
                    }

                    /* Shift callback data - the rest are extra user arguments. */
                    zend_hash_index_del(Z_ARRVAL_PP(callback_data), 0);
                    user_args = *callback_data;
                }
            }
        }
    }

    /*
     * Make a simple function callback if everything else failed. 
     */
    if (callback == NULL) {
        MAKE_STD_ZVAL(callback);
        ZVAL_STRING(callback, (char *)handler_name, 1);
    }

    /*
     * If we have a swapped connection object, make a PHP wrapper for it and use it with
     * 'replace' type of connection.
     */
    if (connect_object) {
        zval *php_connect_object = NULL;
        phpg_gobject_new(&php_connect_object, (GObject*)connect_object TSRMLS_CC);
        closure = phpg_closure_new(callback, user_args, PHPG_CONNECT_REPLACE, php_connect_object TSRMLS_CC);
        /* it's okay to decrement the only reference to the wrapper here - the GObject will save it! */
        zval_ptr_dtor(&php_connect_object);
    } else if (!connect_normal) {
        closure = phpg_closure_new(callback, user_args, PHPG_CONNECT_SIMPLE, NULL TSRMLS_CC);
    } else {
        closure = phpg_closure_new(callback, user_args, PHPG_CONNECT_NORMAL, NULL TSRMLS_CC);
    }

    phpg_gobject_new(&php_object, (GObject*)object TSRMLS_CC);
    phpg_gobject_watch_closure(php_object, closure TSRMLS_CC);
    handler_id = g_signal_connect_closure(object, signal_name, closure, after);

    /* same as above - okay to decrement the reference here */
    zval_ptr_dtor(&php_object);
    zval_ptr_dtor(&callback);
    if (user_args) {
        zval_ptr_dtor(&user_args);
    }
}

static PHP_METHOD(GladeXML, signal_autoconnect)
{
    zval *map = NULL;
    phpg_autoc_t data;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "|a", &map))
        return;

    data.instance = NULL;
    data.extra = map;
    glade_xml_signal_autoconnect_full(GLADE_XML(PHPG_GOBJECT(this_ptr)),
                                      (GladeXMLConnectFunc)phpg_glade_signal_connect_auto, &data);
}

#line 359 "ext/libglade/gen_libglade.c"



static PHP_METHOD(GladeXML, get_widget)
{
	char *name;
	zend_bool free_name = FALSE;
	GtkWidget* php_retval;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &name, &free_name))
		return;

    php_retval = glade_xml_get_widget(GLADE_XML(PHPG_GOBJECT(this_ptr)), name);
	if (free_name) g_free(name);
    phpg_gobject_new(&return_value, (GObject *)php_retval TSRMLS_CC);
}

#line 110 "ext/libglade/libglade.overrides"
static PHP_METHOD(GladeXML, get_widget_prefix)
{
    char *name;
    zend_bool free_name;
    GList *list, *item;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &name, &free_name)) {
        return;
    }

    list = glade_xml_get_widget_prefix(GLADE_XML(PHPG_GOBJECT(this_ptr)), (const char *)name);
    if (free_name) g_free(name);

    array_init(return_value);
    for (item = list; item; item = item->next) {
        zval *php_item = NULL;
        phpg_gobject_new(&php_item, G_OBJECT(item->data) TSRMLS_CC);
        add_next_index_zval(return_value, php_item);
    }

    g_list_free(list);
}

#line 405 "ext/libglade/gen_libglade.c"



static PHP_METHOD(GladeXML, relative_file)
{
	char *filename;
	zend_bool free_filename = FALSE, free_result;
	gchar *php_retval, *cp_ret;
	gsize cp_len;

    NOT_STATIC_METHOD();

	if (!php_gtk_parse_args(ZEND_NUM_ARGS(), "u", &filename, &free_filename))
		return;

    php_retval = glade_xml_relative_file(GLADE_XML(PHPG_GOBJECT(this_ptr)), filename);
	if (free_filename) g_free(filename);
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

#line 345 "ext/libglade/libglade.overrides"
static PHP_METHOD(GladeXML, signal_autoconnect_instance)
{
    zval *instance = NULL;
    zval *extra = NULL;
    phpg_autoc_t data;

    NOT_STATIC_METHOD();

    if (!php_gtk_parse_varargs(ZEND_NUM_ARGS(), 1, &extra, "o", &instance))
        return;

    data.instance = instance;
    data.extra = extra;
    glade_xml_signal_autoconnect_full(GLADE_XML(PHPG_GOBJECT(this_ptr)),
                                      (GladeXMLConnectFunc)phpg_glade_signal_connect_auto, &data);
}

#line 455 "ext/libglade/gen_libglade.c"


static
ZEND_BEGIN_ARG_INFO_EX(arginfo_glade_gladexml_glade_xml_new, 0, 0, 1)
    ZEND_ARG_INFO(0, filename)
    ZEND_ARG_INFO(0, root)
    ZEND_ARG_INFO(0, domain)
ZEND_END_ARG_INFO();

static
ZEND_BEGIN_ARG_INFO_EX(arginfo_glade_gladexml_glade_xml_new_from_buffer, 0, 0, 1)
    ZEND_ARG_INFO(0, buffer)
    ZEND_ARG_INFO(0, root)
    ZEND_ARG_INFO(0, domain)
ZEND_END_ARG_INFO();


static
ZEND_BEGIN_ARG_INFO(arginfo_glade_gladexml_get_widget, 0)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO();
static
ZEND_BEGIN_ARG_INFO(arginfo_glade_gladexml_get_widget_prefix, 0)
    ZEND_ARG_INFO(0, prefix)
ZEND_END_ARG_INFO();


static
ZEND_BEGIN_ARG_INFO(arginfo_glade_gladexml_relative_file, 0)
    ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO();
static
ZEND_BEGIN_ARG_INFO(arginfo_glade_gladexml_signal_autoconnect_instance, 0)
    ZEND_ARG_INFO(0, object)
ZEND_END_ARG_INFO();


static function_entry gladexml_methods[] = {
	PHP_ME(GladeXML, __construct,          arginfo_glade_gladexml_glade_xml_new, ZEND_ACC_PUBLIC)
	PHP_ME(GladeXML, new_from_buffer,      arginfo_glade_gladexml_glade_xml_new_from_buffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GladeXML, get_widget,           arginfo_glade_gladexml_get_widget, ZEND_ACC_PUBLIC)
	PHP_ME(GladeXML, get_widget_prefix,    arginfo_glade_gladexml_get_widget_prefix, ZEND_ACC_PUBLIC)
	PHP_ME(GladeXML, relative_file,        arginfo_glade_gladexml_relative_file, ZEND_ACC_PUBLIC)
	PHP_ME(GladeXML, signal_autoconnect,   NULL, ZEND_ACC_PUBLIC)
	PHP_ME(GladeXML, signal_autoconnect_instance, arginfo_glade_gladexml_signal_autoconnect_instance, ZEND_ACC_PUBLIC)
	PHP_ME(GladeXML, signal_connect,       NULL, ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

void phpg_glade_register_classes(void)
{
	TSRMLS_FETCH();

	glade_ce = phpg_register_class("Glade", glade_methods, NULL, 0, NULL, NULL, 0 TSRMLS_CC);

	gladexml_ce = phpg_register_class("GladeXML", gladexml_methods, gobject_ce, 0, gladexml_prop_info, NULL, GLADE_TYPE_XML TSRMLS_CC);
}

void phpg_glade_register_constants(const char *strip_prefix)
{
    TSRMLS_FETCH();


    /* register gtype constants for all classes */

	phpg_register_int_constant(gladexml_ce, "gtype", sizeof("gtype")-1, GLADE_TYPE_XML);

}

#endif /* HAVE_PHP_GTK */
