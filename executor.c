#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "executor.h"

int executor(char* cmd[][64]){
	int cmd_count = 0;
	for(int i=0; cmd[i][0]!=NULL; i++){
		cmd_count++;
	}
	if(cmd_count == 1){
		pid_t pid1;
		pid1 = fork();
		if(pid1 < 0){
			perror("forking failed");
		}
		if(pid1 == 0){
			execvp(cmd[0][0],cmd[0]);
			perror("exec failed");
		}
		waitpid(pid1,NULL,0);
	}
	else{
		int fd[2];
		if(pipe(fd) < 0){
			perror("Pipe failed");
		}
		pid_t pid1, pid2;

		if((pid1 = fork())<0){
			perror("fork failed");
		}
		//first child
		if(pid1 == 0){
			close(fd[0]);
			dup2(fd[1],STDOUT_FILENO);
			close(fd[1]);
			execvp(cmd[0][0],cmd[0]);
			perror("exec failed");
		}

		if((pid2 = fork())<0){
			perror("forking failed");
		}
		//second child
		if(pid2 == 0){
			close(fd[1]);
			dup2(fd[0],STDIN_FILENO);
			close(fd[0]);
			execvp(cmd[1][0],cmd[1]);
			perror("exec failed");
		}
		//parent processes
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1,NULL,0);
		waitpid(pid2,NULL,0);
	}
	return 0;
}
