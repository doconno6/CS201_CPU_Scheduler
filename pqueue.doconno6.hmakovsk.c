#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pqueue.doconno6.hmakovsk.h"


int enqueue(PQueueNode **pqueue, int priority, void *data){
    PQueueNode* newNode= (PQueueNode*) malloc(sizeof(PQueueNode));
    PQueueNode* curr= (PQueueNode*) malloc(sizeof(PQueueNode));

    newNode->priority=priority;
    newNode->data=data;
    newNode->next=NULL;

    if (*pqueue==NULL || (*pqueue)->priority>newNode->priority){
        newNode->next=*pqueue;
        *pqueue=newNode;
        return 0;
    }else{
        curr=*pqueue;
    }
    while(curr->next!=NULL && curr->next->priority<=newNode->priority){
        curr=curr->next;
    }
    if(curr->next==NULL){
        curr->next=newNode;
        return 0;
    }else{
        newNode->next=curr->next;
        curr->next=newNode;
        return 0;
    }
}


void *dequeue(PQueueNode **pqueue){
    if(*pqueue==NULL){
        return NULL;
    }else{
        void *data=(*pqueue)->data;
        *pqueue=(*pqueue)->next;
        return data;
    }

}

void *peek(PQueueNode *pqueue){
    if((pqueue)==NULL){
        return NULL;
    }else{
        return pqueue->data;
    }
}


void printQueue(PQueueNode *pqueue, void (printFunction)(void *)){
    while(pqueue!=NULL){
        printf("priority = %d data = ",pqueue->priority);
        printFunction(pqueue->data);
        pqueue=pqueue->next;
    }
}

int getMinPriority(PQueueNode *pqueue){
    if(pqueue==NULL){
        return -1;
    }else{
        return pqueue->priority;
    }
}

int queueLength(PQueueNode *pqueue){
    int length=0;
    while(pqueue!=NULL){
        length++;
        pqueue=pqueue->next;
    }
    return length;
}

void printStudentRecord(void *data){
    StudentRecord *node = (StudentRecord *) data;
    printf("%s %d\n", node->name, node->id);
}
