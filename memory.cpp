#include "memory.h"

#include <iostream>
#include <fstream>

memory::memory(uint32_t s)
    {
        s = (s+15)&0xfffffff0; // round the length up, mod-16
        mem.resize(s, 0xa5); // Allocate s bytes in the mem vector and initialize every byte/element to 0xa5.
    }


bool memory::check_illegal(uint32_t addr) const
{
    if (addr >= mem.size())
    {
        std::cout << "WARNING: Address out of range: " << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}

uint8_t memory::get8(uint32_t addr) const
{
    return mem[addr];
}

uint16_t memory::get16(uint32_t addr) const
{
    return (static_cast<uint16_t>(get8(addr)) << 8 | static_cast<uint16_t>(get8(addr+1)));
}

uint32_t memory::get32(uint32_t addr) const
{
    return (static_cast<uint32_t>(get16(addr)) << 16 | static_cast<uint32_t>(get16(addr+2)));
}

int32_t memory::get8_sx(uint32_t addr) const
{
    int32_t val = get8(addr);
    return val | (val&0x00000080 ? 0xffffff00 : 0);
}

int32_t memory::get16_sx(uint32_t addr) const
{
    int32_t val = get16(addr);
    return val | (val&0x00008000 ? 0xffff0000 : 0);
}

void memory::set8(uint32_t addr, uint8_t val)
{
    mem[addr] = val;
}

void memory::set16(uint32_t addr, uint16_t val)
{
    set8((addr+1), val >> 8);
    set8(addr, val);
}

void memory::set32(uint32_t addr, uint32_t val)
{
    set16((addr+2), val >> 16);
    set16(addr, val);
}

void memory::dump() const
{   
    std::string sdump = "";

    for(unsigned int i = 0; i < mem.size(); i++)
    {       
        if (i == 0 || i % 16 == 0)
        {
            std::cout << "0x" << setfill('0') << setw(8) << (i) << ": ";
        }

        std::cout << std::hex << setfill('0') << setw(2) << static_cast<uint16_t>(get8(i)) << " ";

        if ((i+1) % 8 == 0 && (i+1) % 16 != 0)
        {
            std::cout << " ";
        }
        
        uint8_t ch = get8(i);
        ch = isprint(ch) ? ch : '.';
        sdump += ch;

        if ((i+1) % 16 == 0 && i != 0)
        {
            std::cout << "*" + sdump + "*" << std::endl;
            sdump = "";
        }
    }
}


