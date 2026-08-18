Q1
CODE -->
#include <stdio.h>

#define MAX_BLOCKS 1000

/* 0 = free block, 1 = occupied block */
static int disk[MAX_BLOCKS];
static int nextBlock[MAX_BLOCKS];
static int indexTable[MAX_BLOCKS];

int main(void)
{
    int diskSize, fileSize, method;
    int occupiedCount, occupiedBlock;
    int allocated[MAX_BLOCKS];
    int i, j, start, freeBlocks = 0;
    int found, count, indexBlock = -1;

    printf("Enter total disk size (1-1000): ");
    scanf("%d", &diskSize);

    printf("Enter file size (number of blocks): ");
    scanf("%d", &fileSize);

    printf("Choose allocation method:\n");
    printf("1. Contiguous\n2. Linked\n3. Indexed\n");
    printf("Enter choice: ");
    scanf("%d", &method);

    if (diskSize < 1 || diskSize > MAX_BLOCKS || fileSize < 1 ||
        method < 1 || method > 3) {
        printf("Invalid input.\n");
        return 1;
    }

    /* Optional existing occupied blocks to demonstrate fragmentation */
    printf("Enter number of already occupied blocks: ");
    scanf("%d", &occupiedCount);

    if (occupiedCount < 0 || occupiedCount > diskSize) {
        printf("Invalid occupied-block count.\n");
        return 1;
    }

    for (i = 0; i < occupiedCount; i++) {
        printf("Enter occupied block number: ");
        scanf("%d", &occupiedBlock);

        if (occupiedBlock < 0 || occupiedBlock >= diskSize ||
            disk[occupiedBlock] == 1) {
            printf("Invalid or duplicate block number.\n");
            return 1;
        }

        disk[occupiedBlock] = 1;
    }

    for (i = 0; i < diskSize; i++) {
        if (disk[i] == 0)
            freeBlocks++;
    }

    /* Contiguous Allocation */
    if (method == 1) {
        if (freeBlocks < fileSize) {
            printf("Allocation failed: insufficient free blocks.\n");
            return 0;
        }

        found = 0;

        for (start = 0; start <= diskSize - fileSize; start++) {
            found = 1;

            for (j = 0; j < fileSize; j++) {
                if (disk[start + j] == 1) {
                    found = 0;
                    break;
                }
            }

            if (found) {
                for (j = 0; j < fileSize; j++) {
                    disk[start + j] = 1;
                    allocated[j] = start + j;
                }

                printf("\nContiguous allocation successful.\n");
                printf("Allocated blocks: ");

                for (j = 0; j < fileSize; j++)
                    printf("%d ", allocated[j]);

                printf("\n");
                return 0;
            }
        }

        printf("\nAllocation failed: no continuous sequence of %d free blocks exists.\n",
               fileSize);
        printf("This is external fragmentation.\n");
    }

    /* Linked Allocation */
    else if (method == 2) {
        if (freeBlocks < fileSize) {
            printf("Allocation failed: insufficient free blocks.\n");
            return 0;
        }

        count = 0;

        for (i = 0; i < diskSize && count < fileSize; i++) {
            if (disk[i] == 0) {
                disk[i] = 1;
                allocated[count] = i;
                count++;
            }
        }

        for (i = 0; i < fileSize - 1; i++)
            nextBlock[allocated[i]] = allocated[i + 1];

        nextBlock[allocated[fileSize - 1]] = -1;

        printf("\nLinked allocation successful.\n");
        printf("Allocated block chain: ");

        for (i = 0; i < fileSize; i++) {
            printf("%d", allocated[i]);

            if (nextBlock[allocated[i]] != -1)
                printf(" -> ");
        }

        printf(" -> NULL\n");
    }

    /* Indexed Allocation */
    else {
        /* One additional block is required for the index block */
        if (freeBlocks < fileSize + 1) {
            printf("Allocation failed: indexed allocation needs %d data blocks "
                   "and 1 index block.\n", fileSize);
            return 0;
        }

        for (i = 0; i < diskSize; i++) {
            if (disk[i] == 0) {
                indexBlock = i;
                disk[i] = 1;
                break;
            }
        }

        count = 0;

        for (i = 0; i < diskSize && count < fileSize; i++) {
            if (disk[i] == 0) {
                disk[i] = 1;
                allocated[count] = i;
                indexTable[count] = i;
                count++;
            }
        }

        printf("\nIndexed allocation successful.\n");
        printf("Index block: %d\n", indexBlock);
        printf("Data blocks: ");

        for (i = 0; i < fileSize; i++)
            printf("%d ", indexTable[i]);

        printf("\n");
    }

    return 0;
}

OUTPUT -->
      Enter total disk size (1-1000): 10
Enter file size (number of blocks): 3
Choose allocation method:
1. Contiguous
2. Linked
3. Indexed
Enter choice: 1
Enter number of already occupied blocks: 4
Enter occupied block number: 1
Enter occupied block number: 3
Enter occupied block number: 5
Enter occupied block number: 7

Allocation failed: no continuous sequence of 3 free blocks exists.
This is external fragmentation.

Q2
CODE -->
      #include <stdio.h>

#define MAX_BLOCKS 1000

int main(void)
{
    int totalBlocks, bitmap[MAX_BLOCKS];
    int requiredBlocks, allocated[MAX_BLOCKS];
    int deallocateCount, blockNumber;
    int i, count, freeBlocks;

    printf("Enter total number of disk blocks (1-1000): ");
    scanf("%d", &totalBlocks);

    if (totalBlocks < 1 || totalBlocks > MAX_BLOCKS) {
        printf("Invalid disk size.\n");
        return 1;
    }

    printf("Enter initial bitmap (%d values of 0 or 1):\n", totalBlocks);

    for (i = 0; i < totalBlocks; i++) {
        scanf("%d", &bitmap[i]);

        if (bitmap[i] != 0 && bitmap[i] != 1) {
            printf("Invalid bitmap value. Use only 0 or 1.\n");
            return 1;
        }
    }

    printf("\nInitial bitmap: ");
    for (i = 0; i < totalBlocks; i++)
        printf("%d ", bitmap[i]);

    printf("\n\nEnter number of blocks required for allocation: ");
    scanf("%d", &requiredBlocks);

    if (requiredBlocks < 1) {
        printf("Invalid allocation request.\n");
        return 1;
    }

    /* Count free blocks */
    freeBlocks = 0;
    for (i = 0; i < totalBlocks; i++) {
        if (bitmap[i] == 0)
            freeBlocks++;
    }

    if (freeBlocks < requiredBlocks) {
        printf("\nAllocation failed: only %d free block(s) available.\n", freeBlocks);
    } else {
        /* Search bitmap and allocate free blocks */
        count = 0;

        for (i = 0; i < totalBlocks && count < requiredBlocks; i++) {
            if (bitmap[i] == 0) {
                bitmap[i] = 1;
                allocated[count] = i;
                count++;
            }
        }

        printf("\nAllocation successful.\n");
        printf("Allocated block numbers: ");

        for (i = 0; i < requiredBlocks; i++)
            printf("%d ", allocated[i]);

        printf("\nUpdated bitmap after allocation: ");

        for (i = 0; i < totalBlocks; i++)
            printf("%d ", bitmap[i]);

        printf("\n");
    }

    /* Deallocation */
    printf("\nEnter number of blocks to deallocate (0 to skip): ");
    scanf("%d", &deallocateCount);

    if (deallocateCount < 0 || deallocateCount > totalBlocks) {
        printf("Invalid deallocation request.\n");
        return 1;
    }

    if (deallocateCount > 0) {
        printf("Enter block numbers to deallocate:\n");

        for (i = 0; i < deallocateCount; i++) {
            scanf("%d", &blockNumber);

            if (blockNumber < 0 || blockNumber >= totalBlocks) {
                printf("Invalid block number: %d\n", blockNumber);
                continue;
            }

            if (bitmap[blockNumber] == 0) {
                printf("Block %d is already free.\n", blockNumber);
            } else {
                bitmap[blockNumber] = 0;
                printf("Block %d deallocated.\n", blockNumber);
            }
        }

        printf("\nUpdated bitmap after deallocation: ");

        for (i = 0; i < totalBlocks; i++)
            printf("%d ", bitmap[i]);

        printf("\n");
    }

    return 0;
}

OUTPUT -->
      Enter total number of disk blocks (1-1000): 10
Enter initial bitmap (10 values of 0 or 1):
0 1 0 0 1 0 1 0 0 1

Initial bitmap: 0 1 0 0 1 0 1 0 0 1

Enter number of blocks required for allocation: 3

Allocation successful.
Allocated block numbers: 0 2 3
Updated bitmap after allocation: 1 1 1 1 1 0 1 0 0 1

Enter number of blocks to deallocate (0 to skip): 2
Enter block numbers to deallocate:
2
5
Block 2 deallocated.
Block 5 deallocated.

Updated bitmap after deallocation: 1 1 0 1 1 0 1 0 0 1

Q3
CODE -->
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

Q4
CODE -->
      #include <stdio.h>

#define MAX_REQUESTS 100
#define MAX_SEQUENCE (MAX_REQUESTS + 3)

int absoluteDifference(int a, int b)
{
    return (a > b) ? (a - b) : (b - a);
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

void printSequence(int head, int sequence[], int count)
{
    int i;

    printf("%d", head);

    for (i = 0; i < count; i++)
        printf(" -> %d", sequence[i]);

    printf("\n");
}

/* direction: 1 = right, 0 = left */
int cscan(int requests[], int n, int head, int diskSize, int direction,
          int sequence[], int *count)
{
    int sorted[MAX_REQUESTS];
    int i, split = 0, current = head, totalMovement = 0;

    *count = 0;

    for (i = 0; i < n; i++)
        sorted[i] = requests[i];

    sortRequests(sorted, n);

    while (split < n && sorted[split] < head)
        split++;

    if (direction == 1) {
        /* Service requests to the right */
        for (i = split; i < n; i++) {
            totalMovement += absoluteDifference(current, sorted[i]);
            current = sorted[i];
            sequence[(*count)++] = current;
        }

        /* Go to end and jump to beginning */
        if (split > 0) {
            if (current != diskSize - 1) {
                totalMovement += absoluteDifference(current, diskSize - 1);
                current = diskSize - 1;
                sequence[(*count)++] = current;
            }

            totalMovement += diskSize - 1;
            current = 0;
            sequence[(*count)++] = current;

            /* Service remaining lower requests */
            for (i = 0; i < split; i++) {
                totalMovement += absoluteDifference(current, sorted[i]);
                current = sorted[i];
                sequence[(*count)++] = current;
            }
        }
    } else {
        /* Service requests to the left */
        for (i = split - 1; i >= 0; i--) {
            totalMovement += absoluteDifference(current, sorted[i]);
            current = sorted[i];
            sequence[(*count)++] = current;
        }

        /* Go to beginning and jump to end */
        if (split < n) {
            if (current != 0) {
                totalMovement += absoluteDifference(current, 0);
                current = 0;
                sequence[(*count)++] = current;
            }

            totalMovement += diskSize - 1;
            current = diskSize - 1;
            sequence[(*count)++] = current;

            /* Service remaining higher requests */
            for (i = n - 1; i >= split; i--) {
                totalMovement += absoluteDifference(current, sorted[i]);
                current = sorted[i];
                sequence[(*count)++] = current;
            }
        }
    }

    return totalMovement;
}

int look(int requests[], int n, int head, int direction,
         int sequence[], int *count)
{
    int sorted[MAX_REQUESTS];
    int i, split = 0, current = head, totalMovement = 0;

    *count = 0;

    for (i = 0; i < n; i++)
        sorted[i] = requests[i];

    sortRequests(sorted, n);

    while (split < n && sorted[split] < head)
        split++;

    if (direction == 1) {
        /* Move right until the last request, then reverse */
        for (i = split; i < n; i++) {
            totalMovement += absoluteDifference(current, sorted[i]);
            current = sorted[i];
            sequence[(*count)++] = current;
        }

        for (i = split - 1; i >= 0; i--) {
            totalMovement += absoluteDifference(current, sorted[i]);
            current = sorted[i];
            sequence[(*count)++] = current;
        }
    } else {
        /* Move left until the last request, then reverse */
        for (i = split - 1; i >= 0; i--) {
            totalMovement += absoluteDifference(current, sorted[i]);
            current = sorted[i];
            sequence[(*count)++] = current;
        }

        for (i = split; i < n; i++) {
            totalMovement += absoluteDifference(current, sorted[i]);
            current = sorted[i];
            sequence[(*count)++] = current;
        }
    }

    return totalMovement;
}

int main(void)
{
    int diskSize, numberOfRequests, head, direction;
    int requests[MAX_REQUESTS];
    int cscanSequence[MAX_SEQUENCE];
    int lookSequence[MAX_SEQUENCE];
    int cscanCount, lookCount;
    int cscanMovement, lookMovement;
    int i;

    printf("Enter disk size (number of cylinders): ");
    scanf("%d", &diskSize);

    printf("Enter number of requests (maximum %d): ", MAX_REQUESTS);
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
            printf("Invalid disk request: %d\n", requests[i]);
            return 1;
        }
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    if (head < 0 || head >= diskSize || (direction != 0 && direction != 1)) {
        printf("Invalid head position or direction.\n");
        return 1;
    }

    cscanMovement = cscan(requests, numberOfRequests, head, diskSize,
                           direction, cscanSequence, &cscanCount);

    lookMovement = look(requests, numberOfRequests, head, direction,
                        lookSequence, &lookCount);

    printf("\n--- C-SCAN Disk Scheduling ---\n");
    printf("Seek sequence: ");
    printSequence(head, cscanSequence, cscanCount);
    printf("Total head movement: %d cylinders\n", cscanMovement);

    printf("\n--- LOOK Disk Scheduling ---\n");
    printf("Seek sequence: ");
    printSequence(head, lookSequence, lookCount);
    printf("Total head movement: %d cylinders\n", lookMovement);

    printf("\n--- Performance Comparison ---\n");

    if (cscanMovement < lookMovement) {
        printf("C-SCAN performs better.\n");
        printf("Reason: It requires fewer total head movements for this request queue.\n");
    } else if (lookMovement < cscanMovement) {
        printf("LOOK performs better.\n");
        printf("Reason: It avoids unnecessary movement to the disk ends.\n");
    } else {
        printf("Both algorithms perform equally.\n");
        printf("Reason: Both require the same total head movement.\n");
    }

    return 0;
}

OUTPUT -->
      Enter disk size (number of cylinders): 200
Enter number of requests (maximum 100): 8
Enter request queue:
98 183 37 122 14 124 65 67
Enter initial head position: 53
Enter direction (1 for right, 0 for left): 1

--- C-SCAN Disk Scheduling ---
Seek sequence: 53 -> 65 -> 67 -> 98 -> 122 -> 124 -> 183 -> 199 -> 0 -> 14 -> 37
Total head movement: 382 cylinders

--- LOOK Disk Scheduling ---
Seek sequence: 53 -> 65 -> 67 -> 98 -> 122 -> 124 -> 183 -> 37 -> 14
Total head movement: 299 cylinders

--- Performance Comparison ---
LOOK performs better.
Reason: It avoids unnecessary movement to the disk ends.

Q5
CODE -->
#include <stdio.h>

#define MAX_BLOCKS 1000
#define MAX_REQUESTS 1000
#define MAX_ACCESS_QUEUE (MAX_BLOCKS + MAX_REQUESTS)

/* Stores the result of one allocation method */
typedef struct {
    int success;
    int indexBlock;                 /* -1 for contiguous allocation */
    int dataBlocks[MAX_BLOCKS];
    int dataCount;
} AllocationResult;

int absoluteDifference(int a, int b)
{
    return (a > b) ? (a - b) : (b - a);
}

void copyDisk(int source[], int destination[], int size)
{
    int i;

    for (i = 0; i < size; i++)
        destination[i] = source[i];
}

void printBlocks(int blocks[], int count)
{
    int i;

    for (i = 0; i < count; i++) {
        printf("%d", blocks[i]);

        if (i < count - 1)
            printf(" ");
    }

    printf("\n");
}

/* Finds a continuous group of free blocks */
AllocationResult contiguousAllocation(int originalDisk[], int diskSize,
                                      int fileSize)
{
    AllocationResult result;
    int disk[MAX_BLOCKS];
    int start, i, found;

    result.success = 0;
    result.indexBlock = -1;
    result.dataCount = 0;

    copyDisk(originalDisk, disk, diskSize);

    for (start = 0; start <= diskSize - fileSize; start++) {
        found = 1;

        for (i = 0; i < fileSize; i++) {
            if (disk[start + i] == 1) {
                found = 0;
                break;
            }
        }

        if (found) {
            for (i = 0; i < fileSize; i++) {
                disk[start + i] = 1;
                result.dataBlocks[i] = start + i;
            }

            result.success = 1;
            result.dataCount = fileSize;
            return result;
        }
    }

    return result;
}

/* Uses one free block as index block and free blocks for file data */
AllocationResult indexedAllocation(int originalDisk[], int diskSize,
                                   int fileSize)
{
    AllocationResult result;
    int disk[MAX_BLOCKS];
    int i, freeCount = 0, count = 0;

    result.success = 0;
    result.indexBlock = -1;
    result.dataCount = 0;

    copyDisk(originalDisk, disk, diskSize);

    for (i = 0; i < diskSize; i++) {
        if (disk[i] == 0)
            freeCount++;
    }

    /* Indexed allocation needs data blocks + one index block */
    if (freeCount < fileSize + 1)
        return result;

    /* Allocate index block */
    for (i = 0; i < diskSize; i++) {
        if (disk[i] == 0) {
            result.indexBlock = i;
            disk[i] = 1;
            break;
        }
    }

    /* Allocate data blocks */
    for (i = 0; i < diskSize && count < fileSize; i++) {
        if (disk[i] == 0) {
            disk[i] = 1;
            result.dataBlocks[count] = i;
            count++;
        }
    }

    result.success = 1;
    result.dataCount = fileSize;

    return result;
}

/*
   Creates a combined access queue:
   original disk requests + allocated file blocks.
   Duplicate requests are removed.
*/
int createAccessQueue(int requests[], int requestCount,
                      AllocationResult allocation,
                      int accessQueue[])
{
    int present[MAX_BLOCKS] = {0};
    int i, count = 0;

    for (i = 0; i < requestCount; i++) {
        if (!present[requests[i]]) {
            present[requests[i]] = 1;
            accessQueue[count++] = requests[i];
        }
    }

    /* Indexed files require access to their index block */
    if (allocation.indexBlock != -1 && !present[allocation.indexBlock]) {
        present[allocation.indexBlock] = 1;
        accessQueue[count++] = allocation.indexBlock;
    }

    for (i = 0; i < allocation.dataCount; i++) {
        if (!present[allocation.dataBlocks[i]]) {
            present[allocation.dataBlocks[i]] = 1;
            accessQueue[count++] = allocation.dataBlocks[i];
        }
    }

    return count;
}

int fcfs(int queue[], int count, int head, int sequence[])
{
    int i, current = head, totalSeek = 0;

    for (i = 0; i < count; i++) {
        totalSeek += absoluteDifference(current, queue[i]);
        sequence[i] = queue[i];
        current = queue[i];
    }

    return totalSeek;
}

int sstf(int queue[], int count, int head, int sequence[])
{
    int visited[MAX_ACCESS_QUEUE] = {0};
    int current = head, totalSeek = 0;
    int i, j, selected, shortestDistance;

    for (i = 0; i < count; i++) {
        selected = -1;
        shortestDistance = 1000000;

        for (j = 0; j < count; j++) {
            if (!visited[j] &&
                absoluteDifference(current, queue[j]) < shortestDistance) {
                shortestDistance = absoluteDifference(current, queue[j]);
                selected = j;
            }
        }

        visited[selected] = 1;
        sequence[i] = queue[selected];
        totalSeek += absoluteDifference(current, queue[selected]);
        current = queue[selected];
    }

    return totalSeek;
}

void printSchedulingResult(char allocationName[], char schedulingName[],
                           AllocationResult allocation, int accessQueue[],
                           int accessCount, int head)
{
    int sequence[MAX_ACCESS_QUEUE];
    int totalSeek, i;

    printf("\n--- %s + %s ---\n", allocationName, schedulingName);

    printf("Allocated data blocks: ");
    printBlocks(allocation.dataBlocks, allocation.dataCount);

    if (allocation.indexBlock != -1)
        printf("Index block: %d\n", allocation.indexBlock);

    if (schedulingName[0] == 'F')
        totalSeek = fcfs(accessQueue, accessCount, head, sequence);
    else
        totalSeek = sstf(accessQueue, accessCount, head, sequence);

    printf("Seek sequence: %d", head);

    for (i = 0; i < accessCount; i++)
        printf(" -> %d", sequence[i]);

    printf("\nTotal seek time: %d\n", totalSeek);
}

int main(void)
{
    int diskSize, fileSize, requestCount, head;
    int selectedAllocation, selectedScheduling;
    int disk[MAX_BLOCKS] = {0};
    int requests[MAX_REQUESTS];
    int occupiedCount, occupiedBlock;
    int contigQueue[MAX_ACCESS_QUEUE], indexedQueue[MAX_ACCESS_QUEUE];
    int contigCount = 0, indexedCount = 0;
    int contigFCFS, contigSSTF, indexedFCFS, indexedSSTF;
    int contigSequence[MAX_ACCESS_QUEUE], indexedSequence[MAX_ACCESS_QUEUE];
    int bestSeek = 1000000;
    int i;

    AllocationResult contiguous;
    AllocationResult indexed;

    printf("Enter total number of disk blocks (1-1000): ");
    scanf("%d", &diskSize);

    printf("Enter file size (number of blocks required): ");
    scanf("%d", &fileSize);

    printf("Enter number of existing disk requests: ");
    scanf("%d", &requestCount);

    if (diskSize < 1 || diskSize > MAX_BLOCKS || fileSize < 1 ||
        requestCount < 1 || requestCount > MAX_REQUESTS) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter disk request queue:\n");

    for (i = 0; i < requestCount; i++) {
        scanf("%d", &requests[i]);

        if (requests[i] < 0 || requests[i] >= diskSize) {
            printf("Invalid request block.\n");
            return 1;
        }
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Choose allocation method (1 = Contiguous, 2 = Indexed): ");
    scanf("%d", &selectedAllocation);

    printf("Choose scheduling method (1 = FCFS, 2 = SSTF): ");
    scanf("%d", &selectedScheduling);

    printf("Enter number of blocks already occupied: ");
    scanf("%d", &occupiedCount);

    if (head < 0 || head >= diskSize ||
        selectedAllocation < 1 || selectedAllocation > 2 ||
        selectedScheduling < 1 || selectedScheduling > 2 ||
        occupiedCount < 0 || occupiedCount > diskSize) {
        printf("Invalid input.\n");
        return 1;
    }

    for (i = 0; i < occupiedCount; i++) {
        printf("Enter occupied block number: ");
        scanf("%d", &occupiedBlock);

        if (occupiedBlock < 0 || occupiedBlock >= diskSize ||
            disk[occupiedBlock] == 1) {
            printf("Invalid or duplicate occupied block.\n");
            return 1;
        }

        disk[occupiedBlock] = 1;
    }

    contiguous = contiguousAllocation(disk, diskSize, fileSize);
    indexed = indexedAllocation(disk, diskSize, fileSize);

    if (!contiguous.success)
        printf("\nContiguous allocation failed: no continuous free space exists.\n");

    if (!indexed.success)
        printf("\nIndexed allocation failed: insufficient free blocks.\n");

    if (!contiguous.success && !indexed.success) {
        printf("\nNo allocation method can allocate this file.\n");
        return 0;
    }

    if (contiguous.success) {
        contigCount = createAccessQueue(requests, requestCount,
                                        contiguous, contigQueue);

        contigFCFS = fcfs(contigQueue, contigCount, head, contigSequence);
        contigSSTF = sstf(contigQueue, contigCount, head, contigSequence);

        printSchedulingResult("Contiguous", "FCFS", contiguous,
                              contigQueue, contigCount, head);

        printSchedulingResult("Contiguous", "SSTF", contiguous,
                              contigQueue, contigCount, head);

        if (contigFCFS < bestSeek)
            bestSeek = contigFCFS;

        if (contigSSTF < bestSeek)
            bestSeek = contigSSTF;
    }

    if (indexed.success) {
        indexedCount = createAccessQueue(requests, requestCount,
                                         indexed, indexedQueue);

        indexedFCFS = fcfs(indexedQueue, indexedCount, head, indexedSequence);
        indexedSSTF = sstf(indexedQueue, indexedCount, head, indexedSequence);

        printSchedulingResult("Indexed", "FCFS", indexed,
                              indexedQueue, indexedCount, head);

        printSchedulingResult("Indexed", "SSTF", indexed,
                              indexedQueue, indexedCount, head);

        if (indexedFCFS < bestSeek)
            bestSeek = indexedFCFS;

        if (indexedSSTF < bestSeek)
            bestSeek = indexedSSTF;
    }

    printf("\n--- Best Performance ---\n");

    if (contiguous.success && contigFCFS == bestSeek)
        printf("Contiguous Allocation + FCFS: %d seek operations\n", bestSeek);

    if (contiguous.success && contigSSTF == bestSeek)
        printf("Contiguous Allocation + SSTF: %d seek operations\n", bestSeek);

    if (indexed.success && indexedFCFS == bestSeek)
        printf("Indexed Allocation + FCFS: %d seek operations\n", bestSeek);

    if (indexed.success && indexedSSTF == bestSeek)
        printf("Indexed Allocation + SSTF: %d seek operations\n", bestSeek);

    return 0;
}

OUTPUT -->
      Enter total number of disk blocks (1-1000): 15
Enter file size (number of blocks required): 3
Enter number of existing disk requests: 3
Enter disk request queue:
12 10 14
Enter initial head position: 8
Choose allocation method (1 = Contiguous, 2 = Indexed): 2
Choose scheduling method (1 = FCFS, 2 = SSTF): 2
Enter number of blocks already occupied: 7
Enter occupied block number: 1
Enter occupied block number: 3
Enter occupied block number: 5
Enter occupied block number: 7
Enter occupied block number: 9
Enter occupied block number: 11
Enter occupied block number: 13

Contiguous allocation failed: no continuous free space exists.

--- Indexed + FCFS ---
Allocated data blocks: 2 4 6
Index block: 0
Seek sequence: 8 -> 12 -> 10 -> 14 -> 0 -> 2 -> 4 -> 6
Total seek time: 30

--- Indexed + SSTF ---
Allocated data blocks: 2 4 6
Index block: 0
Seek sequence: 8 -> 10 -> 12 -> 14 -> 6 -> 4 -> 2 -> 0
Total seek time: 20

--- Best Performance ---
Indexed Allocation + SSTF: 20 seek operations
