## Entry-01: Array passing in c

### What it is: The address of the first value is passed when passing an array to a function in c 

### In-depth:
When we pass an array to a function the first index gets passed to it. It is normal to pass the array and its length hence there is no way for the function to know how long it is.

void example_function(int array, size_t lenth)

example_function(array,length);

A caveat: array of structs -
when passing an array of struct we essentially pass the first structs address.

Struct struct_arr[10];

example_function(Struct* a, size_t length)

example_function(struct_arr, length)
