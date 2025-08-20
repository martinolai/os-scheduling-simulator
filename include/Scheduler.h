/**
 * Scheduler.h - Abstract Scheduler Base Class Header File
 * 
 * This header file defines the abstract Scheduler base class that provides
 * common functionality for all CPU scheduling algorithms. It implements the
 * Template Method pattern where concrete schedulers implement the specific
 * scheduling logic while inheriting common process management functionality.
 * 
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>     // For input/output operations
#include <vector>       // For dynamic arrays
#include <queue>        // For process ready queues
#include <memory>       // For smart pointers
#include <iomanip>      // For formatted output
#include <string>       // For string operations
#include <algorithm>    // For sorting and searching

#include "Process.h"    // Include Process class definition

using namespace std;

// ========================================================================================
// ABSTRACT SCHEDULER BASE CLASS
// ========================================================================================

/**
 * Abstract Scheduler Class
 * 
 * This is the base class for all scheduling algorithms using the Template Method pattern.
 * It provides common functionality needed by all schedulers:
 * - Process management and storage
 * - Ready queue handling  
 * - Performance metrics calculation and reporting
 * - Common simulation utilities
 * 
 * Each concrete scheduler must implement the pure virtual schedule() method
 * which contains the specific scheduling algorithm logic.
 */
class Scheduler {
protected:
    // ==================================================================================
    // PROTECTED MEMBER VARIABLES
    // ==================================================================================
    
    vector<shared_ptr<Process>> processes;      // All processes in the system
    queue<shared_ptr<Process>> readyQueue;      // Queue of processes ready to run
    shared_ptr<Process> currentProcess;         // Currently executing process
    int currentTime;                           // System clock/timer (time units)
    string algorithmName;                      // Name of the scheduling algorithm
    bool isPreemptive;                        // Whether algorithm supports preemption
    
    // Statistics tracking
    int totalProcesses;                       // Total number of processes
    int completedProcesses;                   // Number of completed processes
    double totalWaitingTime;                  // Sum of all waiting times
    double totalTurnaroundTime;               // Sum of all turnaround times
    double totalResponseTime;                 // Sum of all response times
    
public:
    // ==================================================================================
    // PUBLIC CONSTRUCTORS AND DESTRUCTOR
    // ==================================================================================
    
    /**
     * Scheduler Constructor
     * Initializes the base scheduler with algorithm name and preemption flag
     * 
     * @param name - Name of the scheduling algorithm
     * @param preemptive - Whether the algorithm supports preemption (default: false)
     */
    Scheduler(const string& name, bool preemptive = false);
    
    /**
     * Virtual Destructor
     * Ensures proper cleanup of derived classes
     */
    virtual ~Scheduler() = default;
    
    // ==================================================================================
    // PUBLIC INTERFACE METHODS
    // ==================================================================================
    
    /**
     * Add Process to Scheduler
     * Adds a new process to the system for scheduling
     * 
     * @param process - Shared pointer to the process to be added
     * @return Boolean indicating success of addition
     */
    bool addProcess(shared_ptr<Process> process);
    
    /**
     * Add Multiple Processes
     * Convenience method to add multiple processes at once
     * 
     * @param processList - Vector of processes to add
     * @return Number of processes successfully added
     */
    int addProcesses(const vector<shared_ptr<Process>>& processList);
    
    /**
     * Pure Virtual Schedule Function
     * Each scheduling algorithm must implement this function
     * This is where the actual scheduling logic is implemented
     * 
     * @return Boolean indicating successful completion of scheduling
     */
    virtual bool schedule() = 0;
    
    /**
     * Run Scheduling Simulation
     * High-level method that sets up and runs the complete simulation
     * 
     * @param verbose - Whether to display detailed execution trace (default: true)
     * @return Boolean indicating successful simulation completion
     */
    bool runSimulation(bool verbose = true);
    
    /**
     * Print Performance Statistics
     * Calculates and displays comprehensive performance metrics
     * Including individual process metrics and system averages
     */
    void printStatistics() const;
    
    /**
     * Print Detailed Statistics
     * Displays extended statistics including algorithm-specific metrics
     */
    void printDetailedStatistics() const;
    
    /**
     * Get Algorithm Name
     * Returns the name of the scheduling algorithm
     * 
     * @return String containing algorithm name
     */
    string getAlgorithmName() const;
    
    /**
     * Get Total Execution Time
     * Returns the total time taken to complete all processes
     * 
     * @return Total execution time in time units
     */
    int getTotalExecutionTime() const;
    
    /**
     * Get Average Waiting Time
     * Calculates and returns the average waiting time across all processes
     * 
     * @return Average waiting time as a double
     */
    double getAverageWaitingTime() const;
    
    /**
     * Get Average Turnaround Time
     * Calculates and returns the average turnaround time across all processes
     * 
     * @return Average turnaround time as a double
     */
    double getAverageTurnaroundTime() const;
    
    /**
     * Get Average Response Time
     * Calculates and returns the average response time across all processes
     * 
     * @return Average response time as a double
     */
    double getAverageResponseTime() const;
    
    /**
     * Reset Scheduler State
     * Resets the scheduler for a fresh simulation run
     * Useful when comparing multiple algorithms on the same process set
     */
    void reset();
    
    /**
     * Clear All Processes
     * Removes all processes from the scheduler
     */
    void clearProcesses();
    
    /**
     * Get Process Count
     * Returns the number of processes in the system
     * 
     * @return Number of processes
     */
    size_t getProcessCount() const;
    
    /**
     * Is Preemptive Algorithm
     * Returns whether this scheduling algorithm supports preemption
     * 
     * @return Boolean indicating preemptive capability
     */
    bool isPreemptiveAlgorithm() const;

protected:
    // ==================================================================================
    // PROTECTED HELPER METHODS FOR DERIVED CLASSES
    // ==================================================================================
    
    /**
     * Update Waiting Times
     * Increments waiting time for all processes in READY state
     * Should be called once per time unit during simulation
     */
    void updateWaitingTimes();
    
    /**
     * Check for Process Arrivals
     * Moves processes from NEW to READY state when they arrive
     * Adds newly arrived processes to the ready queue
     */
    void checkArrivals();
    
    /**
     * Check All Processes Completed
     * Determines if all processes have finished execution
     * 
     * @return Boolean indicating if all processes are completed
     */
    bool allProcessesCompleted() const;
    
    /**
     * Get Next Ready Process
     * Returns the next process from the ready queue without removing it
     * 
     * @return Shared pointer to next ready process (nullptr if queue empty)
     */
    shared_ptr<Process> getNextReadyProcess() const;
    
    /**
     * Remove Process from Ready Queue
     * Removes and returns the next process from the ready queue
     * 
     * @return Shared pointer to the removed process (nullptr if queue empty)
     */
    shared_ptr<Process> removeFromReadyQueue();
    
    /**
     * Add Process to Ready Queue
     * Adds a process to the ready queue and updates its state
     * 
     * @param process - Process to add to ready queue
     */
    void addToReadyQueue(shared_ptr<Process> process);
    
    /**
     * Start Process Execution
     * Handles the transition of a process to running state
     * Updates timing information and process state
     * 
     * @param process - Process to start executing
     */
    void startProcessExecution(shared_ptr<Process> process);
    
    /**
     * Complete Process Execution
     * Handles the completion of a process
     * Updates statistics and process state
     * 
     * @param process - Process that has completed
     */
    void completeProcessExecution(shared_ptr<Process> process);
    
    /**
     * Preempt Current Process
     * Handles preemption of the currently running process
     * Returns process to ready queue if not completed
     * 
     * @param reason - Reason for preemption (for logging)
     */
    void preemptCurrentProcess(const string& reason = "");
    
    /**
     * Execute Time Slice
     * Executes the current process for one time unit
     * Handles process completion and timing updates
     * 
     * @return Boolean indicating if process completed during this slice
     */
    bool executeTimeSlice();
    
    /**
     * Print Execution Step
     * Displays current execution state for verbose output
     * 
     * @param action - Description of current action
     */
    void printExecutionStep(const string& action) const;
    
    /**
     * Validate Process Set
     * Checks if the current process set is valid for scheduling
     * 
     * @return Boolean indicating validity of process set
     */
    bool validateProcessSet() const;
    
    /**
     * Calculate Statistics
     * Internal method to calculate performance metrics
     * Called automatically during simulation
     */
    void calculateStatistics();
    
    /**
     * Reset Process States
     * Resets all processes to their initial state
     * Used when rerunning simulations
     */
    void resetProcessStates();
    
    /**
     * Sort Processes by Arrival Time
     * Utility method to sort processes by arrival time
     * Useful for FCFS and other arrival-based algorithms
     */
    void sortProcessesByArrivalTime();
    
    /**
     * Get Ready Queue Size
     * Returns the current number of processes in ready queue
     * 
     * @return Size of ready queue
     */
    size_t getReadyQueueSize() const;
    
    /**
     * Is System Idle
     * Checks if system is currently idle (no running or ready processes)
     * 
     * @return Boolean indicating idle state
     */
    bool isSystemIdle() const;

private:
    // ==================================================================================
    // PRIVATE UTILITY METHODS
    // ==================================================================================
    
    /**
     * Initialize Statistics
     * Initializes all statistical tracking variables
     */
    void initializeStatistics();
    
    /**
     * Print Statistics Header
     * Prints the header for statistics table
     */
    void printStatisticsHeader() const;
    
    /**
     * Print Statistics Footer
     * Prints summary statistics and averages
     */
    void printStatisticsFooter() const;
};

#endif // SCHEDULER_H
