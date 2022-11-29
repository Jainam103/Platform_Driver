#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include "platform.h"

/* 
 *  Probe method will get called once the driver
 *  gets registered
 *
*/
static int pdrv_probe(struct platform_device* pdev)
{
		struct resource* res1;

		res1 = platform_get_resource(pdev,IORESOURCE_MEM,0);
		printk(KERN_ALERT "\n Memory Area1\n");
		printk(KERN_ALERT "Start:%lx,  End:%lx Size:%lld\n", 
						(unsigned long)res1->start, (unsigned long)res1->end, 
						resource_size(res1));

		printk(KERN_ALERT "\n IRQ Number of Device :%d\n", platform_get_irq(pdev, 0));
		return 0;
}


static int pdrv_release(struct platform_device* pdev)
{
		return 0;
}

/* Platform driver structure
 *
 * Members:
 *		probe: Driver's probe method
 *		remove: Driver's remove method
 *		driver: Specify Driver name in this field
 *
 */
static struct platform_driver pdrv = {
		.probe =  pdrv_probe,
		.remove = pdrv_release,
		.driver = {
				.name = DRIVER_NAME,
		},
};

static int platform_driver_init(void)
{
		/* Register platform driver to the kernel */
		platform_driver_register(&pdrv);
		return 0;
}

static void platform_driver_cleanup(void)
{
		/* Unregister platform driver to the kernel */
		platform_driver_unregister(&pdrv);
}

module_init(platform_driver_init);
module_exit(platform_driver_cleanup);
MODULE_LICENSE("GPL");
