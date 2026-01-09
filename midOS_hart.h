#ifndef MIDOS_HART_H
#define MIDOS_HART_H

#include "registerfile.h"
#include "memory.h"

#include <iostream>
#include <string>

class midOS_hart
{
public:
    /**
     * @brief Constructer to initialize mem
     * 
     * @param m Mem object
     */
    midOS_hart(memory &m) : mem(m) {}

    /**
     * @brief When true, dump the registers before instruction is executed.
     * 
     * @param b True or False to show or not to show the registers
     */
    void set_show_registers(bool b) { show_registers = b; }

    /**
     * @brief Return true if the hart has been halted for any reason.
     * 
     * @return true if halt is set to true
     * @return false if halt is set to false
     */
    bool is_halted() const { return halt; }

    /**
     * @brief Get the halt reason.
     * 
     * @return const std& String indicating the reason the hart has been halted.
     */
    const std::string &get_halt_reason() const { return halt_reason; }

    /**
     * @brief Get the instruction counter
     * 
     * @return uint64_t Number of instructions that have been executed by the simulator since the last reset()
     */
    uint64_t get_insn_counter() const { return insn_counter; }


    /**
     * @brief Tells the simulator to execute and instruction
     * 
     * @param hdr String to be printed on the left of any and all output that is displayed as a
     *      result of calling this method
     */
    void tick(const std::string &hdr ="");

    /**
     * @brief Dump the entire state of the hart
     * 
     * @param hdr String to prefix each line
     */
    void dump(const std::string &hdr ="") const;

    /**
     * @brief Reset the rv32i object and the registerfile
     * 
     */
    void reset();

private:
    /**
     * @brief execute the given RV32I instruction
     * 
     * @param insn Instruction
     * 
     */
    void exec(uint32_t insn);

    /**
     * @brief Set the halt flag
     * 
     * @param insn Instruction
     * 
     */
     
    bool check_register(uint32_t r);
    void exec_illegal_insn(uint32_t insn);

    static uint32_t get_opcode(uint32_t insn) { return (insn & 0xff000000) >> 24; }           ///< Get opcode from instruction set
    static uint32_t get_param1(uint32_t insn) { return (insn & 0x00ff0000) >> 16; }       ///< Get rd from instruction set
    static uint32_t get_param2(uint32_t insn) { return (insn & 0x0000ffff); }  ///< Get funct3 from instruction set

    /**
     * @defgroup exec_x Used to execute an instruction based on their opcode
     * 
     * @param insn instruction
     * 
     */
    void exec_incr(uint32_t insn);
    void exec_addi(uint32_t insn);
    void exec_addr(uint32_t insn);
    void exec_pushr(uint32_t insn);
    void exec_pushi(uint32_t insn);
    void exec_movi(uint32_t insn);
    void exec_movr(uint32_t insn);
    void exec_movmr(uint32_t insn);
    void exec_movrm(uint32_t insn);
    void exec_movmm(uint32_t insn);
    void exec_printr(uint32_t insn);
    void exec_printm(uint32_t insn);
    void exec_jmp(uint32_t insn);
    void exec_cmpi(uint32_t insn);
    void exec_cmpr(uint32_t insn);
    void exec_jlt(uint32_t insn);
    void exec_jgt(uint32_t insn);
    void exec_je(uint32_t insn);
    void exec_call(uint32_t insn);
    void exec_callm(uint32_t insn);
    void exec_ret(uint32_t insn);
    void exec_alloc(uint32_t insn);
    void exec_acquire_lock(uint32_t insn);
    void exec_release_lock(uint32_t insn);
    void exec_sleep(uint32_t insn);
    void exec_set_priority(uint32_t insn);
    void exec_exit(uint32_t insn);
    void exec_free_memory(uint32_t insn);
    void exec_map_shared_mem(uint32_t insn);
    void exec_signal_event(uint32_t insn);
    void exec_wait_event(uint32_t insn);
    void exec_input(uint32_t insn);
    void exec_memory_clear(uint32_t insn);
    void exec_terminate_process(uint32_t insn);
    void exec_popr(uint32_t insn);
    void exec_popm(uint32_t insn);

    static constexpr int instruction_width = 35; ///< width for setw when outputting instruction output

    bool halt = { false };                  ///< flag to stop the hart from executing instructions
    std::string halt_reason = { " none " }; ///< when halt is set to true, also set this to contain a string describing the reason for the halt

    bool show_registers = { false };    ///< flag to print a dump of the hart state 
    uint64_t insn_counter = { 0 };      ///< will count the number of instructions that have been executed
    uint32_t pc = { 0 };                ///< contains the address of the instruction being decoded/disassembled

protected:
    registerfile regs; ///< general purpose registers
    memory &mem;       ///< reference to the memory object
};

#endif
