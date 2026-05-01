#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int executor(char *argv[]){
	int pid = fork();
	if(pid == -1){
		perror("forking failed");
		return 1;
	}
	if(pid == 0){	//child process
		int err = execvp(argv[0],argv);
		if(err == -1){
			perror("execution failed");
			exit(1);	//kills child process 
		}
	}else{	        //parent process
		int wstatus;
		wait(&wstatus);
		if(WIFEXITED(wstatus)){
			int statuscode = WEXITSTATUS(wstatus);
			if(statuscode == 0){
				return 0;
			}else{
				return 1;
			}
		}
	}
	return 0;
}
