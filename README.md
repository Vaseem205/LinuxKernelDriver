# Linux Kernel Driver

Sample code for a Linux kernel driver.

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
