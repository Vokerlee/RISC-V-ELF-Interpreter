all: array_sum.out
	riscv32-unknown-elf-objdump -S array_sum.out > array_sum.dump

array_sum.out: array_sum.o
	riscv32-unknown-elf-ld array_sum.o -o array_sum.out
	rm array_sum.o

array_sum.o: array_sum.s
	riscv32-unknown-elf-as array_sum.s -o array_sum.o

array_sum.s: array_sum.c
	riscv32-unknown-elf-gcc -S array_sum.c -o array_sum.s
