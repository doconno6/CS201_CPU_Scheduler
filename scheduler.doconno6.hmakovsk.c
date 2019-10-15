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
    for(int i = 0; i < numProcesses; i++) {
        enqueue(eventPQueue, startTimes[i], &processes[i]);
    }
}


void runSimulation(int schedulerType, int quantum, PQueueNode **eventPQueue){
    int currentTime = getMinPriority(*eventPQueue);
    Event *event = dequeue(eventPQueue);
    while (event != NULL){
        //handleEvent(event)
        currentTime = getMinPriority(*eventPQueue);
        event = dequeue(eventPQueue);
    }
}

int main(){
    PQueueNode eventNode
    return 0;
}

