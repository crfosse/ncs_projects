#ifndef _KERNEL_VERSION_H_
#define _KERNEL_VERSION_H_

/*  values come from cmake/version.cmake */

#define ZEPHYR_VERSION_CODE 132096
#define ZEPHYR_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))

#define KERNELVERSION          0x2040000
#define KERNEL_VERSION_NUMBER  0x20400
#define KERNEL_VERSION_MAJOR   2
#define KERNEL_VERSION_MINOR   4
#define KERNEL_PATCHLEVEL      0
#define KERNEL_VERSION_STRING  "2.4.0"

#endif /* _KERNEL_VERSION_H_ */
