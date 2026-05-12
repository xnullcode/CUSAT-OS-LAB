#include <stdio.h>

int queue[100], front = 0, rear = -1, size = 0;
void enqueue(int v) { rear = (rear+1)%100; queue[rear] = v; size++; }
int dequeue() { int v = queue[front]; front = (front+1)%100; size--; return v; }

int main() {
    int n, tq;
    int at[100],pid[100], bt[100], rbt[100], ct[100], wt[100], tat[100], done[100] = {0};
    
    printf("Processes: "); scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter Pid:",pid[i]);
        scanf("%d",&pid[i]);
        printf("P-%d AT BT: ", pid[i]); 
        scanf("%d %d", &at[i], &bt[i]);
        rbt[i] = bt[i];
    }
    printf("Time Quantum: "); scanf("%d", &tq);

    // sort by arrival time (simple bubble sort)
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (at[j] > at[j+1]) {
                int t;
                t=pid[j];pid[j]=pid[j+1];pid[j+1]=t;
                t=at[j]; at[j]=at[j+1]; at[j+1]=t;
                t=bt[j]; bt[j]=bt[j+1]; bt[j+1]=t;
                t=rbt[j]; rbt[j]=rbt[j+1]; rbt[j+1]=t;
            }

    int enqueued[100] = {0};
    int current_time = at[0], completed = 0;
    enqueue(0); enqueued[0] = 1;

    while (completed < n) {
        int p = dequeue();

        if (rbt[p] > tq) {
            rbt[p] -= tq;
            current_time += tq;
        } else {
            current_time += rbt[p];
            rbt[p] = 0;
            completed++;
            ct[p] = current_time;
            tat[p] = ct[p] - at[p];
            wt[p] = tat[p] - bt[p];
            done[p] = 1;
        }

        // enqueue newly arrived
        for (int i = 0; i < n; i++)
            if (!enqueued[i] && at[i] <= current_time && rbt[i] > 0) {
                enqueue(i); enqueued[i] = 1;
            }

        // re-enqueue current if unfinished
        if (rbt[p] > 0) enqueue(p);

        // if queue empty, jump to next arrival
        if (size == 0) {
            for (int i = 0; i < n; i++)
                if (!done[i] && rbt[i] > 0) {
                    current_time = at[i];
                    enqueue(i); enqueued[i] = 1;
                    break;
                }
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);

    return 0;
}
