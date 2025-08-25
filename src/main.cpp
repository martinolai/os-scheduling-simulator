#include <iostream>
#include "Process.h"
using namespace std;

// ========================================================================================
// DEMONSTRATION AND TESTING FUNCTIONS
// ========================================================================================

/**
 * Demonstrate Scheduling Algorithms
 * 
 * Creates a set of sample processes and runs them through all
 * implemented scheduling algorithms for comparison.
 * Displays execution traces and performance statistics.
 */
void demonstrateScheduling() {
    // Create sample processes with varied characteristics
    // Process parameters: (name, arrival_time, burst_time, priority)
    vector<shared_ptr<Process>> sampleProcesses = {
        make_shared<Process>("P1", 0, 8, Priority::MEDIUM),   // Long CPU-bound process
        make_shared<Process>("P2", 1, 4, Priority::HIGH),    // Short high-priority process  
        make_shared<Process>("P3", 2, 9, Priority::LOW),     // Long low-priority process
        make_shared<Process>("P4", 3, 5, Priority::MEDIUM),  // Medium process
        make_shared<Process>("P5", 4, 2, Priority::HIGH)     // Short high-priority process
    };
    
    // Display program header and process information
    cout << "=== OS Process Scheduling System Demo ===" << endl;
    cout << "\nThis program demonstrates various CPU scheduling algorithms" << endl;
    cout << "and compares their performance on the same set of processes.\n" << endl;
    
    cout << "Process Information:" << endl;
    cout << setw(5) << "PID" << setw(8) << "Name" 
         << setw(10) << "Arrival" << setw(8) << "Burst" 
         << setw(10) << "Priority" << endl;
    cout << string(40, '-') << endl;
    
    // Display process details
    for (const auto& process : sampleProcesses) {
        cout << setw(5) << process->pid 
             << setw(8) << process->name
             << setw(10) << process->arrivalTime
             << setw(8) << process->burstTime
             << setw(10) << static_cast<int>(process->priority) << endl;
    }
    
    // Create instances of all scheduling algorithms
    vector<unique_ptr<Scheduler>> schedulers;
    schedulers.push_back(make_unique<FCFSScheduler>());
    schedulers.push_back(make_unique<SJFScheduler>());
    schedulers.push_back(make_unique<RoundRobinScheduler>(3));  // Quantum = 3
    schedulers.push_back(make_unique<PriorityScheduler>());
    
    // Run each scheduling algorithm
    for (auto& scheduler : schedulers) {
        // Add copies of processes to scheduler (each algorithm gets fresh processes)
        for (const auto& process : sampleProcesses) {
            auto processCopy = make_shared<Process>(process->name, process->arrivalTime, 
                                                   process->burstTime, process->priority);
            scheduler->addProcess(processCopy);
        }
        
        // Execute the scheduling algorithm
        scheduler->schedule();
        
        // Display performance statistics
        scheduler->printStatistics();
        
        // Wait for user input before proceeding to next algorithm
        cout << "Press Enter to continue to next algorithm...";
        cin.get();
    }
    
    cout << "\n=== Simulation Complete ===" << endl;
    cout << "Compare the average waiting times, turnaround times, and response times" << endl;
    cout << "to understand the performance characteristics of each algorithm." << endl;
}

// ========================================================================================
// MAIN FUNCTION
// ========================================================================================

/**
 * Main Function
 * Entry point of the program
 * Handles program execution and error management
 */
int main() {
    try {
        // Run the scheduling demonstration
        demonstrateScheduling();
    } catch (const exception& e) {
        // Handle any unexpected errors
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;  // Successful program termination
}
