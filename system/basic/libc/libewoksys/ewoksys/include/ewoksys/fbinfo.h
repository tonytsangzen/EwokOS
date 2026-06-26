#ifndef FRAMEBUFFER_INFO_H
#define FRAMEBUFFER_INFO_H

#include <stdint.h>

/* Pixel byte layout in the framebuffer memory:
 *   RGBX8 = [R, G, B, X],  BGRX8 = [B, G, R, X] */
#define FB_PIXEL_RGBX8 0U
#define FB_PIXEL_BGRX8 1U

typedef struct  {
	uint32_t width, height;
	uint32_t vwidth, vheight; /* virtual? */
	uint32_t pitch; /* byte count in a row */
	uint32_t depth; /* bits per pixel */
	uint32_t xoffset, yoffset;
	uint32_t pointer, size, size_max;
	int32_t  dma_id;
	uint32_t phy_base;
	uint8_t  format; /* FB_PIXEL_RGBX8 / FB_PIXEL_BGRX8 */
} fbinfo_t;

#endif
