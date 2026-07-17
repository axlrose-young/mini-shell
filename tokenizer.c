#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "tokenizer.h"

Pipes pipeline[64];

void tokenize(char* input){
	// clear the struct so previous values are not retained
	memset(pipeline, 0, sizeof(pipeline)); 
					      
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
			pipeline[i].cmds[cmd_index] = NULL; // NULL terminate current 
			index++;
			cmd_index = 0;
		}
		else if(strcmp(tokens[i], ">")==0){
			pipeline[index].outfile = tokens[i+1];
			i++; // skips the output file token
		}
		else{
			pipeline[index].count++;
			pipeline[index].cmds[cmd_index] = tokens[i];	
			cmd_index++;
		}
	}	
	pipeline[index].cmds[cmd_index] = NULL;

	for(int i = 0; pipeline[i].cmds[0] != NULL; i++){
		printf("Count: %ld\n", pipeline[i].count);
		for(int j = 0; pipeline[i].cmds[j] != NULL; j++){
			printf("pipe %d cmd %d: %s\n",i,j,pipeline[i].cmds[j]);
		}	
		if(pipeline[i].outfile != 0){
			printf("Outfile: %s\n",pipeline[i].outfile);	
		}	
	}
}
