#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

//RETURN 0 IF ERROR

int parse_input(char *input,char* cmd[10][64]){
	char* argv[64];
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

	
	//pipe parser 
	int pos = 0;
	int cmd_pos = 0;
	char* temp[20];
	if(strcmp(argv[0],"|")==0){
		puts("cannot start with pipe");
		return 0;
	}
	for(int i = 0; argv[i] != NULL; i++){
		if(argv[i] == "|"){
			for(int j=0; j < pos; j++){
				cmd[cmd_pos][j] = temp[j];
			}
			cmd[cmd_pos][pos] = NULL;
			cmd_pos++;
			pos = 0;
			memset(temp,'0',sizeof(temp));
		}
		else{
			temp[pos] = argv[i];
			pos++;
		}
	}
	if(pos>0){
		for(int j=0; j<pos; j++){
			cmd[cmd_pos][j] = temp[j];
		}
		cmd[cmd_pos][pos] = NULL;
		cmd_pos++;
	}
	else{
		puts("cannot end in pipe");
		return 0;
	}
	cmd[cmd_pos][0] = NULL;
}

