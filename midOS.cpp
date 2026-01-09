#include "midOS.h"
//#include "program_object.h"
//#include "program_object.cpp"
#include <ctime>

memory mem(memory_limit);
midOS_hart cpu(mem);

midOS::midOS(int argc, char **argv)
{
    this->argc = argc;
    this->argv = argv;
    
    memory_limit = stoi(argv[1]);
    
    for (int i = 2; i < argc; i++)
    {
		program_object p; 
		p.load_file(argv[i]);
		program_vector.push_back(p);
		process proc = process(pidCounter, memory_limit);
		if(argv[i] == "idle.txt" || argv[i] == "idle2.txt"){
			proc.PCB.time_quantum = 5;
		}
		process_vector.push_back(proc);
		pidCounter++;
	}

}

void midOS::load_program(memory &mem, program_object program, uint32_t addr)
{
	uint32_t prog_addr = 0;
	for (uint i = addr; i < program.get_size(); i++)
	{
		mem.set8(i, program.get8(prog_addr));
		prog_addr++;
	}
}

void sleep(float seconds){
	clock_t startClock = clock();
	float secondsAhead = seconds * CLOCKS_PER_SEC;
	while(clock() < startClock + secondsAhead);
	return;
}

void load_cpu_state(){

}

void save_cpu_state(){
	for(int i = 0; i < 10; i++){
		
	}
}

void midOS::start()
{
    //if (optind >= argc)
	//	usage();
    
    memory mem(memory_limit);

    //if (!mem.load_file(argv[optind], 0))
	//	usage();

    //cpu_single_hart cpu(mem);
	midOS_hart cpu(mem);

    cpu.set_show_registers(show_registers);

	//Executing idle process
	//load_program(mem, program_vector[process_vector[0].PCB.get_pid() - 1], 0);
	mem.dump();

	while(true){
		if(!process_vector.empty()){

			for(process p : process_vector){
				switch(p.PCB.state){
					case process_control_block::process_state::terminated:
						break;
					case process_control_block::process_state::waiting_asleep:
						break;
					case process_control_block::process_state::waiting_on_event:
						break;
					case process_control_block::process_state::waiting_on_lock:
						break;
					case process_control_block::process_state::new_process:
					case process_control_block::process_state::ready:
						p.PCB.state = process_control_block::process_state::running;
						load_program(mem, program_vector[p.PCB.get_pid()], 0);
						//sleep(0.01);
						cpu.tick();
						p.PCB.clock_cycles++;
						if(p.PCB.clock_cycles%p.PCB.time_quantum == 0){
							p.PCB.sleep_counter =
						}
				}
			}



			//load_program(mem, program_vector[process_vector[0].PCB.get_pid() - 1], 0);
			//cpu.tick();
			//process_vector[0].PCB.clock_cycles++;
		}
	}



	  
	//cpu.run();
	
	cpu.dump("");

	if (final_dump)
	{
		cpu.dump("");
		mem.dump();
	}
}
