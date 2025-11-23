#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "bankers.hpp"

//these are named badly but were having some conflicts with simpler names so whatever
enum inputMode { inpNull, inpAvail, inpAlloc, inpMax }; 

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
    std::string currentLine;
    inputMode mode = inpNull;
    do {
        std::getline(file, currentLine, '\n');
        //mode set if applicable
        if (currentLine == "[available]") {
            mode = inpAvail;
        }
        if (currentLine == "[allocation]") {
            mode = inpAlloc;
        }
        if (currentLine == "[max]") {
            mode = inpMax;
        }
        else { //if not a modeset, then must be a data line. begin next operation
            std::stringstream ss(currentLine);
            std::vector<int> process;
            std::string token;
            switch (mode)
            {
                case inpAvail:
                    while (std::getline(ss,token,',')) {
                        available.push_back(std::stoi(token));
                    }
                break;
                case inpAlloc:
                    while (std::getline(ss,token,',')) {
                        process.push_back(std::stoi(token));
                    }
                    allocation.push_back(process);
                break;
                case inpMax:
                    while (std::getline(ss,token,',')) {
                        process.push_back(std::stoi(token));
                    }
                    max.push_back(process);
                break;
                case inpNull:
                    std::cout << "ERROR: Invalid formatting. Please format your file similar to the provided sample_input.txt." << std::endl;
                    exit(0);
                break;
            }
        }
        
    } while (file.good() && !file.eof());
    std::cout << "Input read in successfully." << std::endl;
    //print out data
    
    //perform algorithm
}