#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL"); //*
MODULE_AUTHOR("InPyjama - Vaseem"); //!
MODULE_DESCRIPTION("Our first dynamically loadable kernel module"); //!

#define ECHO_BUFFER_SIZE 256  // Define an appropriate buffer size

char echo[ECHO_BUFFER_SIZE];

static struct proc_dir_entry *proc_entry;

// char echo[];

// ssize_t	(*proc_read)(struct file *, char __user *, size_t, loff_t *);
static ssize_t vaseem_read(struct file* file_pointer, char *user_space_buffer, size_t count, loff_t* offset){
    // char msg[] = "Ack\n";
    size_t len = strlen(echo);

    int result;

    printk("vaseem_read");
    printk("\n");

    if(*offset >= len){
        return 0;
    }

    //copy_to_user(destination, source, NoOfBytesToBeRead)
    result = copy_to_user(user_space_buffer, echo, len);
    *offset += len;
    return len;
    // strcpy(user_space_buffer, "Ack\n");
    // return strlen(6);
}


// ssize_t	(*proc_write)(struct file *, const char __user *, size_t, loff_t *);
static ssize_t vaseem_write(struct file *file_pointer, const char __user *kernel_space_buffer, size_t count, loff_t *offset) {
    size_t len = (count > ECHO_BUFFER_SIZE) ? ECHO_BUFFER_SIZE : count; // Limit to buffer size
    size_t not_copied;

    // Copy data from user space to kernel space
    not_copied = copy_from_user(echo, kernel_space_buffer, len);
    if (not_copied > 0) {
        printk(KERN_ERR "vaseem_write: Failed to copy %zu bytes from user space\n", not_copied);
    }

    // Log the data copied (Optional, for debugging purposes)
    printk(KERN_INFO "vaseem_write: Copied %zu bytes\n", len);

    return len; // Return the number of bytes written
}


struct proc_ops driver_proc_ops = {
    .proc_read = vaseem_read,
    .proc_write = vaseem_write
};



static int pyjama_module_init(void) {

    printk("Entered Init\n");

    /*
    struct proc_dir_entry *proc_create (const char *name,
                                        umode_t mode,
                                        struct proc_dir_entry *parent,
                                        const struct proc_ops *proc_ops);
    */
    proc_entry = proc_create ("pyjama_driver", 0666, NULL, &driver_proc_ops);

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


/*

Understanding::


*/
