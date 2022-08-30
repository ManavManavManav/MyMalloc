Introduction
    For this assignment, we implemented our own versions fo the stdlib malloc() and free() methods.

    Project Structure:
        |->README.txt(this file)
        |->mymalloc.h(containing the functions and macros)
        |->mymalloc.c(main implementation of malloc)
        |->memgrind.c(testing program to check the implementation)
        `->Makefile

Implementation
  A char memory block of 4096 bytes is created, then a struct linked list of metadata. The metadata has a previous and next pointer, and 2 properties, open or closed and size.
  The metadata node root is created, and if its the first use of malloc, the root is initialized before using the malloc functions.
  Then depending on the status of the memory block, the chunks are createed at the first available slot, otherwise an error is reported.
  For free method we first check if the pointer is not NULL. Then we check if the address p is out of memor. Then we intialize 
  the root to first address of the memory. Checks if root is NULL and if the memory is allocated then handles the coalescing. 
  
Test Plan

(a) What properties your library must have for you to consider it correct
  *coalescing should function properly
  *all available memory should be available without any phantom chunks
(b) How you intend to check that your code has these properties
  *allocate 3 chunks and remove the middle one, then test
  *allocate all available memory minus metadata
(c) The specific method(s) you will use to check each property
  *Test4: malloc 3 pointers 1000bytes each, then freeing 1st 3rd and 2nd, then mallocing the newly available free chunks
  *Test5: a 2d array of pointers that utilizes all available memory and frees the array after

Testing

    Test1: Expected time=1-3 microseconds (ilab)
        malloc() and immediately free() a 1-byte chunk, 120 times.
    Test2: Expected time=30-35 microseconds (ilab)
        Use malloc() to get 120 1-byte chunks, storing the pointers in an array, then use free() to deallocate the chunks.
    Test3: Expected time=8-11 microseconds (ilab)
        Randomly choose between
            •Allocating a 1-byte chunk and storing the pointer in an array
            •Deallocating one of the chunks in the array (if any)
        Repeat until you have called malloc() 120 times, then free all remaining allocated chunks.
    Test4: Expected time=9-12 microseconds (ilab)
        A struct of maxiumum available size malloced and freed 120 times, then additional minor tests for coalescing
    Test5: Expected time=1-3 microseconds (ilab)
        A 2d array of chars 26*120 size
    
    
    What a great day. After viewing this bit of code, what a great day. 
