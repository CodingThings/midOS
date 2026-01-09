#include "midOS_hart.h"

#include <iomanip>
#include <cassert>

void midOS_hart::reset()
{
    regs.reset();
    insn_counter = 0;
    halt = false;
    halt_reason = "none";
}

void midOS_hart::dump(const std::string &hdr) const
{
    regs.dump(hdr);
}

void midOS_hart::tick(const std::string &hdr)
{
    if (halt)
        return;

    if (show_registers)
        dump(hdr);

    if (regs.get(0) % 4 != 0)
    {
        halt_reason = "PC alignment error";
        halt = true;
        return;
    }

    insn_counter++;

	auto insn = mem.get32(regs.get(0));
    
    exec(insn);
    
}

void midOS_hart::exec(uint32_t insn)
{   
    uint32_t opcode = get_opcode(insn);
    
/*	FOR TESTING 

    uint32_t param1 = get_param1(insn);
    uint32_t param2 = get_param2(insn);

    std::cout << "\nOpcode: " << opcode;
    std::cout << "\nParam1: " << param1;
    std::cout << "\nParam2: " << param2;
*/

    switch (opcode)
    {
    default:                    exec_illegal_insn(insn); return;
    case 1:                     exec_incr(insn); return;
    case 2:                     exec_addi(insn); return;
    case 3:                     exec_addr(insn); return;
    case 4:                     exec_pushr(insn); return;
    case 5:                     exec_pushi(insn); return;
    case 6:                     exec_movi(insn); return;
    case 7:                     exec_movr(insn); return;
    case 8:                     exec_movmr(insn); return;
    case 9:                     exec_movrm(insn); return;
    case 10:                    exec_movmm(insn); return;
    case 11:                    exec_printr(insn); return;
    case 12:                    exec_printm(insn); return;
    case 13:                    exec_jmp(insn); return;
    case 14:                    exec_cmpi(insn); return;
    case 15:                    exec_cmpr(insn); return;
    case 16:                    exec_jlt(insn); return;
    case 17:                    exec_jgt(insn); return;
    case 18:                    exec_je(insn); return;
    case 19:                    exec_call(insn); return;
    case 20:                    exec_callm(insn); return;
    case 21:                    exec_ret(insn); return;
    case 22:                    exec_alloc(insn); return;
    case 23:                    exec_acquire_lock(insn); return;
    case 24:                    exec_release_lock(insn); return;
    case 25:                    exec_sleep(insn); return;
    case 26:                    exec_set_priority(insn); return;
    case 27:                    exec_exit(insn); return;
    case 28:                    exec_free_memory(insn); return;
    case 29:                    exec_map_shared_mem(insn); return;
    case 30:                    exec_signal_event(insn); return;
    case 31:                    exec_wait_event(insn); return;
    case 32:                    exec_input(insn); return;
    case 33:                    exec_memory_clear(insn); return;
    case 34:                    exec_terminate_process(insn); return;
    case 35:                    exec_popr(insn); return;
    case 36:                    exec_popm(insn); return;
    }
}

bool midOS_hart::check_register(uint32_t r)
{
	if (r < regs.get_size()) { return true; }
	else { return false; }
}

void midOS_hart::exec_illegal_insn(uint32_t insn)
{
    halt = true;
    halt_reason = "Execution terminated. Reason: Illegal instruction";
}

void midOS_hart::exec_incr(uint32_t insn) //finished and tested
{
    uint32_t param1 = get_param1(insn);
	
	if (check_register(param1))
	{
		regs.set(param1, (regs.get(param1)+1));
	}
	if (!check_register(param1)) { cout << "invalid register" << endl; }

    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_addi(uint32_t insn) //finished and tested
{
    uint32_t param1 = get_param1(insn);
    uint32_t param2 = get_param2(insn);

    if (regs.get(param1) == -252645136)
    {
        regs.set(param1, 0);
    }
    
    //sign extend
    uint32_t val;
    if (param2 >= 0x8000)
    {
		val = param2 + 0xffff0000;
	}
	
	if (param2 < 0x8000)
    {
		val = param2;
	}
	
	if (check_register(param1))
	{
		regs.set(param1, (regs.get(param1) + val));
	}
	if (!check_register(param1)) { cout << "invalid register" << endl; }
	
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_addr(uint32_t insn) //finished and tested
{
    uint32_t r1 = get_param1(insn);
    uint32_t r2 = get_param2(insn);

	if (check_register(r1) && check_register(r2))
	{
		regs.set(r1, (regs.get(r1) + regs.get(r2)));
	}
	if (!check_register(r1) || !check_register(r2)) 
	{ 
		cout << "invalid register" << endl; 
	}
	
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_pushr(uint32_t insn)
{
    std::cout << "\npushr - work in progress\n";
    //push contents of a register onto stack
    //decrease value in register 10 by 4.
    
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_pushi(uint32_t insn)
{
    std::cout << "\npushi - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_movi(uint32_t insn) //finished and tested
{
    uint32_t r1 = get_param1(insn);
    uint32_t param2 = get_param2(insn);
    
    //sign extend
    uint32_t val;
    if (param2 >= 0x8000)
    {
		val = param2 + 0xffff0000;
	}
	
	if (param2 < 0x8000)
    {
		val = param2;
	}

    if (check_register(r1)) { regs.set(r1, val); }
    
    if (!check_register(r1)) { cout << "invalid register" << endl; }
    
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_movr(uint32_t insn) //finished and tested
{
    uint32_t r1 = get_param1(insn);
    uint32_t r2 = get_param2(insn);
    
    if (check_register(r1) && check_register(r2)) 
    { 
		regs.set(r1, regs.get(r2)); 
	}
    if (!check_register(r1) || !check_register(r2)) 
    { 
		cout << "invalid register" << endl; 
	}
    
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_movmr(uint32_t insn)
{
    std::cout << "\nmovmr - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_movrm(uint32_t insn)
{
    std::cout << "\nmovrm - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_movmm(uint32_t insn)
{
    std::cout << "\nmovmm - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_printr(uint32_t insn) //finished and tested
{
    uint32_t reg = get_param1(insn);
    
    std::cout << dec << regs.get(reg) << hex;
    
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_printm(uint32_t insn)
{
    std::cout << "\nprintm - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_jmp(uint32_t insn) //finished and tested
{
    uint32_t reg = get_param1(insn);
    if (check_register(reg))
    {
		int16_t val = regs.get(reg);
		regs.set(0, regs.get(0) + (val - 1));
	}
	if (!check_register(reg)) { cout << "invalid register" << endl; }
}

void midOS_hart::exec_cmpi(uint32_t insn)
{
    std::cout << "\ncmpi - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_cmpr(uint32_t insn)
{
    std::cout << "\ncmpr - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_jlt(uint32_t insn)
{
    std::cout << "\njlt - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_jgt(uint32_t insn)
{
    std::cout << "\njgt - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_je(uint32_t insn)
{
    std::cout << "\nje - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_call(uint32_t insn)
{
    std::cout << "\ncall - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_callm(uint32_t insn)
{
    std::cout << "\ncallm - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_ret(uint32_t insn)
{
    std::cout << "\nret - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_alloc(uint32_t insn)
{
    std::cout << "\nalloc - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_acquire_lock(uint32_t insn)
{
    std::cout << "\naquire_lock - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_release_lock(uint32_t insn)
{
    std::cout << "\nrelease_lock - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_sleep(uint32_t insn)
{
    std::cout << "\nsleep - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_set_priority(uint32_t insn)
{
    //std::cout << "\nset_priority - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_exit(uint32_t insn)
{
    std::cout << "\nexit - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_free_memory(uint32_t insn)
{
    std::cout << "\nfree_memory - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_map_shared_mem(uint32_t insn)
{
    std::cout << "\nmap_shared_mem - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_signal_event(uint32_t insn)
{
    std::cout << "\nsignal_event - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_wait_event(uint32_t insn)
{
    std::cout << "\nwait_event - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_input(uint32_t insn)
{
    std::cout << "\ninput - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_memory_clear(uint32_t insn)
{
    std::cout << "\nmemory_clear - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_terminate_process(uint32_t insn)
{
    std::cout << "\nterminate_process - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_popr(uint32_t insn)
{
    std::cout << "\npopr - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}

void midOS_hart::exec_popm(uint32_t insn)
{
    std::cout << "\npopm - work in progress\n";
    regs.set(0, regs.get(0) + 4); //increment ip register by 4
}
