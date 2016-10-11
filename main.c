#include <cstring>

/*There are two options - I'm not sure which one we should pursue, both seem to involve some string manipulation
The program needs to receive argument lists that contain:
PID ArrivalTime RequiredCPU IOFrequency IODuration
1 - pass a file that has each process as a line in the file, split it by spaces, convert the 'strings' (remember C doesn't have strings) to numbers
2 - pass a whole bunch of command line arguments, only continue if argc % 5 == 0, this still requires converting the strings to numbers

The assignment tends to reference an input file so I guess that's the best way.
*/
int main(int argc, char const *argv[])
{

	/*Start of a line-by-line file read loop*/
	char str[] //= However we get a list of parameters (looks like probably files read line by line)
	char* tableEntries[5]; //array of strings
	tableEntries[0] = strtok(str, " ") //split it at the first space
	for (int i = 1; i < 5; ++i){ //split it at subsequent spaces
		tableEntries[i] = strtok(NULL, " ");

		if (tableEntries[1] == NULL){ //they provided less than 5 arguments or something else broke
			printf("Invalid arguments were specified");
			exit(0);
		}

	} //end for

	//put tableentries[] into a specific processes' struct (a process control block). 
	
	/*End of a line-by-line file read loop*/


	while(1){
		/*dank memes and stuff*/
	}
	return 0;
}