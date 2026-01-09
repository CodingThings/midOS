#include "process.h"

process::process(int process_id, uint32_t memory_size){

    PCB = process_control_block(process_id, memory_size);

}

/*

Return value meaining:
1 - process p has higher priority
-1 - process p has lower priority
0 - process p has equal priority

*/
int process::compare(process p){

    if(PCB.priority < p.PCB.priority){
        return 1;
    }
    if(PCB.priority > p.PCB.priority){
        return -1;
    }
    if(PCB.priority == p.PCB.priority){
        if(PCB.clock_cycles < p.PCB.clock_cycles){
            return 1;
        }
        if(PCB.clock_cycles > p.PCB.clock_cycles){
            return -1;
        }
    }
    return 0;

}