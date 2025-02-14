#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <ewoksys/vdevice.h>
#include <ewoksys/klog.h>
#include <ewoksys/proc.h>
#include <ewoksys/keydef.h>
#include <ewoksys/kernel_tic.h>
#include <ewoksys/core.h>
#include <x/xwin.h>
#include <string.h>
#include <ewoksys/timer.h>
#include <keyb/keyb.h>

class XIM {
	int x_pid;
	int keybFD;
	bool escHome;

	void input(uint8_t c, uint8_t state) {
		xevent_t ev;
		ev.type = XEVT_IM;
		if((c == KEY_ESC || c == KEY_BUTTON_SELECT) && escHome)
			c = KEY_HOME;
		ev.value.im.value = c;
		ev.state = state;

		proto_t in;
		PF->init(&in)->add(&in, &ev, sizeof(xevent_t));
		dev_cntl_by_pid(x_pid, X_DCNTL_INPUT, &in, NULL);
		PF->clear(&in);
	}

public:
	inline XIM(const char* keyb_dev, bool escHome) {
		x_pid = -1;
		keybFD = -1;
		this->escHome = escHome;

		while(true) {
			//keybFD = open(keyb_dev, O_RDONLY | O_NONBLOCK);
			keybFD = open(keyb_dev, O_RDONLY);
			if(keybFD > 0)
				break;
			proc_usleep(300000);
		}
	}

	inline ~XIM() {
		if(keybFD < 0)
			return;
		::close(keybFD);
	}

	int read(void) {
		if(x_pid < 0)
			x_pid = dev_get_pid("/dev/x");
		if(x_pid <= 0 || keybFD < 0)
			return 0;
		int ux = core_get_active_ux();
		if(ux != UX_X_DEFAULT)
			return 0;

		keyb_evt_t evts[KEYB_EVT_MAX];
		int n = keyb_read(keybFD, evts, KEYB_EVT_MAX);
		for(int i=0; i<n; i++)
			input(evts[i].key, evts[i].state);
		return n;
	}
};

int main(int argc, char* argv[]) {
	const char* keyb_dev = "/dev/keyb0";
	if(argc > 1)
		keyb_dev = argv[1];

	bool escHome = false;
	if(argc > 2 && strcmp(argv[2], "esc_home") == 0) {
		escHome = true;
	}

	core_set_ux(UX_X_DEFAULT);

	XIM xim(keyb_dev, escHome);
	while(true) {
		if(xim.read() == 0)
			proc_usleep(10000);
	}
	return 0;
}
