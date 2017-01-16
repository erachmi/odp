/* Copyright (c) 2017, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */

#ifndef _ODP_TEST_DRVDRIVER_H_
#define _ODP_TEST_DRVDRIVER_H_

#include <odp_cunit_common.h>

/* test functions: */
void drvdriver_test_enumr_class_register(void);
void drvdriver_test_enumr_register(void);

/* test arrays: */
extern odp_testinfo_t drvdriver_suite[];

/* test registry: */
extern odp_suiteinfo_t drvdriver_suites[];

/* main test program: */
int drvdriver_main(int argc, char *argv[]);

#endif
