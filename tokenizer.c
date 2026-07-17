#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define ARG_MAX 256

typedef struct{
	char* cmds[ARG_MAX];
}Pipes;

Pipes pipe[64] = { 0 };

void tokenize(char* input){
	// tokenize input based on whitespace
	char* tokens[ARG_MAX]; 
	tokens[0]= strtok(input, " ");		
	int index = 0;
	while(tokens[index] != NULL){
		tokens[++index] = strtok(NULL, " ");	
	}
	tokens[index] = NULL;

	// convert it into arrays of struct for multiple pipes
	index = 0;
	int cmd_index = 0;
	for(int i = 0; tokens[i] != NULL; i++){
		if(strcmp(tokens[i],"|")==0){
			index++;
			cmd_index = 0;
		}
		else{
			pipe[index].cmds[cmd_index] = tokens[i];	
			cmd_index++;
		}
	}	
	pipe[index].cmds[cmd_index] = NULL;

	for(int i = 0; pipe[i].cmds[0] != NULL; i++){
		for(int j = 0; pipe[i].cmds[j] != NULL; j++){
			printf("pipe %d: %s\n",i,pipe[i].cmds[j]);
		}	
	}
}




/*
int parse_input(char *input, char *argv[]){
	int index = 0;
	bool inword = false;
	bool inquotes = false;
	for(int i = 0; input[i] != '\0'; i++){
		if(input[i] == '"'){
			if(inquotes == false){	//starting quotes
				argv[index] = &input[i+1];
				inquotes = true;
				index++;
			}else{	//ending quotes
				input[i] = '\0';
					inquotes = false;
			}
		}else if(inquotes){
			continue;
		}else if(!isspace(input[i])){
			if(inword == false){
				argv[index] = &input[i];
				inword = true;
				index++;
			}
		}else if(isspace(input[i])){
			if(inword){
				inword = false;
				input[i] = '\0';
			}
		}
	}
	argv[index] = NULL;
	if(argv[0] == NULL){
		return 0;
	}
	
	return index; //returns count of argv
}
*/
