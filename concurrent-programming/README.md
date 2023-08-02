
## Thread Demo and Example

This repository contains two C source code files demonstrating the usage of threads and semaphores. The code showcases multithreading concepts using the `pthread` library in C.

### Files:

1. **thread_demo.c**: This file demonstrates the use of threads and semaphores to manage shared resources between threads. It creates three threads that repeatedly print "Hello" along with the thread index and an integer from 0 to 9. Semaphores ensure synchronized access to the standard output, preventing overlapping of outputs.

2. **thread_example.c**: This file serves as an example of using threads and semaphores with `pthread` library. It contains similar functionality to `thread_demo.c`, showcasing multithreading principles and proper synchronization with semaphores.

### Compilation:

To compile each C file, you can use the following command:

```sh
gcc -pthread -o thread_demo thread_demo.c
gcc -pthread -o thread_example thread_example.c
```

### Usage:

Run the compiled executables to execute the respective programs:

```sh
./thread_demo
./thread_example
```

### Notes:

- Both programs utilize semaphores to synchronize access to shared resources between threads.
- The code demonstrates proper multithreading practices and ensures controlled output with synchronized access to the standard output.
- The programs run indefinitely and can be terminated manually.

