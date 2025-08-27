#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int priority;
    int value;
} Node;

typedef struct {
    Node heap[MAX];
    int size;
} PriorityQueue;

void insert(PriorityQueue *pq, int priority, int value);
void heapifyUp(PriorityQueue *pq, int index);
void heapifyDown(PriorityQueue *pq, int index);
Node peek(PriorityQueue *pq);
Node pop(PriorityQueue *pq);
int changePriority(PriorityQueue *pq, int value, int newPriority);
void printHeap(PriorityQueue *pq);
int getSize(PriorityQueue *pq);

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void insert(PriorityQueue *pq, int priority, int value) {
    if (pq->size >= MAX) {
        printf("Heap is full!\n");
        return;
    }
    pq->heap[pq->size].priority = priority;
    pq->heap[pq->size].value = value;
    pq->size++;
    heapifyUp(pq, pq->size - 1);
}

void heapifyUp(PriorityQueue *pq, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->heap[index].priority > pq->heap[parent].priority) {
            swap(&pq->heap[index], &pq->heap[parent]);
            index = parent;
        } else break;
    }
}

void heapifyDown(PriorityQueue *pq, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < pq->size && pq->heap[left].priority > pq->heap[largest].priority)
            largest = left;
        if (right < pq->size && pq->heap[right].priority > pq->heap[largest].priority)
            largest = right;

        if (largest != index) {
            swap(&pq->heap[index], &pq->heap[largest]);
            index = largest;
        } else break;
    }
}

Node peek(PriorityQueue *pq) {
    if (pq->size == 0) {
        Node empty = {-1, -1};
        return empty;
    }
    return pq->heap[0];
}

Node pop(PriorityQueue *pq) {
    if (pq->size == 0) {
        Node empty = {-1, -1};
        return empty;
    }
    Node top = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    return top;
}

int changePriority(PriorityQueue *pq, int value, int newPriority) {
    for (int i = 0; i < pq->size; i++) {
        if (pq->heap[i].value == value) {
            pq->heap[i].priority = newPriority;
            heapifyUp(pq, i);
            heapifyDown(pq, i);
            return 1;
        }
    }
    return 0; 
}

void printHeap(PriorityQueue *pq) {
    printf("Heap: ");
    for (int i = 0; i < pq->size; i++) {
        printf("(%d,%d) ", pq->heap[i].priority, pq->heap[i].value);
    }
    printf("\n");
}

int getSize(PriorityQueue *pq) {
    return pq->size;
}

int main() {
    PriorityQueue pq;
    pq.size = 0;

    int choice, priority, value, newPriority;
    Node top;

    while (1) {
        printf("\n1. Insert(priority, value)\n");
        printf("2. Peek top\n");
        printf("3. Pop top\n");
        printf("4. Change priority by value\n");
        printf("5. Size\n");
        printf("6. Print Heap\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter priority and value: ");
                scanf("%d %d", &priority, &value);
                insert(&pq, priority, value);
                break;
            case 2:
                top = peek(&pq);
                if (top.priority == -1) printf("Heap is empty!\n");
                else printf("Top Element -> Priority: %d, Value: %d\n", top.priority, top.value);
                break;
            case 3:
                top = pop(&pq);
                if (top.priority == -1) printf("Heap is empty!\n");
                else printf("Popped -> Priority: %d, Value: %d\n", top.priority, top.value);
                break;
            case 4:
                printf("Enter value and new priority: ");
                scanf("%d %d", &value, &newPriority);
                if (changePriority(&pq, value, newPriority))
                    printf("Priority updated!\n");
                else
                    printf("Value not found!\n");
                break;
            case 5:
                printf("Size: %d\n", getSize(&pq));
                break;
            case 6:
                printHeap(&pq);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
