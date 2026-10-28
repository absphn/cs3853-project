#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
    CS3853 Computer Architecture
    Virtual Memory & Cache Simulator
    Milestone #1
    Team #09
*/

int main(int argc, char *argv[])
{
    /* Input parameters */
    int cacheSize = 0;
    int blockSize = 0;
    int associativity = 0;
    int physicalMemory = 0;
    double osPercent = 0;
    int timeSlice = 0;

    char replacement[10] = "";
    char traceFile[100] = "";

    int i;
    
    /* Parse command-line arguments */
    for(i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-s") == 0)
            cacheSize = atoi(argv[++i]);

        else if(strcmp(argv[i], "-b") == 0)
            blockSize = atoi(argv[++i]);

        else if(strcmp(argv[i], "-a") == 0)
            associativity = atoi(argv[++i]);

        else if(strcmp(argv[i], "-r") == 0)
            strcpy(replacement, argv[++i]);

        else if(strcmp(argv[i], "-p") == 0)
            physicalMemory = atoi(argv[++i]);

        else if(strcmp(argv[i], "-u") == 0)
            osPercent = atof(argv[++i]);

        else if(strcmp(argv[i], "-n") == 0)
            timeSlice = atoi(argv[++i]);

        else if(strcmp(argv[i], "-f") == 0)
            strcpy(traceFile, argv[++i]);
    }

    /* Cache calculations */
    int totalBlocks =
        (cacheSize * 1024) / blockSize;

    int totalRows =
        totalBlocks / associativity;

    int indexBits =
        (int)log2(totalRows);

    /* Physical memory calculations */
    long physicalMemoryBytes =
        (long)physicalMemory * 1024 * 1024;

    int physicalPages =
        physicalMemoryBytes / 4096;

    int systemPages =
        physicalPages * (osPercent / 100.0);

    /* Page table calculations */
    int pageTableEntryBits =
        (int)log2(physicalPages) + 1;

    int offsetBits =
        (int)log2(blockSize);

    int physicalAddressBits =
        (int)log2(physicalMemoryBytes);

    int tagBits =
        physicalAddressBits -
        indexBits -
        offsetBits;

    int numberOfTraceFiles = 1;

    long pageTableRAM =
        (512L * 1024 *
         numberOfTraceFiles *
         pageTableEntryBits) / 8;

    /* Cache overhead calculations */

    long overheadSize =
        ((long)totalBlocks *
        (tagBits + 1)) / 8;

    long implementationBytes =
        (cacheSize * 1024L) +
        overheadSize;

    double implementationKB =
        implementationBytes / 1024.0;

    double cost = 
       implementationKB * 0.07;

    /* Output report */

    printf("Cache Simulator - CS3853 - Team #09\n\n");

    printf("Trace File(s):\n");
    printf("    %s\n\n", traceFile);

    printf("***** Cache Input Parameters *****\n");

    printf("Cache Size:                     %d KB\n", cacheSize);
    printf("Block Size:                     %d bytes\n", blockSize);
    printf("Associativity:                  %d\n", associativity);
    printf("Replacement Policy:             %s\n", replacement);
    printf("Physical Memory:                %d MB\n", physicalMemory);
    printf("Percent Memory Used by System:  %.1f%%\n", osPercent);
    printf("Instructions / Time Slice:      %d\n", timeSlice);

    printf("\n");

    printf("***** Cache Calculated Values *****\n");

    printf("Total # Blocks:                 %d\n", totalBlocks);
    printf("Tag Size:                       %d bits\n", tagBits);
    printf("Index Size:                     %d bits\n", indexBits);
    printf("Total # Rows:                   %d\n", totalRows);

    printf("Overhead Size:                  %ld bytes\n",
       overheadSize);

    printf("Implementation Memory Size:     %.2f KB (%ld bytes)\n",
       implementationKB,
       implementationBytes);

    printf("Cost:                           $%.2f @ $0.07 per KB\n",
       cost);

    printf("\n");

    printf("***** Physical Memory Calculated Values *****\n");

    printf("Number of Physical Pages:       %d\n", physicalPages);
    printf("Number of Pages for System:     %d\n", systemPages);

    printf("Size of Page Table Entry:       %d bits\n",
           pageTableEntryBits);

    printf("Total RAM for Page Table(s):    %ld bytes\n",
           pageTableRAM);

    return 0;
}
