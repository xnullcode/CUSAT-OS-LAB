# Page Replacement Algorithms

Programs to implement various page replacement algorithms.

## Algorithms Covered
- FIFO (First In First Out)
- LRU (Least Recently Used)
- Optimal Page Replacement

## Files
| File | Description |
|------|-------------|
| [pagee.c](./pagee.c) | LRU page replacement algorithm |

## Viva Questions and Answers

**1. What is a page fault? When does it occur?**
A page fault occurs when a process tries to access a page that is not currently loaded in physical memory (RAM). The OS must then load the required page from secondary storage (disk) into a free frame. If no frame is free, a page replacement algorithm is used to select a victim page to evict.

**2. What is demand paging? How does it differ from pre-paging?**
Demand paging loads pages into memory only when they are actually needed (on demand), resulting in fewer pages loaded initially and less memory usage. Pre-paging loads multiple pages into memory at once, anticipating future needs, which can reduce page faults but wastes memory if the anticipated pages are never used. Most modern OS implementations use demand paging.

**3. Explain the FIFO page replacement algorithm. What is Belady's anomaly?**
FIFO replaces the page that has been in memory the longest — the one that arrived first. It is simple to implement using a queue. Belady's anomaly is the counterintuitive observation that increasing the number of page frames can sometimes increase the number of page faults with FIFO. This anomaly does not occur in LRU or Optimal algorithms.

**4. What is Belady's anomaly? Which algorithms suffer from it?**
Belady's anomaly is the phenomenon where adding more page frames leads to more page faults rather than fewer. It is specific to certain replacement algorithms and arises because FIFO does not have the stack property. Only FIFO (and some other non-stack algorithms) suffer from this anomaly. LRU and Optimal algorithms are stack algorithms and are immune to Belady's anomaly.

**5. Explain the LRU (Least Recently Used) page replacement algorithm.**
LRU replaces the page that has not been used for the longest period of time. The idea is based on the principle of locality — pages used recently are likely to be used again soon. LRU is a good approximation of the Optimal algorithm and does not suffer from Belady's anomaly. However, it requires tracking the order of page accesses, which adds overhead.

**6. How is LRU implemented in the program pagee.c? What data structures are used?**
In pagee.c, LRU is implemented using two arrays: frames (which stores the pages currently in memory) and lastUsed (which stores the time index of the last access for each frame). On a page fault, the page in the frame with the smallest lastUsed value (least recently used) is replaced. The time index is updated on every access, whether a hit or a miss.

**7. What is the Optimal page replacement algorithm? Why is it not practically implementable?**
The Optimal algorithm replaces the page that will not be used for the longest time in the future. It produces the minimum number of page faults for any given reference string and frame count. It is not practically implementable because it requires future knowledge of the page reference string, which is not available at runtime. It is used as a theoretical benchmark to compare other algorithms.

**8. How do you calculate the number of page faults for a given reference string and frame count?**
Simulate the algorithm step by step. For each page reference, check if the page is already in a frame (a hit). If not, it is a page fault — load the page into a free frame if available, or apply the replacement algorithm to evict a page. Count the total number of page faults across the entire reference string.

**9. What is thrashing? How can it be prevented?**
Thrashing occurs when a process spends more time handling page faults than executing, because it does not have enough frames to hold its working set. The system becomes overloaded with paging activity. It can be prevented by using the working set model to ensure each process has enough frames for its current locality, or by load control — reducing the degree of multiprogramming when thrashing is detected.

**10. What is the difference between internal fragmentation and external fragmentation in the context of memory management?**
Internal fragmentation occurs when allocated memory is slightly larger than what is needed, wasting space within allocated blocks (common in paging). External fragmentation occurs when free memory is scattered in small, non-contiguous blocks that cannot satisfy a large request (common in segmentation and contiguous allocation). Paging eliminates external fragmentation but may introduce internal fragmentation.

**11. What is the working set model? How does it help in reducing page faults?**
The working set model defines the working set of a process as the set of pages it has referenced in the last delta (window) time units. By ensuring that each process has enough frames to hold its working set, the OS prevents thrashing. If the total working set size exceeds available memory, some processes are suspended to reduce the load.

**12. What is the difference between paging and segmentation?**
Paging divides memory into fixed-size blocks (pages and frames), eliminating external fragmentation but potentially causing internal fragmentation. Segmentation divides memory into variable-size logical segments based on program structure (code, stack, heap), which is more natural for the programmer but can cause external fragmentation. Modern systems often combine both using segmented paging.

**13. What is a page table? What information does a page table entry contain?**
A page table is a data structure maintained by the OS that maps virtual page numbers to physical frame numbers. Each page table entry (PTE) typically contains the frame number, a valid/invalid bit (indicating if the page is in memory), a dirty bit (indicating if the page has been modified), a reference bit (for replacement algorithms), and protection bits (read/write/execute permissions).

**14. How does the LRU algorithm compare to FIFO in terms of performance?**
LRU generally outperforms FIFO because it uses temporal locality — recently used pages are likely to be used again. FIFO ignores usage frequency and may evict heavily-used pages simply because they were loaded first. LRU does not suffer from Belady's anomaly while FIFO does. However, LRU has higher implementation overhead than FIFO.

**15. What is the clock (second chance) page replacement algorithm?**
The clock algorithm is an approximation of LRU that uses a circular list of frames and a reference bit per frame. When a page is accessed, its reference bit is set to 1. When replacement is needed, the algorithm scans frames in circular order; if a frame's reference bit is 1, it is cleared and the scan continues (giving it a second chance). The first frame with a reference bit of 0 is replaced. It is efficient and avoids the overhead of true LRU.