/* Copyright (c) 2017, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */

#include <odp_config_internal.h>
#include <_ishmpool_internal.h>

#include <odp/api/std_types.h>
#include <odp/api/debug.h>
#include <odp/api/spinlock.h>
#include <odp/drv/driver.h>
#include <odp/drv/spec/driver.h>
#include <odp_debug_internal.h>

static int init_global_done; /* true when init_global has been completed */

/* pool from which different list elements are alocated: */
#define ELT_POOL_SIZE (1 << 20)  /* 1Mb */
static _odp_ishm_pool_t *list_elt_pool;

/* an enumerator class (list element) */
typedef struct _odpdrv_enumr_class_t {
	odpdrv_enumr_class_param_t param;
	_odp_ishm_pool_t *pool;
	struct _odpdrv_enumr_class_t *next;
} _odpdrv_enumr_class_t;

/* the enumerator class list: */
typedef struct _odpdrv_enumr_class_lst_t {
	odp_spinlock_t lock;
	_odpdrv_enumr_class_t *head;
} _odpdrv_enumr_class_lst_t;
static struct _odpdrv_enumr_class_lst_t enumr_class_lst;

odpdrv_enumr_class_t odpdrv_enumr_class_register(odpdrv_enumr_class_param_t
						 *param)
{
	_odpdrv_enumr_class_t *enumr_c;

	/* allocate memory for the new enumerator class:
	 * If init_global has not been done yet, then, we cannot allocate
	 * from any _ishm pool (ishm has not even been initialised at this
	 * stage...this happens when statically linked enumerator classes
	 * register: their __constructor__ function is run before main()
	 * is called). But any malloc performed here(before init_global)
	 * will be inherited by any odpthreads (process or pthreads) as we
	 * are still running in the ODP instantiation processes and all
	 * other processes are guaranteed to be descendent of this one...
	 * If init_global has been done, then we allocate from the _ishm pool
	 * to guarantee visibility from any ODP thread.
	 */

	if (!init_global_done) {
		enumr_c = malloc(sizeof(_odpdrv_enumr_class_t));
		if (!enumr_c)
			return ODPDRV_ENUMR_CLASS_INVALID;
		enumr_c->pool = NULL;
	} else {
		enumr_c = _odp_ishm_pool_alloc(list_elt_pool,
					       sizeof(_odpdrv_enumr_class_t));
		if (!enumr_c) {
			ODP_ERR("_odp_ishm_pool_alloc failed!\n");
			return ODPDRV_ENUMR_CLASS_INVALID;
		}
		enumr_c->pool = list_elt_pool;
	}

	/* save init parameters and insert enumerator class in list */
	enumr_c->param = *param;
	if (init_global_done)
		odp_spinlock_lock(&enumr_class_lst.lock);
	enumr_c->next = enumr_class_lst.head;
	enumr_class_lst.head = enumr_c;
	if (init_global_done)
		odp_spinlock_unlock(&enumr_class_lst.lock);

	/* if we have done init_global, probe the new enumerator class */
	if (init_global_done)
		enumr_c->param.probe();

	return (odpdrv_enumr_class_t)enumr_c;
}

odpdrv_enumr_t odpdrv_enumr_register(odpdrv_enumr_param_t *param)
{
	ODP_ERR("NOT Supported yet! Enumerator API %s Registration!\n.",
		param->api_name);

	return ODPDRV_ENUMR_INVALID;
}

odpdrv_device_t odpdrv_device_create(odpdrv_device_param_t *param)
{
	ODP_ERR("odpdrv_device_create not Supported yet! devaddress: %s\n.",
		param->address);
	return ODPDRV_DEVICE_INVALID;
}

void odpdrv_device_destroy(odpdrv_device_t dev)
{
	if (dev == ODPDRV_DEVICE_INVALID)
		ODP_ERR("Invalid device\n");
}

odpdrv_devio_t odpdrv_devio_register(odpdrv_devio_param_t *param)
{
	ODP_ERR("NOT Supported yet! Driver %s Registration!\n.",
		param->api_name);

	return ODPDRV_DEVIO_INVALID;
}

odpdrv_driver_t odpdrv_driver_register(odpdrv_driver_param_t *param)
{
	ODP_ERR("NOT Supported yet! Driver %s Registration!\n.",
		param->name);

	return ODPDRV_DRIVER_INVALID;
}

int odpdrv_print_all(void)
{
	_odpdrv_enumr_class_t *enumr_c;

	/* we cannot use ODP_DBG before ODP init... */
	if (!init_global_done)
		return 0;

	ODP_DBG("ODP Driver status:\n");

	/* print the list of registered enumerator classes: */
	odp_spinlock_lock(&enumr_class_lst.lock);
	enumr_c = enumr_class_lst.head;
	ODP_DBG("The following enumerator classes have been registered:\n");
	while (enumr_c) {
		ODP_DBG(" class: %s\n", enumr_c->param.name);
		enumr_c = enumr_c->next;
	}
	odp_spinlock_unlock(&enumr_class_lst.lock);
	return 0;
}

int _odpdrv_driver_init_global(void)
{
	_odpdrv_enumr_class_t *enumr_c;

	/* create a memory pool to for list elements: */
	list_elt_pool = _odp_ishm_pool_create(NULL, ELT_POOL_SIZE,
					      0, ELT_POOL_SIZE, 0);

	/* remember that init global is done so the further list allocs
	 * are made from the list_elt_pool: */
	init_global_done = 1;

	/* from now, we want to ensure mutex on the list: init lock: */
	odp_spinlock_init(&enumr_class_lst.lock);

	/* probe all registered enumerator classes registered so far:
	 * (yes: those being staticaly linked have already registered)*/
	enumr_c = enumr_class_lst.head;
	while (enumr_c) {
		enumr_c->param.probe();
		enumr_c = enumr_c->next;
	}

	return 0;
}

int _odpdrv_driver_term_global(void)
{
	_odpdrv_enumr_class_t *enumr_c;

	if (!init_global_done)
		return 0;

	/* remove all enumerator classes which are registered: */
	odp_spinlock_lock(&enumr_class_lst.lock);
	while (enumr_class_lst.head) {
		enumr_c = enumr_class_lst.head;
		enumr_c->param.remove();
		enumr_class_lst.head = enumr_c->next;
		if (enumr_c->pool)
			_odp_ishm_pool_free(list_elt_pool, enumr_c);
		else
			free(enumr_c);
	}
	odp_spinlock_unlock(&enumr_class_lst.lock);

	/* destroy the list element pool: */
	_odp_ishm_pool_destroy(list_elt_pool);

	return 0;
}
