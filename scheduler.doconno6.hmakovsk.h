#include "pqueue.doconno6.hmakovsk.c"
#include <stdio.h>

//
// Dan O'Connor-D'Amico
// Harry Makovsky
// Assignment 4
// CS201A
//
#ifndef CPU_SCHEDULER_SCHEDULER_DOCONNO6_HMAKOVSK_H
#define CPU_SCHEDULER_SCHEDULER_DOCONNO6_HMAKOVSK_H

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

/**
 * creates the five processes and returns them in an array.
 *
 * @return Processes
 */
Process *createProcesses();

/**
* enqueue the processes in the event queue at the times specified in the table.
*
* @param eventPQueue priority queue of events
* @param processes processes being added
* @param numProcesses number of processes being added
*/
void enqueueProcesses(PQueueNode **eventPQueue, Process *processes, int numProcesses);

/**
* runs all processe through the simulation
*
* @param schedulerType
* @param quantum
* @param eventPQueue
*/
void runSimulation(int schedulerType, int quantum, PQueueNode **eventPQueue);


//====================[Part 2]==================================================


Process* createRandomProcesses(int numProcesses, double meanBurstTime);

void enqueueRandomProcesses(int numProcesses, PQueueNode **eventQeueue,
                            Process* processes, double meanIAT);
//==============================================================================
#endif //CPU_SCHEDULER_SCHEDULER_DOCONNO6_HMAKOVSK_H
