#include <fstream>
#include <iostream>
#include "config.h"
#include "phys_page.h"

using namespace risc;

PhysPage::PhysPage(size_t mem_size) :
    mem_size_(mem_size)
{
    memory_ = new uint8_t[mem_size]{};
}

PhysPage::~PhysPage()
{
    delete [] memory_;
}

bool PhysPage::write(PhysPageOffset addr, size_t size, RegValue value)
{
    if (addr > (mem_size_ - size))
        return false;

    memcpy(memory_ + addr, &value, size);

    return true;
}

bool PhysPage::read(PhysPageOffset addr, size_t size, RegValue* value) const
{
    if (value == nullptr)
        return false;
    if (addr > (mem_size_ - size))
        return false;

    memcpy(value, memory_ + addr, size);

    return true;
}

void PhysPage::dump(std::ostream& fout) const
{
    fout << "Memory capacity: " << mem_size_ << std::endl;
    fout << "Memory dump:"      << std::endl;

    for (size_t i = 0; i < mem_size_; ++i)
        fout << "byte #" << i << " = " << int(memory_[i]) << std::endl;
}
