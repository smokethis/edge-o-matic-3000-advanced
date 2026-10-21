/**
 * @file mt_actions_internal.h
 * @brief Stub internal API for the unavailable private "mt-actions" library.
 *
 * Only used by src/drivers/plugin_driver.c. All functions are no-op
 * static inline so the driver module compiles without the real library.
 * At runtime, no driver instances will ever be created (since no plugins
 * load), so these stubs are unreachable.
 */
#ifndef __mt_actions_internal_h
#define __mt_actions_internal_h

#ifdef __cplusplus
extern "C" {
#endif

#include "mt_actions.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* ---------- Driver instance lifecycle ---------- */

static inline mta_driver_instance_t* mta_driver_instance_create(
    mta_plugin_t* plugin, void* device, const mta_io_backend_t* io
) {
    (void)plugin;
    (void)device;
    (void)io;
    return NULL;
}

static inline void mta_driver_instance_destroy(mta_driver_instance_t* instance) {
    (void)instance;
}

static inline void mta_driver_instance_add(mta_driver_instance_t* instance) {
    (void)instance;
}

static inline void mta_driver_instance_remove(mta_driver_instance_t* instance) {
    (void)instance;
}

/* ---------- Accessors ---------- */

static inline mta_scope_t* mta_driver_instance_get_scope(mta_driver_instance_t* instance) {
    (void)instance;
    return NULL;
}

static inline void* mta_driver_instance_get_device(mta_driver_instance_t* instance) {
    (void)instance;
    return NULL;
}

/* ---------- Event dispatch ---------- */

static inline void mta_driver_instance_dispatch(
    mta_driver_instance_t* instance, const char* event, int arg_int, void* arg_ptr
) {
    (void)instance;
    (void)event;
    (void)arg_int;
    (void)arg_ptr;
}

static inline void mta_driver_instance_dispatch_all(const char* event, int arg_int) {
    (void)event;
    (void)arg_int;
}

/* ---------- Iteration ---------- */

typedef void (*mta_driver_instance_iter_cb_t)(mta_driver_instance_t* instance, void* arg);

static inline void mta_driver_instance_foreach(mta_driver_instance_iter_cb_t cb, void* arg) {
    (void)cb;
    (void)arg;
}

#ifdef __cplusplus
}
#endif

#endif /* __mt_actions_internal_h */
