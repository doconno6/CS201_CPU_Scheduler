#include "scheduler.doconno6.hmakovsk.h"


Process *createProcesses(){
    Process *processes[5];
    processes[0] = (Process*) malloc(sizeof(Process));
    processes[0]->pid = 1;
    processes[0]->lastTime = 0;
    processes[0]->waitTime = 0;
    processes[0]->burstTime = 6;

    processes[1] = (Process*) malloc(sizeof(Process));
    processes[1]->pid = 2;
    processes[1]->lastTime = 0;
    processes[1]->waitTime = 0;
    processes[1]->burstTime = 7;

    processes[2] = (Process*) malloc(sizeof(Process));
    processes[2]->pid = 3;
    processes[2]->lastTime = 0;
    processes[2]->waitTime = 0;
    processes[2]->burstTime = 2;

    processes[3] = (Process*) malloc(sizeof(Process));
    processes[3]->pid = 4;
    processes[3]->lastTime = 0;
    processes[3]->waitTime = 0;
    processes[3]->lastTime = 3;
    processes[3]->burstTime = 5;

    processes[4] = (Process*) malloc(sizeof(Process));
    processes[4]->pid = 5;
    processes[4]->lastTime = 0;
    processes[4]->waitTime = 0;
    processes[4]->lastTime = 3;
    processes[4]->burstTime = 2;

    return *processes;
}


void enqueueProcesses(PQueueNode **eventPQueue, Process *processes, int numProcesses){
    int startTimes[5] = {0, 3, 4, 6, 6};

    Event *event = (Event *)malloc(sizeof(Event));
    event->eventType = PROCESS_SUBMITTED;
    for(int i = 0; i < numProcesses; i++) {
        event->process = &processes[i];
        enqueue(eventPQueue, startTimes[i], event);
    }
}


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
                    newEvent = (Event *) malloc(sizeof(Event));
                    newEvent->eventType = PROCESS_STARTS;
                    newEvent->process = currProcess;
                    enqueue(eventPQueue, currTime, newEvent);
                    CPUBusy = 1;
                } else {
                    enqueue(&waitQueue, 0, currProcess);
                }
            } else if (event->eventType == PROCESS_STARTS) {
                currProcess->waitTime = currTime - currProcess->waitTime;
                totalWaitTime += currProcess->waitTime;

                newEvent = (Event *) malloc(sizeof(Event));
                newEvent->eventType = PROCESS_ENDS;
                newEvent->process = currProcess;
                enqueue(eventPQueue, currTime + currProcess->burstTime, newEvent);
            } else if (event->eventType == PROCESS_ENDS) {
                if (queueLength(waitQueue) > 0) {
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
        }
        currTime = getMinPriority(*eventPQueue);
        event = dequeue(eventPQueue);
    }
}



int main(){
    PQueueNode *eventQueue = NULL;
    enqueueProcesses(&eventQueue, createProcesses(), 5);
    runSimulation(1, 1, &eventQueue);
    return 0;
}

