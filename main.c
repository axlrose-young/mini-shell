#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	while(true){
		char *buffer = getlogin();
		//buffer = getlogin();
		printf("[%s]$ ",buffer);
		//getting input
		char commands[50];
		fgets(commands, sizeof(commands), stdin);
		commands[strlen(commands) - 1] = '\0';
				
		//converting to individual commands (array of pointers)
		int prevchar = 0;
		char *argv[64];
		int index = 0;
		for(int i = 0; commands[i] != '\0'; i++){
			if((commands[i] != ' ' || commands[i] != '\t') && prevchar == 0){
				argv[index] = &commands[i];
				prevchar = 1;
				index++;
			}
			else if(commands[i] == ' '){
				commands[i] = '\0';
				prevchar = 0;
			}
		}
		argv[index] = NULL;

		int pid;
		pid = fork();
		if(pid == -1){
			printf("Error forking\n");
		}else if(pid != 0){
			wait(NULL);
		}else{
			execvp(argv[0],argv);
		}

		
	}
	return 0;	
}
