#/bin/ipcserv /drivers/raspix/soundd   /dev/sound
/bin/ipcserv /drivers/raspix/usbd     /dev/touch0

/bin/ipcserv /drivers/raspix/fbd      /dev/fb0
/bin/ipcserv /drivers/displayd        /dev/display /dev/fb0
/bin/ipcserv /drivers/fontd           /dev/font

/bin/ipcserv /drivers/timerd          /dev/timer
/bin/ipcserv /drivers/ramfsd          /tmp

/bin/ipcserv /drivers/nulld           /dev/null
/bin/ipcserv /drivers/proc/sysinfod   /proc/sysinfo
/bin/ipcserv /drivers/proc/stated     /proc/state

/bin/ipcserv /drivers/xserverd        /dev/x

@/bin/ipcserv /sbin/sessiond

@/bin/session -r &

#@/sbin/x/xmoused /dev/mouse0 &
@/sbin/x/xim_none &
@/bin/x/xsession  misa &
