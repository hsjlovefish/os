build:
	as -o hello.o hello.s
	as -o sum.o sum.s
	ld -Ttext=0 hello.o sum.o -o hello.elf
	objcopy -O binary hello.elf hello.bin

dump: build
	objdump -d -m i8086 hello.elf

run: build
	../kvmtool/lkvm run -c 1 -k hello.bin
