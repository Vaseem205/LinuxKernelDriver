
# Linux Kernel Driver

Sample code for a Linux kernel driver. (Loadable Kernel Module)

## Prerequisites

Ensure you have [Multipass](https://multipass.run) installed and running. If the primary Multipass instance is stopped, start it using:

```bash
multipass start primary
```

## Building and Loading the Driver

1. Compile the driver:
   ```bash
   make
   ```

2. Load the driver into the kernel:
   ```bash
   sudo insmod ldd.ko
   ```

3. Verify if the module is loaded successfully:
   ```bash
   lsmod | grep ldd
   ```

4. View kernel log messages:
   ```bash
   sudo dmesg
   ```

5. To remove the driver:
   ```bash
   sudo rmmod ldd
   ```

6. Get detailed information about the module:
   ```bash
   modinfo ldd.ko
   ```

## Multipass Commands

- **Open Multipass**:
  ```bash
  multipass
  ```

- **List all Multipass instances**:
  ```bash
  multipass list
  ```
  > If the primary instance is stopped, start it with:
  ```bash
  multipass start primary
  ```

- **Start a shell in the primary instance**:
  ```bash
  multipass shell
  ```

- **Stop the primary instance**:
  ```bash
  multipass stop primary
  ```

## User→Kernel→User

1. **Module Creation**:
    - The code defines a Linux kernel module (`ldd.ko`) with `pyjama_module_init` as its initialization function and `pyjama_module_exit` as its cleanup function.
    - The module is dynamically loadable, meaning it can be inserted into and removed from the kernel as needed using commands like `insmod` and `rmmod`.
2. **`proc_create` and `/proc/pyjama_driver`**:
    - When the module is inserted, it creates a **procfs entry** named `pyjama_driver` under the `/proc` directory using the `proc_create` function.
    - The `proc_ops` structure (`driver_proc_ops`) defines how the kernel should handle operations (e.g., `read`, `write`, etc.) on this procfs entry. In this case, only the `read` operation (`proc_read`) is implemented and points to your custom function `vaseem_read`.
3. **`vaseem_read` Function**:
    - This function is invoked when you perform a `cat /proc/pyjama_driver`. Here's what happens:
        - A string (`"Ack\n"`) is prepared.
        - The `copy_to_user` function is used to copy this string from kernel space to the user space buffer (`user_space_buffer`).
            - **Why `copy_to_user`?** Directly accessing user space memory from the kernel can lead to issues like invalid memory access. `copy_to_user` safely transfers data, preventing kernel crashes.
        - The `offset` is updated to prevent repeated output when the `cat` command tries to read further.
        - The function returns the number of bytes written (`len`).
4. **How `cat` Works Here**:
    - When you run `cat /proc/pyjama_driver`, the kernel:
        - Looks up the `proc_ops` for the file.
        - Calls the function assigned to `.proc_read`, which is `vaseem_read`.
        - The string `"Ack\n"` is copied to the user-space buffer and displayed on the terminal.
5. **Clean-Up (`proc_remove`)**:
    - When the module is removed using `rmmod`, the `pyjama_module_exit` function is executed.
    - This removes the `pyjama_driver` entry from `/proc`, ensuring there are no dangling references.
