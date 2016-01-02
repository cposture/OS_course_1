#include "Process.h"

bool JobList::schedule(ProcessList &p,unsigned int time)
{
	if(hasJob() == false)
		return false;
	auto min = jlist.begin();
	bool sign = false;
	min++;
	for(auto i = min; i != jlist.end(); ++i)
		if(i->stime <= time && i->ntime <= min->ntime)
		{
			min = i;
			sign = true;
		}
	if(!sign)
		return false;
	p.insertJob(*min);	
	int size = jlist.size();
	jlist.erase(min);
	return true;
}

void JobList::init(std::istream &in)
{
	PCB t;
	while(!in.eof() && !in.bad() && !in.fail())
	{
		in >> *(t.name) >> t.stime >> t.ntime >> t.memory >> t.tape >> t.super;
		jlist.push_front(t);
		if(!(in.eof() && in.bad() && in.fail()))
			break;
	}
}

bool JobList::hasJob(void) const
{
	return (bool)(jlist.size());
}

void ProcessList::insertJob(const PCB &t)
{
	plist.push_front(t);
}

bool ProcessList::hasProcess(void) const
{
	return (bool)(plist.size());
}

bool ProcessList::schedule(PCB& p)
{
	if(hasProcess() == false)
		return false;
	auto min = plist.begin();
	bool sign = false;
	min++;
	for(auto i = min; i != plist.end(); ++i)
		if(i->state == WAIT && i->super <= min->super)
		{
			min = i;
			sign = true;
		}
	if(!sign)
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


