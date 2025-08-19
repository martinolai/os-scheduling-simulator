/**
 * Process.cpp - Process Control Block Implementation File
 * 
 * This source file contains the implementation of the Process class
 * which represents a Process Control Block (PCB) used in operating system
 * process scheduling simulation.
 * 
 * Author: [Your Name]
 * Date: [Current Date]
 * Version: 1.0
 */

#include "Process.h"

// ========================================================================================
// STATIC MEMBER INITIALIZATION
// ========================================================================================

// Initialize static PID counter - starts from 1
int Process::nextPID = 1;

// ========================================================================================
// CONSTRUCTOR AND DESTRUCTOR IMPLEMENTATIONS
// ========================================================================================

/**
 * Process Constructor Implementation
 * Creates a new process with specified parameters and initializes all member variables
 */
Process::Process(const string& processName, int arrival, int burst, Priority prio)
    : pid(nextPID++),                    // Assign unique PID and increment counter
      name(processName),                 // Set process name
      state(ProcessState::NEW),          // Initial state is NEW
      priority(prio),                    // Set priority level
      arrivalTime(arrival),              // Set arrival time
      burstTime(burst),                  // Set required CPU time
      remainingTime(burst),              // Initially equals burst time
      waitingTime(0),                    // No waiting time initially
      turnaroundTime(0),                 // No turnaround time initially
      responseTime(-1),                  // -1 indicates not yet started
      startTime(-1),                     // -1 indicates not yet started
      hasStarted(false)                  // Process hasn't started execution
{
    // Validate input parameters
    if (arrival < 0) {
        cout << "Warning: Process " << name << " has negative arrival time. Setting to 0." << endl;
        arrivalTime = 0;
    }
    
    if (burst <= 0) {
        cout << "Warning: Process " << name << " has invalid burst time. Setting to 1." << endl;
        burstTime = 1;
        remainingTime = 1;
    }
}

/**
 * Copy Constructor Implementation
 * Creates a copy of an existing process with a new unique PID
 */
Process::Process(const Process& other)
    : pid(nextPID++),                    // New unique PID
      name(other.name),                  // Copy name
      state(other.state),                // Copy state
      priority(other.priority),          // Copy priority
      arrivalTime(other.arrivalTime),    // Copy arrival time
      burstTime(other.burstTime),        // Copy burst time
      remainingTime(other.remainingTime), // Copy remaining time
      waitingTime(other.waitingTime),    // Copy waiting time
      turnaroundTime(other.turnaroundTime), // Copy turnaround time
      responseTime(other.responseTime),  // Copy response time
      startTime(other.startTime),        // Copy start time
      hasStarted(other.hasStarted)       // Copy execution flag
{
    // Copy constructor creates a new process with fresh PID
    // but copies all other attributes from the original process
}

/**
 * Assignment Operator Implementation
 * Assigns one process to another while maintaining the original PID
 */
Process& Process::operator=(const Process& other) {
    // Self-assignment check
    if (this == &other) {
        return *this;
    }
    
    // Copy all attributes except PID (maintain original PID)
    name = other.name;
    state = other.state;
    priority = other.priority;
    arrivalTime = other.arrivalTime;
    burstTime = other.burstTime;
    remainingTime = other.remainingTime;
    waitingTime = other.waitingTime;
    turnaroundTime = other.turnaroundTime;
    responseTime = other.responseTime;
    startTime = other.startTime;
    hasStarted = other.hasStarted;
    
    return *this;
}

// ========================================================================================
// PUBLIC MEMBER FUNCTION IMPLEMENTATIONS
// ========================================================================================

/**
 * Reset Process State Implementation
 * Resets all timing and state information for algorithm comparison
 */
void Process::reset() {
    state = ProcessState::NEW;          // Reset to initial state
    remainingTime = burstTime;          // Reset remaining time to full burst time
    waitingTime = 0;                    // Clear waiting time
    turnaroundTime = 0;                 // Clear turnaround time
    responseTime = -1;                  // Reset response time indicator
    startTime = -1;                     // Reset start time indicator
    hasStarted = false;                 // Reset execution flag
}

/**
 * Print Current Process Status Implementation
 * Displays comprehensive information about the process state
 */
void Process::printStatus() const {
    cout << "PID: " << setw(3) << pid 
         << " | Name: " << setw(10) << name
         << " | State: " << setw(9) << stateToString()
         << " | Priority: " << setw(6) << priorityToString()
         << " | Remaining: " << setw(3) << remainingTime
         << " | Arrival: " << setw(3) << arrivalTime
         << " | Burst: " << setw(3) << burstTime << endl;
}

/**
 * Get Process Information Summary Implementation
 * Returns a formatted string with complete process details
 */
string Process::getProcessInfo() const {
    string info = "Process " + name + " (PID: " + to_string(pid) + ")\n";
    info += "  State: " + stateToString() + "\n";
    info += "  Priority: " + priorityToString() + "\n";
    info += "  Arrival Time: " + to_string(arrivalTime) + "\n";
    info += "  Burst Time: " + to_string(burstTime) + "\n";
    info += "  Remaining Time: " + to_string(remainingTime) + "\n";
    
    if (hasStarted) {
        info += "  Start Time: " + to_string(startTime) + "\n";
        info += "  Response Time: " + to_string(responseTime) + "\n";
    }
    
    if (state == ProcessState::TERMINATED) {
        info += "  Waiting Time: " + to_string(waitingTime) + "\n";
        info += "  Turnaround Time: " + to_string(turnaroundTime) + "\n";
    }
    
    return info;
}

/**
 * Check if Process is Complete Implementation
 * Returns true if the process has finished execution
 */
bool Process::isComplete() const {
    return (state == ProcessState::TERMINATED) || (remainingTime <= 0);
}

/**
 * Get Remaining Execution Time Implementation
 * Returns the remaining CPU time needed by the process
 */
int Process::getRemainingTime() const {
    return remainingTime;
}

/**
 * Update Process Statistics Implementation
 * Calculates and updates performance metrics when process completes
 */
void Process::updateStatistics(int completionTime) {
    // Calculate turnaround time (completion time - arrival time)
    turnaroundTime = completionTime - arrivalTime;
    
    // Calculate waiting time (turnaround time - burst time)
    waitingTime = turnaroundTime - burstTime;
    
    // Ensure waiting time is not negative (shouldn't happen in proper scheduling)
    if (waitingTime < 0) {
        waitingTime = 0;
    }
    
    // If response time hasn't been set, calculate it
    if (responseTime == -1) {
        responseTime = (startTime != -1) ? (startTime - arrivalTime) : 0;
    }
    
    // Mark process as terminated
    state = ProcessState::TERMINATED;
    remainingTime = 0;
}

// ========================================================================================
// PRIVATE HELPER FUNCTION IMPLEMENTATIONS
// ========================================================================================

/**
 * Convert Process State to String Implementation
 * Helper function that returns a string representation of the process state
 */
string Process::stateToString() const {
    switch (state) {
        case ProcessState::NEW:
            return "NEW";
        case ProcessState::READY:
            return "READY";
        case ProcessState::RUNNING:
            return "RUNNING";
        case ProcessState::WAITING:
            return "WAITING";
        case ProcessState::TERMINATED:
            return "TERMINATED";
        default:
            return "UNKNOWN";
    }
}

/**
 * Convert Priority to String Implementation
 * Helper function that returns a string representation of the process priority
 */
string Process::priorityToString() const {
    switch (priority) {
        case Priority::HIGH:
            return "HIGH";
        case Priority::MEDIUM:
            return "MEDIUM";
        case Priority::LOW:
            return "LOW";
        default:
            return "UNKNOWN";
    }
}
