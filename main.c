#define READYLISTSIZE 40
#define WAITINGLISTSIZE 40

#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



/*There are two options - I'm not sure which one we should pursue, both seem to involve some string manipulation
The program needs to receive argument lists that contain:
PID arrivalTime requiredCPU IOFrequency IODuration
1 - pass a file that has each process as a line in the file, split it by spaces, convert the 'strings' (remember C doesn't have strings) to numbers
2 - pass a whole bunch of command line arguments, only continue if argc % 5 == 0, this still requires converting the strings to numbers

The assignment tends to reference an input file so I guess that's the best way.
*/

typedef struct PCB{
	int PID, ArrivalTime, requiredCPUTime, IOFrequency, IODuration;
	// PCB* next; //for linked list - could make another wrapper struct with just a PCB and a head, may do that later
} PCB;

// enum TaskSchedulerJob{  This might be used later
// 	KICK,

// }


// PCB* getLastElement(PCB* list){
// 	for (/*list*/; list->next != NULL; list = list->next); //walk the list until next is null and then return
// 	return list;
// }




/*These are global variables that contain the readyList and waitingList.
These are global so that the taskScheduler can access them easily. They could be passed as references to the taskScheduler, however that involves stacking pointers
which wastes CPU time since nothing is using the CPU while we wait for those parameters to be stacked.
*/
//newListHead, terminatedListHead aren't needed right now - new goes straight to ready and terminated dies immediately
PCB* readyList[READYLISTSIZE]; //this has to be shared
int numberOfProcessesInReadyList = 0; //this has to be shared
PCB* waitingList[WAITINGLISTSIZE]; //this has to be shared
int numberOfProcessesInWaitingList = 0; //this has to be shared

PCB* currentProcess; //this is equivalent to "the processor"

void taskScheduler(/*TaskSchedulerJob t*/){
	if(currentProcess != NULL){ //If there was a process in the processor - this means we're kicking it out, so we have to save it's PCB at the end of the list
		if (numberOfProcessesInReadyList < READYLISTSIZE){ //put the current process at the end of the readyList
			readyList[numberOfProcessesInReadyList++] = currentProcess;
		}
	}//otherwise the process has already put itself at the end of the wait list, we can use the processer as we want
	currentProcess = readyList[0]; //the first thing we always do is dispatch a process to the processor
	 //the process we put in the processor is no longer in the readyList
}

void addToWaitList(PCB* putThisInWaitList){

	int i;
	for (i = 0; waitingList[i] != NULL && i < WAITINGLISTSIZE; ++i);
	if (i == WAITINGLISTSIZE - 1) return; //if the waiting list is full, this process doesn't get to be in the waiting list, it dies (for now, in the future we may do something about it)
	
	waitingList[i] = putThisInWaitList;

	/*DEPRECATED
	//somehow have to wait and then put putThisInWaitList in the readyList after a set period of time. Ideally a fork with shared memory, however that makes things much much much more complicated	
	// if (fork() == 0){
	// 	I'm still struggling to figure out how we're going to do this. sharing the entire waitingListHead linked list is inefficient and very error prone
	// 	The other option is to let the task scheduler handle everything and just expire after a certain timeout. I think there's a way to check if a child died, so that would be a good indicator to put something in the ready list
		
	// }*/
	return;
}

int main(int argc, char const *argv[])
{

	//these inits are done so that we can search the lists and add to the end of them
	for (int i = 0; i < READYLISTSIZE; ++i){
		readyList[i] = NULL;
	}

	for (int i = 0; i < WAITINGLISTSIZE; ++i)
	{
		waitingList[i] = NULL;
	}

	/*Start of a line-by-line file read loop*/
	/*Read each processes process control block (PCB) and put it into an array (or linked list) of PCB's.*/
	/*NOTE - if we have to use shared memory. This should be the only place that malloc or shmget has to be used. No new elements are ever created in the rest of the code, pointers are exchanged between lists.
	Freeing the memory is another story but in theory that only happens once in the task scheduler.*/

	char str[5]; //= However we get a list of parameters (looks like probably files read line by line)
	char* tableEntries[5]; //array of strings
	tableEntries[0] = strtok(str, " "); //split it at the first space
	//convert tableEntries[0] to int

	for (int i = 1; i < 5; ++i){ //split it at subsequent spaces
		tableEntries[i] = strtok(NULL, " ");

		if (tableEntries[i] == NULL){ //they provided less than 5 arguments or something else broke
			printf("Invalid arguments were specified");
			exit(0);
		}
		//convert tableEntries[i] to int

	} //end for

	//put tableentries[] into a specific processes' struct (a process control block). 
	
	/*End of a line-by-line file read loop*/

	struct timespec t;

	long lastTime; //=get current time
	long curTime;
	while(1){ //always
		timespec_get(&t, TIME_UTC);
		curTime = (t.tv_nsec/1000);//= get_current_time in microseconds


		if (curTime - lastTime > 1000) { //1000uSec = 1 millisecond per process maximum
			lastTime = curTime;
			taskScheduler(); //kick it by calling the taskscheduler - it handles kicking the process
		}
		if ((currentProcess->requiredCPU /*- current time*/) % currentProcess->IOFrequency == 0){ //IF it's time to do IO - this will run indefinitely until - currentTime is added
			addToWaitList(currentProcess); //this adds the current process to the wait listand starts counting down it's IO time
			currentProcess=NULL; //there's another existing pointer to this (in the stack frame for IOMachine - to be in waitingList)
			taskScheduler(); //put something new in the processor
		}

		for (int i = 0; (i < WAITINGLISTSIZE) && (waitingList[i] != NULL); ++i) //loop through the waiting list and take away from IOTIME, put back in readylist if applicable
		{
			/* code */
		}

	}
	return 0;
}