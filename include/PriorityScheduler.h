#ifndef PRIORITYSCHEDULER_H
#define PRIORITYSCHEDULER_H

#include "Scheduler.h"
#include <iostream>
#include <memory>
#include <queue>
#include <vector>
using namespace std;

/**
 * Priority Scheduler
 * 
 * Non-preemptive scheduling algorithm that selects processes based on
 * their priority level. Higher priority processes are executed first.
 * 
 * Characteristics:
 * - Non-preemptive
 * - Supports system and user priority levels
 * - Can cause starvation of low-priority processes
 * - Often used in real-time systems
 */
class PriorityScheduler : public Scheduler {
public:
    /**
     * Priority Scheduler Constructor
     */
    PriorityScheduler();

    /**
     * Priority Scheduling Algorithm Implementation
     * Always selects highest priority process from ready queue
     */
    void schedule() override;
};

#endif
