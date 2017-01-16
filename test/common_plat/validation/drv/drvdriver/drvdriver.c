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

static int enumr1_probed;
static int enumr2_probed;
static int enumr3_probed;
static int enumr4_probed;

static odpdrv_enumr_class_t enumr_class1, enumr_class2;

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

/*enumerator probe functions, just making sure they have been ran: */
static int enumr1_probe(void)
{
	enumr1_probed = 1;
	return 0;
}

static int enumr2_probe(void)
{
	enumr2_probed = 1;
	return 0;
}

static int enumr3_probe(void)
{
	enumr3_probed = 1;
	return 0;
}

static int enumr4_probe(void)
{
	enumr4_probed = 1;
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

/*enumerator remove functions, just making sure they have been ran: */
static int enumr1_remove(void)
{
	enumr1_probed = -1;
	return 0;
}

static int enumr2_remove(void)
{
	enumr2_probed = -1;
	return 0;
}

static int enumr3_remove(void)
{
	enumr3_probed = -1;
	return 0;
}

static int enumr4_remove(void)
{
	enumr4_probed = -1;
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

	enumr_class1 = odpdrv_enumr_class_register(&param);
}

static void __attribute__ ((constructor)) enumr_class2_register(void)
{
	odpdrv_enumr_class_param_t param = {
		.name = "Enumerator_class2",
		.probe = enumr_class2_probe,
		.remove = enumr_class2_remove
	};

	enumr_class2 = odpdrv_enumr_class_register(&param);
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

/*enumerator register functions */
static void enumr1_register(void)
{
	odpdrv_enumr_param_t param = {
		.enumr_class = enumr_class1,
		.api_name = "Enumerator_interface_1",
		.api_version = 1,
		.probe = enumr1_probe,
		.remove = enumr1_remove,
		.register_notifier = NULL
	};

	odpdrv_enumr_register(&param);
}

static void enumr2_register(void)
{
	odpdrv_enumr_param_t param = {
		.enumr_class = enumr_class1,
		.api_name = "Enumerator_interface_2",
		.api_version = 1,
		.probe = enumr2_probe,
		.remove = enumr2_remove,
		.register_notifier = NULL
	};

	odpdrv_enumr_register(&param);
}

static void enumr3_register(void)
{
	odpdrv_enumr_param_t param = {
		.enumr_class = enumr_class2,
		.api_name = "Enumerator_interface_3",
		.api_version = 1,
		.probe = enumr3_probe,
		.remove = enumr3_remove,
		.register_notifier = NULL
	};

	odpdrv_enumr_register(&param);
}

static void enumr4_register(void)
{
	odpdrv_enumr_param_t param = {
		.enumr_class = enumr_class2,
		.api_name = "Enumerator_interface_4",
		.api_version = 1,
		.probe = enumr4_probe,
		.remove = enumr4_remove,
		.register_notifier = NULL
	};

	odpdrv_enumr_register(&param);
}

/* C_unit tests: */
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

void drvdriver_test_enumr_register(void)
{
	CU_ASSERT(odpdrv_print_all() == 0);

	CU_ASSERT(enumr1_probed == 0);
	CU_ASSERT(enumr2_probed == 0);
	CU_ASSERT(enumr3_probed == 0);
	CU_ASSERT(enumr4_probed == 0);

	/* now registers the enumerators. They should be probed immediately: */
	enumr1_register();
	CU_ASSERT(enumr1_probed == 1);
	enumr2_register();
	CU_ASSERT(enumr2_probed == 1);
	enumr3_register();
	CU_ASSERT(enumr3_probed == 1);
	enumr4_register();
	CU_ASSERT(enumr4_probed == 1);

	CU_ASSERT(odpdrv_print_all() == 0);
}


odp_testinfo_t drvdriver_suite[] = {
	ODP_TEST_INFO(drvdriver_test_enumr_class_register),
	ODP_TEST_INFO(drvdriver_test_enumr_register),
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

	if ((enumr1_probed != -1) ||
	    (enumr2_probed != -1) ||
	    (enumr3_probed != -1) ||
	    (enumr4_probed != -1))
		ret = -1;

	return ret;
}
