#include <iostream>
#include "Process.h"

using namespace std;

enum class ProcessState { NEW, READY, RUNNING, WAITING, TERMINATED };
enum class Priority { HIGH = 1, MEDIUM = 2, LOW = 3 };

int main() {
    Process p1(1, 5, 0);  // pid=1, burst=5, arrival=0
    Process p2(2, 3, 2);  // pid=2, burst=3, arrival=2

    cout << p1.toString() << endl;
    cout << p2.toString() << endl;

    return 0;
}
