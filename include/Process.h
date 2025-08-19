/**
 * Process.h - Process Control Block Header File
 * 
 * This header file defines the Process class which represents a Process Control Block (PCB)
 * used in operating system process scheduling simulation.
 *
 */

#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>     // For input/output operations
#include <iomanip>      // For formatted output
#include <string>       // For string operations

using namespace std;

// ========================================================================================
// ENUMERATIONS
// ========================================================================================

/**
 * Process States - Represents the current state of a process in the system
 * Based on the standard 5-state process model used in operating systems
 */
enum class ProcessState {
    NEW,        // Process is being created
    READY,      // Process is waiting to be assigned to a processor
    RUNNING,    // Instructions are being executed
    WAITING,    // Process is waiting for some event to occur (I/O, etc.)
    TERMINATED  // Process has finished execution
};

/**
 * Process Priority Levels
 * Lower numeric values represent higher priority
 * Used in priority-based scheduling algorithms
 */
enum class Priority {
    HIGH = 1,    // Critical system processes
    MEDIUM = 2,  // Normal user processes
    LOW = 3      // Background/batch processes
};

// ========================================================================================
// PROCESS CLASS DECLARATION
// ========================================================================================

/**
 * Process Class - Represents a Process Control Block (PCB)
 * 
 * This class contains all the information the operating system needs
 * about a particular process including:
 * - Process identification (PID)
 * - Process state and priority
 * - CPU scheduling information
 * - Memory management information (simplified here)
 * - I/O status information (not implemented in this simulation)
 */
class Process {
private:
    static int nextPID;  // Static counter for generating unique PIDs
    
public:
    // ==================================================================================
    // PUBLIC MEMBER VARIABLES
    // ==================================================================================
    
    // Process Identification
    int pid;                    // Process ID (unique identifier)
    string name;               // Human-readable process name
    
    // Process State Information
    ProcessState state;        // Current process state
    Priority priority;         // Process priority level
    
    // CPU Scheduling Information
    int arrivalTime;           // Time when process arrives in the system
    int burstTime;            // Total CPU time required by the process
    int remainingTime;        // Remaining CPU time (for preemptive algorithms)
    
    // Performance Metrics
    int waitingTime;          // Total time spent in ready queue
    int turnaroundTime;       // Total time from arrival to completion
    int responseTime;         // Time from arrival to first CPU allocation
    int startTime;            // Time when process first gets CPU
    bool hasStarted;          // Flag to track if process has started execution
    
    // ==================================================================================
    // PUBLIC MEMBER FUNCTIONS
    // ==================================================================================
    
    /**
     * Process Constructor
     * Creates a new process with specified parameters
     * 
     * @param processName - Human-readable name for the process
     * @param arrival - Time when process arrives in system
     * @param burst - Total CPU time required
     * @param prio - Priority level (default: MEDIUM)
     */
    Process(const string& processName, int arrival, int burst, Priority prio = Priority::MEDIUM);
    
    /**
     * Process Destructor
     * Default destructor for cleanup
     */
    ~Process() = default;
    
    /**
     * Copy Constructor
     * Creates a copy of an existing process with new PID
     * 
     * @param other - Process to copy from
     */
    Process(const Process& other);
    
    /**
     * Assignment Operator
     * Assigns one process to another (maintains original PID)
     * 
     * @param other - Process to assign from
     * @return Reference to this process
     */
    Process& operator=(const Process& other);
    
    /**
     * Reset Process State
     * Resets all timing and state information for algorithm comparison
     * Allows the same process to be used across different scheduling algorithms
     */
    void reset();
    
    /**
     * Print Current Process Status
     * Displays current state of the process for debugging
     */
    void printStatus() const;
    
    /**
     * Get Process Information Summary
     * Returns formatted string with process details
     * 
     * @return String containing process summary
     */
    string getProcessInfo() const;
    
    /**
     * Check if Process is Complete
     * Returns true if process has finished execution
     * 
     * @return Boolean indicating completion status
     */
    bool isComplete() const;
    
    /**
     * Get Remaining Execution Time
     * Returns the remaining CPU time needed
     * 
     * @return Remaining time in time units
     */
    int getRemainingTime() const;
    
    /**
     * Update Process Statistics
     * Updates waiting time, turnaround time, and response time
     * Called when process completes execution
     * 
     * @param completionTime - Time when process completed
     */
    void updateStatistics(int completionTime);

private:
    // ==================================================================================
    // PRIVATE HELPER FUNCTIONS
    // ==================================================================================
    
    /**
     * Convert Process State to String
     * Helper function for displaying process state
     * 
     * @return String representation of current process state
     */
    string stateToString() const;
    
    /**
     * Convert Priority to String
     * Helper function for displaying process priority
     * 
     * @return String representation of process priority
     */
    string priorityToString() const;
};

#endif // PROCESS_H
