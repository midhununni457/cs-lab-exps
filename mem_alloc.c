#include <stdio.h>
#include <stdlib.h>

struct block {
    int space;
    int free;
    struct block* next;
};

struct block* input_block(struct block* head, int i) {
    int space;
    printf("Enter size of block %d: ", i+1);
    scanf("%d", &space);
    struct block* new = malloc(sizeof(struct block));
    new->space = space;
    new->free = 1;
    new->next = NULL;
    if (head == NULL) {
        head = new;
    } else {
        struct block* cur = head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = new;
    }
    return head;
}

struct block* create_mem() {
    int n;
    printf("Enter no: of blocks: ");
    scanf("%d", &n);
    struct block* head = NULL;
    for (int i=0; i<n; i++) {
        head = input_block(head, i);
    }
    return head;
}

struct block* split(struct block* head, int target_space, int process_size) {
    struct block* cur = head;
    while (cur->space != target_space) {
        cur = cur->next;
    }
    struct block* new = malloc(sizeof(struct block));
    new->space = target_space - process_size;
    cur->space = process_size;
    cur->free = 0;
    new->free = 1;
    new->next = cur->next;
    cur->next = new;
    return head;
}

struct block* first_fit(struct block* head, int process_size) {
    struct block* cur = head;
    while (cur != NULL) {
        if (cur->free == 1 && cur->space >= process_size) {
            head = split(head, cur->space, process_size);
            return head;
        }
        cur = cur->next;
    }
    printf("No space available for process with size %d", process_size);
}

struct block* best_fit(struct block* head, int process_size) {
    struct block* cur = head;
    int min_diff = 1000000;
    while (cur != NULL) {
        if (cur->free == 1 && cur->space - process_size > 0 && cur->space - process_size < min_diff) {
            min_diff = cur->space - process_size;
        }
        cur = cur->next;
    }
    head = split(head, process_size+min_diff, process_size);
    return head;
}

struct block* worst_fit(struct block* head, int process_size) {
    struct block* cur = head;
    int max_diff = -1;
    while (cur != NULL) {
        if (cur->free == 1 && cur->space - process_size > max_diff) {
            max_diff = cur->space - process_size;
        }
        cur = cur->next;
    }
    head = split(head, process_size+max_diff, process_size);
    return head;
}

void display(struct block* head) {
    struct block* cur = head;
    while (cur != NULL) {
        printf("%d(%c)", cur->space, cur->free == 1 ? 'F' : 'T');
        cur = cur->next;
    }
}

void main() {
    struct block* head = create_mem();
    int n;
    printf("Enter no: of processes: ");
    scanf("%d", &n);
    int a[n];
    for (int i=0; i<n; i++) {
        printf("Enter size of process %d", i+1);
        scanf("%d", &a[i]);
    }
    printf("Select allocation method\n1. First fit\n2. Best fit\n3. Worst fit");
    int opt;
    scanf("%d", &opt);
    for (int i=0; i<n; i++) {
        if (opt == 1) {
            head = first_fit(head, a[i]);
        } else if (opt == 2) {
            head = best_fit(head, a[i]);
        } else if (opt == 3) {
            head = worst_fit(head, a[i]);
        }
    }
    display(head);
    
}