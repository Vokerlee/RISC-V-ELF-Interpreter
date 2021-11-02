# Multiplier example

To compile multiplier program with RISC-V GNU Compiler Toolchain do the following;

```console
make
```

To launch interpreter do the following:

```console
./../../build/RISC-V-Interpreter multiplier.out > log_interpreter.log
```

At the end of `log_interpreter.log` we can see:
```
65664: sw x10, -28(x8)
x10 = 152
x8 = 805306368
```

Here `152 = 19 * 6` - the result of multiplication, what was expected.
