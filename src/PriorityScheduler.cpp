#include "../include/PriorityScheduler.h"

PriorityScheduler::PriorityScheduler() : Scheduler("Priority") {}

void PriorityScheduler::schedule() {
    resetProcesses();

    cout << "\n=== Priority Scheduling Execution ===" << endl;

    // Main scheduling loop
    while (true) {
        // Check for new process arrivals
        checkArrivals();

        // If no current process, get highest priority process from ready queue
        if (!currentProcess && !readyQueue.empty()) {
            shared_ptr<Process> highestPriorityProcess = nullptr;
            queue<shared_ptr<Process>> tempQueue;

            // Search through ready queue to find highest priority process
            while (!readyQueue.empty()) {
                auto process = readyQueue.front();
                readyQueue.pop();

                // Lower priority number means higher priority
                if (!highestPriorityProcess || process->priority < highestPriorityProcess->priority) {
                    if (highestPriorityProcess) tempQueue.push(highestPriorityProcess);
                    highestPriorityProcess = process;
                } else {
                    tempQueue.push(process);
                }
            }

            // Put remaining processes back in ready queue
            while (!tempQueue.empty()) {
                readyQueue.push(tempQueue.front());
                tempQueue.pop();
            }

            // Start execution of highest priority process
            currentProcess = highestPriorityProcess;
            currentProcess->state = ProcessState::RUNNING;

            // Record timing information for first execution
            if (!currentProcess->hasStarted) {
                currentProcess->startTime = currentTime;
                currentProcess->responseTime = currentTime - currentProcess->arrivalTime;
                currentProcess->hasStarted = true;
            }

            cout << "Time " << currentTime << ": Process " << currentProcess->name
                 << " (Priority " << static_cast<int>(currentProcess->priority) << ") started" << endl;
        }

        // Execute current process for one time unit
        if (currentProcess) {
            currentProcess->remainingTime--;

            // Check if process completed
            if (currentProcess->remainingTime == 0) {
                currentProcess->state = ProcessState::TERMINATED;
                currentProcess->turnaroundTime = currentTime + 1 - currentProcess->arrivalTime;
                currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->burstTime;

                cout << "Time " << (currentTime + 1) << ": Process " << currentProcess->name << " completed" << endl;
                currentProcess = nullptr;
            }
        }

        // Update waiting times
        updateWaitingTimes();
        currentTime++;

        // Check termination condition
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
