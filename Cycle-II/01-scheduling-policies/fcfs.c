#include <stdio.h>

int main() {
    int n;
    int pid[100], at[100], bt[100];
    int ct[100], wt[100], tat[100];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Process %d Arrival Time: ", pid[i]);
        scanf("%d", &at[i]);
        printf("Process %d Burst Time: ", pid[i]);
        scanf("%d", &bt[i]);
    }

    // Sort by arrival time (stable sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[j] < at[i]) {
                int temp;
                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = pid[i]; pid[i] = pid[j]; pid[j] = temp;
            }
        }
    }

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < at[i]) {
            current_time = at[i]; // CPU idle until process arrives
        }
        current_time += bt[i];
        ct[i] = current_time;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
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
