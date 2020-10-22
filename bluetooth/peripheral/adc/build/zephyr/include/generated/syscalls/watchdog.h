
/* auto-generated by gen_syscalls.py, don't edit */
#ifndef Z_INCLUDE_SYSCALLS_WATCHDOG_H
#define Z_INCLUDE_SYSCALLS_WATCHDOG_H


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

extern int z_impl_wdt_setup(struct device * dev, u8_t options);
static inline int wdt_setup(struct device * dev, u8_t options)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (int) arch_syscall_invoke2(*(uintptr_t *)&dev, *(uintptr_t *)&options, K_SYSCALL_WDT_SETUP);
	}
#endif
	compiler_barrier();
	return z_impl_wdt_setup(dev, options);
}


extern int z_impl_wdt_disable(struct device * dev);
static inline int wdt_disable(struct device * dev)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (int) arch_syscall_invoke1(*(uintptr_t *)&dev, K_SYSCALL_WDT_DISABLE);
	}
#endif
	compiler_barrier();
	return z_impl_wdt_disable(dev);
}


extern int z_impl_wdt_feed(struct device * dev, int channel_id);
static inline int wdt_feed(struct device * dev, int channel_id)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (int) arch_syscall_invoke2(*(uintptr_t *)&dev, *(uintptr_t *)&channel_id, K_SYSCALL_WDT_FEED);
	}
#endif
	compiler_barrier();
	return z_impl_wdt_feed(dev, channel_id);
}


#ifdef __cplusplus
}
#endif

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic pop
#endif

#endif
#endif /* include guard */