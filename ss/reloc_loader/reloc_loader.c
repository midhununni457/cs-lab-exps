#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char bitmask[12];
char bit[50];

void convert(char h[12]);

int main() {
    char add[10], length[10], input[10], pn[10];
    int start, address, opcode, addr, actualadd, tlen;
    char relocbit;
    int len, i, orig_start, offset;

    FILE *fp1, *fp2;

    printf("Enter the actual starting address: ");
    scanf("%x", &start);

    fp1 = fopen("RLIN.txt", "r");
    if (fp1 == NULL) {
        printf("Error opening input file.\n");
        exit(1);
    }

    fp2 = fopen("RLOUT.txt", "w");
    if (fp2 == NULL) {
        printf("Error creating output file.\n");
        fclose(fp1);
        exit(1);
    }

    fprintf(fp2, " ----------------------------\n");
    fprintf(fp2, " ADDRESS\tCONTENT\n");
    fprintf(fp2, " ----------------------------\n");

    while (fscanf(fp1, "%s", input) != EOF) {
        if (strcmp(input, "H") == 0) {
            fscanf(fp1, "%s %x %s", pn, &orig_start, length);
        } 
        else if (strcmp(input, "T") == 0) {
            fscanf(fp1, "%x %x %s", &address, &tlen, bitmask);

            offset = start - orig_start;
            address += offset;

            convert(bitmask);

            len = strlen(bit);
            if (len > 10) len = 10;

            for (i = 0; i < len; i++) {
                if (fscanf(fp1, "%x %x", &opcode, &addr) != 2)
                    break;

                relocbit = bit[i];
                if (relocbit == '0')
                    actualadd = addr;
                else
                    actualadd = addr + offset;

                fprintf(fp2, "%04X\t\t%02X%04X\n", address, opcode, actualadd);
                address += 3;
            }
        } 
        else if (strcmp(input, "E") == 0) {
            break;
        }
    }

    fprintf(fp2, " ----------------------------\n");
    fclose(fp1);
    fclose(fp2);

    printf("Successfully implemented relocating loader.\n");
    return 0;
}

void convert(char h[12]) {
    int i, l;
    strcpy(bit, "");
    l = strlen(h);

    for (i = 0; i < l; i++) {
        switch (h[i]) {
            case '0': strcat(bit, "0000"); break;
            case '1': strcat(bit, "0001"); break;
            case '2': strcat(bit, "0010"); break;
            case '3': strcat(bit, "0011"); break;
            case '4': strcat(bit, "0100"); break;
            case '5': strcat(bit, "0101"); break;
            case '6': strcat(bit, "0110"); break;
            case '7': strcat(bit, "0111"); break;
            case '8': strcat(bit, "1000"); break;
            case '9': strcat(bit, "1001"); break;
            case 'A': strcat(bit, "1010"); break;
            case 'B': strcat(bit, "1011"); break;
            case 'C': strcat(bit, "1100"); break;
            case 'D': strcat(bit, "1101"); break;
            case 'E': strcat(bit, "1110"); break;
            case 'F': strcat(bit, "1111"); break;
        }
    }
}
