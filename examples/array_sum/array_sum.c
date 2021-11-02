#define ARRAY_SIZE 40

int main()
{
    int array[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = i;
    }

    int summ = 0;

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        summ += array[i];
    }

    return 0;
}
