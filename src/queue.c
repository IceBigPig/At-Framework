//
// Created by dell on 2024-07-23.
//
#include <string.h>
#include "stdio.h"
#include "queue.h"

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int isFull(Queue *q) {
    return q->count == QUEUE_SIZE;
}

int isEmpty(Queue *q) {
    return q->count == 0;
}

void enqueue(Queue *q, const char *item) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    q->data[q->rear] = strdup(item);
    q->count++;
}

char *dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return NULL;
    }
    char *item = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    q->count--;
    return item;
}
