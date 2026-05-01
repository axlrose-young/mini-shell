#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

extern int errno;

void executor(char *argv[]){
	int pid = fork();
	if(pid == -1){
		perror("Error forking");
	}
	if(pid != 0){
		wait(NULL);
	}else{
		execvp(argv[0],argv);
	}
}
