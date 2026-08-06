Q1. CODE -->
#include <stdio.h>

int main() {
    int base, limit, logicalAddress, physicalAddress;

    // Input base and limit registers
    printf("Enter Base Register Value: ");
    scanf("%d", &base);

    printf("Enter Limit Register Value: ");
    scanf("%d", &limit);

    // Input logical address
    printf("Enter Logical Address: ");
    scanf("%d", &logicalAddress);

    // Check validity
    if (logicalAddress >= 0 && logicalAddress < limit) {
        physicalAddress = base + logicalAddress;
        printf("\nValid Logical Address.\n");
        printf("Physical Address = %d\n", physicalAddress);
    } else {
        printf("\nInvalid Logical Address! Address exceeds limit.\n");
    }

    return 0;
}

OUTPUT -->
Enter Base Register Value: 500
Enter Limit Register Value: 300
Enter Logical Address: 120

Valid Logical Address.
Physical Address = 620


=== Code Execution Successful ===

Q2. CODE -->
#include <stdio.h>

int main() {
    int pageSize, numPages;
    int pageTable[50];
    int pageNumber, offset;
    int frameNumber, physicalAddress;

    // Input page size and number of pages
    printf("Enter Page Size: ");
    scanf("%d", &pageSize);

    printf("Enter Number of Pages: ");
    scanf("%d", &numPages);

    // Input page table
    printf("Enter Frame Number for each Page:\n");
    for (int i = 0; i < numPages; i++) {
        printf("Page %d -> Frame: ", i);
        scanf("%d", &pageTable[i]);
    }

    // Input logical address
    printf("\nEnter Page Number: ");
    scanf("%d", &pageNumber);

    printf("Enter Offset: ");
    scanf("%d", &offset);

    // Validate page number and offset
    if (pageNumber >= 0 && pageNumber < numPages &&
        offset >= 0 && offset < pageSize) {

        frameNumber = pageTable[pageNumber];
        physicalAddress = (frameNumber * pageSize) + offset;

        printf("\nValid Logical Address.\n");
        printf("Frame Number = %d\n", frameNumber);
        printf("Physical Address = %d\n", physicalAddress);
    } else {
        printf("\nInvalid Page Number or Offset!\n");
    }

    return 0;
}
OUTPUT -->
  Enter Page Size: 1024
Enter Number of Pages: 4
Enter Frame Number for each Page:
Page 0 -> Frame: 5
Page 1 -> Frame: 2
Page 2 -> Frame: 8
Page 3 -> Frame: 1

Enter Page Number: 2
Enter Offset: 100

Valid Logical Address.
Frame Number = 8
Physical Address = 8292


=== Code Execution Successful ===

Q3. CODE -->
#include <stdio.h>

int main() {
    int numPages, pageSize;
    int pageTable[50];
    int pageNumber, offset;
    int frameNumber, physicalAddress;
    int i;

    // Input number of pages and page size
    printf("Enter Number of Pages: ");
    scanf("%d", &numPages);

    printf("Enter Page Size: ");
    scanf("%d", &pageSize);

    // Input page table entries
    printf("\nEnter Page Table Entries (Frame Numbers):\n");
    for(i = 0; i < numPages; i++) {
        printf("Page %d -> Frame: ", i);
        scanf("%d", &pageTable[i]);
    }

    // Display page table
    printf("\nPage Table:\n");
    printf("Page No.\tFrame No.\n");
    for(i = 0; i < numPages; i++) {
        printf("%d\t\t%d\n", i, pageTable[i]);
    }

    // Input logical address
    printf("\nEnter Page Number: ");
    scanf("%d", &pageNumber);

    printf("Enter Offset: ");
    scanf("%d", &offset);

    // Validate and translate
    if(pageNumber >= 0 && pageNumber < numPages &&
       offset >= 0 && offset < pageSize) {

        frameNumber = pageTable[pageNumber];
        physicalAddress = (frameNumber * pageSize) + offset;

        printf("\nAddress Translation:\n");
        printf("Page Number %d --> Frame Number %d\n", pageNumber, frameNumber);
        printf("Physical Address = (%d x %d) + %d = %d\n",
               frameNumber, pageSize, offset, physicalAddress);
    }
    else {
        printf("\nInvalid Logical Address!\n");
    }

    return 0;
}
OUTPUT -->
  Enter Number of Pages: 4
Enter Page Size: 1024

Enter Page Table Entries (Frame Numbers):
Page 0 -> Frame: 5
Page 1 -> Frame: 2
Page 2 -> Frame: 7
Page 3 -> Frame: 1

Page Table:
Page No.	Frame No.
0		5
1		2
2		7
3		1

Enter Page Number: 2
Enter Offset: 300

Address Translation:
Page Number 2 --> Frame Number 7
Physical Address = (7 x 1024) + 300 = 7468


=== Code Execution Successful ===

Q4. CODE -->
#include <stdio.h>

int main() {
    float memoryAccessTime, tlbLookupTime;
    float hitRatio;
    float ematWithTLB, ematWithoutTLB;

    // Input values
    printf("Enter Memory Access Time (in ns): ");
    scanf("%f", &memoryAccessTime);

    printf("Enter TLB Lookup Time (in ns): ");
    scanf("%f", &tlbLookupTime);

    printf("Enter TLB Hit Ratio (0 to 1): ");
    scanf("%f", &hitRatio);

    // Calculate Effective Memory Access Time
    ematWithoutTLB = 2 * memoryAccessTime;

    ematWithTLB = (hitRatio * (tlbLookupTime + memoryAccessTime)) +
                  ((1 - hitRatio) * (tlbLookupTime + 2 * memoryAccessTime));

    // Display results
    printf("\n----- Results -----\n");
    printf("Effective Memory Access Time without TLB = %.2f ns\n",
           ematWithoutTLB);

    printf("Effective Memory Access Time with TLB    = %.2f ns\n",
           ematWithTLB);

    if (ematWithTLB < ematWithoutTLB)
        printf("TLB improves memory access time.\n");
    else
        printf("No improvement in memory access time.\n");

    return 0;
}
OUTPUT -->
  Enter Memory Access Time (in ns): 100
Enter TLB Lookup Time (in ns): 20
Enter TLB Hit Ratio (0 to 1): 0.9

----- Results -----
Effective Memory Access Time without TLB = 200.00 ns
Effective Memory Access Time with TLB    = 130.00 ns
TLB improves memory access time.


=== Code Execution Successful ===

Q5. CODE -->
#include <stdio.h>

int main() {
    int base, limit;
    int logicalAddress, physicalAddress;

    // Input base and limit registers
    printf("Enter Base Register Value: ");
    scanf("%d", &base);

    printf("Enter Limit Register Value: ");
    scanf("%d", &limit);

    // Input logical address
    printf("Enter Logical Address: ");
    scanf("%d", &logicalAddress);

    // Check memory protection
    if (logicalAddress >= 0 && logicalAddress < limit) {
        physicalAddress = base + logicalAddress;

        printf("\nAccess Granted.\n");
        printf("Logical Address : %d\n", logicalAddress);
        printf("Physical Address: %d\n", physicalAddress);
    } else {
        printf("\nAccess Denied!\n");
        printf("Unauthorized Memory Access.\n");
    }

    return 0;
}
OUTPUT -->
  Enter Base Register Value: 5000
Enter Limit Register Value: 1000
Enter Logical Address: 450

Access Granted.
Logical Address : 450
Physical Address: 5450


=== Code Execution Successful ===
