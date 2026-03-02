# Deadlock Prevention and Avoidance

Programs to implement deadlock prevention and avoidance strategies.

## Topics
- Deadlock conditions
- Deadlock prevention
- Deadlock avoidance: Banker's Algorithm
- Deadlock detection and recovery

## Files
| File | Description |
|------|-------------|
| [dining_philosopher.c](./dining_philosopher.c) | Demonstrates synchronization of the Dining Philosophers problem using semaphores with multiple threads |

## Viva Questions and Answers

**1. What is a deadlock? Give a real-world analogy.**
A deadlock is a situation where a set of processes are blocked indefinitely because each process is holding a resource and waiting for a resource held by another process in the set. A real-world analogy is a traffic gridlock, where cars at an intersection each block the path of the next car, and none can move forward.

**2. What are the four necessary conditions for a deadlock to occur (Coffman conditions)?**
The four conditions are: Mutual Exclusion (at least one resource must be non-shareable), Hold and Wait (a process holds at least one resource and waits for more), No Preemption (resources cannot be forcibly taken from a process), and Circular Wait (a circular chain of processes exists where each waits for a resource held by the next).

**3. What is the difference between deadlock prevention, deadlock avoidance, and deadlock detection?**
Deadlock prevention eliminates one of the four Coffman conditions so a deadlock can never occur. Deadlock avoidance allows resource requests dynamically but uses algorithms like Banker's Algorithm to ensure the system never enters an unsafe state. Deadlock detection allows deadlocks to occur but periodically checks for them and recovers by aborting or preempting processes.

**4. Explain the Banker's Algorithm for deadlock avoidance.**
The Banker's Algorithm checks whether granting a resource request will leave the system in a safe state. It maintains data structures for maximum demand, current allocation, remaining need, and available resources. When a process requests resources, the algorithm tentatively allocates them and checks if a safe sequence of process execution exists. If yes, the request is granted; otherwise, the process waits.

**5. What is a safe state? How is it used in deadlock avoidance?**
A safe state is one in which there exists at least one safe sequence — an ordering of all processes such that each process can obtain all required resources, execute, and release them, allowing the next process in the sequence to proceed. Deadlock avoidance algorithms ensure the system always remains in a safe state by rejecting requests that would lead to an unsafe state.

**6. What is a resource allocation graph? How can it be used to detect deadlocks?**
A resource allocation graph (RAG) is a directed graph where nodes represent processes and resources, with edges showing assignments (resource to process) and requests (process to resource). A deadlock exists if and only if the RAG contains a cycle. For multi-instance resources, a cycle does not guarantee a deadlock; a more detailed analysis is required.

**7. How does deadlock prevention work by negating each of the four Coffman conditions?**
Mutual exclusion can be eliminated by making resources shareable (not always possible). Hold and Wait can be prevented by requiring processes to request all resources at once before starting. No Preemption can be addressed by allowing the OS to preempt resources from waiting processes. Circular wait can be prevented by imposing a total ordering on resource types and requiring processes to request resources in that order.

**8. What is circular wait and how can it be prevented?**
Circular wait is a condition where process P1 waits for a resource held by P2, P2 waits for a resource held by P3, and so on, with the last process waiting for a resource held by P1. It can be prevented by assigning a numerical order to all resource types and requiring that processes always request resources in increasing order of their assigned numbers.

**9. What is the difference between a deadlock and starvation?**
In a deadlock, a set of processes are all blocked and none can proceed, regardless of what happens in the rest of the system. In starvation, a process is indefinitely delayed but the system itself is not blocked — other processes continue to run. Starvation can be resolved (e.g., using aging), while a deadlock requires explicit intervention such as process termination or resource preemption.

**10. What is preemption in the context of deadlock recovery?**
Preemption in deadlock recovery involves forcibly taking resources away from one or more processes to break the deadlock cycle. The preempted process is rolled back to a safe state (checkpoint) and restarted later. The challenge is selecting which process to preempt and ensuring that the same process is not always chosen, which could cause starvation.

**11. How does the program semaphores.c in this directory demonstrate mutual exclusion?**
In semaphores.c, a semaphore sem_p is initialized to 1. Each of the three threads calls sem_wait before accessing the shared variable x and sem_post after modifying it. This ensures that only one thread can read or write x at a time, demonstrating mutual exclusion and preventing race conditions on the shared variable.

**12. Why is sem_wait and sem_post used around the shared variable x in the program?**
The variable x is shared among three threads and is subject to concurrent modification, which can cause a race condition. sem_wait acquires the semaphore (locking access), ensuring only one thread enters the critical section at a time. sem_post releases the semaphore after the modification, allowing the next waiting thread to proceed.

**13. What would happen if the sem_wait and sem_post calls were removed from the program?**
Without sem_wait and sem_post, all three threads could access and modify x simultaneously. This would introduce a race condition where reads and writes interleave unpredictably, producing incorrect and non-deterministic final values of x. The program's output would vary between runs and the integrity of the shared data would not be guaranteed.

**14. What is a livelock? How does it differ from a deadlock?**
A livelock is a situation where two or more processes continuously change their state in response to each other without making any progress — they are not blocked but are stuck in a loop of reactions. Unlike a deadlock where processes are completely blocked, in a livelock processes are active but unable to complete their work.

**15. What is the difference between pthread_mutex_lock and sem_wait?**
Both are used for synchronization, but pthread_mutex_lock is a mutex operation where only the thread that locked the mutex can unlock it, enforcing ownership. sem_wait is a semaphore operation that can be signaled by any thread, making it suitable for signaling scenarios as well as mutual exclusion. Mutexes are preferred for protecting critical sections within a single thread's scope, while semaphores are more flexible for inter-thread or inter-process signaling.
