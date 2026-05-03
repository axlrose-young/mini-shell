#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtin.h"
/*
void exit_builtin(char **argv, int count);
void cd_builtin(char **argv, int count);

int handle_builtin(char* cmd[], int count){
	if(strcmp(cmd[0][0],"cd") == 0){
		cd_builtin(argv[0],count);
		return 0;
	}
	if(strcmp(argv[0][0],"exit") == 0){
		exit_builtin(argv[0],count);
		return 0;
	}
	return 1;
}

void cd_builtin(char* argv[], int count){
	if(count==1){
		chdir(getenv("HOME"));
	}
	else if(count>2){
		puts("too many arguments");
	}
	else{
		chdir(argv[0][1]);
	}
}
void exit_builtin(char* argv[], int count){
	if(count==1){
		exit(0);	
	}
	else if(count==2){
		char *end;
		long int n = strtol(argv[0][1],&end,10);
		if(end==argv[0][1]){
			puts("enter an integer");
		}
		else if(*end!='\0'){
			puts("enter an integer");
		}
		else{
			exit(n);
		}
	}
	else{
		puts("too many arguments");
	}
}
int main(){
	char* cmd[10][64] = {
		{"ex","/etc"},
		{NULL}
	};
	int cmd_count = 1;
	if(cmd_count == 1){
		if(handle_builtin(cmd) == 0){
			puts("skip to next loop");
		}
	}
}
*/
int handle_builtin(char* cmd[][64]){
	int count = 0;
	for(int i = 0; cmd[0][i] != NULL; i++){
		count++;
	}
	if(strcmp(cmd[0][0],"cd") == 0){
		if(count==1){
			chdir(getenv("HOME"));
		}
		else if(count>2){
			puts("too many arguments");
		}
		else{
			chdir(cmd[0][1]);
		}
		return 0;
	}
	else if(strcmp(cmd[0][0],"exit")==0){
		if(count==1){
			exit(0);	
		}
		else if(count==2){
			char *end;
			long int n = strtol(cmd[0][1],&end,10);
			if(end==cmd[0][1]){
				puts("enter an integer");
			}
			else if(*end!='\0'){
				puts("enter an integer");
			}
			else{
				exit(n);
			}
		}
		else{
			puts("too many arguments");
		}
		return 0;
	}
	return 1;
}
