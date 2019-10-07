#include "pqueue.doconno6.hmakovsk.h"

int enqueue(PQueueNode **pqueue, int priority, void *data) {
    PQueueNode *newNode = (PQueueNode *) malloc(sizeof(PQueueNode));
    newNode->priority = priority;
    newNode->data = data;
    newNode->next = NULL;
    if((*pqueue) == NULL){
        *pqueue = newNode;
        return 0;
    } else if ((*pqueue)->priority > priority){
        newNode->next = *pqueue;
        *pqueue = newNode;
        return 0;
    }
    PQueueNode *this = *pqueue;
    while (this->next != NULL){
        if(this->next->priority > priority){
            newNode->next = this->next;
            this->next = newNode;
            return 0;
        }
        this = this->next;
    }
    this->next = newNode;
    return 1;
}

void *dequeue(PQueueNode **pqueue) {
    if((*pqueue) == NULL){
        return NULL;
    }
    PQueueNode *temp = *pqueue;
    void *data = temp->data;
    *pqueue = (*pqueue)->next;
    free(temp);
    return data;
}

void *peek(PQueueNode **pqueue) {
    if((*pqueue) == NULL){
        return NULL;
    } else {
        return (*pqueue)->data;
    }
}

void printQueue(PQueueNode *pqueue, void (*printFunction)(void *)) {
    PQueueNode *this = pqueue;
    while(this != NULL){
        printf("priority = %d\tname = ", this->priority);
        printFunction(this->data);
        this = this->next;
    }
}

int getMinPriority(PQueueNode *pqueue){
    if(pqueue == NULL){
        return -1;
    }
    return pqueue->priority;
}

int queueLength(PQueueNode *pqueue){
    if(pqueue == NULL){
        return 0;
    }
    PQueueNode *this = pqueue;
    int nodeCount = 1;
    while(this->next != NULL){
        nodeCount++;
        this = this->next;
    }
    return nodeCount;
}

void printStudentRecord(void *data) {
    StudentRecord *node = (StudentRecord *) data;
    printf("%s %d\n", node->name, node->id);
}

StudentRecord* createRecord(int id, char name[]){
    StudentRecord *rec = (StudentRecord*)malloc(sizeof(StudentRecord));
    rec->id = id;
    strcpy(rec->name, name);
    return rec;
}