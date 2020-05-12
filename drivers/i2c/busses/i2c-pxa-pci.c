/*
 * The CE4100's I2C device is more or less the same one as found on PXA.
 * It does not support slave mode, the register slightly moved. This PCI
 * device provides three bars, every contains a single I2C controller.
 */
#include <linux/pci.h>
#include <linux/platform_device.h>
#include <linux/i2c/pxa-i2c.h>
#include <linux/moduleparam.h>

/*
 * the number of bars is hardcoded because pci_select_bars() reports the
 * wrong thing.
 */
#define CE4100_PCI_I2C_DEVS	3


#define CE4200_PCI_ROOT_DEVID 0x0709

struct ce4100_i2c_device {
	struct platform_device pdev;
	struct resource res[2];
	struct i2c_pxa_platform_data pdata;
};

unsigned int		pio_mode = 0;
unsigned int		fast_mode = 0;

module_param(pio_mode, uint, S_IRUGO);
MODULE_PARM_DESC(pio_mode, "whether the I2C running at polling mode(0) or Interrupt mode(1)");
module_param(fast_mode, uint, S_IRUGO);
MODULE_PARM_DESC(fast_mode, "whether the I2C running at standard mode(0) or fast mode(1)");

struct ce4100_devices {
	struct ce4100_i2c_device sd[CE4100_PCI_I2C_DEVS];
};

static void plat_dev_release(struct device *dev)
{
   struct ce4100_i2c_device * sd = container_of(dev,
       struct ce4100_i2c_device, pdev.dev);
   printk(KERN_INFO "%s %d released\n", sd->pdev.name, sd->pdev.id);
}


static int add_i2c_device(struct pci_dev *dev, int bar,
		struct ce4100_i2c_device *sd)
{
	struct platform_device *pdev = &sd->pdev;
	struct i2c_pxa_platform_data *pdata = &sd->pdata;

	pdev->name = "pxa2xx-i2c";
	pdev->dev.parent = &dev->dev;
	pdev->dev.release = plat_dev_release;
        pdev->id = bar;

        pdata->use_pio = pio_mode;
        pdata->fast_mode = fast_mode;
	pdev->dev.platform_data = pdata;
   
	pdev->resource = sd->res;

	sd->res[0].flags = IORESOURCE_MEM;
	sd->res[0].start = pci_resource_start(dev, bar);
	sd->res[0].end = pci_resource_end(dev, bar);

	sd->res[1].flags = IORESOURCE_IRQ;
	sd->res[1].start = dev->irq;
	sd->res[1].end = dev->irq;
	pdev->num_resources = 2;
  
        dev_dbg(&dev->dev, "MEM-start=0x%x, end=0x%x\n",(unsigned int)sd->res[0].start, (unsigned int)sd->res[0].end);
        dev_dbg(&dev->dev, "IRQ-start=0x%x, end=0x%x\n",(unsigned int)sd->res[1].start, (unsigned int)sd->res[1].end);
        dev_dbg(&dev->dev, "pio_mode =0x%x, fast_mode=0x%x\n", pio_mode, fast_mode);
   
	return platform_device_register(pdev);
}

static int __devinit ce4100_i2c_probe(struct pci_dev *dev,
		const struct pci_device_id *ent)
{
	int ret;
	int i;
	struct ce4100_devices *sds;

	ret = pci_enable_device_mem(dev);
	if (ret)
		return ret;
  
	sds = kzalloc(sizeof(*sds), GFP_KERNEL);
	if (!sds)
		goto err_mem;

	pci_set_drvdata(dev, sds);

	for (i = 0; i < ARRAY_SIZE(sds->sd); i++) {
		ret = add_i2c_device(dev, i, &sds->sd[i]);
		if (ret) {
			while (--i >= 0)
				platform_device_unregister(&sds->sd[i].pdev);
			goto err_dev_add;
		}
	}
	return 0;

err_dev_add:
	pci_set_drvdata(dev, NULL);
	kfree(sds);
err_mem:
	pci_disable_device(dev);
	return ret;
}

static void __devexit ce4100_i2c_remove(struct pci_dev *dev)
{
	struct ce4100_devices *sds;
	unsigned int i;

	sds = pci_get_drvdata(dev);
	pci_set_drvdata(dev, NULL);

	for (i = 0; i < ARRAY_SIZE(sds->sd); i++)
		platform_device_unregister(&sds->sd[i].pdev);

	pci_disable_device(dev);
	kfree(sds);
}

#ifdef CONFIG_PM
static int ce4100_i2c_suspend(struct pci_dev *dev, pm_message_t state)
{

	pci_save_state(dev);
	pci_set_power_state(dev, pci_choose_state(dev, state));
	return 0;
}

static int ce4100_i2c_resume(struct pci_dev *dev)
{

	pci_set_power_state(dev, PCI_D0);
	pci_restore_state(dev);

	return 0;
}

#endif
static struct pci_device_id ce4100_i2c_devices[] __devinitdata = {
	{ PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2e68)},
	{ },
};
MODULE_DEVICE_TABLE(pci, ce4100_i2c_devices);

static struct pci_driver ce4100_i2c_driver = {
	.name           = "ce4100_i2c",
	.id_table       = ce4100_i2c_devices,
	.probe          = ce4100_i2c_probe,
	.remove         = __devexit_p(ce4100_i2c_remove),
#ifdef CONFIG_PM
   .suspend      =   ce4100_i2c_suspend,
   .resume       =   ce4100_i2c_resume,
#endif
};

static int __init ce4100_i2c_init(void)
{
   struct pci_dev *root;
   unsigned short devid; 
   root = pci_get_bus_and_slot(0,0);
   if (NULL == root) {
      printk(KERN_ERR "Can't detect the PCI root bridge!!");
      return -ENODEV;
    }
   pci_read_config_word(root, PCI_DEVICE_ID, &devid);
   pci_dev_put(root);

   if (CE4200_PCI_ROOT_DEVID == devid) 
	 return pci_register_driver(&ce4100_i2c_driver);
   
   return 0; 
}
module_init(ce4100_i2c_init);

static void __exit ce4100_i2c_exit(void)
{
   struct pci_dev *root;
   unsigned short devid; 
   root = pci_get_bus_and_slot(0,0);
   if (NULL == root) {
      printk(KERN_ERR "Can't detect the PCI root bridge!!");
      return;
    }
   pci_read_config_word(root, PCI_DEVICE_ID, &devid);
   pci_dev_put(root);

   if (CE4200_PCI_ROOT_DEVID == devid) 
	 return pci_unregister_driver(&ce4100_i2c_driver);

}
module_exit(ce4100_i2c_exit);

MODULE_DESCRIPTION("CE4100 PCI-I2C glue code for PXA's driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Sebastian Andrzej Siewior <bigeasy@linutronix.de>");
