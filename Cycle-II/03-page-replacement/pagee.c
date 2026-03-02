	#include <stdio.h>
	int pageFaults(int pages[], int n, int capacity) {
	    int frames[100];
	    int lastUsed[100];
	    int faults = 0;
	    for (int i = 0; i < capacity; i++) {
		frames[i] = -1;
		lastUsed[i] = -1;
	    }
	    for (int i = 0; i < n; i++) {
		int page = pages[i];
		int found = 0;
		for (int j = 0; j < capacity; j++) {
		    if (frames[j] == page) {
		        found = 1;
		        lastUsed[j] = i;
		        break;
		    }
		}
	     if (!found) {
		    int lruIndex = 0;
		    for (int j = 0; j < capacity; j++) {
		        if (frames[j] == -1) {
		            lruIndex = j;
		            break;
		        }
		        if (lastUsed[j] < lastUsed[lruIndex]) {
		            lruIndex = j;
		        }
		    }
		    frames[lruIndex] = page;
		    lastUsed[lruIndex] = i;
		    faults++;
		}
	    }
	    return faults;
	}
	int main() {
	    int capacity, n;
	    int pages[100];
	    printf("Enter number of frames (capacity): ");
	    scanf("%d", &capacity);
	    printf("Enter number of page references: ");
	    scanf("%d", &n);
	    printf("Enter the %d page references:\n", n);
	    for (int i = 0; i < n; i++) {
		scanf("%d", &pages[i]);
	    }

	    int result = pageFaults(pages, n, capacity);
	    printf("Page faults: %d\n", result);

	    return 0;
	}
