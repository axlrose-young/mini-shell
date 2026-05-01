#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtin.h"

void exit_builtin(char **argv, int count);
void cd_builtin(char **argv, int count);

int handle_builtin(char **argv, int count){
	if(strcmp(argv[0],"cd") == 0){
		cd_builtin(argv,count);
		return 0;
	}
	if(strcmp(argv[0],"exit") == 0){
		exit_builtin(argv,count);
		return 0;
	}
	return 1;
}

void cd_builtin(char **argv, int count){
	if(count==1){
		chdir(getenv("HOME"));
	}
	else if(count>2){
		puts("too many arguments");
	}
	else{
		chdir(argv[1]);
	}
}
void exit_builtin(char **argv, int count){
	if(count==1){
		exit(0);	
	}
	else if(count==2){
		char *end;
		long int n = strtol(argv[1],&end,10);
		if(end==argv[1]){
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
