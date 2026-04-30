#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include "parser.h"
#include "builtin.h"

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
		char *input = NULL;
		size_t n = 0;
		getline(&input,&n,stdin);
		input[strlen(input) - 1] = '\0';
		if(input[0] == '\0'){
			continue;
		}

		//converting to individual commands (array of pointers)
		char *argv[64];
		int count = parse_input(input, argv);
			
		//if builtin then continue otherwise exec
		if(cd_builtin(&argv[0],count)){
			continue;
		}
		if(exit_builtin(&argv[0],count)){
			continue;
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

		free(input);	//getline	
	}
	return 0;	
}
