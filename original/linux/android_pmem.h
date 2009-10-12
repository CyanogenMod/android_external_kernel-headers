/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _ANDROID_PMEM_H_
#define _ANDROID_PMEM_H_

#include <stdint.h>

#ifndef __user
#define __user
#endif

struct pmem_region {
    unsigned long offset;
    unsigned long len;
};

#define PMEM_IOCTL_MAGIC 'p'
#define PMEM_GET_PHYS       _IOW(PMEM_IOCTL_MAGIC, 1, struct pmem_region *)
#define PMEM_MAP        _IOW(PMEM_IOCTL_MAGIC, 2, struct pmem_region *)
#define PMEM_GET_SIZE       _IOW(PMEM_IOCTL_MAGIC, 3, struct pmem_region *)
#define PMEM_UNMAP      _IOW(PMEM_IOCTL_MAGIC, 4, struct pmem_region *)
/* This ioctl will allocate pmem space, backing the file, it will fail
 * if the file already has an allocation, pass it the len as the argument
 * to the ioctl */
#define PMEM_ALLOCATE       _IOW(PMEM_IOCTL_MAGIC, 5, unsigned int)
/* This will connect a one pmem file to another, pass the file that is already
 * backed in memory as the argument to the ioctl
 */
#define PMEM_CONNECT        _IOW(PMEM_IOCTL_MAGIC, 6, unsigned int)
/* Returns the total size of the pmem region it is sent to as a pmem_region
 * struct (with offset set to 0).
 */
#define PMEM_GET_TOTAL_SIZE _IOW(PMEM_IOCTL_MAGIC, 7, struct pmem_region *)
/* Revokes gpu registers and resets the gpu.  Pass a pointer to the
 * start of the mapped gpu regs (the vaddr returned by mmap) as the argument.
 */

#define HW3D_REVOKE_GPU     _IOW(PMEM_IOCTL_MAGIC, 8, unsigned int)
#define HW3D_GRANT_GPU      _IOW(PMEM_IOCTL_MAGIC, 9, unsigned int)
#define HW3D_WAIT_IRQ       _IOW(PMEM_IOCTL_MAGIC,10, unsigned int)

int get_pmem_file(unsigned int fd, unsigned long *start, unsigned long *end, struct file **filp);
int get_pmem_fd(unsigned int fd, unsigned long *start, unsigned long *end);
int get_pmem_user_addr(struct file *file, unsigned long *start, unsigned long *end);
void put_pmem_file(struct file* file);
void put_pmem_fd(unsigned int fd);
void flush_pmem_fd(unsigned int fd, unsigned long start, unsigned long len);

struct android_pmem_platform_data;
struct pmem_file_operations {
    int (*mmap) (struct file *, struct vm_area_struct *);
    int (*open) (struct inode *, struct file *);
    ssize_t (*read) (struct file *, char __user *, size_t, long long *);
    int (*release) (struct inode *, struct file *);
    long (*ioctl) (struct file *, unsigned int, unsigned long);
};

int pmem_setup(struct android_pmem_platform_data *pdata,
           struct pmem_file_operations *custom_fops);
int pmem_remap(struct pmem_region *region, struct file *file,
           unsigned operation);

#endif //_ANDROID_PMEM_H_

