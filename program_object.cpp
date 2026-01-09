
#include "program_object.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


//count lines of infile
uint32_t program_object::get_file_size(const string &fname) 
{
	std::ifstream infile(fname);

    if(infile.fail())
    {
        std::cerr << "Can't open file '" << fname << "' for reading." << std::endl;
    }
    
    uint32_t count = 0;
    string line;
    while (std::getline(infile, line)) { ++count; }
    
    return count * 4;

}


void program_object::dump() const
{   
    for(unsigned int i = 0; i < program.size(); i++)
    {       
        if (i % 4 == 0 && i != 0) { cout << endl; }
        cout << std::hex << setfill('0') << setw(2) << static_cast<uint16_t>(program[i]);
        
    }
    cout << endl;
}


//load_file
void program_object::load_file(const string &fname)
{
    std::ifstream infile(fname);

    if(infile.fail())
    {
        std::cerr << "Can't open file '" << fname << "' for reading." << std::endl;
    }
	uint32_t size = get_file_size(fname);
	program.resize(size, 0xa5);
    uint32_t addr = 0;	
    int opCode;
    infile >> opCode;

    while (!infile.eof())
    {
		string param1;
		string param2;
	
		uint8_t param1_8bit;
		uint8_t param2_first_8bit;
		uint8_t param2_second_8bit;
		
		// case for each op Code
		switch (opCode) 
		{
		case 1:	//Incr
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 2:	//Addi
			infile >> param1;
			infile >> param2;
			handle_rv_signed(param1, param2, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 3:	//Addr
			infile >> param1;
			infile >> param2;
			handle_rr(param1, param2, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 4: //Pushr
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 5:	//Pushi
			infile >> param1;
			handle_v(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 6: //Movi
			infile >> param1;
			infile >> param2;
			handle_rv_signed(param1, param2, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 7: //Movr
			infile >> param1;
			infile >> param2;
			handle_rr(param1, param2, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 8: //Movmr
			infile >> param1;
			infile >> param2;
			handle_rr(param1, param2, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 9: //Movrm
			infile >> param1;
			infile >> param2;
			handle_rr(param1, param2, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
    		case 10: //Movmm
			infile >> param1;
			infile >> param2;
			handle_rr(param1, param2, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 11: //Printr
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 12: //Printm
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 13: //Jmp
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 14: //Cmpi
			infile >> param1;
			infile >> param2;
			handle_rv_signed(param1, param2, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 15: //Cmpr
			infile >> param1;
			infile >> param2;
			handle_rr(param1, param2, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 16: //Jlt
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 17: //Jgt
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 18: //Je
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 19: //Call
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 20: //Callm
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 21: //Ret
			handle_none(param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
    		case 22: //Alloc
			infile >> param1;
			infile >> param2;
			handle_rr(param1, param2, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 23: //AcquireLock
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 24: //ReleaseLock
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 25: //Sleep
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 26: //SetPriority
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 27: //Exit
			handle_none(param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 28: //FreeMemory
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 29: //MapSharedMemory
			infile >> param1;
			infile >> param2;
			handle_rr(param1, param2, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 30: //SignalEvent
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 31: //WaitEvent
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 32: //Input
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 33: //MemoryClear
			infile >> param1;
			infile >> param2;
			handle_rr(param1, param2, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 34: //TerminateProcess
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;	
		case 35: //Popr
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		case 36: //popm
			infile >> param1;
			handle_r(param1, param1_8bit, param2_first_8bit, param2_second_8bit);
			break;
		}

		// enter 8bit values into memory
		set8_nc(addr, opCode);
		addr += 1;
		set8_nc(addr, param1_8bit);
		addr += 1;
		set8_nc(addr, param2_first_8bit);
		addr += 1;
		set8_nc(addr, param2_second_8bit);
		addr += 1;
		
		// read next opCode
		infile >> opCode;

    }

    infile.close();

}

uint8_t program_object::get8(uint32_t addr)
{
		return program[addr];
}
/*
uint16_t program_object::get16(uint32_t addr)
{
		return (static_cast<uint16_t>(get8(addr)) | static_cast<uint16_t>(get8(addr+1)));
}

uint32_t program_object::get32(uint32_t addr)
{
		return (static_cast<uint32_t>(get16(addr)) | static_cast<uint32_t>(get16(addr+2)));
}
*/
// set a byte of memory
void program_object::set8_nc(uint32_t addr, uint8_t value) {
	program[addr] = value;
	return;
}

// render instruction containing 1 register parameter
void program_object::handle_r(string r, uint8_t &p1_8bit,
	uint8_t &p2_first_8bit, uint8_t &p2_second_8bit) 
{
	trim_r(r);
	uint p1_uint;			
	p1_uint = stoi(r);
	
	//check int size ( < 256 unsigned)
	if (p1_uint < 11) {
		p1_8bit = p1_uint;
	}
	
	//set unused parameter to 0
	p2_first_8bit = 0;
	p2_second_8bit = 0;
}

// render instruction containing 2 register parameters
void program_object::handle_rr(string r, string v, uint8_t &p1_8bit,
	uint8_t &p2_first_8bit, uint8_t &p2_second_8bit) 
{
	//trim 'r' and ',' from string
	trim_r(r);
	trim_comma(r);
	
	uint p1_uint;			
	p1_uint = stoi(r);
				
	//check int size ( < 256 unsigned)
	if (p1_uint < 256) {
		p1_8bit = p1_uint;
	}
				
	//trim 'r' from string
	trim_r(v);
	uint p2_uint;		
	p2_uint = stoi(v);
	
	uint16_t p2_16bit;
	p2_16bit = p2_uint;
				
	if (p2_uint < 11) {
		p2_first_8bit = 0;
		p2_second_8bit = (p2_16bit & 0x000f);
	}
}

// render instruction containing: 1 register parameter,
//				  1 signed value
void program_object::handle_rv_signed(string r, string v, uint8_t &p1_8bit,
		uint8_t &p2_first_8bit, uint8_t &p2_second_8bit) 
{

	//trim 'r' and ',' from r string
	trim_r(r);
	trim_comma(r);
	
	//convert string to int
	uint p1_uint;			
	p1_uint = stoi(r);
				
	//check int size ( < 256 unsigned)
	if (p1_uint < 256) {
		p1_8bit = p1_uint;
	}
				
	//trim '$' from string
	trim_dollar(v);
	
	// convert string to int
	int p2_int;		
	p2_int = stoi(v);
	int16_t p2_16bit;
	p2_16bit = p2_int;
	
	// check size and assign values to parameters			
	if (p2_int < 2048 && p2_int > -2049) {
		p2_first_8bit = (p2_16bit & 0xff00) >> 8;
		p2_second_8bit = (p2_16bit & 0x00ff);
	}
}

// render instruction containing 1 signed value parameter
void program_object::handle_v(string v, uint8_t &p1_8bit,
		uint8_t &p2_first_8bit, uint8_t &p2_second_8bit)
{
	p1_8bit = 0;	//set first parameter value
	
	//trim '$' from string
	trim_dollar(v);
	
	int p2_int;
	p2_int = stoi(v);
	
	int16_t p2_16bit;
	p2_16bit = p2_int;
				
	if (p2_int < 2048 && p2_int > -2049) {
		p2_first_8bit = (p2_16bit & 0xff00) >> 8;
		p2_second_8bit = (p2_16bit & 0x00ff);
	}
}

// render instruction containing no parameters
void program_object::handle_none(uint8_t &p1_8bit, uint8_t &p2_first_8bit, uint8_t &p2_second_8bit)
{
	p1_8bit = 0;
	p2_first_8bit = 0;
	p2_second_8bit = 0;
}



