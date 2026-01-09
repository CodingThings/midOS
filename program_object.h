
#ifndef PROGRAM_OBJECT_H
#define PROGRAM_OBJECT_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class program_object
{
public:
    //constructor
    program_object() { }

    // trim all 'r' from string
    static inline void trim_r(std::string &s) {
        s.erase(remove(s.begin(), s.end(), 'r'), s.end());
    }

    // trim all ',' from string
    static inline void trim_comma(std::string &s) {
        s.erase(remove(s.begin(), s.end(), ','), s.end());
    }

    // trim all '$' from string
    static inline void trim_dollar(std::string &s) {
        s.erase(remove(s.begin(), s.end(), '$'), s.end());
    }
    
    void dump() const; //dump for testing
    
    uint32_t get_file_size(const string &fname);
	
	void load_file(const string &fname);
	
	uint get_size() { return program.size(); }
	
	uint8_t get8(uint32_t addr);
	//uint16_t get16(uint32_t addr);
	//uint32_t get32(uint32_t addr);
	
    // render instruction from input containing 1 register
    void handle_r(string r, uint8_t &p1_8bit,
		uint8_t &p2_first_8bit, uint8_t &p2_second_8bit);
    
    // render instruction from input containing 1 register and 1 value	
    void handle_rv_signed(string r, string v, uint8_t &p1_8bit,
		uint8_t &p2_first_8bit, uint8_t &p2_second_8bit);
	
    // render instruction from input containing 2 registers
    void handle_rr(string r, string v, uint8_t &p1_8bit,
		uint8_t &p2_first_8bit, uint8_t &p2_second_8bit);

    // render instruction from input containing 1 value
    void handle_v(string v, uint8_t &p1_8bit,
		uint8_t &p2_first_8bit, uint8_t &p2_second_8bit);
    
    // render instruction from input containing no parameters
    void handle_none(uint8_t &p1_8bit, uint8_t &p2_first_8bit, 
		uint8_t &p2_second_8bit);

    void set8_nc(uint32_t addr, uint8_t value);


    //get program
private:
    vector<uint8_t> program; 	//program file

};

#endif

