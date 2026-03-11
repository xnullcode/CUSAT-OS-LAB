#include <stdio.h>

int main() {
    int n, r, i, j, k;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    scanf("%d", &r);

    int alloc[n][r];
    int max[n][r];
    int avail[r];
    int need[n][r];
    int f[n], ans[n], ind = 0;

    for (k = 0; k < n; k++) {
        f[k] = 0;
    }

    printf("Enter the Allocation Matrix (%d x %d):\n", n, r);
    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the MAX Matrix (%d x %d):\n", n, r);
    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Available Resources (%d values):\n", r);
    for (j = 0; j < r; j++) {
        scanf("%d", &avail[j]);
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int y = 0;
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < r; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < r; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    int isSafe = 1;
    for(int i = 0; i < n; i++) {
        if(f[i] == 0) {
            isSafe = 0;
            printf("\nThe system is NOT in a safe state. Deadlock imminent.\n");
            break;
        }
    }

    if(isSafe == 1) {
        printf("\nThe SAFE Sequence is as follows:\n");
        for (i = 0; i < n - 1; i++) {
            printf(" P%d ->", ans[i]);
        }
        printf(" P%d\n", ans[n - 1]);
    }

    return 0;
}
