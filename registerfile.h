#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include <string>
#include <vector>

class registerfile
{
public:
    /**
     * @brief Construct a new registerfile object
     *  Uses reset() to initialize register x0 to zero, and all other registers to 0xf0f0f0f0.
     * 
     */
    registerfile() { reset(); }

    /**
     * @brief Initialize register x0 to zero, and all other registers to 0xf0f0f0f0.
     * 
     */
    void reset();

    /**
     * @brief Assign register r the given val. If r is zero then do nothing.
     * 
     * @param r The register
     * @param val The value to assign to r
     */
    void set(uint32_t r, int32_t val);

    /**
     * @brief Return the value of register r. If r is zero then return zero.
     * 
     * @param r The register
     * @return int32_t Value of the register
     */
    int32_t get(uint32_t r) const;
    
    uint32_t get_size() { return regs.size(); }

    /**
     * @brief  Dump of the registers.
     * 
     * @param hdr String that must be printed at the begining of the output lines.
     */
    void dump(const std::string &hdr) const;

private:
    std::vector<int32_t> regs;   ///< Vector to store registers
};

#endif
