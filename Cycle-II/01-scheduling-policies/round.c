#include <stdio.h>

int queue[100], front = 0, rear = -1, queueSize = 0;

void enqueue(int val) {
    rear = (rear + 1) % 100;
    queue[rear] = val;
    queueSize++;
}

int dequeue() {
    int val = queue[front];
    front = (front + 1) % 100;
    queueSize--;
    return val;
}

int main() {
    int n, tq;
    int pid[100], at[100], bt[100], rbt[100];
    int ct[100], wt[100], tat[100];
    int enqueued[100] = {0};
    int current_time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Process %d Arrival Time: ", pid[i]);
        scanf("%d", &at[i]);
        printf("Process %d Burst Time: ", pid[i]);
        scanf("%d", &bt[i]);
        rbt[i] = bt[i];
        ct[i] = 0;
        wt[i] = 0;
        tat[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int first = 0;
    for (int i = 1; i < n; i++) {
        if (at[i] < at[first])
            first = i;
    }

    current_time = at[first];
    enqueue(first);
    enqueued[first] = 1;

    while (completed < n) {

        if (queueSize == 0) {
            int nextArrival = -1;
            for (int i = 0; i < n; i++) {
                if (at[i] > current_time && rbt[i] > 0) {
                    if (nextArrival == -1 || at[i] < at[nextArrival])
                        nextArrival = i;
                }
            }
            current_time = at[nextArrival];

            for (int i = 0; i < n; i++) {
                if (at[i] <= current_time && !enqueued[i] && rbt[i] > 0) {
                    enqueue(i);
                    enqueued[i] = 1;
                }
            }
            continue;
        }

        int p = dequeue();

        if (rbt[p] > tq) {
            rbt[p] = rbt[p] - tq;
            current_time = current_time + tq;
        } else {
            current_time = current_time + rbt[p];
            rbt[p] = 0;
            completed++;
            ct[p] = current_time;
            tat[p] = ct[p] - at[p];
            wt[p] = tat[p] - bt[p];
        }

        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && !enqueued[i] && rbt[i] > 0) {
                enqueue(i);
                enqueued[i] = 1;
            }
        }

        if (rbt[p] > 0) {
            enqueue(p);
        }
    }

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
