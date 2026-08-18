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
