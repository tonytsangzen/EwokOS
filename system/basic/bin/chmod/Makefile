SYS_DIR=../../..
include $(SYS_DIR)/platform/$(ARCH)/make.rule

BUILD_DIR = $(SYS_DIR)/build/$(HW)
TARGET_DIR = $(BUILD_DIR)/rootfs

LDFLAGS = -L$(BUILD_DIR)/lib

CFLAGS += -I $(BUILD_DIR)/include

CHMOD_OBJS = chmod.o

CHMOD = $(TARGET_DIR)/bin/chmod

$(CHMOD): $(CHMOD_OBJS) \
		$(EWOK_LIBC_A) 
	$(LD) -Ttext=100 $(CHMOD_OBJS) -o $(CHMOD) $(LDFLAGS) $(EWOK_LIBC)

clean:
	rm -f $(CHMOD_OBJS)

