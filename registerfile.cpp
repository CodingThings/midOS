#include "registerfile.h"

#include <iostream>
#include <iomanip>

void registerfile::reset()
{
    regs.push_back(0);	//ip register
    for (int i = 0; i < 10; i++)
    {
        regs.push_back(0);
    }
}

void registerfile::set(uint32_t r, int32_t val)
{
    if (r < 11)
    {
        regs[r] = val;
    }

    return;
}

int32_t registerfile::get(uint32_t r) const
{
    return regs[r];
}

void registerfile::dump(const std::string &hdr) const
{
	std::cout << " ip: " << std::hex << std::setfill('0') << std::setw(8)<< regs[0] << std::endl;
	
    for(unsigned int i = 1; i < 11; i++)
    {   
        std::cout << "r" << std::dec << std::setw(2) << i << ": ";

        std::cout << std::hex << std::setfill('0') << std::setw(8) << (regs[i]) << std::endl;

    }
}
