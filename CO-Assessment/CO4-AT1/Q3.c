#include <stdio.h>

#define MAX_REQUESTS 100

void printSequence(const int sequence[], int count)
{
    int i;

    for (i = 0; i < count; i++) {
        printf("%d", sequence[i]);

        if (i < count - 1)
            printf(" -> ");
    }

    printf("\n");
}

int absoluteDifference(int a, int b)
{
    return (a > b) ? (a - b) : (b - a);
}

int fcfs(int requests[], int n, int head, int sequence[])
{
    int i, totalSeek = 0, current = head;

    for (i = 0; i < n; i++) {
        totalSeek += absoluteDifference(current, requests[i]);
        sequence[i] = requests[i];
        current = requests[i];
    }

    return totalSeek;
}

int sstf(int requests[], int n, int head, int sequence[])
{
    int visited[MAX_REQUESTS] = {0};
    int current = head, totalSeek = 0;
    int i, j, shortestDistance, selected;

    for (i = 0; i < n; i++) {
        shortestDistance = 1000000;
        selected = -1;

        for (j = 0; j < n; j++) {
            if (!visited[j] &&
                absoluteDifference(current, requests[j]) < shortestDistance) {
                shortestDistance = absoluteDifference(current, requests[j]);
                selected = j;
            }
        }

        visited[selected] = 1;
        sequence[i] = requests[selected];
        totalSeek += absoluteDifference(current, requests[selected]);
        current = requests[selected];
    }

    return totalSeek;
}

void sortRequests(int requests[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

int scan(int requests[], int n, int head, int diskSize, int direction,
         int sequence[], int *sequenceCount)
{
    int sorted[MAX_REQUESTS];
    int i, split = 0, count = 0;
    int current = head, totalSeek = 0;

    for (i = 0; i < n; i++)
        sorted[i] = requests[i];

    sortRequests(sorted, n);

    /* First request positioned at or to the right of the initial head */
    while (split < n && sorted[split] < head)
        split++;

    if (direction == 1) {
        /* Move right, then to disk end, then reverse left */
        for (i = split; i < n; i++) {
            totalSeek += absoluteDifference(current, sorted[i]);
            current = sorted[i];
            sequence[count++] = current;
        }

        if (split > 0) {
            totalSeek += absoluteDifference(current, diskSize - 1);
            current = diskSize - 1;
        }

        for (i = split - 1; i >= 0; i--) {
            totalSeek += absoluteDifference(current, sorted[i]);
            current = sorted[i];
            sequence[count++] = current;
        }
    } else {
        /* Move left, then to disk start, then reverse right */
        for (i = split - 1; i >= 0; i--) {
            totalSeek += absoluteDifference(current, sorted[i]);
            current = sorted[i];
            sequence[count++] = current;
        }

        if (split < n) {
            totalSeek += absoluteDifference(current, 0);
            current = 0;
        }

        for (i = split; i < n; i++) {
            totalSeek += absoluteDifference(current, sorted[i]);
            current = sorted[i];
            sequence[count++] = current;
        }
    }

    *sequenceCount = count;
    return totalSeek;
}

int main(void)
{
    int diskSize, numberOfRequests, head, direction;
    int requests[MAX_REQUESTS];
    int fcfsSequence[MAX_REQUESTS];
    int sstfSequence[MAX_REQUESTS];
    int scanSequence[MAX_REQUESTS];
    int fcfsSeek, sstfSeek, scanSeek, scanCount;
    int i, bestSeek;

    printf("Enter disk size (number of cylinders): ");
    scanf("%d", &diskSize);

    printf("Enter number of disk requests (maximum %d): ", MAX_REQUESTS);
    scanf("%d", &numberOfRequests);

    if (diskSize < 1 || numberOfRequests < 1 ||
        numberOfRequests > MAX_REQUESTS) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter request queue:\n");

    for (i = 0; i < numberOfRequests; i++) {
        scanf("%d", &requests[i]);

        if (requests[i] < 0 || requests[i] >= diskSize) {
            printf("Invalid request: %d\n", requests[i]);
            return 1;
        }
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    if (head < 0 || head >= diskSize) {
        printf("Invalid head position.\n");
        return 1;
    }

    printf("Enter SCAN direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    if (direction != 0 && direction != 1) {
        printf("Invalid direction.\n");
        return 1;
    }

    fcfsSeek = fcfs(requests, numberOfRequests, head, fcfsSequence);
    sstfSeek = sstf(requests, numberOfRequests, head, sstfSequence);
    scanSeek = scan(requests, numberOfRequests, head, diskSize, direction,
                    scanSequence, &scanCount);

    printf("\n--- FCFS Disk Scheduling ---\n");
    printf("Seek sequence: %d -> ", head);
    printSequence(fcfsSequence, numberOfRequests);
    printf("Total seek time: %d\n", fcfsSeek);

    printf("\n--- SSTF Disk Scheduling ---\n");
    printf("Seek sequence: %d -> ", head);
    printSequence(sstfSequence, numberOfRequests);
    printf("Total seek time: %d\n", sstfSeek);

    printf("\n--- SCAN Disk Scheduling ---\n");
    printf("Seek sequence: %d -> ", head);
    printSequence(scanSequence, scanCount);
    printf("Total seek time: %d\n", scanSeek);

    bestSeek = fcfsSeek;

    if (sstfSeek < bestSeek)
        bestSeek = sstfSeek;

    if (scanSeek < bestSeek)
        bestSeek = scanSeek;

    printf("\n--- Performance Comparison ---\n");

    if (fcfsSeek == bestSeek)
        printf("Best-performing algorithm: FCFS (%d seek operations)\n", fcfsSeek);

    if (sstfSeek == bestSeek)
        printf("Best-performing algorithm: SSTF (%d seek operations)\n", sstfSeek);

    if (scanSeek == bestSeek)
        printf("Best-performing algorithm: SCAN (%d seek operations)\n", scanSeek);

    return 0;
}

OUTPUT -->
Enter disk size (number of cylinders): 200
Enter number of disk requests (maximum 100): 8
Enter request queue:
98 183 37 122 14 124 65 67
Enter initial head position: 53
Enter SCAN direction (1 for right, 0 for left): 1

--- FCFS Disk Scheduling ---
Seek sequence: 53 -> 98 -> 183 -> 37 -> 122 -> 14 -> 124 -> 65 -> 67
Total seek time: 632

--- SSTF Disk Scheduling ---
Seek sequence: 53 -> 65 -> 67 -> 37 -> 14 -> 98 -> 122 -> 124 -> 183
Total seek time: 236

--- SCAN Disk Scheduling ---
Seek sequence: 53 -> 65 -> 67 -> 98 -> 122 -> 124 -> 183 -> 37 -> 14
Total seek time: 331

--- Performance Comparison ---
Best-performing algorithm: SSTF (236 seek operations)
