# RISC-V-ELF-Interpreter

Here is a simple implementation of RISC-V instructions interpreter with ELF files' parsing.

There are the following features of the project:

* Firstly ELF file is parsed and checked for correctness.
* The program in ELF file is loaded into virtual memory (paging memory), as it usually OS does.
* The interpreter supports all instructions from RV32I set, except `ECALL`, `EBREAK` and `FENCE` instructions.

# How to compile

First of all make sure you have `git`, `cmake`, `libelf` on your device. Then do the following:

```console
git clone https://github.com/Vokerlee/RISC-V-ELF-Interpreter.git
cd RISC-V-ELF-Interpreter
mkdir build
cd build
cmake ..
make
```

Now you have compiled program in `build` folder with name `RISC-V-Interpreter`.

# How to use

The usage is plain: you are to create ELF file (with RISC-V architecture) and next launch `RISC-V-Interpreter` as follows:

```console
./RISC-V-Interpreter elf_file_name.out
```

All information about executed instructions is placed in `stdout`stream. It is recommended to redirect stream to another file, using the launch of the program in the following form:

```console
./RISC-V-Interpreter elf_file_name.out > log_instructions.log
```

Mind that you cannot use any library while compiling your ELF program, otherwise the interpreter will not work (it doesn't support system calls).

# How to create ELF file with RISC-V architecture

Normally compilers generate ELF files of `x86/64` architecture. To change it you are to install another compiler: download and install `https://github.com/riscv-collab/riscv-gnu-toolchain` RISC-V GNU Compiler Toolchain (mind to disable `RVC` extension!).] with `RV32` configuration.

Now you let's look at an example how to compile a simple program:

```C++
int mult(int a, int b);

int main()
{
    int a = 19;
    int b = 8;
    int c = mult(a, b);
    
    return 0;
}

int mult(int a, int b)
{
    int result = 0;

    while (b != 0)
    {
        if (b & 0x1 == 0x1)
        result += a;

        b >>= 1;
        a <<= 1;
    }

    return result;
}
```

```console
riscv32-unknown-elf-gcc -S test_prog.c -o test_prog.s
riscv32-unknown-elf-as test_prog.s -o test_prog.o
riscv32-unknown-elf-ld test_prog.o -o test_prog.out
```

Also you can use `objdump` to check for correctness ELF file:
```console
riscv32-unknown-elf-objdump -S test_prog.out > test_prog.dump
```

Different examples of compilation and usage of the program you can see in `examples` folder.

