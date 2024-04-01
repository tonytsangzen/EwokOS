#include <Widget/WidgetWin.h>
#include <WidgetEx/FileWidget.h>
#include <x++/X.h>
#include <unistd.h>
#include <ewoksys/proc.h>
#include <elf/elf.h>
#include <upng/upng.h>
#include <dirent.h>

#include <string>
using namespace EwokSTL;
using namespace Ewok;

class FileManager: public FileWidget {

	bool check_elf(const string& fname) {
		elf_header_t header;
		if(elf_read_header(fname.c_str(), &header) != 0)
			return false;

		int pid = fork();
		if(pid == 0)  {
			proc_detach();
			proc_exec(fname.c_str());
			exit(0);
		}
		return true;
	}

protected:
	void onFile(const string& fname, const string& open_with) {
		if(check_elf(fname))
			return;

		char cmd[FS_FULL_NAME_MAX+1] = "";
		if(open_with.length() == 0)
			return;

		snprintf(cmd, FS_FULL_NAME_MAX, "%s %s", open_with.c_str(), fname.c_str());
		int pid = fork();
		if(pid == 0)  {
			proc_detach();
			proc_exec(cmd);
			exit(0);
		}
	}

	void onPath(const string& pathname) {
	}
};

int main(int argc, char** argv) {
	X x;
	WidgetWin win;
	RootWidget* root = new RootWidget();
	win.setRoot(root);
	root->setType(Container::VERTICLE);
	root->setAlpha(false);

	FileManager* fm = new FileManager();
	root->add(fm);

	x.open(0, &win, -1, -1, 320, 240, "xfinder", XWIN_STYLE_NORMAL);
	win.setVisible(true);
	x.run(NULL, &win);
	return 0;
}