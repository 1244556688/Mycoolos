CC = gcc
AS = as
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
LDFLAGS = -ffreestanding -O2 -nostdlib -m32 -T linker.ld

OBJS = boot.o kernel.o graphics.o mouse.o
KERNEL_BIN = myos.bin
ISO_IMAGE = myos.iso

.PHONY: all clean iso

all: $(ISO_IMAGE)

$(KERNEL_BIN): $(OBJS) linker.ld
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -lgcc

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) --32 -o $@ $<

$(ISO_IMAGE): $(KERNEL_BIN) grub.cfg
	mkdir -p isodir/boot/grub
	cp $(KERNEL_BIN) isodir/boot/
	cp grub.cfg isodir/boot/grub/
	grub-mkrescue -o $(ISO_IMAGE) isodir

clean:
	rm -rf *.o $(KERNEL_BIN) $(ISO_IMAGE) isodir
