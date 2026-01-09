CXXFLAGS = -ansi -pedantic -Werror -std=c++14

midOS: main.o memory.o registerfile.o midOS_hart.o midOS.o program_object.o process.o
		g++ $(CXXFLAGS) -o midOS main.o memory.o registerfile.o midOS_hart.o midOS.o program_object.o process.o

main.o: main.cpp 
		g++ $(CXXFLAGS) -c -o main.o main.cpp

memory.o: memory.cpp
		g++ $(CXXFLAGS) -c -o memory.o memory.cpp

registerfile.o: registerfile.cpp
		g++ $(CXXFLAGS) -c -o registerfile.o registerfile.cpp

midOS_hart.o: midOS_hart.cpp
		g++ $(CXXFLAGS) -c -o midOS_hart.o midOS_hart.cpp

midOS.o: midOS.cpp
		g++ $(CXXFLAGS) -c -o midOS.o midOS.cpp

program_object.o: program_object.cpp
		g++ $(CXXFLAGS) -c -o program_object.o program_object.cpp

process.o: process.cpp
		g++ $(CXXFLAGS) -c -o process.o process.cpp
		
clean:
		rm -f *.o midOS
