#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_BLOCKS 100
#define MAX_FILES 10

typedef struct File {
    char filename[20];
    int start_block;
    int num_blocks;
} File;

int disk[MAX_BLOCKS] = {0};

int allocateContiguous(File *file, const char* name, int startBlock, int numBlocks) {
    if (startBlock + numBlocks > MAX_BLOCKS) {
        printf("Not enough space to allocate\n");
        return 0;
    }

    for (int i=startBlock; i<startBlock+numBlocks;i++) {
        if (disk[i]==1) {
            printf("Block %d is already allocated. Allocation failed\n", i);
            return 0;   
        }
    }

    for (int i=startBlock; i<startBlock+numBlocks;i++) {
        disk[i]=1;
    }

    strcpy(file->filename, name);
    file->start_block = startBlock;
    file->num_blocks = numBlocks;

    printf("File '%s' allocated from block %d to %d\n", name, startBlock, startBlock + numBlocks - 1);
    return 1;
}

void main() {
    struct File files[MAX_FILES];
    int fileCount = 0;

    int choice;
    do {
        if (fileCount >= MAX_FILES) {
            printf("Limit reached\n");
            break;
        }

        char name[20];
        int startBlock, numBlocks;


        printf("\nEnter file name: ");
        scanf("%s", name);

        printf("Enter start block: ");
        scanf("%d", &startBlock);

        printf("Enter number of blocks: ");
        scanf("%d", &numBlocks);

        if (allocateContiguous(&files[fileCount], name, startBlock, numBlocks)) {
            fileCount++;
        }


        printf("Do you want to allocate another file? (1: Yes, 0: No): ");
        scanf("%d", &choice);
    } while (choice == 1);

    printf("\nFile Allocation Table:\n");
    printf("--------------------------------------------------\n");
    printf("%-20s %-15s %-10s\n", "File Name", "Start Block", "No. of Blocks");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < fileCount; i++) {
        printf("%-20s %-15d %-10d\n",
            files[i].filename,
            files[i].start_block,
            files[i].num_blocks);
    }
    printf("--------------------------------------------------\n");
}