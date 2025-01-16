#include <stdio.h>
#include <stdbool.h>

#define MAX 100

// Function to check if a page exists in the frame
bool isPageInFrame(int frame[], int capacity, int page) {
    for (int i = 0; i < capacity; i++) {
        if (frame[i] == page) {
            return true;
        }
    }
    return false;
}

// Function to find the optimal page to replace
int findOptimalPageIndex(int frame[], int capacity, int pages[], int n, int currentIndex) {
    int farthest = currentIndex, replaceIndex = -1;

    for (int i = 0; i < capacity; i++) {
        int j;
        for (j = currentIndex; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    replaceIndex = i;
                }
                break;
            }
        }

        // If a page is not going to be used in the future, replace it
        if (j == n) {
            return i;
        }
    }

    // If all pages are in future, return the farthest used
    return (replaceIndex == -1) ? 0 : replaceIndex;
}

// Function to calculate page faults using Optimal Page Replacement Algorithm
int pageFaultsOptimal(int pages[], int n, int capacity) {
    int frame[MAX];
    int page_faults = 0;

    // Initialize the frame with -1 (empty)
    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        // Check if the current page is already in the frame
        if (!isPageInFrame(frame, capacity, pages[i])) {
            // Page fault occurs
            page_faults++;

            // If there is space in the frame, add the page
            if (i < capacity) {
                frame[i] = pages[i];
            } else {
                // Find the optimal page to replace
                int replaceIndex = findOptimalPageIndex(frame, capacity, pages, n, i + 1);
                frame[replaceIndex] = pages[i];
            }
        }
    }

    return page_faults;
}

// Driver code
int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 4;

    printf("Total Page Faults (Optimal): %d\n", pageFaultsOptimal(pages, n, capacity));
    return 0;
}
