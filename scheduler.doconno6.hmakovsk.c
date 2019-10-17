#include "scheduler.doconno6.hmakovsk.h"


Process *createProcesses(){
    Process *processes = (Process *) malloc(5 * sizeof(Process));


    processes[0].pid = 1;
    processes[0].burstTime = 6;


    processes[1].pid = 2;
    processes[1].burstTime = 7;


    processes[2].pid = 3;
    processes[2].burstTime = 2;


    processes[3].pid = 4;
    processes[3].burstTime = 5;


    processes[4].pid = 5;
    processes[4].burstTime = 2;


    return processes;
}


void enqueueProcesses(PQueueNode **eventPQueue, Process *processes, int numProcesses){
    int startTimes[5] = {0, 3, 4, 6, 6};
    *eventPQueue=NULL;

    for(int i = 0; i < numProcesses; i++) {
        Event *event = (Event *)malloc(sizeof(Event));
        event->eventType = PROCESS_SUBMITTED;
        event->process = &processes[i];
        enqueue(eventPQueue, startTimes[i], event);
    }




}

//void printEvent(void* data){
//    Process* proc;
//    Event* event;
//    event= (Event *) data;
//    proc=event->process;
//
//    if(event->eventType==PROCESS_SUBMITTED){
//        printf("")
//    }
//}


void runSimulation(int schedulerType, int quantum, PQueueNode **eventPQueue){
    int CPUBusy=0;
    PQueueNode* waitQueue;
    Event* newEvent;
    Process* currProcess;
    int totalWaitTime=0;

    waitQueue=NULL;

    int currTime = getMinPriority(*eventPQueue);
    Event *event = dequeue(eventPQueue);
    while (event != NULL){
        if(schedulerType==1) {

            currProcess = event->process;
            if (event->eventType == PROCESS_SUBMITTED) {

                currProcess->waitTime = currTime;
                if (CPUBusy == 0) {
                    printf("t = %d  PROCESS_SUBMITTED  pid = %d\n",currTime,currProcess->pid);
                    newEvent = (Event *) malloc(sizeof(Event));
                    newEvent->eventType = PROCESS_STARTS;
                    newEvent->process = currProcess;
                    enqueue(eventPQueue, currTime, newEvent);
                    CPUBusy = 1;
                } else {
                    printf("t = %d  PROCESS_SUBMITTED  pid = %d\n",currTime,currProcess->pid);
                    //difference
                    enqueue(&waitQueue, 0, currProcess);
                }
            } else if (event->eventType == PROCESS_STARTS) {
                printf("t = %d  PROCESS_STARTS  pid = %d\n",currTime,currProcess->pid);
                currProcess->waitTime = currTime - currProcess->waitTime;
                totalWaitTime += currProcess->waitTime;

                newEvent = (Event *) malloc(sizeof(Event));
                newEvent->eventType = PROCESS_ENDS;
                newEvent->process = currProcess;
                enqueue(eventPQueue, currTime + currProcess->burstTime, newEvent);
            } else if (event->eventType == PROCESS_ENDS) {
                printf("t = %d  PROCESS_ENDS  pid = %d  wait time = %d\n",currTime,currProcess->pid,currProcess->waitTime);

                if (queueLength(waitQueue) > 0) {
                    currProcess= dequeue(&waitQueue);
                    newEvent = (Event *) malloc(sizeof(Event));
                    newEvent->eventType = PROCESS_STARTS;
                    newEvent->process = currProcess;
                    enqueue(eventPQueue, currTime, newEvent);
                } else {
                    CPUBusy = 0;
                }
            }
        }else if(schedulerType==2) {
            //SJF handle
            currProcess = event->process;
            if (event->eventType == PROCESS_SUBMITTED) {
                currProcess->waitTime = currTime;
                if (CPUBusy == 0) {
                    printf("t = %d  PROCESS_SUBMITTED  pid = %d\n",currTime,currProcess->pid);
                    newEvent = (Event *) malloc(sizeof(Event));
                    newEvent->eventType = PROCESS_STARTS;
                    newEvent->process = currProcess;
                    enqueue(eventPQueue, currTime, newEvent);
                    CPUBusy = 1;
                } else {
                    printf("t = %d  PROCESS_SUBMITTED  pid = %d\n",currTime,currProcess->pid);
                    //difference
                    enqueue(&waitQueue,currProcess->burstTime, currProcess);
                }
            } else if (event->eventType == PROCESS_STARTS) {
                printf("t = %d  PROCESS_STARTS  pid = %d\n",currTime,currProcess->pid);

                currProcess->waitTime = currTime - currProcess->waitTime;
                totalWaitTime += currProcess->waitTime;

                newEvent = (Event *) malloc(sizeof(Event));
                newEvent->eventType = PROCESS_ENDS;
                newEvent->process = currProcess;
                enqueue(eventPQueue, currTime + currProcess->burstTime, newEvent);
            } else if (event->eventType == PROCESS_ENDS) {
                printf("t = %d  PROCESS_ENDS  pid = %d  wait time = %d\n",currTime,currProcess->pid,currProcess->waitTime);

                if (queueLength(waitQueue) > 0) {
                    currProcess= dequeue(&waitQueue);
                    newEvent = (Event *) malloc(sizeof(Event));
                    newEvent->eventType = PROCESS_STARTS;
                    newEvent->process = currProcess;
                    enqueue(eventPQueue, currTime, newEvent);
                } else {
                    CPUBusy = 0;
                }
            }
        }
        currTime = getMinPriority(*eventPQueue);
        event = dequeue(eventPQueue);
    }
}



int main(){
    PQueueNode *eventQueue = NULL;
    enqueueProcesses(&eventQueue, createProcesses(), 5);
    printf("-----------------FCFS-----------------\n");
    runSimulation(1, 1, &eventQueue);

    printf("\n\n");
    eventQueue = NULL;
    enqueueProcesses(&eventQueue, createProcesses(), 5);
    printf("-----------------SJF-----------------\n");
    runSimulation(2, 1, &eventQueue);
    return 0;
}

