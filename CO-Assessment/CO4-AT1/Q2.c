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
Enter total number of disk blocks (1-1000): 5
Enter initial bitmap (5 values of 0 or 1):
1 1 0 1 0

Initial bitmap: 1 1 0 1 0

Enter number of blocks required for allocation: 3

Allocation failed: only 2 free block(s) available.

Enter number of blocks to deallocate (0 to skip): 1
Enter block numbers to deallocate:
1
Block 1 deallocated.

Updated bitmap after deallocation: 1 0 0 1 0
