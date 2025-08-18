#ifndef PROCESS_H
#define PROCESS_H

#include <string>
using namespace std;

class Process {
private:
    int pid;             // Process ID
    int burstTime;       // CPU burst time richiesto
    int arrivalTime;     // Tempo di arrivo
public:
    Process(int id, int burst, int arrival);

    int getPid() const;
    int getBurstTime() const;
    int getArrivalTime() const;

    string toString() const;
};

#endif
