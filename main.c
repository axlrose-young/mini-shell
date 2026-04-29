#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
	while(true){
		char *buffer = getlogin();
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
		
		//getting sizeof argv[]
		int count = 0;	
		for(int i = 0; argv[i] != NULL; i++){
			count++;
		}

		//getting home dir
		char *home;
		home = getenv("HOME");
		if(home == NULL){
			printf("Could not get home dir\n");
		}

		//cd function
		if(strcmp(argv[0],"cd") == 0){	
			if(count == 1){
				chdir(home);
			}else if(count == 3){
				printf("cd: too many arguments\n");
			}else{
				puts("changing dirs...");
				chdir(argv[1]);
			}
		}
		
		//exit function
		if(strcmp(argv[0],"exit") == 0){
			if(count > 2){
				puts("Too many arguments");
			}else if(count == 2){
				char *end;
				int n = strtol(argv[1],&end, 10);
				if(end == argv[1]){
					puts("Enter integer value");
				}else if(*end != '\0'){
					puts("Enter integer value");
				}else{
					exit(n);
				}
			}else{
				exit(0);
			}
		}


		//forking and executing
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


