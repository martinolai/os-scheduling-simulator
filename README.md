# OS Scheduling Simulator

A **C++** simulator of classic CPU scheduling algorithms. It demonstrates process control blocks (PCB), ready queues, execution traces, and performance metrics (waiting, turnaround, response time).

## ✨ Features

* **First-Come, First-Served (FCFS)**
* **Shortest Job First (SJF)** (non-preemptive)
* **Round Robin (RR)** with configurable time quantum
* **Priority Scheduling** (non-preemptive)
* Clear OOP design with a reusable `Scheduler` base class

## 📂 Project Structure

```text
os-scheduling-simulator/
├── include/
│   ├── FCFScheduler.h
│   ├── PriorityScheduler.h
│   ├── Process.h
│   ├── RoundRobinScheduler.h
│   ├── SJFScheduler.h
│   └── Scheduler.h
├── src/
│   ├── FCFScheduler.cpp
│   ├── PriorityScheduler.cpp
│   ├── Process.cpp
│   ├── RoundRobinScheduler.cpp
│   ├── SJFScheduler.cpp
│   ├── Scheduler.cpp
│   └── main.cpp
└── README.md
```

* `include/` → public headers (interfaces and class declarations)
* `src/` → implementations and `main.cpp` (program entry point)

## 🔧 Requirements

* C++17 (or newer) compiler: **g++**, **clang++**, or **MSVC**
* (Optional) **CMake** for an out-of-source build

## ⚙️ Build Instructions

### Compile with g++

```bash
g++ -std=c++17 -O2 -I include src/*.cpp -o scheduling_simulator
./scheduling_simulator
```

### Build with CMake (recommended)

```bash
mkdir build
cd build
cmake ..
make
./scheduling_simulator
```

## 🚀 Usage

The default `main.cpp` runs a **demonstration** that:
* creates a small set of sample processes,
* runs **FCFS**, **SJF**, **Round Robin**, and **Priority** on the same set,
* prints an execution trace and a table with per-process metrics and averages,
* pauses between algorithms (press **Enter** to continue).

**Change Round Robin quantum:** edit the constructor call in `main.cpp` `RoundRobinScheduler rr(/* quantum = */ 3);`

## 📖 Example Output

```text
=== FCFS Scheduling Execution ===
Time 0: Process P1 started
Time 8: Process P1 completed
Time 8: Process P2 started
...

=== FCFS Scheduling Results ===
  PID        Name  Arrival   Burst   Start   Waiting   Turnaround   Response
---------------------------------------------------------------------------
    1          P1        0       8       0         0            8         0
    2          P2        1       4       8         7           11         7
...
Average Waiting Time: 4.20
Average Turnaround Time: 10.60
Average Response Time: 3.80
```

## 🧩 How to Extend

1. **Create a new scheduler**
   * Add `MyScheduler.h` to `include/` inheriting from `Scheduler`.
   * Add `MyScheduler.cpp` to `src/` and implement `schedule()`.
2. **Register it in** `main.cpp`
   * Instantiate your scheduler and add it to the demo list.
3. **(Optional) Add tests / input parsing**
   * Replace the hardcoded sample set with CLI or file input.

## 🎯 Learning Goals

* Practice **OS scheduling** concepts by simulation
* Strengthen **C++ OOP** and **STL** skills
* Compare algorithms on identical workloads

## 🤝 Contributing

Issues and PRs are welcome! Ideas:
* Preemptive SJF (SRTF), Multilevel Feedback Queue
* Gantt chart printing
* CLI arguments for process lists and quantum

## 📜 License

This project is licensed under the **MIT License**.
