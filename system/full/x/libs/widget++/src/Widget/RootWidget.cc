#include <Widget/RootWidget.h>

namespace Ewok {

RootWidget::RootWidget() {
	doRefresh = false;
	focusedWidget = NULL;
	xwin = NULL;
}

/*void RootWidget::onRepaint(graph_t* g, XTheme* theme, const grect_t& r) {
	graph_fill(g, r.x, r.y, r.w, r.h, theme->basic.bgColor);
}
*/
 
void RootWidget::focus(Widget* wd) {
	if(focusedWidget != NULL && focusedWidget != wd) {
		focusedWidget->onUnfocus();
		focusedWidget->update();
	}

	focusedWidget = wd;
	wd->onFocus();
	wd->update();
}

void RootWidget::repaintWin() { 
	if(xwin == NULL)
		return;
	if(doRefresh) {
		xwin->repaint();
		doRefresh = false;
	}
}

void RootWidget::update() {
	dirty = true;
	doRefresh = true;
}

void RootWidget::sendEvent(xevent_t* ev) {
	onEvent(ev);
}

}