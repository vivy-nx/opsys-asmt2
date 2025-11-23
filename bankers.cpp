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
        else if (currentLine == "[allocation]") {
            mode = inpAlloc;
        }
        else if (currentLine == "[max]") {
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
    //final validation checks
    if (allocation.size() != max.size()) {
        std::cout << "ERROR: Different processes between [allocation] and [max]. Please adjust your input file accordingly." << std::endl;
        exit(0);
    }
    for (int i = 0; i < allocation.size(); ++i) {
        if (allocation[i].size() != available.size()) {
            std::cout << "ERROR: Different resources between [allocation] and [available]. Please adjust your input file accordingly." << std::endl;
            exit(0);
        }
    }
    for (int i = 0; i < max.size(); ++i) {
        if (allocation[i].size() != available.size()) {
            std::cout << "ERROR: Process in [allocation] has wrong number of resources compared to [available]. Please adjust your input file accordingly." << std::endl;
            exit(0);
        }
    }
    
    std::cout << "Input read in successfully." << std::endl << std::endl;
    //print out data
    std::cout << "INITIAL AVAILABLE RESOURCES: " << std::endl;
    for (int i = 0; i < available.size(); ++i) {
        std::cout << available[i] << ' ';
    }
    std::cout << std::endl << std::endl;

    std::cout << "ALLOCATED RESOURCES: " << std::endl;
    for (int i = 0; i < allocation.size(); ++i) {
        std::cout << "p" << i+1 << ": ";
        for (int j = 0; j < allocation[i].size(); ++j) {
            std::cout << allocation[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "MAX RESOURCE USAGE: " << std::endl;
    for (int i = 0; i < max.size(); ++i) {
        std::cout << "p" << i+1 << ": ";
        for (int j = 0; j < max[i].size(); ++j) {
            std::cout << max[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //perform algorithm
    std::cout << "Running Banker's algorithm on given input..." << std::endl;
}