#ifndef WIDGET_MENU_HH
#define WIDGET_MENU_HH

#include <Widget/WidgetWin.h>

#include <string>
#include <vector>
using namespace EwokSTL;

namespace Ewok {

class Menubar;
class MenuItem;
typedef void (*menufunc_t)(MenuItem*, void*);

class Menu: public WidgetWin {
protected:
    Menubar* menubar;
    Menu* menu;
    void onUnfocus();
    bool subMenued;
    uint32_t itemSize;
public:
    inline void setItemSize(uint32_t size) { itemSize = size; }
    inline uint32_t getItemSize() { return itemSize; }

    inline void attachMenubar(Menubar* bar) { menubar = bar; }
    inline void attachMenu(Menu* menu) { this->menu = menu; }

    Menu();
    uint32_t getItemNum();
    void add(const string& title, graph_t* icon, Menu* menu, menufunc_t func, void* funcArg);
    void subMenu(bool s);
    void hide();
};

class MenuItem {
public:
    string title;
    graph_t* icon;
    Menu* menu;
    menufunc_t func;
    void* funcArg;

    inline MenuItem() {
        icon = NULL;
        menu = NULL;
        func = NULL;
        funcArg = NULL;
    }

    inline ~MenuItem() {
        if(icon != NULL)
            graph_free(icon);

        if(menu != NULL)
            delete menu;
    }
};



}

#endif