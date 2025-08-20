/**
 * Scheduler.cpp - Abstract Scheduler Base Class Implementation File
 * 
 * This source file contains the implementation of the abstract Scheduler base class
 * that provides common functionality for all CPU scheduling algorithms.
 * 
 */

#include "Scheduler.h"

// ========================================================================================
// CONSTRUCTOR AND DESTRUCTOR IMPLEMENTATIONS
// ========================================================================================

/**
 * Scheduler Constructor Implementation
 * Initializes the base scheduler with algorithm name and settings
 */
Scheduler::Scheduler(const string& name, bool preemptive)
    : currentProcess(nullptr),
      currentTime(0),
      algorithmName(name),
      isPreemptive(preemptive),
      totalProcesses(0),
      completedProcesses(0),
      totalWaitingTime(0.0),
      totalTurnaroundTime(0.0),
      totalResponseTime(0.0)
{
    // Initialize the ready queue (already empty by default)
    // Clear any existing processes
    processes.clear();
    
    cout << "Initialized " << algorithmName << " Scheduler" 
         << (isPreemptive ? " (Preemptive)" : " (Non-preemptive)") << endl;
}

// ========================================================================================
// PUBLIC INTERFACE METHOD IMPLEMENTATIONS
// ========================================================================================

/**
 * Add Process to Scheduler Implementation
 * Validates and adds a process to the system
 */
bool Scheduler::addProcess(shared_ptr<Process> process) {
    // Validate input
    if (!process) {
        cerr << "Error: Cannot add null process to scheduler" << endl;
        return false;
    }
    
    // Check for duplicate PIDs (shouldn't happen with proper Process class)
    for (const auto& existingProcess : processes) {
        if (existingProcess->pid == process->pid) {
            cerr << "Warning: Process with PID " << process->pid << " already exists" << endl;
            return false;
        }
    }
    
    // Add process to system
    processes.push_back(process);
    totalProcesses++;
    
    cout << "Added process " << process->name << " (PID: " << process->pid 
         << ") to " << algorithmName << " scheduler" << endl;
    
    return true;
}

/**
 * Add Multiple Processes Implementation
 * Convenience method to add multiple processes at once
 */
int Scheduler::addProcesses(const vector<shared_ptr<Process>>& processList) {
    int successCount = 0;
    
    for (const auto& process : processList) {
        if (addProcess(process)) {
            successCount++;
        }
    }
    
    cout << "Successfully added " << successCount << " out of " 
         << processList.size() << " processes" << endl;
    
    return successCount;
}

/**
 * Run Scheduling Simulation Implementation
 * Main simulation driver that calls the specific scheduling algorithm
 */
bool Scheduler::runSimulation(bool verbose) {
    // Validate process set before starting
    if (!validateProcessSet()) {
        cerr << "Error: Invalid process set. Cannot run simulation." << endl;
        return false;
    }
    
    // Reset scheduler state for fresh simulation
    reset();
    
    if (verbose) {
        cout << "\n=== Starting " << algorithmName << " Scheduling Simulation ===" << endl;
        cout << "Total processes: " << totalProcesses << endl;
        cout << "Algorithm type: " << (isPreemptive ? "Preemptive" : "Non-preemptive") << endl;
        cout << string(60, '=') << endl;
    }
    
    // Call the specific scheduling algorithm (implemented by derived classes)
    bool success = schedule();
    
    if (success) {
        // Calculate final statistics
        calculateStatistics();
        
        if (verbose) {
            cout << string(60, '=') << endl;
            cout << "=== " << algorithmName << " Simulation Completed ===" << endl;
            cout << "Total execution time: " << currentTime << " time units" << endl;
            cout << "All " << completedProcesses << " processes completed successfully" << endl;
        }
    } else {
        cerr << "Error: Simulation failed for " << algorithmName << " scheduler" << endl;
    }
    
    return success;
}

/**
 * Print Performance Statistics Implementation
 * Displays comprehensive performance metrics in tabular format
 */
void Scheduler::printStatistics() const {
    cout << "\n=== " << algorithmName << " Scheduling Results ===" << endl;
    
    printStatisticsHeader();
    
    // Print individual process statistics
    for (const auto& process : processes) {
        cout << setw(5) << process->pid 
             << setw(12) << process->name
             << setw(8) << process->arrivalTime
             << setw(8) << process->burstTime
             << setw(8) << process->startTime
             << setw(10) << process->waitingTime
             << setw(12) << process->turnaroundTime
             << setw(10) << process->responseTime << endl;
    }
    
    printStatisticsFooter();
}

/**
 * Print Detailed Statistics Implementation
 * Shows extended metrics and algorithm-specific information
 */
void Scheduler::printDetailedStatistics() const {
    // First print standard statistics
    printStatistics();
    
    // Then print additional detailed information
    cout << "\n=== Detailed Performance Analysis ===" << endl;
    cout << "Algorithm: " << algorithmName 
         << (isPreemptive ? " (Preemptive)" : " (Non-preemptive)") << endl;
    cout << "Total execution time: " << getTotalExecutionTime() << " time units" << endl;
    cout << "CPU utilization: " << fixed << setprecision(2) 
         << (getTotalExecutionTime() > 0 ? 
             (double)(totalProcesses * 100) / getTotalExecutionTime() : 0.0) 
         << "%" << endl;
    cout << "Throughput: " << fixed << setprecision(2)
         << (getTotalExecutionTime() > 0 ? 
             (double)completedProcesses / getTotalExecutionTime() : 0.0)
         << " processes/time unit" << endl;
    
    // Process completion order
    cout << "\nProcess completion order:" << endl;
    vector<pair<int, string>> completionOrder;
    for (const auto& process : processes) {
        if (process->isComplete()) {
            int completionTime = process->startTime + process->burstTime;
            completionOrder.push_back({completionTime, process->name});
        }
    }
    
    sort(completionOrder.begin(), completionOrder.end());
    for (size_t i = 0; i < completionOrder.size(); ++i) {
        cout << (i + 1) << ". " << completionOrder[i].second 
             << " (completed at time " << completionOrder[i].first << ")" << endl;
    }
}

/**
 * Get Algorithm Name Implementation
 */
string Scheduler::getAlgorithmName() const {
    return algorithmName;
}

/**
 * Get Total Execution Time Implementation
 */
int Scheduler::getTotalExecutionTime() const {
    return currentTime;
}

/**
 * Get Average Waiting Time Implementation
 */
double Scheduler::getAverageWaitingTime() const {
    return totalProcesses > 0 ? totalWaitingTime / totalProcesses : 0.0;
}

/**
 * Get Average Turnaround Time Implementation
 */
double Scheduler::getAverageTurnaroundTime() const {
    return totalProcesses > 0 ? totalTurnaroundTime / totalProcesses : 0.0;
}

/**
 * Get Average Response Time Implementation
 */
double Scheduler::getAverageResponseTime() const {
    return totalProcesses > 0 ? totalResponseTime / totalProcesses : 0.0;
}

/**
 * Reset Scheduler State Implementation
 * Prepares scheduler for a fresh simulation run
 */
void Scheduler::reset() {
    // Reset timing
    currentTime = 0;
    currentProcess = nullptr;
    
    // Clear ready queue
    while (!readyQueue.empty()) {
        readyQueue.pop();
    }
    
    // Reset statistics
    completedProcesses = 0;
    totalWaitingTime = 0.0;
    totalTurnaroundTime = 0.0;
    totalResponseTime = 0.0;
    
    // Reset all process states
    resetProcessStates();
    
    cout << "Scheduler state reset for " << algorithmName << endl;
}

/**
 * Clear All Processes Implementation
 */
void Scheduler::clearProcesses() {
    processes.clear();
    totalProcesses = 0;
    reset();
    cout << "All processes cleared from " << algorithmName << " scheduler" << endl;
}

/**
 * Get Process Count Implementation
 */
size_t Scheduler::getProcessCount() const {
    return processes.size();
}

/**
 * Is Preemptive Algorithm Implementation
 */
bool Scheduler::isPreemptiveAlgorithm() const {
    return isPreemptive;
}

// ========================================================================================
// PROTECTED HELPER METHOD IMPLEMENTATIONS
// ========================================================================================

/**
 * Update Waiting Times Implementation
 * Increments waiting time for all processes in READY state
 */
void Scheduler::updateWaitingTimes() {
    for (auto& process : processes) {
        if (process->state == ProcessState::READY) {
            process->waitingTime++;
        }
    }
}

/**
 * Check for Process Arrivals Implementation
 * Moves newly arrived processes to ready queue
 */
void Scheduler::checkArrivals() {
    for (auto& process : processes) {
        if (process->state == ProcessState::NEW && process->arrivalTime <= currentTime) {
            process->state = ProcessState::READY;
            readyQueue.push(process);
        }
    }
}

/**
 * Check All Processes Completed Implementation
 */
bool Scheduler::allProcessesCompleted() const {
    for (const auto& process : processes) {
        if (process->state != ProcessState::TERMINATED) {
            return false;
        }
    }
    return true;
}

/**
 * Get Next Ready Process Implementation
 */
shared_ptr<Process> Scheduler::getNextReadyProcess() const {
    return readyQueue.empty() ? nullptr : readyQueue.front();
}

/**
 * Remove Process from Ready Queue Implementation
 */
shared_ptr<Process> Scheduler::removeFromReadyQueue() {
    if (readyQueue.empty()) {
        return nullptr;
    }
    
    auto process = readyQueue.front();
    readyQueue.pop();
    return process;
}

/**
 * Add Process to Ready Queue Implementation
 */
void Scheduler::addToReadyQueue(shared_ptr<Process> process) {
    if (process && process->state != ProcessState::TERMINATED) {
        process->state = ProcessState::READY;
        readyQueue.push(process);
    }
}

/**
 * Start Process Execution Implementation
 */
void Scheduler::startProcessExecution(shared_ptr<Process> process) {
    if (!process) return;
    
    currentProcess = process;
    currentProcess->state = ProcessState::RUNNING;
    
    // Record start time and response time if first execution
    if (!currentProcess->hasStarted) {
        currentProcess->startTime = currentTime;
        currentProcess->responseTime = currentTime - currentProcess->arrivalTime;
        currentProcess->hasStarted = true;
    }
}

/**
 * Complete Process Execution Implementation
 */
void Scheduler::completeProcessExecution(shared_ptr<Process> process) {
    if (!process) return;
    
    process->state = ProcessState::TERMINATED;
    process->remainingTime = 0;
    process->updateStatistics(currentTime);
    completedProcesses++;
    
    // Clear current process if it's the completed one
    if (currentProcess == process) {
        currentProcess = nullptr;
    }
}

/**
 * Preempt Current Process Implementation
 */
void Scheduler::preemptCurrentProcess(const string& reason) {
    if (currentProcess && currentProcess->remainingTime > 0) {
        currentProcess->state = ProcessState::READY;
        readyQueue.push(currentProcess);
        currentProcess = nullptr;
    }
}

/**
 * Execute Time Slice Implementation
 */
bool Scheduler::executeTimeSlice() {
    if (!currentProcess) return false;
    
    // Execute for one time unit
    currentProcess->remainingTime--;
    
    // Check if process completed
    if (currentProcess->remainingTime <= 0) {
        completeProcessExecution(currentProcess);
        return true;  // Process completed
    }
    
    return false;  // Process still running
}

/**
 * Print Execution Step Implementation
 */
void Scheduler::printExecutionStep(const string& action) const {
    cout << "Time " << setw(3) << currentTime << ": " << action;
    
    if (currentProcess) {
        cout << " (Process " << currentProcess->name 
             << ", remaining: " << currentProcess->remainingTime << ")";
    }
    
    cout << endl;
}

/**
 * Validate Process Set Implementation
 */
bool Scheduler::validateProcessSet() const {
    if (processes.empty()) {
        cerr << "Error: No processes to schedule" << endl;
        return false;
    }
    
    // Check each process for validity
    for (const auto& process : processes) {
        if (!process) {
            cerr << "Error: Null process found in process set" << endl;
            return false;
        }
        
        if (process->burstTime <= 0) {
            cerr << "Error: Process " << process->name << " has invalid burst time" << endl;
            return false;
        }
        
        if (process->arrivalTime < 0) {
            cerr << "Error: Process " << process->name << " has negative arrival time" << endl;
            return false;
        }
    }
    
    return true;
}

/**
 * Calculate Statistics Implementation
 */
void Scheduler::calculateStatistics() {
    totalWaitingTime = 0.0;
    totalTurnaroundTime = 0.0;
    totalResponseTime = 0.0;
    
    for (const auto& process : processes) {
        totalWaitingTime += process->waitingTime;
        totalTurnaroundTime += process->turnaroundTime;
        totalResponseTime += process->responseTime;
    }
}

/**
 * Reset Process States Implementation
 */
void Scheduler::resetProcessStates() {
    for (auto& process : processes) {
        process->reset();
    }
}

/**
 * Sort Processes by Arrival Time Implementation
 */
void Scheduler::sortProcessesByArrivalTime() {
    sort(processes.begin(), processes.end(), 
         [](const shared_ptr<Process>& a, const shared_ptr<Process>& b) {
             return a->arrivalTime < b->arrivalTime;
         });
}

/**
 * Get Ready Queue Size Implementation
 */
size_t Scheduler::getReadyQueueSize() const {
    return readyQueue.size();
}

/**
 * Is System Idle Implementation
 */
bool Scheduler::isSystemIdle() const {
    return (!currentProcess && readyQueue.empty());
}

// ========================================================================================
// PRIVATE UTILITY METHOD IMPLEMENTATIONS
// ========================================================================================

/**
 * Initialize Statistics Implementation
 */
void Scheduler::initializeStatistics() {
    totalWaitingTime = 0.0;
    totalTurnaroundTime = 0.0;
    totalResponseTime = 0.0;
    completedProcesses = 0;
}

/**
 * Print Statistics Header Implementation
 */
void Scheduler::printStatisticsHeader() const {
    cout << setw(5) << "PID" << setw(12) << "Name" 
         << setw(8) << "Arrival" << setw(8) << "Burst"
         << setw(8) << "Start" << setw(10) << "Waiting"
         << setw(12) << "Turnaround" << setw(10) << "Response" << endl;
    cout << string(70, '-') << endl;
}

/**
 * Print Statistics Footer Implementation
 */
void Scheduler::printStatisticsFooter() const {
    cout << string(70, '-') << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(2) 
         << getAverageWaitingTime() << " time units" << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2) 
         << getAverageTurnaroundTime() << " time units" << endl;
    cout << "Average Response Time: " << fixed << setprecision(2) 
         << getAverageResponseTime() << " time units" << endl;
    cout << "Total Execution Time: " << getTotalExecutionTime() << " time units" << endl;
    cout << endl;
}
