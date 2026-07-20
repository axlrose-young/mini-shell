#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "tokenizer.h"

void exec_commands(Pipes* p, size_t ncmds){
	pid_t pid = fork();	

	if(pid == -1){
		perror("fork error");	
		return;
	}

	if(pid == 0){
		/* child process */
		execvp(p[0].cmds[0], p[0].cmds);
		/* reaches here only if failes */
		perror("exec failed");
		exit(127);
	}
	else {
		/* parent process */
		wait(NULL);	
	}
}

/*
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
*/
