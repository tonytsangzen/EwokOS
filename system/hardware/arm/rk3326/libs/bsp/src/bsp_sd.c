#include <bsp/bsp_sd.h>
#include <stdint.h>
#include <sysinfo.h>
#include <string.h>
#include <sys/syscall.h>
#include <sd/sd.h>
#include <arch/rk3326/sd.h>

int bsp_sd_init(void) {
  sys_info_t sysinfo;
  syscall1(SYS_GET_SYS_INFO, (int32_t)&sysinfo);
  int res = sd_init(rk3326_sd_init, rk3326_sd_read_sector, rk3326_sd_write_sector);
	return res;
}
