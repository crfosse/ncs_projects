
/* auto-generated by gen_syscalls.py, don't edit */
#ifndef Z_INCLUDE_SYSCALLS_HWINFO_H
#define Z_INCLUDE_SYSCALLS_HWINFO_H


#ifndef _ASMLANGUAGE

#include <syscall_list.h>
#include <syscall.h>

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic push
#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern ssize_t z_impl_hwinfo_get_device_id(u8_t * buffer, size_t length);
static inline ssize_t hwinfo_get_device_id(u8_t * buffer, size_t length)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (ssize_t) arch_syscall_invoke2(*(uintptr_t *)&buffer, *(uintptr_t *)&length, K_SYSCALL_HWINFO_GET_DEVICE_ID);
	}
#endif
	compiler_barrier();
	return z_impl_hwinfo_get_device_id(buffer, length);
}


#ifdef __cplusplus
}
#endif

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic pop
#endif

#endif
#endif /* include guard */
