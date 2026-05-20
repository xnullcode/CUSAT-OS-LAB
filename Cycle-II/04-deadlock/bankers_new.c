#include <stdio.h>

int main() {
    int n, r;
    printf("Enter the number of processes: "); scanf("%d", &n);
    printf("Enter the number of resources: "); scanf("%d", &r);

    int alloc[n][r], max[n][r], avail[r], need[n][r];
    int finished[n], safe_seq[n], safe_count = 0;

    for (int i = 0; i < n; i++) finished[i] = 0;

    printf("Enter the Allocation Matrix (%d x %d):\n", n, r);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter the MAX Matrix (%d x %d):\n", n, r);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &max[i][j]);

    printf("Enter the Available Resources (%d values):\n", r);
    for (int j = 0; j < r; j++)
        scanf("%d", &avail[j]);

    // Calculate need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Banker's Algorithm: repeat until no progress in a full pass
    int progress = 1;
    while (progress) {
        progress = 0;
        for (int i = 0; i < n; i++) {
            if (finished[i]) continue;

            // Check if need[i] <= avail for all resources
            int can_run = 1;
            for (int j = 0; j < r; j++)
                if (need[i][j] > avail[j]) { can_run = 0; break; }

            if (can_run) {
                for (int j = 0; j < r; j++)
                    avail[j] += alloc[i][j];   // release resources
                finished[i] = 1;
                safe_seq[safe_count++] = i;
                progress = 1;
            }
        }
    }

    if (safe_count == n) {
        printf("\nSafe sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d%s", safe_seq[i], i < n-1 ? " -> " : "\n");
    } else {
        printf("\nNot in a safe state — deadlock imminent.\n");
    }

    return 0;
}
