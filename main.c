#include <stdio.h>
#include <stdlib.h>

#define NUM_QUEUES 3
#define TIME_SLICE 1
#define NUM_PROCESSES 5

typedef struct {
    int pid;
    int burst_time;
    int remaining_time;
} Process;

typedef struct {
    Process* processes[NUM_PROCESSES];
    int front;
    int rear;
} Queue;

Queue* create_queue() {
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    queue->front = 0;
    queue->rear = 0;
    return queue;
}

void enqueue(Queue* queue, Process* process) {
    queue->processes[queue->rear++] = process;
}

Process* dequeue(Queue* queue) {
    return queue->processes[queue->front++];
}

int is_empty(Queue* queue) {
    return queue->front == queue->rear;
}

int main() {
    Process processes[NUM_PROCESSES] = {
        {1, 1, 3},
        {2, 2, 3},
        {3, 3, 3},
        {4, 4, 3},
        {5, 5, 3}
    };

    Queue* queues[NUM_QUEUES + 1]; // Last queue is FCFS
    for (int i = 0; i <= NUM_QUEUES; i++) {
        queues[i] = create_queue();
    }

    // Enqueue processes into the highest priority queue initially
    for (int i = 0; i < NUM_PROCESSES; i++) {
        enqueue(queues[0], &processes[i]);
    }

    int time = 0;
    for (int q = 0; q < NUM_QUEUES; q++) {
        int queue_size = queues[q]->rear;
        for (int i = 0; i < queue_size; i++) {
            Process* process = dequeue(queues[q]);
            printf("Time %d: Executing Process %d from Queue %d\n", time++, process->pid, q + 1);
            process->remaining_time--;
            if (process->remaining_time > 0) {
                enqueue(queues[q + 1], process);
            }
        }
    }

    // Move all processes to FCFS queue
    for (int i = 0; i < NUM_PROCESSES; i++) {
        enqueue(queues[NUM_QUEUES], &processes[i]);
    }

    while (!is_empty(queues[NUM_QUEUES])) {
        Process* process = dequeue(queues[NUM_QUEUES]);
        printf("Time %d: Executing Process %d from FCFS Queue\n", time, process->pid);
        time += process->burst_time;
        printf("Process %d finished at time %d\n", process->pid, time);
    }

    // Free memory
    for (int i = 0; i <= NUM_QUEUES; i++) {
        free(queues[i]);
    }

    return 0;
}
