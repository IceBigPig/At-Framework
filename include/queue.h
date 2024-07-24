//
// Created by dell on 2024-07-23.
//

#ifndef ATCOMMANDFRAMEWORK_QUEUE_H
#define ATCOMMANDFRAMEWORK_QUEUE_H

#define QUEUE_SIZE 10

typedef struct {
    char *data[QUEUE_SIZE];
    int front;
    int rear;
    int count;
} Queue;

void initQueue(Queue *q);
int isFull(Queue *q);
int isEmpty(Queue *q);
void enqueue(Queue *q, const char *item);
char *dequeue(Queue *q);

#endif //ATCOMMANDFRAMEWORK_QUEUE_H
