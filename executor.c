#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "tokenizer.h"

void apply_redir(Pipes* p){
	int fd = open(p[0].outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if(fd < 0){
		perror("file open");
		exit(1);	
	}

	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void exec_commands(Pipes* p, size_t ncmds){
	pid_t pid = fork();	

	if(pid == -1){
		perror("fork error");	
		return;
	}

	if(pid == 0){
		/* should apply redir after fork 
		   That way parent shell's fds don't change */

		if(p[0].outfile != 0){
			apply_redir(p); 		
		}
		
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
