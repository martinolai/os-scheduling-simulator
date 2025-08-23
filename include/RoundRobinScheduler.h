#ifndef ROUND_ROBIN_SCHEDULER_H
#define ROUND_ROBIN_SCHEDULER_H

#include "Scheduler.h"
#include <memory>
#include <vector>
#include <queue>
#include <iostream>

/**
 * ========================================================================================
 * ROUND ROBIN SCHEDULER
 * ========================================================================================
 *
 * Round Robin Scheduler
 * 
 * Preemptive scheduling algorithm that gives each process a fixed time slice
 * (quantum) to execute. When the quantum expires, the process is preempted
 * and moved to the back of the ready queue.
 * 
 * Characteristics:
 * - Preemptive
 * - Fair time allocation
 * - Good response time for interactive systems
 * - Performance depends heavily on quantum size
 */
class RoundRobinScheduler : public Scheduler {
private:
    int timeQuantum;        ///< Time slice allocated to each process
    int quantumRemaining;   ///< Remaining time in current quantum

public:
    /**
     * Round Robin Constructor
     * 
     * @param quantum - Time quantum for each process (default: 4)
     */
    RoundRobinScheduler(int quantum = 4);

    /**
     * Round Robin Scheduling Algorithm Implementation
     * Implements time-sliced preemptive scheduling
     */
    void schedule() override;
};

#endif // ROUND_ROBIN_SCHEDULER_H
