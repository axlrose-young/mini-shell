## Entry-01: Array passing in c

### What it is: The address of the first value is passed when passing an array to a function in c 

### In-depth:
When we pass an array to a function the first index gets passed to it. It is normal to pass the array and its length hence there is no way for the function to know how long it is.

void example-function(int array, size-t lenth)
example-function(array,length);

Note: array of structs -
when passing an array of struct we essentially pass the first struct's address.

Struct struct-arr[10];

example-function(struct-arr, length)
example-function(Struct* a, size-t length)


## Entry-02: wait() call

### What it is: Is used to report any change in status of child and free up child process's resources.

### In-depth:
Even after a child process's termination wait() has to be called to free up it's resources and to avoid it being in a zombie state.

The parent can wait on the child process later (doesn't have to be called right after it's execution). 
After termination of the child process the kernel maintains some minimal information about the zombie process so a parent can wait on it later on. 

### Usage in the project:
loop:
{ created all process (pipe, fork) and executed }
loop:
// in a loop after all piping is done
// this clears zombie processes 
{ wait() on all child processes } 
