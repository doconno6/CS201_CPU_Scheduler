#include <stdio.h>
#include <stdlib.h>
#include "string.h"

//
// Dan O'Connor-D'Amico
// Harry Makovsky
// Assignment 4
// CS201A
//


#ifndef PQUEUE_DOCONNO6_PQUEUE_DOCONNO6_H
#define PQUEUE_DOCONNO6_PQUEUE_DOCONNO6_H

typedef struct {
    int id;
    char name[32];
} StudentRecord;

typedef struct PQueueStruct {
    int priority;
    void *data;
    struct PQueueStruct *next;
} PQueueNode;

int enqueue(PQueueNode **pqueue, int priority, void *data);

void *dequeue(PQueueNode **pqueue);

void *peek(PQueueNode **pqueue);

void printQueue(PQueueNode *pqueue, void (printFunction)(void*));

int getMinPriority(PQueueNode *pqueue);

int queueLength(PQueueNode *pqueue);

void printStudentRecord(void *data);

#endif //PQUEUE_DOCONNO6_PQUEUE_DOCONNO6_H
