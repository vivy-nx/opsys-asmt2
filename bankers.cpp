#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "bankers.hpp"


int main(int argc, char *argv[]) {
    //check valid arguments.
    if (argc == 1) {
        std::cout << "ERROR: No filename provided. Try ";
        std::cout << argv[0];
        std::cout << " <filename>" << std::endl;
        exit(0);
    }
    if (argc > 2) {
        std::cout << "ERROR: Too many arguments." << std::endl;
        exit(0);
    }
    std::string inFile = argv[1];
    std::ifstream file;
    file.open(inFile);
    if (!file.is_open()) {
        std::cout << "ERROR: File '" + inFile + "' does not exist." << std::endl;
        exit(0);
    } 
    //create relevant data structures;
    std::vector<int> available; //contains [resources] many items.
    std::vector<std::vector<int>> allocation; //contains [processes] many vectors of [resources] many items.
    std::vector<std::vector<int>> max; //contains [processes] many vectors of [resources] many items.
    //read the file into our variables
    
}