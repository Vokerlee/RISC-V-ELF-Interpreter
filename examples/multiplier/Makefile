all: multiplier.out
	riscv32-unknown-elf-objdump -S multiplier.out > multiplier.dump

multiplier.out: multiplier.o
	riscv32-unknown-elf-ld multiplier.o -o multiplier.out
	rm multiplier.o

multiplier.o: multiplier.s
	riscv32-unknown-elf-as multiplier.s -o multiplier.o

multiplier.s: multiplier.c
	riscv32-unknown-elf-gcc -S multiplier.c -o multiplier.s
