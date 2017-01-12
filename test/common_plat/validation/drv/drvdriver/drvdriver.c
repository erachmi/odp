/* Copyright (c) 2017, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */

#include <odp_drv.h>
#include <odp_api.h>
#include <odp_cunit_common.h>
#include "drvdriver.h"
#include <stdlib.h>

static int enumr_class1_probed;
static int enumr_class2_probed;
static int enumr_class3_probed;
static int enumr_class4_probed;

/*enumerator class probe functions, just making sure they have been ran: */
static int enumr_class1_probe(void)
{
	enumr_class1_probed = 1;
	return 0;
}

static int enumr_class2_probe(void)
{
	enumr_class2_probed = 1;
	return 0;
}

static int enumr_class3_probe(void)
{
	enumr_class3_probed = 1;
	return 0;
}

static int enumr_class4_probe(void)
{
	enumr_class4_probed = 1;
	return 0;
}

/*enumerator class remove functions, just making sure they have been ran: */
static int enumr_class1_remove(void)
{
	enumr_class1_probed = -1;
	return 0;
}

static int enumr_class2_remove(void)
{
	enumr_class2_probed = -1;
	return 0;
}

static int enumr_class3_remove(void)
{
	enumr_class3_probed = -1;
	return 0;
}

static int enumr_class4_remove(void)
{
	enumr_class4_probed = -1;
	return 0;
}

/*enumerator class register functions, the 2 first ones being
 *"statically linked" *(i.e. directely run at start): */
static void __attribute__ ((constructor)) enumr_class1_register(void)
{
	odpdrv_enumr_class_param_t param = {
		.name = "Enumerator_class1",
		.probe = enumr_class1_probe,
		.remove = enumr_class1_remove
	};

	odpdrv_enumr_class_register(&param);
}

static void __attribute__ ((constructor)) enumr_class2_register(void)
{
	odpdrv_enumr_class_param_t param = {
		.name = "Enumerator_class2",
		.probe = enumr_class2_probe,
		.remove = enumr_class2_remove
	};

	odpdrv_enumr_class_register(&param);
}

static void enumr_class3_register(void)
{
	odpdrv_enumr_class_param_t param = {
		.name = "Enumerator_class3",
		.probe = enumr_class3_probe,
		.remove = enumr_class3_remove
	};

	odpdrv_enumr_class_register(&param);
}

static void enumr_class4_register(void)
{
	odpdrv_enumr_class_param_t param = {
		.name = "Enumerator_class4",
		.probe = enumr_class4_probe,
		.remove = enumr_class4_remove
	};

	odpdrv_enumr_class_register(&param);
}

void drvdriver_test_enumr_class_register(void)
{
	/* at this point (after odp init), the 2 first (__constructor__)
	 * enumerator classes should have registered and been probed:
	 */
	CU_ASSERT(odpdrv_print_all() == 0);

	CU_ASSERT(enumr_class1_probed == 1);
	CU_ASSERT(enumr_class2_probed == 1);

	/* now registers the 2 other enumerators, simulating a module loading:
	 * They should be probed immediately: */
	enumr_class3_register();
	CU_ASSERT(enumr_class3_probed == 1);
	enumr_class4_register();
	CU_ASSERT(enumr_class4_probed == 1);

	CU_ASSERT(odpdrv_print_all() == 0);
}

odp_testinfo_t drvdriver_suite[] = {
	ODP_TEST_INFO(drvdriver_test_enumr_class_register),
	ODP_TEST_INFO_NULL,
};

odp_suiteinfo_t drvdriver_suites[] = {
	{"Enumerator registration", NULL, NULL, drvdriver_suite},
	ODP_SUITE_INFO_NULL,
};

int drvdriver_main(int argc, char *argv[])
{
	int ret;

	/* parse common options: */
	if (odp_cunit_parse_options(argc, argv))
		return -1;

	/* register the tests: */
	ret = odp_cunit_register(drvdriver_suites);

	if (ret == 0)
		ret = odp_cunit_run();

	/* after ODP terminaison completion, all enumerators should be removed*/
	if ((enumr_class1_probed != -1) ||
	    (enumr_class2_probed != -1) ||
	    (enumr_class3_probed != -1) ||
	    (enumr_class4_probed != -1))
		ret = -1;

	return ret;
}
