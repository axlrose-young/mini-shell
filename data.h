#ifndef DATA_H
#define DATA_H

#define ARG_MAX 256
#define PATH_MAX 4096

struct Pipes{
	char* cmds[ARG_MAX];
	char* outfile;
	size_t count;
};

#endif
