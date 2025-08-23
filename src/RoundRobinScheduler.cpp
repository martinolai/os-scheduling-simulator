#include "RoundRobinScheduler.h"

using namespace std;

/**
 * Round Robin Constructor
 */
RoundRobinScheduler::RoundRobinScheduler(int quantum) 
    : Scheduler("Round Robin"), timeQuantum(quantum), quantumRemaining(quantum) {}

/**
 * Implements the Round Robin (RR) Scheduling Algorithm
 * 
 * Algorithm flow:
 * 1. Reset all processes to initial state and reset quantum counter.
 * 2. At each time unit:
 *    - Check for new arrivals and place them in the ready queue.
 *    - If no current process or quantum has expired, pick the next ready process:
 *         - If the current process was preempted (not finished), push it back.
 *         - Load the next process and reset its quantum.
 *    - Run the selected process for one time unit (preemptive).
 *    - If process finishes, compute turnaround and waiting times.
 * 3. Stop when all processes are terminated.
 */
void RoundRobinScheduler::schedule() {
    resetProcesses();
    quantumRemaining = timeQuantum;
    
    cout << "\n=== Round Robin Scheduling Execution (Quantum: " 
         << timeQuantum << ") ===" << endl;
    
    // Main scheduling loop
    while (true) {
        // Check for new process arrivals
        checkArrivals();
        
        // Check if we need to switch processes
        if ((!currentProcess || quantumRemaining == 0) && !readyQueue.empty()) {
            // Preemption: if quantum expired but process not finished
            if (currentProcess && quantumRemaining == 0 && currentProcess->remainingTime > 0) {
                currentProcess->state = ProcessState::READY;
                readyQueue.push(currentProcess);
                cout << "Time " << currentTime << ": Process " 
                     << currentProcess->name << " preempted" << endl;
            }
            
            // Get next process from ready queue
            currentProcess = readyQueue.front();
            readyQueue.pop();
            currentProcess->state = ProcessState::RUNNING;
            quantumRemaining = timeQuantum;  // Reset quantum
            
            // Record first execution timing
            if (!currentProcess->hasStarted) {
                currentProcess->startTime = currentTime;
                currentProcess->responseTime = currentTime - currentProcess->arrivalTime;
                currentProcess->hasStarted = true;
            }
            
            cout << "Time " << currentTime << ": Process " 
                 << currentProcess->name << " started/resumed" << endl;
        }
        
        // Execute current process for one unit
        if (currentProcess) {
            currentProcess->remainingTime--;
            quantumRemaining--;
            
            // If process completed
            if (currentProcess->remainingTime == 0) {
                currentProcess->state = ProcessState::TERMINATED;
                currentProcess->turnaroundTime = currentTime + 1 - currentProcess->arrivalTime;
                currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->burstTime;
                
                cout << "Time " << (currentTime + 1) << ": Process " 
                     << currentProcess->name << " completed" << endl;
                
                currentProcess = nullptr;
                quantumRemaining = timeQuantum; // Reset quantum for next process
            }
        }
        
        // Update waiting times of ready processes
        updateWaitingTimes();
        currentTime++;
        
        // Check if all processes are finished
        bool allCompleted = true;
        for (const auto& process : processes) {
            if (process->state != ProcessState::TERMINATED) {
                allCompleted = false;
                break;
            }
        }
        
        if (allCompleted) break;
    }
}
