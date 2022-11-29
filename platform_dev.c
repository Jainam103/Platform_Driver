#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/platform_device.h>
#include "platform.h"

/* Resource structure 
 *
 * It describes starting address and IRQ number
 *
*/
static struct resource sample_resources[] = {
		{
				.start          = START_ADD,
				.end            = END_ADD,
				.flags          = IORESOURCE_MEM,
		},
		{
				.start          = DEV_IRQ_NUM,
				.end            = DEV_IRQ_NUM,
				.flags          = IORESOURCE_IRQ,
		}

};

/*
 * static struct platform_device pdev : Platform device is represented 
 *										by this structure
 * members:
 *			name: Name of the platform device. This name should be same
 *				  for platform driver and platform device.
 *			num_resources: number of resources.
 *			struct resource: Described resource ranges and flags
*/

static struct platform_device pdev = {
	.name = DRIVER_NAME,
	.num_resources = ARRAY_SIZE(sample_resources),
	.resource = sample_resources,
};

static int pdev_init(void)
{
	/* Register our platform device to the kernel */
	platform_device_register(&pdev);
	return 0;
}

static void pdev_cleanup(void)
{
	/* Unregister our platform device from the kernel */
	platform_device_unregister(&pdev);
}

module_init(pdev_init);
module_exit(pdev_cleanup);
MODULE_LICENSE("GPL");
