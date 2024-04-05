kernel.bin: build boot16.bin boot32.bin system.bin app/app1.bin
	./build

boot16.bin: boot16.S
	gcc -c boot16.S -o boot16.o
	ld -Ttext=0x0 boot16.o -o boot16.elf
	objcopy -O binary boot16.elf boot16.bin

boot32.bin: boot32.S
	gcc -c boot32.S -o boot32.o
	ld -Ttext=0x20000 boot32.o -o boot32.elf
	objcopy -O binary boot32.elf boot32.bin

CFLAGS = -std=c11 -I. -fno-pic -mcmodel=kernel -fno-stack-protector -fcf-protection=none \
				 -nostdinc -fno-builtin
SRCS = main.c $(wildcard mm/*.c) $(wildcard lib/*.c) $(wildcard kernel/*.c)
OBJS = $(SRCS:.c=.o)

system.bin: head64.o $(OBJS)
	ld -Ttext=0xffffffff80100000 $^ -o system.elf
	objcopy -O binary system.elf $@

.depend: $(SRCS)
	@rm -f .depend
	@$(foreach src,$(SRCS), \
		echo -n $(dir $(src)) >> .depend; \
		gcc -I. -MM $(src) >> .depend; \
	)
include .depend

# app
app/app1.bin: app/app1.S
	gcc -c app/app1.S -o app/app1.o
	ld -Ttext=0x100000 app/app1.o -o app/app1.elf
	objcopy -O binary app/app1.elf app/app1.bin

build: build.c
	gcc $< -o $@

.PHONY: clear run

run: kernel.bin
	../kvmtool/lkvm run -c 1 -k ./kernel.bin

clean:
	rm -rf *.bin *.elf *.o build
