#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/kmod.h>

#define MAX_CMD_LEN 256

static char *cmd = "/home/parallels/git/openwrt/package/paros/paros";
static struct subprocess_info *sub_info;

static int __init my_init(void)
{
    char *argv[] = {cmd, NULL};
    static char *envp[] = {"HOME=/", "TERM=linux", "PATH=/sbin:/usr/sbin:/bin:/usr/bin", NULL};
    int ret;

    printk(KERN_INFO "paros: Starting executable: %s\n", cmd);
    sub_info = call_usermodehelper_setup(argv[0], argv, envp, GFP_KERNEL, NULL, NULL, NULL);
    if (!sub_info) {
        printk(KERN_ERR "paros: Failed to allocate memory for subprocess\n");
        return -ENOMEM;
    }

    ret = call_usermodehelper_exec(sub_info, UMH_WAIT_EXEC);
    if (ret) {
        printk(KERN_ERR "paros: Failed to start subprocess: %s\n", cmd);
        call_usermodehelper_freeinfo(sub_info);
        return -1;
    }

    printk(KERN_INFO "paros: Executable started successfully\n");
    return 0;
}

static void __exit my_exit(void)
{
    int ret;

    printk(KERN_INFO "paros: Stopping executable: %s\n", cmd);
    ret = call_usermodehelper("killall", "-q", cmd, NULL);
    if (ret) {
        printk(KERN_ERR "paros: Failed to stop subprocess: %s\n", cmd);
    } else {
        printk(KERN_INFO "paros: Executable stopped successfully\n");
    }

    call_usermodehelper_freeinfo(sub_info);
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Keyang Yu");
MODULE_DESCRIPTION("Running paros as kernel service");

