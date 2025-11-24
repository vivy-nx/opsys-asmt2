#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

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
        if (allocation[i].size() != max.size()) {
            std::cout << "ERROR: Process in [allocation] has wrong number of resources compared to [max]. Please adjust your input file accordingly." << std::endl;
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
    std::vector<std::vector<int>> need; 
    std::vector<int> hasRun; //0 if hasn't run, 1 if has run.
    std::vector<int> safeSequence;
    for (int i = 0; i < allocation.size(); ++i) {
        hasRun.push_back(0); //none have run at first.
    }
    //calculate need
    for (int i = 0; i < allocation.size(); ++i) {
        std::vector<int> process;
        for (int j = 0; j < allocation[i].size(); ++j) {
            process.push_back(max[i][j] - allocation[i][j]);
        }
        need.push_back(process);
    }
    std::cout << std::endl;
    //loop: while processes still need to be added to safe sequence,
    while (safeSequence.size() != allocation.size()) {
        bool hasProgressed = false;
        for (int i = 0; i < allocation.size(); ++i) { // for all processes
            if (hasRun[i] == 0) { //that haven't run, 
                //is this process's [need] less than or equal to [available]
                bool needLesserEqualToAvailable = true;
                for (int j = 0; j < available.size(); ++j) {
                    if (need[i][j] > available[j]) { 
                        needLesserEqualToAvailable = false;
                        break;
                    }
                }
                if (needLesserEqualToAvailable) { 
                    hasRun[i] = 1;
                    hasProgressed = true;
                    safeSequence.push_back(i+1);
                    //and then return its [allocation] to [available].
                    for (int j = 0; j < available.size(); ++j) {
                        available[j] += allocation[i][j];
                    }
                }
            }
        }
        if (hasProgressed == false) { //if iterated over all processes and found no legal next steps then state is unsafe; abort
            if (safeSequence.size() == 0) {
                std::cout << "UNSAFE STATE: Could not find any valid candidates for safe sequence at all." << std::endl;
            } 
            else {
                std::cout << "UNSAFE STATE: Could not find any valid candidates for safe sequence from this point forward." << std::endl;
                std::cout << "Incomplete process sequence: ";
                for (int i = 0; i < safeSequence.size(); ++i) {
                    std::cout << safeSequence[i] << " ";
                }
                std::cout << std::endl;
            }
            exit(0); 
        }
    }
    //if exited this while loop, then hasRun has entries for all 
    std::cout << "SAFE STATE: A safe sequence containing all processes was found!" << std::endl;
    std::cout << "Safe sequence: ";
    for (int i = 0; i < safeSequence.size(); ++i) {
        std::cout << safeSequence[i] << ' ';
    }
    std::cout << std::endl;
}