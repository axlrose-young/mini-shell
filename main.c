#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "executor.h"

#define PATH_MAX 4096

void init_shell(){
	// getting root user 
	char* login = getenv("USER");
	if(login == NULL)	login = "user";

	// get current working dir
	char dir[PATH_MAX];
	if(getcwd(dir,PATH_MAX) == NULL){
		perror("Error");
		strcpy(dir,"??");
	}

	printf("%s:%s$ ",login,dir);
}

int main(){
	while(true){
		init_shell();	

		// getting input
		char *input = NULL;
		size_t n = 0;

		getline(&input,&n,stdin);
		input[strlen(input) - 1] = '\0';

		if(input[0] == '\0')	continue;

		/*
		 * tokenize the input 
		 * array of structs handling pipes 
		 */	
		tokenize(input);
		free(input);	//getline	

		/* pass the array of structs and length */
		exec_commands(pipe_arr, ncmds); 	
	}
	return 0;	
}
