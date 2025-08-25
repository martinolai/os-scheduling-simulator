# OS Scheduling Simulator  

A **C++ simulator** for classic CPU scheduling algorithms, useful for learning, experimentation, and analysis of operating system concepts.  

---

## ✨ Features  
- **First-Come, First-Served (FCFS)**  
- **Shortest Job First (SJF)**  
- **Round Robin (RR)** with configurable time quantum  
- **Priority Scheduling** (non-preemptive)  
- Extendable base `Scheduler` class for adding new algorithms  

---

## 📂 Project Structure  
os-scheduling-simulator/
├── include/
│ ├── FCFScheduler.h
│ ├── PriorityScheduler.h
│ ├── Process.h
│ ├── RoundRobinScheduler.h
│ ├── SJFScheduler.h
│ └── Scheduler.h
├── src/
│ ├── FCFScheduler.cpp
│ ├── PriorityScheduler.cpp
│ ├── Process.cpp
│ ├── RoundRobinScheduler.cpp
│ ├── SJFScheduler.cpp
│ ├── Scheduler.cpp
│ └── main.cpp
└── README.md

- `include/` → all **header files** (class definitions, interfaces)  
- `src/` → all **implementations** + `main.cpp` entry point  

---

## ⚙️ Build Instructions  

### 🔹 Compile with g++  
```bash
g++ src/*.cpp -I include -o scheduling_simulator
./scheduling_simulator
🔹 Build with CMake (recommended)
mkdir build && cd build
cmake ..
make
./scheduling_simulator

---

### 🚀 Usage

After running the program, you can:

- **Define processes (arrival time, burst time, priority).**

- **Choose a scheduling algorithm (FCFS, SJF, RR, Priority).**

- **View execution order and performance metrics.**
