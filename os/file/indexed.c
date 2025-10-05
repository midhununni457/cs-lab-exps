#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_BLOCKS 100
#define MAX_BLOCKS_PER_FILE 20

struct IndexBlock {
    int data_blocks[MAX_BLOCKS_PER_FILE];
};

struct File {
    char filename[20];
    struct IndexBlock indexBlock;
};

int used[MAX_BLOCKS] = {0};

void initializeIndexBlock(struct IndexBlock* indexBlock) {
    for (int i = 0; i < MAX_BLOCKS_PER_FILE; ++i) {
        indexBlock->data_blocks[i] = -1;
    }
}

int allocateDataBlock(struct IndexBlock* indexBlock, int blockNumber) {
    for (int i = 0; i < MAX_BLOCKS_PER_FILE; ++i) {
        if (indexBlock->data_blocks[i] == -1) {
            indexBlock->data_blocks[i] = blockNumber;
            used[blockNumber] = 1;
            return 1;
        }
    }
    return 0;
}

void displayFile(struct File* file) {
    printf("%-15s -> ", file->filename);
    for (int i = 0; i < MAX_BLOCKS_PER_FILE; i++) {
        if (file->indexBlock.data_blocks[i] != -1) {
            printf("%d ", file->indexBlock.data_blocks[i]);
        }
    }
    printf("\n");
}

int main() {
    struct File files[MAX_FILES];
    int fileCount = 0;
    int choice;

    do {
        if (fileCount >= MAX_FILES) {
            printf("Maximum file limit reached.\n");
            break;
        }

        char name[20];
        int numBlocks, blockNum;

        printf("\nEnter file name: ");
        scanf("%s", name);

        printf("Enter number of blocks required: ");
        scanf("%d", &numBlocks);

        if (numBlocks > MAX_BLOCKS_PER_FILE) {
            printf("Cannot allocate more than %d blocks per file.\n", MAX_BLOCKS_PER_FILE);
            continue;
        }

        struct File newFile;
        strcpy(newFile.filename, name);
        initializeIndexBlock(&newFile.indexBlock);

        printf("Enter %d block numbers:\n", numBlocks);
        int valid = 1;
        for (int i = 0; i < numBlocks; i++) {
            scanf("%d", &blockNum);
            if (blockNum < 0 || blockNum >= MAX_BLOCKS || used[blockNum]) {
                printf("Block %d is invalid or already used.\n", blockNum);
                valid = 0;
                break;
            }
            allocateDataBlock(&newFile.indexBlock, blockNum);
        }

        if (valid) {
            files[fileCount++] = newFile;
            printf("File '%s' allocated successfully.\n", name);
        } else {
            for (int i = 0; i < MAX_BLOCKS_PER_FILE; i++) {
                int b = newFile.indexBlock.data_blocks[i];
                if (b != -1) used[b] = 0;
            }
        }

        printf("Do you want to add another file? (1:Yes, 0:No): ");
        scanf("%d", &choice);

    } while (choice == 1);

    printf("\nIndexed File Allocation Table:\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < fileCount; i++) {
        displayFile(&files[i]);
    }
    printf("-------------------------------------------------\n");

    return 0;
}