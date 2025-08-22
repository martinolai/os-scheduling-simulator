#ifndef SJF_SCHEDULER_H
#define SJF_SCHEDULER_H

#include "Scheduler.h"
#include <memory>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

/**
 * ========================================================================================
 * SHORTEST JOB FIRST (SJF) SCHEDULER
 * ========================================================================================
 *
 * Shortest Job First Scheduler
 * 
 * Non-preemptive scheduling algorithm that selects the process with
 * the smallest burst time from the ready queue.
 * 
 * Characteristics:
 * - Non-preemptive
 * - Optimal for minimizing average waiting time
 * - Can cause starvation of longer processes
 * - Requires knowledge of burst times (unrealistic in practice)
 */
class SJFScheduler : public Scheduler {
public:
    /**
     * SJF Constructor
     */
    SJFScheduler();

    /**
     * SJF Scheduling Algorithm Implementation
     * Always selects the process with the shortest burst time from the ready queue
     */
    void schedule() override;
};

#endif // SJF_SCHEDULER_H
