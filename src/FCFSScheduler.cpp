#include "FCFSScheduler.h"

using namespace std;

/**
 * FCFS Constructor
 */
FCFSScheduler::FCFSScheduler() : Scheduler("FCFS") {}

/**
 * Implements the First Come First Serve (FCFS) Scheduling Algorithm
 * 
 * Algorithm flow:
 * 1. Reset all processes to initial state.
 * 2. Sort processes by arrival time to preserve FCFS order.
 * 3. At each time unit:
 *    - Check for new arrivals and move them to the ready queue.
 *    - If CPU is idle, dispatch the next process from ready queue.
 *    - Run the current process (no preemption).
 *    - On completion, calculate turnaround and waiting times.
 *    - Update waiting times of processes in the ready queue.
 * 4. Stop when all processes are terminated.
 */
void FCFSScheduler::schedule() {
    resetProcesses();
    
    // Sort processes by arrival time for proper FCFS order
    sort(processes.begin(), processes.end(),
         [](const shared_ptr<Process>& a, const shared_ptr<Process>& b) {
             return a->arrivalTime < b->arrivalTime;
         });
    
    cout << "\n=== FCFS Scheduling Execution ===" << endl;
    
    // Main scheduling loop
    while (true) {
        // Check for new process arrivals at this time
        checkArrivals();
        
        // If CPU is idle, get the next process from ready queue
        if (!currentProcess && !readyQueue.empty()) {
            currentProcess = readyQueue.front();
            readyQueue.pop();
            currentProcess->state = ProcessState::RUNNING;
            
            // Record start time and response time for first execution
            if (!currentProcess->hasStarted) {
                currentProcess->startTime = currentTime;
                currentProcess->responseTime = currentTime - currentProcess->arrivalTime;
                currentProcess->hasStarted = true;
            }
            
            cout << "Time " << currentTime << ": Process " 
                 << currentProcess->name << " started" << endl;
        }
        
        // Execute current process for one time unit
        if (currentProcess) {
            currentProcess->remainingTime--;
            
            // Check if process completed
            if (currentProcess->remainingTime == 0) {
                currentProcess->state = ProcessState::TERMINATED;
                currentProcess->turnaroundTime = currentTime + 1 - currentProcess->arrivalTime;
                currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->burstTime;
                
                cout << "Time " << (currentTime + 1) << ": Process " 
                     << currentProcess->name << " completed" << endl;
                currentProcess = nullptr;
            }
        }
        
        // Update waiting times for processes in ready queue
        updateWaitingTimes();
        currentTime++;
        
        // Check if all processes are completed
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

