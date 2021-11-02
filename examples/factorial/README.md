# Factorial example

To compile factorial program with RISC-V GNU Compiler Toolchain do the following;

```console
make
```

To launch interpreter do the following:

```console
./../../build/RISC-V-Interpreter factorial.out > log_interpreter.log
```

At the end of `log_interpreter.log` we can see:
```
65652: sw x10, -24(x8)
x10 = 720
x8 = 805306368
```

Here `805306368` is the address of stack pointer and `720 = 6!` - expected result.
