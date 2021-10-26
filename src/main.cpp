#include <iostream>
#include "utils.hpp"
#include "phys_mem.hpp"

int main()
{
    risc::PhysMemory<10> mem;
    mem.write(0, 4, (0xFF + 1) * 211 + 189);
    mem.dump(std::cout);

    risc::RegValue test_val = 0;

    mem.read(0, 4, &test_val);

    std::cout << test_val << std::endl;


    return 0;
}