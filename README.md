# EwokOS

.Author

	Misa.Z misa.zhu@gmail.com

.About

	A microkernel OS for learning operating system. versatilepb / raspi1,2,3 ported well, raspi4 todo....
	-mmu
	-smp multi-core
 	-64bits & 32bits
	-copy on write
	-multi processes
	-multi thread
	-ipc
	-virtual fs service(everythig is a file)
	-framebuffer device service for graphics
	-uart device service
	-SD card
 	-USB

.Environment & Tools

	QEMU: 
		modified qemu file: hw/sd/sd.c and recompile
		......
		if(req.arg & ACMD41_ENQUIRY_MASK) { //modified by Misa.Z 
		/*if (FIELD_EX32(sd->ocr & req.arg, OCR, VDD_VOLTAGE_WINDOW)) {*/
			/* We accept any voltage.  10000 V is nothing.
			*
			* Once we're powered up, we advance straight to ready state
			* unless it's an enquiry ACMD41 (bits 23:0 == 0).
			*/
			sd->state = sd_ready_state;
		}
		......
	
	risc-v toolchains:
		https://github.com/riscv-software-src/homebrew-riscv

	Mac OSX(with brew installed):	
		brew tap PX4/homebrew-px4
		brew install gcc-arm-none-eabi-49
		brew install e2tools
		(set the right PATH environment after installed)
		download usb to ttl driver https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers
		
	How to create/mount ext2 image in macosx
		===============prepair================
		install macFUSE from official website(https://osxfuse.github.io/)
		brew install e2fsprogs
		brew install libtool 
		brew install autoconf
		brew install automake

		(download https://github.com/alperakcan/fuse-ext2)
		./autogen.sh
		CFLAGS="-idirafter/opt/gnu/include -idirafter/usr/local/include/osxfuse/ -idirafter/$(brew --prefix e2fsprogs)/include" LDFLAGS="-L/usr/local/opt/glib -L/usr/local/lib -L$(brew --prefix e2fsprogs)/lib" ./configure
		sudo xcode-select -s /Applications/Xcode.app/Contents/Developer
		make
		sudo make install
		=================example==============
		dd if=/dev/zero of=root.ext2 bs=1024 count=16384
 		mke2fs -b 1024 -I 128 root.ext2 (make ext2 fs with: block_size=1024 inode_size=128)
 		mkdir -p tmp
		fuse-ext2 -o force,rw+ img tmp
 		(copy files)
 		umount ./tmp
 		rm -r tmp
.tty debug
	
	install minicom(linux/mac)
	
.make 
	
	"cd kernel/build/{arch}; make":
	  build EwokOS kernel image.
	
.make rootfs (system/root.ext2)
	
	"cd system; make basic/make gui(with fbgui)/make(with xgui and extra apps"; make sd:
	  build EwokOS rootfs apps and sd file system.
	
.run by qemu (raspi2)
	
	"cd kernel/build/raspi/pix"
	"make run":
	  run EwokOS(username: root, password: (none));
	"make debug":
	  run EwokOS at debug server-mode.
	"make gdb":
	  debug EwokOS (debug client-mode).

.commands 
	
	Most of commands are in 'rootfs/sbin' directory, like:
	ls, ps, pwd, test ......

.Source code read-guide
	Tips: Don't fall in love with assembly too much;).

