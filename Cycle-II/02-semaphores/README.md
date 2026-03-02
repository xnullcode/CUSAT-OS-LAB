# Semaphores

Programs to study the uses of semaphores for process synchronization.

## Topics
- Binary semaphores
- Counting semaphores
- Producer-Consumer problem
- Reader-Writer problem

## Files
| File | Description |
|------|-------------|
|[semaphores.c](./semaphores.c) | Demonstrates mutual exclusion using semaphores with multiple threads |

## Viva Questions and Answers

**1. What is a semaphore? How does it differ from a mutex?**
A semaphore is an integer variable used for process synchronization, accessed only through two atomic operations: wait (sem_wait / P) and signal (sem_post / V). A mutex is a locking mechanism where only the thread that acquired the lock can release it, enforcing ownership. A semaphore has no such ownership constraint and can be signaled by any thread, making it suitable for both mutual exclusion and signaling.

**2. What are the two atomic operations performed on a semaphore? Explain each.**
The two atomic operations are wait (P / sem_wait) and signal (V / sem_post). Wait decrements the semaphore value; if the value becomes negative, the calling process is blocked. Signal increments the semaphore value; if there are blocked processes waiting, one of them is unblocked. Both operations are atomic, meaning they cannot be interrupted mid-execution.

**3. What is the difference between a binary semaphore and a counting semaphore?**
A binary semaphore has only two values: 0 and 1. It is used to implement mutual exclusion, similar to a mutex. A counting semaphore can take any non-negative integer value and is used to control access to a resource pool with multiple instances, such as limiting the number of concurrent threads accessing a shared resource.

**4. What is the critical section problem? What are the three conditions required for a valid solution?**
The critical section problem involves ensuring that when multiple processes share data, only one process executes in its critical section at a time. A valid solution must satisfy: Mutual Exclusion (only one process in the critical section at a time), Progress (if no process is in the critical section, one of the waiting processes must be allowed to enter), and Bounded Waiting (a process must not wait indefinitely to enter its critical section).

**5. How does a semaphore solve the critical section problem?**
A semaphore initialized to 1 acts as a lock. Before entering the critical section, a process calls sem_wait, which decrements the semaphore. If the value is 0 or less, the process blocks. After leaving the critical section, the process calls sem_post, incrementing the semaphore and waking a waiting process if any. This ensures only one process is in the critical section at a time, satisfying mutual exclusion.

**6. What is the Producer-Consumer problem? How is it solved using semaphores?**
The Producer-Consumer problem involves a producer generating data and placing it in a shared buffer and a consumer removing it. The challenge is to prevent the producer from adding to a full buffer and the consumer from removing from an empty buffer. It is solved using three semaphores: mutex (for mutual exclusion on the buffer), empty (counts empty slots), and full (counts filled slots). The producer waits on empty and signals full; the consumer waits on full and signals empty.

**7. What is a race condition? Give an example.**
A race condition occurs when the outcome of a program depends on the relative timing of operations by multiple threads or processes on shared data. For example, if two threads both read a variable x (value 5), both increment it, and both write back the result, both may write 6 instead of the correct value 7, because neither thread saw the other's update.

**8. What is the purpose of sem_init, sem_wait, sem_post, and sem_destroy in C?**
sem_init initializes a semaphore with a given value and specifies whether it is shared between threads or processes. sem_wait decrements the semaphore and blocks the thread if the value is zero. sem_post increments the semaphore and unblocks a waiting thread. sem_destroy deallocates the resources associated with the semaphore after it is no longer needed.

**9. What is a deadlock? Can semaphores cause deadlocks? Give an example.**
A deadlock is a situation where two or more processes wait indefinitely for each other to release resources. Yes, semaphores can cause deadlocks. For example, if process A acquires semaphore S1 and waits for S2, while process B acquires S2 and waits for S1, both are blocked indefinitely in a circular wait.

**10. What is the difference between busy waiting and blocking in the context of synchronization?**
In busy waiting (spinlock), a process repeatedly checks a condition in a loop, consuming CPU cycles while waiting. In blocking, the process is suspended and placed in a waiting queue, freeing the CPU for other processes. Blocking is more efficient for longer waits, while busy waiting can be faster for very short critical sections on multi-core systems.

**11. What is the Reader-Writer problem? How is it solved using semaphores?**
The Reader-Writer problem involves multiple readers and writers sharing a resource. Multiple readers can read simultaneously, but a writer needs exclusive access. It is solved using a mutex semaphore for mutual exclusion on the reader count and a write semaphore that is acquired exclusively by writers and by the first reader (and released by the last reader), ensuring writers get exclusive access while allowing concurrent reads.

**12. What is a mutex lock? When would you prefer a mutex over a semaphore?**
A mutex (mutual exclusion lock) is a binary lock where only the owning thread can unlock it. You would prefer a mutex when protecting a critical section within a single thread's execution context, ensuring that the thread that locked it is the one that unlocks it. This prevents errors from accidental unlocking by another thread, which is possible with semaphores.

**13. Explain the use of pthread_create and pthread_join in a multithreaded program.**
pthread_create creates a new thread and starts its execution at a specified function, passing optional arguments. pthread_join blocks the calling thread until the specified thread terminates, ensuring the main program does not exit before threads complete. Together they are used to launch concurrent threads and wait for their completion before proceeding.

**14. What is the significance of the second argument (pshared) in sem_init?**
The pshared argument in sem_init specifies the scope of the semaphore. If pshared is 0, the semaphore is shared between threads of the same process. If pshared is non-zero, the semaphore is shared between processes, and it must be placed in a region of shared memory. In most lab programs, pshared is 0 since the semaphore is used for inter-thread synchronization within a single process.

**15. What is priority inversion and how does it relate to semaphore usage?**
Priority inversion occurs when a high-priority process is waiting for a semaphore held by a low-priority process, and a medium-priority process preempts the low-priority process, indirectly blocking the high-priority one. This is a known problem with semaphore-based synchronization. It can be addressed using the priority inheritance protocol, where the low-priority process temporarily inherits the priority of the high-priority process waiting on the semaphore.
