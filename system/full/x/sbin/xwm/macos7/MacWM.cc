#include "MacWM.h"
#include <sys/kernel_tic.h>
#include <sys/klog.h>

using namespace Ewok;

void MacWM::drawTitlePattern(graph_t* g, int x, int y, int w, int h, uint32_t fg) {
	int step = 3;
	y = y + step;
	int steps = h / step;

	for (int i = 0; i < steps; i++)
	{
		graph_line(g, x + 4, y, x + w - 8, y, fg);
		y += step;
	}
}

void MacWM::drawTitle(graph_t* g, xinfo_t* info, grect_t* r, bool top) {
	uint32_t fg, bg;
	getColor(&fg, &bg, top);
	gsize_t sz;
	get_text_size(info->title, font, &sz.w, &sz.h);
	
	grect_t rect;
	getTitle(info, &rect);

	int pw = (r->w-sz.w)/2;
	graph_fill(g, r->x, r->y, r->w, rect.h, bg);//title box
	if(top) {
		drawTitlePattern(g, r->x, r->y, pw, r->h, fg);
		drawTitlePattern(g, r->x+pw+sz.w, r->y, pw, r->h, fg);
	}
	graph_draw_text(g, r->x+pw, r->y+2, info->title, font, fg);//title
}

void MacWM::drawWelcome(graph_t* g) {
	const char* welcome = "EwokOS micro kernel OS";
	gsize_t sz;
	get_text_size(welcome, font, &sz.w, &sz.h);

	graph_fill_round(g,
		(g->w-sz.w)/2 - 12, (g->h-sz.h)/2 - 12, 
		sz.w + 24, sz.h + 24, 
		8, 0x88ffffff);

	graph_round(g,
		(g->w-sz.w)/2 - 16, (g->h-sz.h)/2 - 16, 
		sz.w + 32, sz.h + 32, 
		12, 0x88ffffff);

	graph_draw_text(g,
		(g->w-sz.w)/2, (g->h-sz.h)/2, 
		welcome,  font, 0xff000000);
}

void MacWM::drawDesktop(graph_t* g) {
	XWM::drawDesktop(g);

	if(doWelcome)  {
		doWelcome = false;
		drawWelcome(g);
	}
}