#ifndef TOKENIZER_H
#define TOKENIZER_H

#define ARG_MAX 256

typedef struct{
	char* cmds[ARG_MAX];
	char* outfile;
	size_t count;
}Pipes;

extern Pipes pipe_arr[64]; /* directly used in tokenizer and main */
extern size_t ncmds;       /* tracks number of entries in pipe_arr */

void tokenize(char *input);

#endif
