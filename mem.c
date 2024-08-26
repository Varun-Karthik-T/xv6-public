#include "types.h"
#include "user.h"

#define MAX 100

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n], i, j;

    for (i = 0; i < n; i++)
        allocation[i] = -1;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
           }
        }
    }

    printf(1, "\nProcess Number\t\tProcess_Size\t\t\tBlock number\n");
    printf(1,"----------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf(1, " %d \t\t\t %d \t\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf(1, "%d\n", allocation[i] + 1);
        else
            printf(1, "Not Allocated\n");
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n], i, j;

    for (i = 0; i < n; i++)
        allocation[i] = -1;

    for (i = 0; i < n; i++) {
        int bestIdx = -1;
        for (j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1)
                    bestIdx = j;
                else if (blockSize[bestIdx] > blockSize[j])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

     printf(1, "\nProcess Number\t\tProcess_Size\t\t\tBlock number\n");
    printf(1,"----------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf(1, " %d \t\t\t %d \t\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf(1, "%d\n", allocation[i] + 1);
        else
            printf(1, "Not Allocated\n");
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n], i, j;

    for (i = 0; i < n; i++)
        allocation[i] = -1;

    for (i = 0; i < n; i++) {
        int wstIdx = -1;
        for (j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (wstIdx == -1)
                    wstIdx = j;
                else if (blockSize[wstIdx] < blockSize[j])
                    wstIdx = j;
            }
        }

        if (wstIdx != -1) {
            allocation[i] = wstIdx;
            blockSize[wstIdx] -= processSize[i];
        }
    }

    printf(1, "\nProcess Number\t\tProcess_Size\t\t\tBlock number\n");
    printf(1,"----------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf(1, " %d \t\t\t %d \t\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf(1, "%d\n", allocation[i] + 1);
        else
            printf(1, "Not Allocated\n");
    }
}

int main(int argc, char *argv[]) {
    int blockSize[] = {50, 300, 150, 200, 400};
    int processSize[] = {120, 240, 180, 300};
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    printf(1, "First Fit:\n");
    firstFit(blockSize, m, processSize, n);

    printf(1, "\nBest Fit:\n");
    bestFit(blockSize, m, processSize, n);

    printf(1, "\nWorst Fit:\n");
    worstFit(blockSize, m, processSize, n);

    exit();
}