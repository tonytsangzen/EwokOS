#ifndef EWOKSYS_X86_PLATFORM_H
#define EWOKSYS_X86_PLATFORM_H

#include <stdint.h>
#include <ewokos_config.h>

/*
 * x86 platform data stored in sys_info_t.platform.data[]
 * Parsed by x86 framebuffer driver and other x86-specific user space code.
 * Must match kernel's x86_platform_data.h exactly.
 */

typedef struct {
	/* initrd information from UEFI bootloader */
	ewokos_addr_t  initrd_paddr;
	uint32_t       initrd_size;
	uint32_t       reserved0;

	/* UEFI/GOP framebuffer information */
	ewokos_addr_t  fb_phy_base;   /* physical framebuffer base (may be >4GB) */
	uint32_t       fb_size;       /* framebuffer size in bytes */
	uint16_t       fb_width;
	uint16_t       fb_height;
	uint32_t       fb_pitch;      /* bytes per scanline */
	uint8_t        fb_depth;      /* bits per pixel */
	uint8_t        fb_format;     /* FB_PIXEL_RGBX8 / FB_PIXEL_BGRX8 */
	uint8_t        fb_valid;      /* 1 if populated by firmware (UEFI GOP) */
	uint8_t        reserved1;
} x86_platform_data_t;

#endif