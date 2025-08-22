#include "SJFScheduler.h"

using namespace std;

/**
 * SJF Constructor
 */
SJFScheduler::SJFScheduler() : Scheduler("SJF") {}

/**
 * Implements the Shortest Job First (SJF) Scheduling Algorithm
 * 
 * Algorithm flow:
 * 1. Reset all processes to their initial state.
 * 2. At each time unit:
 *    - Check for new arrivals and place them in the ready queue.
 *    - If CPU is idle, select the process with the **shortest burst time**
 *      from the ready queue (non-preemptive).
 *    - Run the selected process until completion.
 *    - When a process finishes, compute turnaround and waiting times.
 *    - Update waiting times of other processes in the ready queue.
 * 3. Stop when all processes are terminated.
 */
void SJFScheduler::schedule() {
    resetProcesses();
    
    cout << "\n=== SJF Scheduling Execution ===" << endl;
    
    // Main scheduling loop
    while (true) {
        // Check for new process arrivals
        checkArrivals();
        
        // If CPU is idle, select shortest job from ready queue
        if (!currentProcess && !readyQueue.empty()) {
            // Find process with shortest burst time
            shared_ptr<Process> shortestJob = nullptr;
            queue<shared_ptr<Process>> tempQueue;
            
            // Search ready queue for shortest job
            while (!readyQueue.empty()) {
                auto process = readyQueue.front();
                readyQueue.pop();
                
                if (!shortestJob || process->burstTime < shortestJob->burstTime) {
                    if (shortestJob) tempQueue.push(shortestJob);
                    shortestJob = process;
                } else {
                    tempQueue.push(process);
                }
            }
            
            // Restore remaining processes into ready queue
            while (!tempQueue.empty()) {
                readyQueue.push(tempQueue.front());
                tempQueue.pop();
            }
            
            // Start execution of shortest job
            currentProcess = shortestJob;
            currentProcess->state = ProcessState::RUNNING;
            
            // Record start and response time (first execution only)
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
        
        // Update waiting times of processes still in ready queue
        updateWaitingTimes();
        currentTime++;
        
        // Termination check
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

