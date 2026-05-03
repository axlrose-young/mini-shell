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
		char* cmd[10][64] = { 0 };
		if(parse_input(input,cmd) == 0){
			continue;
		}
			
		//builtins
		int cmd_count = 0;
		for(int i = 0; cmd[i][0] != NULL; i++){
			cmd_count++;
		}
		if(cmd_count == 1){
			if(handle_builtin(cmd)==0){
				continue;
			}
		}

		//forking and executing
		executor(cmd);

		free(input);	//getline	
	}
	return 0;	
}
