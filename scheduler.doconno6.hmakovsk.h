#include "pqueue.doconno6.hmakovsk.c"
#include <stdio.h>

//
// Dan O'Connor-D'Amico
// Harry Makovsky
// Assignment 4
// CS201A
//

typedef struct {
    int pid ; //unique identifier
    int burstTime ; //total amount of CPU time this process will need
    int waitTime ; //total amount of time this process has spent waiting
    int numPreemptions ; //for RR, the # times this process was descheduled
    int lastTime ; //keep track of specific value of current time
} Process;

typedef enum EventTypeEnum {
    PROCESS_SUBMITTED,
    PROCESS_STARTS,
    PROCESS_ENDS,
    PROCESS_TIMESLICE_EXPIRES
} EventType;

typedef struct {
    EventType eventType ;
    Process *process;
} Event ;

Process *createProcesses();

void enqueueProcesses(PQueueNode **eventPQueue, Process *processes, int numProcesses);

void runSimulation(int schedulerType, int quantum, PQueueNode **eventPQueue);


#ifndef CPU_SCHEDULER_SCHEDULER_DOCONNO6_HMAKOVSK_H
#define CPU_SCHEDULER_SCHEDULER_DOCONNO6_HMAKOVSK_H

#endif //CPU_SCHEDULER_SCHEDULER_DOCONNO6_HMAKOVSK_H
