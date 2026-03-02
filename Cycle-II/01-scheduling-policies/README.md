# Scheduling Policies

Programs to study and analyze various CPU scheduling policies.

## Algorithms Covered
- First Come First Served (FCFS)
- Shortest Job First (SJF)
- Round Robin (RR)
- Priority Scheduling

## Files
| File | Description |
|------|-------------|
|      |             |

## Viva Questions and Answers

**1. What is CPU scheduling? Why is it necessary in an operating system?**
CPU scheduling is the process by which the OS decides which process in the ready queue should be given the CPU next. It is necessary because multiple processes compete for the CPU, and scheduling ensures efficient CPU utilization, fairness, responsiveness, and throughput.

**2. What is the difference between preemptive and non-preemptive scheduling?**
In preemptive scheduling, the CPU can be taken away from a running process and given to another (e.g., when a higher-priority process arrives or a time quantum expires). In non-preemptive scheduling, once a process starts executing, it runs to completion or until it voluntarily releases the CPU (e.g., FCFS and non-preemptive SJF).

**3. Explain the FCFS scheduling algorithm. What is its major drawback?**
FCFS (First Come First Served) schedules processes in the order they arrive in the ready queue. It is non-preemptive and simple to implement. Its major drawback is the convoy effect, where shorter processes get stuck waiting behind a long process, leading to high average waiting times.

**4. What is the convoy effect in FCFS scheduling?**
The convoy effect occurs when a long CPU-bound process holds the CPU while shorter processes queue up behind it. These shorter processes experience long waiting times even though they require very little CPU time. This results in poor CPU and I/O device utilization overall.

**5. Explain the Shortest Job First (SJF) algorithm. How does it differ from Shortest Remaining Time First (SRTF)?**
SJF selects the process with the smallest burst time from the ready queue. It can be non-preemptive (runs to completion once started) or preemptive. The preemptive version is called SRTF (Shortest Remaining Time First), where if a new process arrives with a shorter remaining time than the currently running process, the CPU is preempted and given to the new process.

**6. What is starvation? Which scheduling algorithm can cause starvation and how can it be prevented?**
Starvation is a condition where a process waits indefinitely because higher-priority or shorter processes keep arriving and getting scheduled first. SJF and Priority Scheduling can cause starvation. It can be prevented using aging — a technique where the priority of a waiting process is gradually increased over time so it eventually gets scheduled.

**7. Explain Round Robin scheduling. How does the time quantum affect its performance?**
Round Robin assigns each process a fixed time slice (quantum) in a cyclic order. If a process does not finish within its quantum, it is preempted and placed at the back of the ready queue. A small quantum increases context switch overhead and reduces efficiency. A very large quantum degrades to FCFS behavior. An optimal quantum balances responsiveness and overhead.

**8. What happens if the time quantum in Round Robin is set too large or too small?**
If the quantum is too large, Round Robin behaves like FCFS, causing long waiting times for short processes. If the quantum is too small, too many context switches occur, consuming significant CPU time for overhead rather than actual process execution, degrading overall performance.

**9. What is Priority Scheduling? How are ties in priority resolved?**
Priority Scheduling assigns each process a priority number, and the CPU is allocated to the process with the highest priority (lowest number in some conventions). It can be preemptive or non-preemptive. Ties in priority are typically resolved using FCFS ordering among processes with the same priority.

**10. What is the difference between arrival time, burst time, completion time, turnaround time, and waiting time?**
Arrival time is when a process enters the ready queue. Burst time is the CPU time required by the process. Completion time is when the process finishes execution. Turnaround time is Completion Time minus Arrival Time. Waiting time is Turnaround Time minus Burst Time — the total time a process spent waiting in the ready queue.

**11. How is the average waiting time calculated for a given scheduling algorithm?**
First compute the waiting time for each process: Waiting Time = Turnaround Time - Burst Time, where Turnaround Time = Completion Time - Arrival Time. Then sum the waiting times of all processes and divide by the total number of processes to get the average waiting time.

**12. What is the difference between long-term, medium-term, and short-term schedulers?**
The long-term (job) scheduler controls the degree of multiprogramming by deciding which jobs are admitted to the ready queue from the job pool. The short-term (CPU) scheduler decides which ready process gets the CPU next and runs very frequently. The medium-term scheduler handles swapping — moving processes in and out of memory to manage the degree of multiprogramming.

**13. What is a Gantt chart and how is it used to represent scheduling?**
A Gantt chart is a horizontal bar chart that shows the sequence and duration of process execution on the CPU over time. Each bar represents a process and its length represents the CPU time it occupies. It is used to visually trace the execution order of processes for a given scheduling algorithm and to calculate completion, turnaround, and waiting times.

**14. Which scheduling algorithm is considered optimal in minimizing average waiting time and why?**
SJF (Shortest Job First) is proven to be optimal for minimizing average waiting time among all non-preemptive scheduling algorithms. By always scheduling the shortest job next, longer delays for short jobs are avoided, resulting in the lowest possible average waiting time for a given set of processes.

**15. What is aging in the context of scheduling algorithms?**
Aging is a technique used to prevent starvation in priority-based scheduling. It gradually increases the priority of a process the longer it waits in the ready queue. This ensures that even low-priority processes will eventually have their priority raised high enough to be scheduled, preventing indefinite postponement.