# opsys-asmt2
Implementation of the Banker's algorithm for a given input file. Given some system state, determine if there is an order you can run the processes in that avoids deadlock. 
# Compiling
The program can be compiled with `g++ bankers.cpp -o bankers`. Other compilers probably work too.
# Usage
The program requires a plaintext input file that describes the system state and conditions under which to perform the Banker's algorithm.
The first field describes initially allocatable resource instances. 
The second field describes the current resource allocation to our set of processes (the number of which is determined here).
The third field describes the maximum amount that you would need to allocate to the program.
A sample is provided below, and in `sample_input.txt`. 
```
[resources]
3
[processes]
5
[available]
3,2,2
[allocation]
0,1,0
2,0,0
3,0,2
2,2,1
0,0,2
[max]
7,5,3
3,3,2
9,0,2
2,2,2
4,3,3
```

Running `.\bankers <filename>` prints the initial state in the terminal, and then runs the algorithm.
```
(put code snippet to show how it looks later...?)
```
If successful, it shows the path it took to run each process without running out of resources. If unsuccessful, it will show the path it took before running out of resources. 