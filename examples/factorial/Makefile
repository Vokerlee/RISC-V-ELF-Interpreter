all: factorial.out
	riscv32-unknown-elf-objdump -S factorial.out > factorial.dump

factorial.out: factorial.o
	riscv32-unknown-elf-ld factorial.o -o factorial.out
	rm factorial.o

factorial.o: factorial.s
	riscv32-unknown-elf-as factorial.s -o factorial.o

factorial.s: factorial.c
	riscv32-unknown-elf-gcc -S factorial.c -o factorial.s
