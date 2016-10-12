#include <cstring>
#include <stdio.h>
#include <stdlib.h>

/*There are two options - I'm not sure which one we should pursue, both seem to involve some string manipulation
The program needs to receive argument lists that contain:
PID arrivalTime requiredCPU IOFrequency IODuration
1 - pass a file that has each process as a line in the file, split it by spaces, convert the 'strings' (remember C doesn't have strings) to numbers
2 - pass a whole bunch of command line arguments, only continue if argc % 5 == 0, this still requires converting the strings to numbers

The assignment tends to reference an input file so I guess that's the best way.
*/

typedef struct PCB{
	int PID, ArrivalTime, requiredCPU, IOFrequency, IODuration;
	PCB* next; //for linked list - could make another wrapper struct with just a PCB and a head, may do that later
} PCB;

void taskScheduler(){
	//switch processes
}


int main(int argc, char const *argv[])
{
	PCB* readyListHead, waitingListHead; //newListHead, terminatedListHead; //Aren't needed right now - new goes straight to ready and terminated dies immediately
	/*Start of a line-by-line file read loop*/
	/*Read each processes process control block (PCB) and put it into an array (or linked list) of PCB's.*/
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

	int lastTime; //=get current time
	while(1){
		int curTime;//= get_current_time (can't quite figure out how to do this)
		if (curTime - lastTime > 1000) { //1000uSec = 1 millisecond per process maximum
			lastTime = curTime;
			//put the current process in the ready list then call the taskScheduler
			taskScheduler();
		}
		//if (The process decides to do IO){}
	}
	return 0;
}