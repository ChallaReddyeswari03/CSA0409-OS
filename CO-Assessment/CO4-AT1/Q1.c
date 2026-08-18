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
