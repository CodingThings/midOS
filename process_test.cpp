#include <iostream>
#include <iomanip>
#include "process.h"

int main(){

    process a = process(1, 1000);
    process b = process(2, 1000);

    std::cout << "Process a id: " << a.PCB.get_pid() << std::endl;
    std::cout << "Process a new process state: " << a.PCB.state << std::endl;
    a.PCB.state = process_control_block::process_state::ready;
    std::cout << "Process a ready state: " << a.PCB.state << std::endl;
    std::cout << "Process a memory size: " << a.PCB.process_memory_size << std::endl;
    a.PCB.process_memory_size = 1000;
    std::cout << "Process a updated memory size: " << a.PCB.process_memory_size << std::endl;
    std::cout << "Process a priority: " << a.PCB.priority << std::endl;
    a.PCB.priority = 2;
    std::cout << "Process a updated priority: " << a.PCB.priority << std::endl;

    std::cout << "Process a priority compared to process b lower priority: " << a.compare(b) << std::endl;
    b.PCB.priority = 3;
    std::cout << "Process a priority compared to process b higher priority: " << a.compare(b) << std::endl;
    b.PCB.priority = 2;
    std::cout << "Process a priority compared to process b equal priority: " << a.compare(b) << std::endl;

    a.PCB.set_ip(5);
    a.PCB.set_sp(10);
    a.PCB.set_sf(true);
    a.PCB.set_zf(true);

    std::cout << "Process a instruction pointer register: " << a.PCB.get_ip() << std::endl;
    std::cout << "Process a stack pointer register: " << a.PCB.get_sp() << std::endl;
    std::cout << "Process a sign flag register: " << a.PCB.get_sf() << std::endl;
    std::cout << "Process a zero flag register: " << a.PCB.get_zf() << std::endl;


    return 0;

}