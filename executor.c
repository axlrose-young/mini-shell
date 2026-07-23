#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "tokenizer.h"

/*
void apply_redir(Pipes* p){
	int fd = open(p[0].outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if(fd < 0){
		perror("file open");
		exit(1);	
	}

	dup2(fd, STDOUT_FILENO);
	close(fd);
}
*/

void exec_commands(Pipes* p, size_t ncmds){
	//if(ncmds == 1){
		
	//}
	//else{
	int old_read;	// var to save old read fd

	for(int i = 0; i < (int)ncmds; i++){
		if(i == 0){ 			// first command 
			int pipefd[2];
			
			if(pipe(pipefd)	== -1){
				perror("pipe error");
				exit(1);	
			}

			pid_t pid = fork();
			if(pid == -1){
				perror("fork error");
				exit(1);	
			}	

			if(pid == 0){
			// child process 	
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[0]);
				close(pipefd[1]);
				
				execvp(p[i].cmds[0], p[i].cmds);
				perror("exec failed");
				exit(1);	
			}
			// parent process

			close(pipefd[1]);
			old_read = pipefd[0];
			wait(NULL);
		}	
		else if(i == (int)(ncmds - 1)){	// last command 
			
			pid_t pid = fork();
			if(pid == -1){
				perror("fork error");
				exit(1);	
			}		

			if(pid == 0){
				dup2(old_read, STDIN_FILENO);	
				close(old_read);

				execvp(p[i].cmds[0], p[i].cmds);
				perror("exec failed");
				exit(1);	
			}
			close(old_read);
			wait(NULL);
		}
		else{				// commands in between 
			int pipefd[2];
			
			if(pipe(pipefd)	== -1){
				perror("pipe error");
				exit(1);	
			}

			pid_t pid = fork();
			if(pid == -1){
				perror("fork error");
				exit(1);	
			}		

			if(pid == 0){
				dup2(old_read, STDIN_FILENO);
				dup2(pipefd[1], STDOUT_FILENO);			
				close(pipefd[0]);
				close(pipefd[1]);
				close(old_read);

				execvp(p[i].cmds[0], p[i].cmds);
				perror("exec failed");
				exit(1);
			}
			close(old_read);	
			close(pipefd[1]);
			old_read = pipefd[0];
			wait(NULL);
		}
	}	
	//}
}
