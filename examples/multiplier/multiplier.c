int mult(int a, int b);

int main()
{
    int a = 19;
    int b = 8;
    int c = mult(a, b); // remember that RV32I doesn't support mul operation
    
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
