#include "Process.h"
#include <sstream>
#include <string>
using namespace std;

Process::Process(int id, int burst, int arrival)
    : pid(id), burstTime(burst), arrivalTime(arrival) {}

int Process::getPid() const { return pid; }
int Process::getBurstTime() const { return burstTime; }
int Process::getArrivalTime() const { return arrivalTime; }

string Process::toString() const {
    std::ostringstream oss;
    oss << "PID: " << pid
        << " | Burst: " << burstTime
        << " | Arrival: " << arrivalTime;
    return oss.str();
}
