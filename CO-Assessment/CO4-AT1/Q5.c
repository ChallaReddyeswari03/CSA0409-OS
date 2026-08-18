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
