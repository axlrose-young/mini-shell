#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

int main(){
	while(true){
		char *buffer = getlogin();
		//buffer = getlogin();
		printf("[%s]$ ",buffer);
		//getting input
		char commands[50];
		fgets(commands, sizeof(commands), stdin);
		commands[strlen(commands) - 1] = '\0';
				
		//converting to individual commands (array of pointers)
		int prevchar = 0;
		char *argv[64];
		int index = 0;
		for(int i = 0; commands[i] != '\0'; i++){
			if((commands[i] != ' ' || commands[i] != '\t') && prevchar == 0){
				argv[index] = &commands[i];
				prevchar = 1;
				index++;
			}
			else if(commands[i] == ' '){
				commands[i] = '\0';
				prevchar = 0;
			}
		}
		argv[index] = NULL;
		for(int i = 0; argv[i] != NULL; i++){
			printf("argv[%d] : %s\t",i,argv[i]);
		}
		printf("\n");
		//to execute the commands
		execvp(argv[0],argv);
	}
	
}
