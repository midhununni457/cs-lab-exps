#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_BLOCKS 100
#define MAX_FILES 10

typedef struct Block {
    int block_number;
    struct Block *next;
} Block;

typedef struct File {
    char filename[20];
    Block *start; 
} File;

Block * allocateBlock(int blockNumber) {
    Block *newBlock = (Block*)malloc(sizeof(Block));
    newBlock->block_number = blockNumber;
    newBlock->next = NULL;
    return newBlock;
}

void main() {
    struct File files[MAX_FILES];
    int disk[MAX_BLOCKS] = {0};
    int fileCount = 0;

    int choice;
    do {
        if (fileCount >= MAX_FILES) {
            printf("Limit reached\n");
            break;
        }

        char name[20];
        int n, blockNum;

        printf("\nEnter file name: ");
        scanf("%s", name);

        printf("Enter number of blocks required: ");
        scanf("%d", &n);

        Block* head = NULL;
        Block* current = NULL;

        printf("Enter %d block numbers:\n", n);
        int valid = 1;

        for (int i=0;i<n;i++) {
            scanf("%d", &blockNum);
            if (blockNum < 0 || blockNum >= MAX_BLOCKS || disk[blockNum]) {
                printf("Block %d is invalid or already used.\n", blockNum);
                valid = 0;
                break;
            }

            disk[blockNum] = 1;

            Block *newBlock = allocateBlock(blockNum);
            if (head == NULL) {
                head = newBlock;
            } else {
                current->next = newBlock;
            }
            current=newBlock;
        }
            
        if (valid) {
            strcpy(files[fileCount].filename, name);
            files[fileCount].start = head;
            fileCount++;
            printf("File '%s' allocated using linked allocation.\n", name);
        } else {
            current = head;
            while (current != NULL) {
                disk[current->block_number] = 0;
                struct Block* temp = current;
                current = current->next;
                free(temp);
            }
        }

        printf("Do you want to allocate another file? (1: Yes, 0: No): ");
        scanf("%d", &choice);
    } while (choice == 1);

    printf("\n📁 File Allocation Table (Linked):\n");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < fileCount; i++) {
        printf("%s -> ", files[i].filename);
        struct Block* current = files[i].start;
        while (current != NULL) {
            printf("%d -> ", current->block_number);
            current = current->next;
        }
        printf("NULL\n");
    }
    printf("----------------------------------------------------\n");


    for (int i = 0; i < fileCount; i++) {
        struct Block* current = files[i].start;
        while (current != NULL) {
            struct Block* temp = current;
            current = current->next;
            free(temp);
        }
    }
}