int mult(int a, int b);
int factorial(int a);

int main()
{
    int init_value = 6;
    int result = factorial(6); // remember that RV32I doesn't support mul operation
    
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

int factorial(int a)
{
    if (a <= 0)
        return 1;

    return mult(a , factorial(a - 1));
}
