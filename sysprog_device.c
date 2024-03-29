#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/slab.h>

static char *buffer = NULL;
static char *buffer2 = NULL;

int sysprog_device_open(struct inode *inode, struct file *filp){
	printk(KERN_ALERT, "sysprog_device open function called\n");
	return 0;
}	

int sysprog_device_release(struct inode *inode, struct file *filp){
		printk(KERN_ALERT, "sysprog_device release function called\n");
		return 0;
}
	
ssize_t sysprog_device_write2(struct file *filp, const char *buf, size_t count, loff_t *f_pos){
		printk(KERN_ALERT, "sysprog_device write function called\n");
		copy_from_user(buffer, buf, 1024);
		return count;
}

ssize_t sysprog_device_read2(struct file *filp, char *buf, size_t count, loff_t *f_pos){
		printk(KERN_ALERT, "sysprog_device read function called\n");
		copy_to_user(buf, buffer, 1024);
		return count;
}

ssize_t sysprog_device_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos){
		printk(KERN_ALERT, "sysprog_device write function called\n");
		//int temp = 0;
		//sprintf(buf, "%d", temp);
		//*buffer2 = *buffer2+temp;
		copy_from_user(buffer, buf, sizeof(int));
		*buffer2=(int)*buffer2 + (int)*buffer;
		
		return count;
}

ssize_t sysprog_device_read(struct file *filp, char *buf, size_t count, loff_t *f_pos){
		printk(KERN_ALERT, "sysprog_device read function called\n");
		copy_to_user(buf, buffer2, sizeof(int));
		return count;
}

static struct file_operations sys_fops = {
	.owner = THIS_MODULE,
	.read = sysprog_device_read,
	.write = sysprog_device_write,
	.open = sysprog_device_open,
	.release = sysprog_device_release
};


int __init sysprog_device_init(void)
{
	if(register_chrdev(240, "sysprog_device", &sys_fops) < 0)
		printk(KERN_ALERT, "[sysprog] driver init failed\n");
	else
		printk(KERN_ALERT, "[sysprog] driver init successful\n");
	
	buffer = (char*)kmalloc(1024, GFP_KERNEL);
	buffer2 = (char*)kmalloc(sizeof(int), GFP_KERNEL);
	if(buffer != NULL)
		memset(buffer, 0, 1024);
	if(buffer2 != NULL)
		memset(buffer, 0, sizeof(int));
	
	return 0;
}

void __exit sysprog_device_exit(void)
{
		unregister_chrdev(240, "sysprog_device");
		printk(KERN_ALERT, "[sysprog] driver cleanup\n");
		kfree(buffer);
}


module_init(sysprog_device_init);
module_exit(sysprog_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("kim");
MODULE_DESCRIPTION("This is the hello world example for device driver in system programming lecture");
