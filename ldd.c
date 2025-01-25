#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL"); //*
MODULE_AUTHOR("InPyjama - Vaseem"); //!
MODULE_DESCRIPTION("Our first dynamically loadable kernel module"); //!

static struct proc_dir_entry *proc_entry;

// ssize_t	(*proc_read)(struct file *, char __user *, size_t, loff_t *);

static ssize_t vaseem_read(struct file* file_pointer, char *user_space_buffer, size_t count, loff_t* offset){
    char msg[] = "Ack\n";
    size_t len = strlen(msg);

    int result;

    printk("vaseem_read");
    printk("\n");

    if(*offset >= len){
        return 0;
    }
    result = copy_to_user(user_space_buffer, msg, len);
    *offset += len;
    return len;
}

struct proc_ops driver_proc_ops = {
    .proc_read = vaseem_read
};



static int pyjama_module_init(void) {

    printk("Entered Init\n");

    /*
    struct proc_dir_entry *proc_create (const char *name,
                                        umode_t mode,
                                        struct proc_dir_entry *parent,
                                        const struct proc_ops *proc_ops);
    */
    proc_entry = proc_create ("pyjama_driver", 0, NULL, &driver_proc_ops);

    printk("Exited Init\n");
    return 0;
}

static void pyjama_module_exit(void) {

    printk("Entered Exit\n");

    proc_remove(proc_entry);

    printk("Exited Exit\n");
}

/*
struct proc_dir_entry *proc_create (const char *name,
                                    umode_t mode,
                                    struct proc_dir_entry *parent,
                                    const struct proc_ops *proc_ops);
*/



module_init(pyjama_module_init);
module_exit(pyjama_module_exit);
