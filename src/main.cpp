#include <iostream>
#include "Process.h"
using namespace std;

int main() {
    // Create processes
    Process p1("Browser", 0, 5, Priority::HIGH);
    Process p2("TextEditor", 2, 3, Priority::MEDIUM);
    
    // Use the processes
    p1.printStatus();
    cout << p1.getProcessInfo() << endl;
    
    return 0;
}
