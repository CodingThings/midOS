#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <bitset>
#include <vector>

class process_control_block{

    private:
        int pid = 0;

    public:

        enum process_state{

            new_process = 0,
            ready,
            running,
            waiting_asleep,
            waiting_on_lock,
            waiting_on_event,
            terminated

        };

        int page_faults = 0;
        int context_switches = 0;
        int clock_cycles = 0;
        int time_quantum = 10;
        int priority = 1;
        uint32_t code_size = 0;
        uint32_t max_stack_size = 0;
        uint32_t data_size = 512;
        uint32_t heap_start = 0;
        uint32_t heap_end = 0;
        uint32_t process_memory_size = 0;
        uint32_t waiting_lock = 0;
        uint32_t waiting_event = 0;
        uint32_t sleep_counter = 0;
        process_state state = new_process;

        //[0] - sign flag  [1] - zero flag
        std::bitset<2> bit_flag_registers;
        uint32_t registers[11];

        process_control_block(){
            pid = 0;
            registers[8] = (uint32_t)0;
            process_memory_size = 0;
        }

        process_control_block(int id, uint32_t memory_size){
            pid = id;
            registers[8] = (uint32_t)pid;
            process_memory_size = memory_size;
        }        

        void set_sp(uint32_t x){
            registers[10] = x;
        }

        uint32_t get_sp(){
            return registers[10];
        }

        void set_ip(uint32_t x){
            registers[0] = x;
        }

        uint32_t get_ip(){
            return registers[0];
        }

        void set_sf(bool x){
            bit_flag_registers[0] = x;
        }

        bool get_sf(){
            return bit_flag_registers[0];
        }

        void set_zf(bool x){
            bit_flag_registers[1] = x;
        }

        bool get_zf(){
            return bit_flag_registers[1];
        }

        int get_pid(){
            return pid;
        }

 };

class process{

    public:
        process_control_block PCB;
        process(int process_id, uint32_t memory_size);

        int compare(process p);

};

#endif