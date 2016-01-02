#ifndef PROCESS_H
#define PROCESS_H

#include <list>
#include <string>
#include <iostream>
typedef enum{
	WAIT,READY,FINISH
}ProcessState;

class PCB{
public:
	PCB(const std::string &pname = std::string("Unified Name"),int super=0,unsigned int ntime=0
			,unsigned int stime=0,unsigned int tape=0,unsigned int memory=0)
		:super(super),ntime(ntime),stime(stime),tape(tape),memory(memory)
	{
		name = new std::string(pname);
		state = WAIT;
		rtime = 0;
		turntime = 0;
		wtime = 0;
		ftime = 0;
	}
	PCB(const PCB& other)
	{
		name = new std::string(*other.name);
	}
	~PCB()
	{
		delete name;
	}
	void running(unsigned int time);
	std::string *name; 
	char state; 
	int super; 
	unsigned int ntime; 
	unsigned int rtime; 
	unsigned int stime;
	unsigned int turntime;
	float wtime; 
	unsigned int ftime; /* finish time*/
	unsigned int tape; /* the amount of tape that process needs */
	unsigned int memory; /* the amount of memory */
};

class ProcessList{
public:
	std::list<PCB> plist;
	bool schedule(PCB& p);
	void insertJob(const PCB &t);
	bool hasProcess(void) const;
};

class JobList{
public:
	bool schedule(ProcessList& p,unsigned int time);
	void init(std::istream &in);
	bool hasJob(void) const;
private:
	std::list<PCB> jlist;
};

#endif
