#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

extern int errno;

int main(){
	while(true){
		//getting username
		char *login = getenv("USER");
		if(login == NULL){
			login = "unkown";
		}

		//getting cwd
		char dir[256];
		if(getcwd(dir,sizeof(dir)) == NULL){
			perror("Error");
			strcpy(dir,"??");
		}
		
		//printing PS1
		printf("[%s %s]$ ",login,dir);

		//getting input
		char *commands = NULL;
		size_t n = 0;
		getline(&commands,&n,stdin);
		commands[strlen(commands) - 1] = '\0';
		if(commands[0] == '\0'){
			continue;
		}

		//converting to individual commands (array of pointers)
		char *argv[64];
		int index = 0;
		bool inword = false;
		bool inquotes = false;
		for(int i = 0; commands[i] != '\0'; i++){
			if(commands[i] == '"'){
				if(inquotes == false){	//starting quotes
					argv[index] = &commands[i+1];
					inquotes = true;
					index++;
				}else{	//ending quotes
					commands[i] = '\0';
						inquotes = false;
				}
			}else if(inquotes){
				continue;
			}else if(!isspace(commands[i])){
				if(inword == false){
					argv[index] = &commands[i];
					inword = true;
					index++;
				}
			}else if(isspace(commands[i])){
				if(inword){
					inword = false;
					commands[i] = '\0';
				}
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
			puts("Could not get home directory");
			strcpy(home,"/");
		}

		//cd function
		if(strcmp(argv[0],"cd") == 0){	
			if(count == 1){
				chdir(home);
			}else if(count == 3){
				puts("cd: too many arguments");
			}else{
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
			perror("Error");
			continue;
		}else if(pid != 0){
			wait(NULL);
		}else{
			execvp(argv[0],argv);
		}

		free(commands);	//getline	
	}
	return 0;	
}
