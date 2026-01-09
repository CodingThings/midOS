#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>


using namespace std;

/**
 * @brief Simulated memory of bytes whose starting address is zero
 * 
 */
class memory
{
public:
    /**
     * @brief Construct a new memory object. S is rounded up to the next
     *  multiple of 16.
     * 
     * @param s Number of bytes to create in simulated memory
     */
    memory(uint32_t s);

    /**
     * @brief Destroy the memory object
     *
     * @note Segmentation fault when uncommented, but works fine without
     */
    //~memory() { delete[] &mem; }

    /**
     * @brief Check if an address is illegal
     * 
     * @param addr The address to be checked
     * @return true if addr is illegal
     * @return false if addr is valid
     */
    bool check_illegal(uint32_t addr) const;

    /**
     * @brief Get the total number of bytes in the simulated memory
     * 
     * @return uint32_t The number of bytes in the simulated memory
     */
    uint32_t get_size() const { return mem.size(); }

    /**
     * @defgroup getX Gets little endian value from the simulated memory
     * 
     * @param addr The address of the least-significant byte of the value
     * @return uint8_t The little endian value starting at addr
     */
    uint8_t get8(uint32_t addr) const;      ///< Get 8-bit value from memory
    uint16_t get16(uint32_t addr) const;    ///< Get 16-bit little endian value from simulated memory
    uint32_t get32(uint32_t addr) const;    ///< Get 32-bit little endian value from simulated memory

    /**
     * @defgroup getX_sx Gets little endian, sign extended value from the simulated memory
     * 
     * @param addr The address of the least-significant byte of the value
     * @return int32_t The signed extended little endian value starting at addr
     */
    /// Get 8-bit value from memory
    int32_t get8_sx(uint32_t addr) const;

    ///< Get 16-bit sign extended little endian value from memory and sign extend to 32 bits
    int32_t get16_sx(uint32_t addr) const;

    ///< Get 32-bit sign extended  little endian value from memory and sign extend to 32 bits
    int32_t get32_sx(uint32_t addr) const { return get32(addr); }

    /**
     * @defgroup setX Stores a little endian value in the simulated memory
     * 
     * @param addr The address of the least-significant byte of the value to store
     * @param val  The value to store in the simulated memory
     * 
     */
    void set8(uint32_t addr, uint8_t val);      ///< Store 8-bit value from simulated memory
    void set16(uint32_t addr, uint16_t val);    ///< Store 16-bit little endian value from simulated memory
    void set32(uint32_t addr, uint32_t val);    ///< Store 32-bit little endian value from simulated memory

    /**
     * @brief Print a hex and ASCII display of the contents of the simulated memory
     *
     */
    void dump() const;

    /**
     * @brief Loads file contents into simulated memory
     * 
     * @param fname Name of file to be open and read
     * @return true if fname was opened and read into simulated memory
     * @return false if fname could not be opened or is larger than the simulated memory
     */


private:
    std::vector<uint8_t> mem;   ///< Vector to store simulated memory
};

#endif
