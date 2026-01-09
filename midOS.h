#ifndef MIDOS_H
#define MIDOS_H

#include <iostream>
#include <sstream>
#include <getopt.h>
#include "memory.h"
#include "registerfile.h"
#include "midOS_hart.h"
//#include "cpu_single_hart.h"
#include "program_object.h"
#include "process.h"

class midOS
{
public:
    /**
    * @brief prints an appropriate “Usage” error message and “Pattern” to
    *	stderr and terminates the program in the traditional manner
    * 
    */
    static void usage()
    {
	    cerr << "Usage: midOS [-r] [-z] [-l exec-limit] [-m hex-mem-size] infile" << endl;
	    cerr << "    -l maximum number of instructions to exec" << endl;
	    cerr << "    -m specify memory size (default = 0x100)" << endl;
	    cerr << "    -r show register printing during execution" << endl;
	    cerr << "    -z show a dump of the regs & memory after simulation" << endl;
	    exit(1);
    }

    midOS(int argc, char **argv);
    
    void load_program(memory &mem, program_object program, uint32_t addr);

    void start();

    bool check_current_process();

    uint pidCounter = 0;
    process current_process;

private:
    void save_cpu_state();
    void load_cpu_state();

    bool show_registers = false;
	bool final_dump = false;
	uint32_t memory_limit = 0x100;	// default memory size is 0x100
	//uint64_t exec_limit = 0;
	vector<program_object> program_vector;
    vector<process> process_vector;

    char **argv;
    int argc;
};

#endif
