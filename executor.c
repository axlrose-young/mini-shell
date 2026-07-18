#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "tokenizer.h"

void handle_redir(){
	/*
	 * open the file
	 * duplicate the stdout as per open
	 * close(fd) 	closes the last fd assigned to outfile
	 */	
	int redirect_fd = open(pipe_arr[0].outfile, O_CREAT | O_TRUNC | O_WRONLY);

	if(redirect_fd == -1){
		perror("Error opening file");	
		exit(1);
	}
	dup2(redirect_fd, STDOUT_FILENO);
	close(redirect_fd);	
}

void exec_commands(Pipes* p, size_t ncmds){

	handle_redir();
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
