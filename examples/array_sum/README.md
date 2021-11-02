# Array summary example

To compile array summary program with RISC-V GNU Compiler Toolchain do the following;

```console
make
```

To launch interpreter do the following:

```console
./../../build/RISC-V-Interpreter array_sum.out > log_interpreter.log
```

At the end of `log_interpreter.log` we can see:
```
65652: sw x10, -24(x8)
x10 = 720
x8 = 805306368
```

Here we can see (at 5107 line) `780 = 40 * (40 - 1) / 2` - the summary of 40 elements of array:
```
65728: sw x15, -24(x8)
x15 = 780
x8 = 805306368
```
