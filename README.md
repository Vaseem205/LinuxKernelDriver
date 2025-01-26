# Linux Kernel Module: Dynamic Procfs Echo Driver

## Overview

This Linux kernel module creates a dynamic procfs entry `/proc/pyjama_driver` that allows bidirectional communication between kernel and user space. It demonstrates key concepts of Linux kernel module development, including:
- Dynamic module loading and unloading
- Procfs entry creation
- Kernel-user space data transfer
- Safe memory operations

## Key Features

### 1. Module Characteristics
- **Dynamically Loadable**: Can be inserted into and removed from the kernel at runtime
- **Procfs Interface**: Creates `/proc/pyjama_driver` for interaction
- **Bidirectional Communication**: Supports both read and write operations

### 2. Module Operations

#### Initialization (`pyjama_module_init`)
- Creates a procfs entry named `pyjama_driver`
- Sets file permissions to `0666` (read/write for all users)
- Registers read and write operations

#### Cleanup (`pyjama_module_exit`)
- Removes the procfs entry 
- Ensures clean module unloading without leaving kernel references

### 3. Read Operation (`vaseem_read`)
- Triggered when user reads from `/proc/pyjama_driver`
- Copies previously stored data from kernel space to user space
- Uses `copy_to_user` for safe memory transfer
- Prevents multiple reads of the same data

### 4. Write Operation (`vaseem_write`)
- Triggered when user writes to `/proc/pyjama_driver`
- Copies data from user space to kernel space
- Limits input to a predefined buffer size (`ECHO_BUFFER_SIZE`)
- Handles partial data copy scenarios
- Logs debug information about data transfer

## Usage Examples

### 1. Compile the Module
```bash
make
```

### 2. Load the Module
```bash
sudo insmod ldd.ko
```

### 3. Write to the Procfs Entry
```bash
echo "Hello, Kernel!" > /proc/pyjama_driver
```

### 4. Read from the Procfs Entry
```bash
cat /proc/pyjama_driver
# Output: Hello, Kernel!
```

### 5. Unload the Module
```bash
sudo rmmod ldd
```

## Dependencies
- Linux Kernel Headers
- Kernel Module Build Tools

## License
GPL (GNU General Public License)



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
### Author
Vaseem Akram

### Reference
[InPyjama](https://www.youtube.com/watch?v=iSiyDHobXHA)


