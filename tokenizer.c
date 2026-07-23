#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "tokenizer.h"

void show_tokens(Pipes* p, size_t ncmds){
	for(int i = 0; p[i].cmds[0] != NULL; i++){
		printf("Count: %ld\n", p[i].count);
		for(int j = 0; p[i].cmds[j] != NULL; j++){
			printf("pipe %d cmd %d: %s\n",i,j,p[i].cmds[j]);
		}	
		if(p[i].outfile != 0){
			printf("Outfile: %s\n",p[i].outfile);	
		}	
	}
	printf("ncmds: %ld\n",ncmds);
}

size_t tokenize(char* input, Pipes* p){
	// clear the struct so previous values are not retained
	memset(p, 0, sizeof(*p)); 
					      
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
			p[index].cmds[cmd_index] = NULL; // NULL terminate current 
			index++;
			cmd_index = 0;
		}
		else if(strcmp(tokens[i], ">")==0){
			p[index].outfile = tokens[i+1];
			i++; // skips the output file token
		}
		else{
			p[index].count++; // counts number of tokens per pipe
			p[index].cmds[cmd_index] = tokens[i];	
			cmd_index++;
		}
	}	
	p[index].cmds[cmd_index] = NULL;

	/* To count number of commands given */
	size_t ncmds = index + 1;

	/* uncomment line to print the tokenized o/p */
	//show_tokens(p, ncmds); 


	return ncmds;
}
