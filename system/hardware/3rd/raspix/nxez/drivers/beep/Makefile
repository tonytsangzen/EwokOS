include ../../make.rule

BUILD_DIR = $(SYS_DIR)/build
TARGET_DIR = $(BUILD_DIR)/$(HW)

LDFLAGS = -L$(BUILD_DIR)/lib

CFLAGS += -I $(BUILD_DIR)/include

BEEPD_OBJS = beepd.o

BEEPD = $(TARGET_DIR)/drivers/raspix/nxez_beepd

$(BEEPD): $(BEEPD_OBJS) \
		$(EWOK_LIBC_A)  \
		$(BUILD_DIR)/lib/libarch_bcm283x.a 
	$(LD) -Ttext=100 $(BEEPD_OBJS) -o $(BEEPD) $(LDFLAGS) -larch_bcm283x $(EWOK_LIBC)

clean:
	rm -f $(BEEPD_OBJS)
