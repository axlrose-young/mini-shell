#include <ctype.h>
#include <stdio.h>
#include "parser.h"

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
