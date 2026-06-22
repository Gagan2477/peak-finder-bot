#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
// ANSI Color Codes for Terminal UI
const string PURPLE = "\033[35m";
const string BOLD_PURPLE = "\033[1;35m";
const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string RESET = "\033[0m";
// Helper function to check if a target minimum height is possible
bool isHeightFeasible(const vector<int>& terrain, int targetHeight, int maxOperations) {
    long long operationsNeeded = 0; // Use long long to prevent integer overflow
    
    for (int height : terrain) {
        if (height < targetHeight) {
            operationsNeeded += (targetHeight - height);
        }
        // If at any point we need more operations than allowed, it's not feasible
        if (operationsNeeded > maxOperations) {
            return false;
        }
    }
    return true;
}
// Core Binary Search Algorithm
int optimizeMountainHeights(const vector<int>& terrain, int maxOperations) {
    int low = 0;
    
    // Find the current maximum height in the terrain to set our upper bound
    int maxCurrentHeight = 0;
    for (int height : terrain) {
        if (height > maxCurrentHeight) {
            maxCurrentHeight = height;
        }
    }
    
    // The highest possible height if we dumped ALL operations on the highest peak
    int high = maxCurrentHeight + maxOperations; 
    int optimalHeight = 0;

    // Binary search loop
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (isHeightFeasible(terrain, mid, maxOperations)) {
            optimalHeight = mid; // This works, save it
            low = mid + 1;       // Try to push for a higher height
        } else {
            high = mid - 1;      // It failed, we must aim lower
        }
    }

    return optimalHeight;
}
int main() {
    // Print the welcome banner
    // Print the styled welcome banner
    cout << BOLD_PURPLE << "==========================================\n";
    cout << "  PeakFinder Optimization Bot Initialized. \n";
    cout << "==========================================\n" << RESET;
    cout << " Commands: HELP, LOAD [data], SET_CONSTRAINT [val], OPTIMIZE, QUIT\n";
    string userInput;
    
    // State variables (Bot's Memory)
    vector<int> terrainData;
    int currentConstraint = -1;

    // The core "chat" loop
    while (true) {
        cout << "\nUser> ";
        getline(cin, userInput);

        // Handle empty inputs
        if (userInput.empty()) continue;

        // Use stringstream to tokenize the input
        stringstream ss(userInput);
        string command;
        ss >> command; // The first word is the command

        // 1. QUIT Command
        if (command == "QUIT" || command == "quit") {
            cout << "Bot: Shutting down systems. Goodbye!\n";
            break; // Breaks the infinite loop
        } 
        
        // 2. HELP Command
        else if (command == "HELP" || command == "help") {
            cout << "Bot: I am an algorithmic optimization assistant.\n";
            cout << "  - Type 'LOAD 10 20 30' to load terrain data.\n";
            cout << "  - Type 'SET_CONSTRAINT 15' to define the max height constraint.\n";
            cout << "  - Type 'OPTIMIZE' to run the binary search algorithm.\n";
            cout << "  - Type 'QUIT' to exit.\n";
        }
        
        // 3. LOAD Command (Parsing an array of integers)
        else if (command == "LOAD" || command == "load") {
            int value;
            terrainData.clear(); // Clear existing memory
            
            // Extract all remaining numbers in the user's string
            while (ss >> value) {
                terrainData.push_back(value);
            }
            
            if (terrainData.empty()) {
                cout << "Bot: Error - You must provide numbers after LOAD (e.g., LOAD 10 25 14).\n";
            } else {
                cout << "Bot: Successfully loaded " << terrainData.size() << " data points into memory.\n";
            }
        }
        
        // 4. SET_CONSTRAINT Command (Parsing a single integer)
        else if (command == "SET_CONSTRAINT" || command == "set_constraint") {
            int value;
            if (ss >> value) {
                currentConstraint = value;
                cout << "Bot: Constraint updated to " << currentConstraint << ".\n";
            } else {
                cout << "Bot: Error - Please provide a numeric value (e.g., SET_CONSTRAINT 50).\n";
            }
        }
        
        // 5. OPTIMIZE Command (Placeholder for Phase 2)
        else if (command == "OPTIMIZE" || command == "optimize") {
            if (terrainData.empty()) {
                cout << RED << "Bot: Error - Terrain data is empty. Please LOAD data first.\n" << RESET;
            } else if (currentConstraint == -1) {
                cout << RED << "Bot: Error - Please SET_CONSTRAINT before optimizing.\n" << RESET;
            } else {
                cout << PURPLE << "Bot: Parameters validated. Running binary search...\n" << RESET;
                
                int result = optimizeMountainHeights(terrainData, currentConstraint);
                
                cout << GREEN << "Bot: --> Optimization complete.\n";
                cout << "Bot: --> The maximum uniform peak height achievable is: " << result << "\n" << RESET;
            }
        }
        
        // Catch-all for unrecognized input
        else {
            cout << "Bot: Command '" << command << "' not recognized. Type HELP for a list of commands.\n";
        }
    }

    return 0;
}