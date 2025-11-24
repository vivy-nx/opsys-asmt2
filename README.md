# Operating Systems Assignment 2
Implementation of the Banker's algorithm for a given input file. Given some system state, determine if there is an order you can run the processes in that avoids deadlock. 
# Compiling
The program can be compiled with `g++ bankers.cpp -o bankers`. Other compilers probably work too.
# Usage
The program requires a plaintext input file that describes the system state and conditions under which to perform the Banker's algorithm.
The first field describes initially allocatable resource instances. 
The second field describes the current resource allocation to our set of processes (the number of which is determined here).
The third field describes the maximum amount that you would need to allocate to the program.
A sample is provided below, and in `sample_input.txt`. More samples can be found in the `samples` folder. 
```
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
Input read in successfully.

INITIAL AVAILABLE RESOURCES: 
3 2 2 

ALLOCATED RESOURCES: 
p1: 0 1 0 
p2: 2 0 0 
p3: 3 0 2 
p4: 2 2 1 
p5: 0 0 2 

MAX RESOURCE USAGE: 
p1: 7 5 3 
p2: 3 3 2 
p3: 9 0 2 
p4: 2 2 2 
p5: 4 3 3 

Running Banker's algorithm on given input...
```
If successful, it shows the path it took to run each process without running out of resources. If unsuccessful, it will show the path it took before running out of resources. 
```
SAFE STATE: A safe sequence containing all processes was found!
Safe sequence: 4 5 2 3 1 
```
```
UNSAFE STATE: Could not find any valid candidates for safe sequence from this point forward.
Incomplete process sequence: 1 3 
```
