#include "Process.h"
#include <iostream>
#include <fstream>

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

	job.init(f);
	while(1)
	{
		job.schedule(process,time);
		if(process.schedule(cur_process))
		{
			cur_process.running(time);
			std::cout << "running" << std::endl;
		}
		else
		{
			std::cout << "no running" << std::endl;
		}
		time++;
	}
	f.close();
	return 0;
}
