#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include "Scheduler.h"
#include <memory>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

/**
 * ========================================================================================
 * FIRST COME FIRST SERVE (FCFS) SCHEDULER
 * ========================================================================================
 *
 * First Come First Serve Scheduler
 * 
 * Non-preemptive scheduling algorithm that serves processes in the order
 * they arrive in the system. Simple but can lead to convoy effect where
 * short processes wait behind long processes.
 * 
 * Characteristics:
 * - Non-preemptive
 * - Fair in terms of arrival order
 * - Can have poor average waiting time
 * - No starvation (every process eventually gets CPU)
 */
class FCFSScheduler : public Scheduler {
public:
    /**
     * FCFS Constructor
     */
    FCFSScheduler();

    /**
     * FCFS Scheduling Algorithm Implementation
     * Processes are executed in arrival order without preemption
     */
    void schedule() override;
};

#endif // FCFS_SCHEDULER_H

