#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ewoksys/syscall.h>
#include <sysinfo.h>

int main(int argc, char* argv[]) {
	sys_info_t sys_info;
	sys_state_t sys_state;
	syscall1(SYS_GET_SYS_INFO, (int32_t)&sys_info);
	syscall1(SYS_GET_SYS_STATE, (int32_t)&sys_state);
	uint32_t fr_mem = sys_state.mem.free / (1024*1024);
	uint32_t t_mem = sys_info.total_usable_mem_size / (1024*1024);

	printf(
		"machine            %s\n" 
		"arch               %s\n"
		"cores              %d\n"
		"mem info           %d/%d MB\n"
		"dma                phy:0x%08x, V:0x%08x, size:%d KB\n"
		"mmio_base          Phy:0x%08x, V:0x%08x, size:%d MB\n"
		"framebuffer_base   Phy:0x%08x, V:0x%08x\n",
		sys_info.machine,
		sys_info.arch,
		sys_info.cores,
		fr_mem, t_mem,
		sys_info.dma.phy_base, sys_info.dma.v_base, sys_info.dma.size/(1024),
		sys_info.mmio.phy_base, sys_info.mmio.v_base, sys_info.mmio.size/(1024*1024),
		sys_info.fb.phy_base, sys_info.fb.v_base);

	return 0;
}

