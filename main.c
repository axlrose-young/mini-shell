#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "parser.h"
#include "builtin.h"
#include "executor.h"

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
		int count;
		if((count = parse_input(input,argv)) == 0){
			continue;
		}
			
		//builtins
		if(handle_builtin(argv,count)==0){
			continue;
		}

		//forking and executing
		executor(argv);

		free(input);	//getline	
	}
	return 0;	
}
