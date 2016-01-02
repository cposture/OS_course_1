#include "Process.h"
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
	void insertJob(const PCB &t)
	{
		plist.push_front(t);
	}
	bool hasProcess(void) const
	{
		return (bool)(plist.size()-1);
	}
};

class JobList{
public:
	bool schedule(ProcessList& p,unsigned int time);
	void init(std::istream &in);
	bool hasJob(void) const
	{
		return (bool)(jlist.size()-1);
	}
private:
	std::list<PCB> jlist;
};


bool JobList::schedule(ProcessList &p,unsigned int time)
{
	if(hasJob() == false)
		return false;
	auto min = jlist.begin();
	min++;
	for(auto i = min; i != jlist.end(); ++i)
		if(i->stime < time && i->ntime < min->ntime)
			min = i;
	if(min == jlist.end())
		return false;
	p.insertJob(*min);	
	jlist.erase(min);
	return true;
}

void JobList::init(std::istream &in)
{
	PCB t;
	while(!in.eof())
	{
		in >> *(t.name) >> t.stime >> t.rtime >> t.memory >> t.tape >> t.super;
		jlist.push_front(t);
	}
}

bool ProcessList::schedule(PCB& p)
{
	if(hasProcess() == false)
		return false;
	auto min = plist.begin();
	min++;
	for(auto i = min; i != plist.end(); ++i)
		if(i->state == WAIT && i->super < min->super)
			min = i;
	if(min == plist.end())
		return false;	
	p = *min;		
	return true;
}

void PCB::running(unsigned int time)
{
	rtime++;
	if(rtime == ntime)
	{
		ftime = time;
		turntime = time - stime;
		wtime = (float)(turntime)/ntime;
		state = FINISH;
	}
	else
	{
		state = WAIT;
	}
}


