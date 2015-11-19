#include "stdio.h" 
#include <stdlib.h> 
#define getpch(type) (type*)malloc(sizeof(type)) 
struct pcb { 
	char name[10]; 
	char state; 
	int super; 
	int ntime; 
	int rtime; 
	int stime;
	int turntime;
	float wtime;
	float respose;
	int ftime;
	struct pcb* link; 
}*ready=NULL,*finish = NULL,*p; 
typedef struct pcb PCB;   
int timer = 0;
void sort(PCB* &p,PCB* &ready) 
{ 
	PCB *first, *second; 
	int insert=0; 
	if((ready==NULL)||(p->respose>ready->respose) || (p->respose == ready->respose && p->stime < ready->stime))
	{ 
		p->link=ready; 
		ready=p; 
	} 
	else
	{ 
		first=ready; 
		second=first->link; 
		while(second!=NULL) 
		{ 
			if((p->respose)>(second->respose) || (p->respose == second->respose && p->stime < ready->stime)) 
			{ 
				p->link=second; 
				first->link=p; 
				second=NULL; 
				insert=1; 
			} 
			else 
			{ 
				first=first->link; 
				second=second->link; 
			} 
		}	 
		if(insert==0) first->link=p; 
	} 
}
void input()
{ 
	int i,num;
	PCB *last = NULL;

	printf("\n process number: "); 
	scanf("%d",&num); 
	for(i=0;i<num;i++) 
	{ 
		printf("\n process number.%d:",i); 
		p=getpch(PCB); 
		printf("\n process name: "); 
		scanf("%s",p->name); 
		printf(" process submit time: ");
		scanf("%d",&p->stime);
		printf(" process pivot: "); 
		scanf("%d",&p->super); 
		printf(" process needing time: "); 
		scanf("%d",&p->ntime); 
		printf("\n");
		p->turntime = 0;
		p->rtime=0;
		p->wtime = 0;
		p->respose = 0;
		p->state='W'; 
		p->ftime = 0;
		p->link=NULL; 
		sort(p,ready);
	} 
} 

int space() 
{ 
	int l=0; PCB* pr=ready; 
	while(pr!=NULL) 
	{ 
		l++; 
		pr=pr->link; 
	} 
	return(l); 
} 

void disp(PCB * pr)
{ 
	printf("\nqname\tstate\tstime\tftimr\tsuper\tndtime\truntime\tturntime\tweighturntime\trespose\n"); 
	printf("|%s\t",pr->name); 
	printf("|%c\t",pr->state);
	printf("|%d\t",pr->stime);
	printf("|%d\t",pr->ftime);
	printf("|%d\t",pr->super); 
	printf("|%d\t",pr->ntime); 
	printf("|%d\t",pr->rtime);
	printf("|%d\t",pr->turntime);
	printf("\t|%0.01f\t",pr->wtime);
	printf("\t|%0.01f\t",pr->respose);
	printf("\n"); 
} 

void check(PCB *p) 
{ 
	while(p!=NULL) 
	{ 
		disp(p); 
		p=p->link; 
	} 
} 

void destroy()
{ 
	printf("\n process[%s] has finish.\n",p->name);
	p->link = finish;
	finish = p;
	p = NULL;
} 

void running() 
{ 
	(p->rtime)++; 
	if(p->rtime==p->ntime)
	{
		p->ftime = timer;
		p->turntime = timer - p->stime;
		p->wtime = (float)(p->turntime)/p->ntime;
		destroy();
	}
} 
void osschedule()
{
	PCB *temp,*list;

	list = NULL;
	temp = ready;
	while(temp)
	{
		ready = ready->link;
		if(temp->state == 'W' && timer>temp->stime)
			temp->respose = 1 + (timer-temp->stime)/(float)temp->ntime;
		temp->link = NULL;
		sort(temp,list);
		temp = ready;
	}
	ready = list;
	if(p != NULL)
	{
		p->link = ready;
		ready = p;
	}
	check(ready);
	getchar();
	printf("continue...");
}
int main() 
{ 
	int len,h=0; 
	PCB *temp = NULL;
	input(); 
	len=space(); 
	while((len!=0)&&(ready!=NULL)) 
	{ 
		getchar(); 
		timer++;
		printf("\n The execute number:%d \n",timer); 
		p=ready; 
		if(timer < p->stime)
		{
			printf("\n****there is no task to run or excutetime less than the least submittime\n");
			continue;
		}
		printf("\n ****the process list is:\n");
		ready=p->link; 
		p->link=NULL;
		p->state = 'R';
		running(); 
		osschedule();
	} 
	printf("\n\n++++++++++++++++++++++++++++++finish\n");
	check(finish);
	while(finish)
	{
		temp = finish->link;
		free(finish);
		finish = temp;
	}
	getchar();
	
	return 0;
} 

