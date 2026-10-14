#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "data.h"

size_t tokenize(char*, struct Pipes*);
void exec_commands(size_t ncmds, struct Pipes*);  

void 
init_shell()
{
	char* login = getenv("USER");
	if (login == NULL)		
		login = "user";

	char dir[PATH_MAX];
	if (getcwd(dir,PATH_MAX) == NULL) {
		perror("Error");
		strcpy(dir,"??");
	}

	printf("%s:%s$ ",login,dir);
}

int 
main()
{
	struct Pipes pipe_arr[64]; 	/* array of structs to store pipe info */
	size_t ncmds = 0; 	    	/* used to store length of array */

	while (true) {		
		init_shell();	

		// getting input
		char *input = NULL;
		size_t n = 0;

		getline(&input,&n,stdin);
		input[strlen(input) - 1] = '\0';

		if (input[0] == '\0')	
			continue;
			
		ncmds = tokenize(input, pipe_arr);

		/* pass the array of structs and length */
		exec_commands(ncmds, pipe_arr); 	

		free(input);	//getline	
	}
	return 0;	
}
