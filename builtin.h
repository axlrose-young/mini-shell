#ifndef BUILTIN_H
#define BUILTIN_H

void exit_builtin(char **argv, int count);
void cd_builtin(char **argv, int count);
int handle_builtin(char **argv, int count);

#endif
