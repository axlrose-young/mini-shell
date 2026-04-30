#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtin.h"

int cd_builtin(char *argv[], int count){
	if(strcmp(argv[0], "cd") != 0){
		return 0;
	}
	if(count == 1){
		chdir(getenv("HOME"));
	}else if(count > 2){
		puts("too many arguments");
	}else{
		chdir(argv[1]);
	}
}

int exit_builtin(char *argv[], int count){
	if(strcmp(argv[0],"exit") != 0){
		return 0;
	}
	if(count == 2){
		char *end;
		long int n = strtol(argv[1],&end,10);
		if(end == argv[1]){
			puts("Enter an integer");
		}else if(*end != '\0'){
			puts("Enter an integer");
		}else{
			exit(n);
		}
	}else if(count > 2){
		puts("Too many arguments");
	}else{
		exit(0);	
	}
		
}
