/**
 * @file mt_actions.h
 * @brief Stub API for the unavailable private "mt-actions" library.
 *
 * The original library provided a scripting/plugin runtime. This stub
 * satisfies compile-time references with no-op static inline functions
 * so the host application compiles and links without the real library.
 *
 * Behavioural contract:
 *  - All "getter" functions return NULL / 0 / false as appropriate.
 *  - All "action" functions become no-ops.
 *  - action_manager_get_plugin_count() will therefore always be 0 at
 *    runtime (the loader never adds anything), which naturally
 *    disables the plugin menu and BLE plugin driver.
 */
#ifndef __mt_actions_h
#define __mt_actions_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

/* Forward-declared types used by the original API. */
typedef struct __mta_plugin_t mta_plugin_t;
typedef struct __mta_scope_t mta_scope_t;
typedef struct __mta_driver_instance_t mta_driver_instance_t;

/* Struct tags need to exist in case any module does sizeof() on them.
 * They remain opaque (incomplete). */
struct __mta_plugin_t;
struct __mta_scope_t;
struct __mta_driver_instance_t;

/* ---------- Argument / value model ---------- */

typedef enum {
    MTA_ARG_NONE = 0,
    MTA_ARG_INT,
    MTA_ARG_FLOAT,
    MTA_ARG_STRING_REF,
    MTA_ARG_BYTES,
} mta_arg_type_t;

typedef enum {
    MTA_KIND_NONE = 0,
    MTA_KIND_INT,
    MTA_KIND_FLOAT,
    MTA_KIND_STRING,
    MTA_KIND_BOOL,
    MTA_KIND_ANY,
} mta_arg_kind_t;

typedef union {
    int32_t i;
    float f;
    const char* s;
    struct {
        const uint8_t* data;
        size_t len;
    } bytes;
} mta_value_t;

typedef struct {
    mta_arg_type_t type;
    mta_value_t val;
} mta_arg_t;

typedef struct {
    const char* name;
    mta_arg_kind_t kind;
} mta_arg_spec_t;

typedef struct {
    mta_arg_kind_t kind;
    mta_value_t val;
} mta_argv_t;

/* ---------- Error model ---------- */

typedef enum {
    MTA_RT_ERR_NONE = 0,
    MTA_RT_ERR_ARG_COUNT_MISMATCH,
    MTA_RT_ERR_TYPE_MISMATCH,
    MTA_RT_ERR_HOST_DISPATCH_FAILED,
    MTA_RT_ERR_INTERNAL,
} mta_runtime_error_kind_t;

/* ---------- Config schema model ---------- */

typedef enum {
    MTA_CONFIG_TYPE_BOOL = 0,
    MTA_CONFIG_TYPE_INT,
    MTA_CONFIG_TYPE_STRING,
} mta_config_type_t;

typedef struct {
    mta_config_type_t type;
    union {
        bool bool_value;
        int32_t int_value;
        const char* string_value;
    } value;
} mta_config_value_t;

typedef struct {
    const char* field_name;
    const char* label;
    mta_config_type_t type;
    int min;
    int max;
    bool has_min;
    bool has_max;
} mta_config_field_info_t;

/* ---------- I/O backend (for driver instances) ---------- */

typedef struct {
    int (*write)(void* device, const void* data, size_t len, bool wait_response);
    int (*read)(void* device, void* buf, size_t len);
    void (*close)(void* device);
} mta_io_backend_t;

/* ---------- Host-provided function signature ---------- */

typedef int (*mta_host_fn_t)(
    mta_plugin_t* plugin, mta_scope_t* scope, mta_arg_t* args, uint8_t arg_count
);

/* ---------- Construction / teardown ---------- */

static inline void mta_init_builtins(void) {}

static inline void mta_load_plugin(mta_plugin_t** out, void* cjson_tree) {
    (void)cjson_tree;
    if (out) *out = NULL;
}

static inline void mta_plugin_free(mta_plugin_t* plugin) {
    (void)plugin;
}

static inline mta_scope_t* mta_scope_create(void) {
    return NULL;
}

static inline void mta_scope_destroy(mta_scope_t* scope) {
    (void)scope;
}

/* ---------- Plugin metadata accessors ---------- */

static inline const char* mta_plugin_get_name(const mta_plugin_t* plugin) {
    (void)plugin;
    return NULL;
}

static inline const char* mta_plugin_get_display_name(const mta_plugin_t* plugin) {
    (void)plugin;
    return NULL;
}

static inline const char* mta_plugin_get_type(const mta_plugin_t* plugin) {
    (void)plugin;
    return NULL;
}

static inline const char* mta_plugin_get_match_ble_name(const mta_plugin_t* plugin) {
    (void)plugin;
    return NULL;
}

static inline const char* mta_plugin_get_match_ble_name_prefix(const mta_plugin_t* plugin) {
    (void)plugin;
    return NULL;
}

/* ---------- Scope binding ---------- */

static inline void mta_scope_set_user_data(mta_scope_t* scope, void* user_data) {
    (void)scope;
    (void)user_data;
}

static inline void* mta_scope_get_user_data(mta_scope_t* scope) {
    (void)scope;
    return NULL;
}

static inline void mta_init_scope_from_plugin_vars(mta_plugin_t* plugin, mta_scope_t* scope) {
    (void)plugin;
    (void)scope;
}

/* ---------- Host API registration ---------- */

static inline void mta_register_system_function(
    const char* name, mta_host_fn_t fn, const char* required_perm
) {
    (void)name;
    (void)fn;
    (void)required_perm;
}

static inline void mta_register_event(const char* name, const char* required_perm) {
    (void)name;
    (void)required_perm;
}

/* ---------- Host function helpers ---------- */

static inline int mta_raise(mta_plugin_t* plugin, mta_runtime_error_kind_t kind, const char* fmt, ...) {
    (void)plugin;
    (void)kind;
    (void)fmt;
    return -1;
}

static inline int mta_return_int(mta_plugin_t* plugin, mta_scope_t* scope, int32_t v) {
    (void)plugin;
    (void)scope;
    (void)v;
    return 0;
}

static inline int mta_return_float(mta_plugin_t* plugin, mta_scope_t* scope, float v) {
    (void)plugin;
    (void)scope;
    (void)v;
    return 0;
}

static inline int mta_return_string(mta_plugin_t* plugin, mta_scope_t* scope, const char* v) {
    (void)plugin;
    (void)scope;
    (void)v;
    return 0;
}

static inline int mta_return_void(mta_plugin_t* plugin, mta_scope_t* scope) {
    (void)plugin;
    (void)scope;
    return 0;
}

static inline int mta_read_args(
    mta_plugin_t* plugin,
    mta_scope_t* scope,
    mta_arg_t* args,
    uint8_t arg_count,
    const mta_arg_spec_t* specs,
    uint8_t spec_count,
    mta_argv_t* out,
    const char* fn_name
) {
    (void)plugin;
    (void)scope;
    (void)args;
    (void)arg_count;
    (void)specs;
    (void)spec_count;
    (void)out;
    (void)fn_name;
    /* Returning -1 forces every caller to treat arg parsing as failed and
     * short-circuit. Since these host functions are never reachable anyway
     * (no plugins ever register), the exact value matters little, but -1
     * matches the "error" contract the callers already check for. */
    return -1;
}

/* ---------- Arg accessors ---------- */

static inline mta_arg_type_t mta_arg_get_type(
    mta_plugin_t* plugin, mta_scope_t* scope, mta_arg_t* args, uint8_t idx
) {
    (void)plugin;
    (void)scope;
    (void)args;
    (void)idx;
    return MTA_ARG_NONE;
}

static inline int32_t mta_arg_get_int(
    mta_plugin_t* plugin, mta_scope_t* scope, mta_arg_t* args, uint8_t idx
) {
    (void)plugin;
    (void)scope;
    (void)args;
    (void)idx;
    return 0;
}

static inline float mta_arg_get_float(
    mta_plugin_t* plugin, mta_scope_t* scope, mta_arg_t* args, uint8_t idx
) {
    (void)plugin;
    (void)scope;
    (void)args;
    (void)idx;
    return 0.0f;
}

static inline const char* mta_arg_get_string(
    mta_plugin_t* plugin, mta_scope_t* scope, mta_arg_t* args, uint8_t idx
) {
    (void)plugin;
    (void)scope;
    (void)args;
    (void)idx;
    return "";
}

static inline int mta_arg_copy_bytes(
    mta_plugin_t* plugin, mta_scope_t* scope, mta_arg_t* args, uint8_t idx, uint8_t* buf, size_t maxlen
) {
    (void)plugin;
    (void)scope;
    (void)args;
    (void)idx;
    (void)buf;
    (void)maxlen;
    return -1;
}

/* ---------- Event dispatch ---------- */

static inline void mta_event_invoke_with_args_scope(
    mta_plugin_t* plugin,
    const char* event_name,
    const mta_arg_t* args,
    uint8_t arg_count,
    mta_scope_t* scope,
    void* user_data
) {
    (void)plugin;
    (void)event_name;
    (void)args;
    (void)arg_count;
    (void)scope;
    (void)user_data;
}

/* ---------- Error reporting ---------- */

typedef void (*mta_error_reporter_t)(
    mta_plugin_t* plugin, const char* msg, int kind_int, void* user_data
);

static inline void mta_set_error_reporter(mta_error_reporter_t cb, void* user_data) {
    (void)cb;
    (void)user_data;
}

static inline const char* mta_runtime_error_kind_str(mta_runtime_error_kind_t kind) {
    switch (kind) {
        case MTA_RT_ERR_ARG_COUNT_MISMATCH: return "ARG_COUNT_MISMATCH";
        case MTA_RT_ERR_TYPE_MISMATCH: return "TYPE_MISMATCH";
        case MTA_RT_ERR_HOST_DISPATCH_FAILED: return "HOST_DISPATCH_FAILED";
        case MTA_RT_ERR_INTERNAL: return "INTERNAL";
        case MTA_RT_ERR_NONE:
        default: return "NONE";
    }
}

/* ---------- Config persistence ---------- */

typedef bool (*mta_config_save_handler_t)(mta_plugin_t* plugin, void* user_data);

static inline void mta_set_config_save_handler(mta_config_save_handler_t cb, void* user_data) {
    (void)cb;
    (void)user_data;
}

static inline void mta_plugin_set_config(mta_plugin_t* plugin, void* cjson_config) {
    (void)plugin;
    (void)cjson_config;
}

static inline void* mta_plugin_serialize_config(mta_plugin_t* plugin) {
    (void)plugin;
    return NULL;
}

static inline bool mta_plugin_set_config_value(
    mta_plugin_t* plugin, const char* field_name, const mta_config_value_t* value
) {
    (void)plugin;
    (void)field_name;
    (void)value;
    return false;
}

static inline bool mta_plugin_get_config_value(
    mta_plugin_t* plugin, const char* field_name, mta_config_value_t* out_value
) {
    (void)plugin;
    (void)field_name;
    (void)out_value;
    return false;
}

static inline bool mta_plugin_has_config_schema(mta_plugin_t* plugin) {
    (void)plugin;
    return false;
}

typedef void (*mta_config_field_iter_cb_t)(const mta_config_field_info_t* field, void* user_data);

static inline void mta_plugin_iterate_config_fields(
    mta_plugin_t* plugin, mta_config_field_iter_cb_t cb, void* user_data
) {
    (void)plugin;
    (void)cb;
    (void)user_data;
}

#ifdef __cplusplus
}
#endif

#endif /* __mt_actions_h */
