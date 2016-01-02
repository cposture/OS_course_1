#include "Process.h"
#include <iostream>
#include <fstream>
#include "DynamicAllocation.h"

int main(int argc, char const *argv[])
{
	std::fstream f;
	f.open("test.txt");
	if(!f)
		std::cout << "open file fail" << std::endl;;

	JobList job;
	ProcessList process;
	PCB cur_process;
	unsigned int time = 0;
	Tape tape;
	unsigned int tapeNum,memory;
	
	f >> memory >> tapeNum;
	mm_init(memory);
	tape.init(tapeNum);
	job.init(f,&tape);
	while(1)
	{
		job.schedule(process,time);
		if(process.schedule(cur_process))
		{
			cur_process.running(process,time);
			std::cout << time << " : "  << *cur_process.name << " :running" << std::endl;
		}
		else
		{
			char c;
			std::cout << "no running" << std::endl;
			std::cin >> c;
			return 0;
		}
		time++;
	}
	f.close();
	return 0;
}
