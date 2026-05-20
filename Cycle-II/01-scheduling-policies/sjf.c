#include <stdio.h>

int main() {
    int n;
    int at[100], pid[100], bt[100], wt[100], tat[100], done[100] = {0};

    printf("Processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter Pid: ");
        scanf("%d", &pid[i]);
        printf("P-%d AT BT: ", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);
    }

    int current_time = 0, completed = 0;

    while (completed < n) {
        int shortest = -1;

        // Pick the arrived process with the smallest burst time
        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && !done[i]) {
                if (shortest == -1 || bt[i] < bt[shortest])
                    shortest = i;
            }
        }

        if (shortest != -1) {
            // Run it to completion
            current_time += bt[shortest];
            tat[shortest] = current_time - at[shortest];
            wt[shortest]  = tat[shortest] - bt[shortest];
            done[shortest] = 1;
            completed++;
        } else {
            // CPU idle — jump to the next arrival
            int next = 999999;
            for (int i = 0; i < n; i++)
                if (!done[i] && at[i] < next)
                    next = at[i];
            current_time = next;
        }
    }

    float total_wt = 0, total_tat = 0;
    printf("\nPID\tAT\tBT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        total_tat += tat[i];
        total_wt  += wt[i];
        printf("P%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
    printf("Average Waiting Time    = %.2f\n", total_wt  / n);
    return 0;
}
