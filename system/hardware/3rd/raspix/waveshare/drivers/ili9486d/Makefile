include ../../make.rule

BUILD_DIR = $(SYS_DIR)/build
TARGET_DIR = $(BUILD_DIR)/$(HW)

LDFLAGS = -L$(BUILD_DIR)/lib

CFLAGS += -I $(BUILD_DIR)/include

ILI9486D_OBJS = ili9486d.o

ILI9486D = $(TARGET_DIR)/drivers/raspix/ili9486d

$(ILI9486D): $(ILI9486D_OBJS) \
		$(EWOK_LIBC_A)  \
		$(BUILD_DIR)/lib/libarch_bcm283x.a \
		$(BUILD_DIR)/lib/libfbd.a \
		$(BUILD_DIR)/lib/libgraph.a \
		$(BUILD_DIR)/lib/libsconf.a \
		$(BUILD_DIR)/lib/libupng.a \
		$(BUILD_DIR)/lib/libili9486.a 
	$(LD) -Ttext=100 $(ILI9486D_OBJS) -o $(ILI9486D) $(LDFLAGS) -lili9486 -larch_bcm283x -lfbd -lupng -lgraph -lbsp -lsconf $(EWOK_LIBC)

clean:
	rm -f $(ILI9486D_OBJS)
